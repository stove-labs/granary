[%%version 0.4]

type storage = int

let%entry main (parameter : int) storage =
  ( [], storage + parameter )