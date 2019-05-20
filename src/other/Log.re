open NodeEmoji;
open Config;

let log = (~message: string) => {
    let message = nodeEmoji
        ->emojify(message);

    Js.log(message);
};