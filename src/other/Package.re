/**
 * Used to print out the current CLI version
 */
let version: string = [%bs.raw {| require("./../../package.json").version |}];
let name: string = [%bs.raw {| require("./../../package.json").name |}];