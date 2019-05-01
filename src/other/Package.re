/**
 * Used to print out the current CLI version
 */
let version: string = [%bs.raw {| require("./../../package.json").version |}];