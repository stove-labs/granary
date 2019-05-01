open Commander;
open Log;
open ConfigStore;

[@bs.send] external showAction: (commander, (option(string)) => unit) => unit = "action";
[@bs.send] external setAction: (commander, (string, option(string)) => unit) => unit = "action";

let defaultConfigPath = "./granary.json";

let getConfigStore = () => {
    
    /* Allow override of the default config path via --config */
    let configPath = switch(Js.Dict.get(Cli.program, "config")) {
        | Some(configPath) => {
            log(
                ~message = ":warning:  Using custom config path: " ++ configPath
            )
            configPath
        }
        | None => defaultConfigPath
    };

    /* %bs.obj to turn this record into a plain JS object */
    let configOptions: ConfigStore.configOptions = [%bs.obj {
        globalConfigPath: None,
        configPath: Some(configPath)
    }];
    
    ConfigStore.configStore(Package.name, [%bs.raw {|{}|}], configOptions);
}

let showProperty = (property) => {
    let configStore = getConfigStore();
    switch (property) {
        | Some(property) => {
            let value = configStore->get(property);
            /* This will also log when the value is undefined */
            Js.log(value);
        }
        | None => {
            Js.log(configStore##all)
        }
    };
}

let setProperty = (property, value) => {
    let configStore = getConfigStore();
    switch (value) {
        | Some(value) => {
            configStore
                ->set(property, value);
        }
        /* If no value is provided, delete the property/key instead */
        | None => {
            log(~message=":warning:  No value set, deleting property '" ++ property ++ "' instead");
            configStore
                ->delete(property);
        }
    };
};

let start = () => {

    Cli.program
        -> description(Cli.granaryArt);

    /**
     * @TODO figure out a way to move this to global options
     */
    Cli.program 
        -> option("--config <path>", "Specify a custom config path")
        |> ignore;

    Cli.program
        -> command("set <property> [value]")
        -> description("Upserts properties into the config")
        -> setAction(setProperty) 
        |> ignore;

    Cli.program
        -> command("show [property]")
        -> description("Prints a property from the config")
        -> showAction(showProperty) 
        |> ignore;


    Cli.parse();
}