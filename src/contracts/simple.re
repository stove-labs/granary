[%%version 0.4];

type storage = int;
[%%init let init_storage = 0];
[%%entry let main = (parameter: int, storage) => ([], storage + parameter)];