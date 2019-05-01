type nodeEmoji;
[@bs.module] external nodeEmoji: nodeEmoji = "node-emoji";
[@bs.send] external emojify: (nodeEmoji, string) => string = "";