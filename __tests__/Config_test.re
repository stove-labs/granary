open Jest;
open Expect;
open Granary_test;
open Config;
open ConfigStore;

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
                let expectedVersion = "{}";
                expect(output) |> toContainString(expectedVersion);
            });

            test("should show a single specific config property", () => {
                Config.setProperty(propertyName, Some(propertyValue));
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

        /* This test is a mess, could use a refactor */
        describe("-c, --config", () => {
            let customConfigPath = "./granary-test.json";

            beforeEach(() => {
                execCommand("config --config='" ++ customConfigPath ++ "' set " ++ propertyName ++ " " ++ propertyValue) |> ignore;
            })

            test("it should not write to the default config file", () => {
                /* read two different configs */
                let output = execCommand("config show " ++ propertyName);
                expect(output) 
                    |> not_ 
                    |> toContainString(propertyValue)
            });

            test("it should write to the custom config file", () => {
                /* read two different configs */
                let outputWithCustomConfig = execCommand("config --config " ++ customConfigPath ++ " show " ++ propertyName);
                expect(outputWithCustomConfig) 
                    |> toContainString(propertyValue)
            });
        });
    });
});