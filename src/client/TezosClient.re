open Docker;
open Dockerode;
open Sandboxnet;
open TezosNodeSandboxnet;

let dockerNetworkName = Config.getExn("dockerNetworkName");
let dockerImage = Config.getExn("tezosClient.networks.<network>.dockerImage");
let clientDataDir = cwd ++ "/" ++ Config.getExn("tezosClient.networks.<network>.baseDir");


let start = (cmd) => {
    let containerHostConfig: hostConfiguration = hostConfiguration(
        ~volumeBindings = Some([|cwd ++ ":" ++ cwd|]),
        ~portBindings = None,
        ~networkMode = Some(dockerNetworkName)
    );

    Js.log(clientDataDir);
    
    let configCmd = [|
        "--base-dir " ++ clientDataDir,
        "--addr " ++ nodeContainerName,
        "--port " ++ nodePort
    |];

    let cmd = Array.concat([configCmd, cmd]);
    
    let containerOptions = createContainerOptions(
        ~image=Some(dockerImage),
        ~cmd= Some(cmd),
        ~hostConfig= Some(containerHostConfig),
        ~name=None,
        ~tty=Some(true)
    );

    Docker.run(containerOptions)
    |> Js.Promise.then_((container) => {
        Js.Promise.resolve(container);
    })
};