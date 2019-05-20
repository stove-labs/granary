open Dockerode;
open Log;

let docker = dockerode();
let cwd = Node.Process.cwd();

let init = () => {
    let networkName = Config.getExn("dockerNetworkName");
    log(":point_right:  Setting up Docker: " ++ networkName);
    docker
        -> createNetwork(createNetworkOptions(
            ~name = networkName,
            ~checkDuplicate = Some(true)
        )) |> ignore;
};

let pull = (imageName: string): Js.Promise.t(string) => {
    log("Updating image: " ++ imageName);
    Js.Promise.make((~resolve, ~reject) => {
        docker
            -> pull(imageName, (err, stream) => {
                [%bs.raw {| docker.modem.followProgress(stream, () => resolve(imageName), () => {}) |}];
            });
    });
};

let run = (containerOptions: createContainerOptions) => {
    let imageName = Belt.Option.getWithDefault(
        containerOptions->imageGet,
        ""
    );
    docker
        -> run(
            /* Use the image from container options instead */
            imageName,
            /* Use the cmd from container options instead */
            Belt.Option.getWithDefault(
                containerOptions->cmdGet,
                [||]
            ),
            [%bs.raw {|process.stdout|}],
            containerOptions
        )
        |> Js.Promise.then_((container) => {
            Js.Promise.resolve(imageName)
        });
};

/**
 * Stop and remove the provided docker container
 */
let stop = (containerName) => {
    let container = docker
        -> getContainer(containerName)

    container
        -> remove(removeContainerOptions(
            ~force = Some(true)
        ))
        |> Js.Promise.then_((container) => {
            Js.Promise.resolve(container);
        })
    Js.Promise.resolve(container);
};