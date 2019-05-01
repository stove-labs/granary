open Commander;

let start = () => {
    Cli.program
        -> command("set <property> [value]")
        -> description("Upserts properties into the config")
        -> action(() => {
            Js.log("setting");
            ()
        });

    Cli.program
        -> command("all")
        -> description("Prints the entire config")
        -> action(() => {
            Js.log("printing all");
            ()
        });

    Cli.program
        -> command("get <property>")
        -> description("Prints a property from the config")
        -> action(() => {
            Js.log("getting");
            ()
        });

    Cli.parse();
}