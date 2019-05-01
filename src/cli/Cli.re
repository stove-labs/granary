open Commander;
open Node.Process;

let program = commander;

/**
 * Register CLI commands
 */
let register = () => {
    program
        -> version(
            Package.version,
            Some("-v, --version")
        )
        -> ConfigCommands.register
};

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