open Dockerode;

let docker = dockerode();
let cwd = Node.Process.cwd();

let connectToNetwork = (containerName: string, network: string) => {
    docker
        -> getNetwork(network)
        -> connect(networkConnectOptions(
            ~container= containerName,
            ~id= network
        ));
};

/**
 * Start a container with the provided options
 */
let start = (containerOptions) => {
    docker
        -> createContainer(containerOptions)
        |> Js.Promise.then_((container: Dockerode.container) => {
            container
                -> start()
                |> Js.Promise.then_((container) => {
                    Js.log("Container started!");
                    Js.Promise.resolve(container);
                })
            Js.Promise.resolve(container);
        });
};

let run = (containerOptions: createContainerOptions) => {
    docker
        -> run(
            /* Use the image from container options instead */
            Belt.Option.getWithDefault(
                containerOptions->imageGet,
                ""
            ),
            /* Use the cmd from container options instead */
            Belt.Option.getWithDefault(
                containerOptions->cmdGet,
                [||]
            ),
            [%bs.raw {|process.stdout|}],
            containerOptions
        )
};

/**
 * Stop and remove the provided docker container
 */
let stop = (containerName) => {
    let container = docker
        -> getContainer(containerName)

    container
        -> stop()
        |> Js.Promise.then_((container) => {
            container
                -> remove()
                |> Js.Promise.then_((container) => {
                    Js.log("Container stopped and removed!");
                    Js.Promise.resolve(container);
                })
            Js.Promise.resolve(container);
        });
};