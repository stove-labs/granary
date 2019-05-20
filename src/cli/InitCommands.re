open Commander;
open Log;
open Config;
open ConfigStore;
open Cli;

let start = () => {

    program
        -> description(granaryArt);

    program
        -> description("Inits the granary config, node and client.")
        -> allowUnknownOption()
        -> action(() => {
            Docker.init();
            ConfigCommands.initConfig();
            ClientCommands.initClient();
            TezosNodeSandboxnet.init();
        })
        |> ignore;

    parse();
};