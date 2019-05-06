[@bs.module "fs"] external copyFileSync: (string, string) => unit = "";
type mkdirOptions = Js.t({
    .
    recursive: bool
});
[@bs.module "fs"] external mkdirSync: (string, mkdirOptions) => unit = "";