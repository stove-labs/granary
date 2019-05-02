open NodeEmoji;

let log = (~message: string) => {
    let message = nodeEmoji
        ->emojify(message);

    Js.log(message);
}