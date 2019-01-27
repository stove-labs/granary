%version
0.4;

type storage = int;
let%init init_storage = 0;
let%entry main = (parameter: int, storage) => ([], storage + parameter);
