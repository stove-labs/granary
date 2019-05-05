open Commander;
open Log;
open Config;
open ConfigStore;

let start = () => {

    Cli.program
        -> description(Cli.granaryArt);

    Cli.program
        -> description("Inits the granary config, node and client.")
        -> allowUnknownOption()
        -> action(() => {
            ConfigCommands.initConfig();
            ClientCommands.initClient();
            TezosNodeSandboxnet.init();
        })
        |> ignore;

    Cli.parse();
};