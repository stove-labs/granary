open Commander;
open Node.Process;
open TerminalLink;

let program = commander;

let granaryArt = {|
     ______                                          
    / _____)                                         
   | /  ___   ____  ____  ____    ____   ____  _   _ 
   | | (___) / ___)/ _  ||  _ \  / _  | / ___)| | | |
   | \____/|| |   ( ( | || | | |( ( | || |    | |_| |
    \_____/ |_|    \_||_||_| |_| \_||_||_|     \__  |
                                              (____/       


                                              
|} 
    ++ terminalLink("Docs", " https://stove-labs.github.io/granary/ ")
    ++ "\n"
    ++ terminalLink("Issues", " https://github.com/stove-labs/granary/issues ");

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
        );

    parse();
}