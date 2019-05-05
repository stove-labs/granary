open Commander;
open Log;
open Config;
open ConfigStore;

[@bs.send] external initAction: (commander, unit => unit) => unit = "action";
[@bs.send] external commandAction: (commander, unit => unit) => unit = "action";

let initClient = () => {
    TezosClient.init();
    ();
}

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
        -> initAction(initClient) 
        |> ignore;

    Cli.program
        -> command("- [command...]")
        -> description("Scaffolds necessary files & folders for a network specific tezos-client")
        -> allowUnknownOption()
        -> commandAction(forwardCommands)
        |> ignore;

    Cli.parse();
}