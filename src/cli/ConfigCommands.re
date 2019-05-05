open Commander;
open Log;
open Config;
open ConfigStore;

[@bs.send] external showAction: (commander, (option(string)) => unit) => unit = "action";
[@bs.send] external setAction: (commander, (string, option(string)) => unit) => unit = "action";


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

    Cli.program
        -> description(Cli.granaryArt);

    /**
     * @TODO figure out a way to move this to global options
     */
    Cli.program 
        -> option("-c, --config <path>", "Specify a custom config path")
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

    TezosClient.start([|
        "import secret key alice unencrypted:edsk39qAm1fiMjgmPkw1EgQYkMzkJezLNewd7PLNHTkr6w9XA2zdfo"
    |]);

    /* Cli.parse(); */
}