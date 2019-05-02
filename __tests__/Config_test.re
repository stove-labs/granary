open Jest;
open Expect;
open Granary_test;

let reset = () => {
    Node.Fs.writeFileAsUtf8Sync("./granary.json", "{}")
    Node.Fs.writeFileAsUtf8Sync("./granary-test.json", "{}")
};

describe("granary", () => {
    describe("config", () => {
        test("show", () => {
            reset();
            let output = execCommand("config show");
            let expectedVersion = "{}";
            expect(output) |> toContainString(expectedVersion);
        });
    });
});