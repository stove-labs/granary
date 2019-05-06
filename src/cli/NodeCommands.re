open Commander;
open Log;
open Config;
open ConfigStore;
open Cli;

let initClient = () => {
    TezosClient.init();
    ();
}

let initNode = () => TezosNodeSandboxnet.init();
let cleanNode = () => TezosNodeSandboxnet.clean();

let startNode = () => {
    TezosNodeSandboxnet.start();
    ();
};
let stopNode = () => {
    TezosNodeSandboxnet.stop();
    ();
};

let start = () => {

    program
        -> description(granaryArt);

    program
        -> command("init")
        -> description("Scaffolds necessary files & folders for a network specific tezos-node")
        -> action(initNode) 
        |> ignore;

    program
        -> command("clean")
        -> description("Cleans up the network specific tezos-node")
        -> action(cleanNode) 
        |> ignore;

    program
        -> command("start")
        -> description("Starts a tezos-node")
        -> action(startNode)
        |> ignore;

    program
        -> command("stop")
        -> description("Stops the tezos-node")
        -> action(stopNode)
        |> ignore;

    parse();
}