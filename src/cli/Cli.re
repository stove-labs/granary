open Commander;
open Node.Process;
open TerminalLink;

let program = commander;

let docsLink = " https://stove-labs.github.io/granary/ ";
let issuesLink = " https://github.com/stove-labs/granary/issues ";
let granaryArt = {|
     ______                                          
    / _____)                                         
   | /  ___   ____  ____  ____    ____   ____  _   _ 
   | | (___) / ___)/ _  ||  _ \  / _  | / ___)| | | |
   | \____/|| |   ( ( | || | | |( ( | || |    | |_| |
    \_____/ |_|    \_||_||_| |_| \_||_||_|     \__  |
                                              (____/       


                                              
|} 
    ++ terminalLink("Docs", docsLink)
    ++ "\n"
    ++ terminalLink("Issues", issuesLink);

/**
 * Run the CLI / parse current arguments
 * 
 * If there are sub-commands (e.g. config) then forward 
 * their execution to the respective handlers (e.g. granary-config.js)
 */
let parse = () => {
    program
        -> parse(argv);
}

let start = () => {
    program
        -> version(
            Package.version,
            Some("-v, --version")
        )
        -> description(granaryArt)
        -> forwardedCommand(
            "config", 
            "Manipulate config values"
        )
        -> forwardedCommand(
            "client", 
            "Encapsulates a pre-configured tezos-client"
        );

    /**
     * Global CLI options
     * 
     * @TODO: this does not play very well if you try to run granary-config.js separately, it should be fixed
     */
    program 
        -> option("-c, --config <path>", "Specify a custom config path")
        |> ignore;

    parse();  
}