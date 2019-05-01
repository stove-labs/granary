open Commander;

let register = (program: Commander.commander) => {
    program
        -> forwardedCommand(
            "config", 
            "Manipulate config values"
        )
}