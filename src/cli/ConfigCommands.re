open Commander;
open Log;
open Config;
open ConfigStore;
open Cli;

[@bs.send] external showAction: (commander, (option(string)) => unit) => unit = "action";
[@bs.send] external setAction: (commander, (string, option(string)) => unit) => unit = "action";
[@bs.send] external initAction: (commander, unit => unit) => unit = "action";


let initConfig = () => {
    getConfigStore();
    ()
}

let showProperty = (property) => {
    switch (property) {
        | Some(property) => {
            let value = Config.getOptional(property);
            /* This will also log when the value is undefined */
            Js.log(value);
        }
        | None => {
            let configStore = getConfigStore();
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

    program
        -> description(granaryArt);

    program
        -> command("set <property> [value]")
        -> description("Upserts properties into the config")
        -> setAction(setProperty) 
        |> ignore;

    program
        -> command("show [property]")
        -> description("Prints a property from the config")
        -> showAction(showProperty) 
        |> ignore;

    program
        -> command("init")
        -> description("Initializes a config with default values")
        -> initAction(initConfig) 
        |> ignore;

    parse();
}