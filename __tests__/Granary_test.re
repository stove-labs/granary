open Jest;
open Expect;
open Node.Child_process;
let execCommand = (command: string) => {
    let granaryCommand = "./granary.js";
    execSync(
        granaryCommand ++ " " ++command,
        option( ~cwd="./", ~encoding="utf8", ())
    )
};

describe("granary", () => {
    test("--version", () => {
        let output = execCommand("--version");
        let expectedVersion: string = [%bs.raw {| require('./../package.json').version |}];
        expect(output) |> toContainString(expectedVersion)
    })

    describe("--help", () => {
        let output = execCommand("--help");

        test("should output granary art", () => {
            let expectedArt = Cli.granaryArt;
            expect(output) |> toContainString(expectedArt)
        });

        test("should output a link to the docs", () => {
            let expectedLink = Granary.Cli.docsLink;
            expect(output) |> toContainString(expectedLink);
        });

        test("should output a link to the github issues", () => {
            let expectedLink = Granary.Cli.issuesLink;
            expect(output) |> toContainString(expectedLink);
        });
    });
});