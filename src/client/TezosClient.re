open Docker;
open Dockerode;
open TezosNodeSandboxnet;

let dockerNetworkName = Config.getExn("dockerNetworkName");
let dockerImage = Config.getExn("tezosClient.networks.<network>.dockerImage");
let clientDataDir = cwd ++ "/" ++ Config.getExn("tezosClient.networks.<network>.baseDir");
let nodeAddr = Config.getExn("tezosClient.networks.<network>.nodeAddr");
let nodeRpcPort = Config.getExn("tezosClient.networks.<network>.nodeRpcPort");

let clientInitFiles = [];
let clientBaseInitFilePath = "";
let clientInitDestinationPath = Config.getExn("data.networks.<network>.clientFolder");

let init = () => Data.init(clientBaseInitFilePath, clientInitDestinationPath, clientInitFiles);
let clean = () => Data.clean(clientInitDestinationPath);

let start = (cmd) => {
    let containerHostConfig: hostConfiguration = hostConfiguration(
        ~volumeBindings = Some([|cwd ++ ":" ++ cwd|]),
        ~portBindings = None,
        ~networkMode = Some(dockerNetworkName)
    );
    
    let configCmd = [|
        "--base-dir " ++ clientDataDir,
        "--addr " ++ nodeAddr,
        "--port " ++ nodeRpcPort
    |];

    let cmd = Array.concat([configCmd, cmd]);

    let containerOptions = createContainerOptions(
        ~image=Some(dockerImage),
        ~cmd= Some(cmd),
        ~hostConfig= Some(containerHostConfig),
        ~name=None,
        ~tty=Some(true),
        ~exposedPorts=None
    );

    Docker.run(containerOptions)
    |> Js.Promise.then_((container) => {
        Js.Promise.resolve(container);
    })
};