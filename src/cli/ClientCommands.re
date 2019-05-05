open Commander;
open Log;
open Config;
open ConfigStore;

let initClient = () => {
    TezosClient.init();
    ();
}

let cleanClient = () => TezosClient.clean();

let forwardCommands = () => {
    let commands: array(string) = Node.Process.argv
        |> Js.Array.slice(
            ~end_= Js.Array.length(Node.Process.argv),
            ~start= 3
        );

    TezosClient.start(commands);
    ();
}

let start = () => {

    Cli.program
        -> description(Cli.granaryArt);

    Cli.program
        -> command("init")
        -> description("Scaffolds necessary files & folders for a network specific tezos-client")
        -> action(initClient) 
        |> ignore;

    Cli.program
        -> command("clean")
        -> description("Cleans up the network specific tezos-client")
        -> action(cleanClient) 
        |> ignore;

    Cli.program
        -> description("Forwards any command to a network specific tezos-client")
        -> allowUnknownOption()
        -> action(forwardCommands)
        |> ignore;

    Cli.parse();
}