open Jest;
open Expect;
open Granary_test;
open Config;
open ConfigStore;
open ConfigCommands;

let reset = () => {
    Node.Fs.writeFileAsUtf8Sync("./granary.json", "{}")
    Node.Fs.writeFileAsUtf8Sync("./granary-test.json", "{}")
};

describe("granary", () => {
    describe("config", () => {
        let propertyName = "test.property";
        let propertyValue = "test-value";

        beforeEach(() => {
            reset();
        });
    
        describe("show", () => {
            test("it should show all config properties", () => {
                let output = execCommand("config show");
                let expectedVersion = "network: 'sandboxnet'";
                expect(output) |> toContainString(expectedVersion);
            });

            test("should show a single specific config property", () => {
                setProperty(propertyName, Some(propertyValue));
                let output = execCommand("config show " ++ propertyName);
                expect(output) |> toContainString(propertyValue);
            });
        });

        describe("set", () => {
            test("should set a config property", () => {
                execCommand("config set " ++ propertyName ++ " " ++ propertyValue) |> ignore;
                let configStore = getConfigStore();
                let value = configStore
                    -> get(propertyName);

                switch (value) {
                    | Some(value) => expect(value) |> toBe(propertyValue)
                    | None => fail("Config property not available"); 
                }
            });

            test("should delete a property when a value was not provided", () => {
                execCommand("config set " ++ propertyName ++ " " ++ propertyValue) |> ignore;
                execCommand("config set " ++ propertyName) |> ignore;
                let configStore = getConfigStore();
                let value = configStore
                    -> get(propertyName);

                switch (value) {
                    | Some(value) => fail("Config property was not deleted"); 
                    | None => pass
                }
            })
        });
    });
});