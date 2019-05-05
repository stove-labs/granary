open Fs;
let basePath = Node.Process.cwd() ++ "/" ++ Config.getExn("data.basePath");

/**
 * Universal function to copy files & create folders for initialization of modules
 */
let init = (baseInitFilePath, destinationPath, initFiles) => {
    let initFilePath = (path: string) => {
        baseInitFilePath ++ "/" ++ path;
    }
    
    let fileToCopy = (file: string) => {
        (initFilePath(file), file)
    }

    mkdirSync(destinationPath, [%bs.obj {
        recursive: true
    }]);

    Belt.List.forEach(initFiles, (initFile) => {
        let (filePath, fileName) = fileToCopy(initFile);
        copyFileSync(filePath, destinationPath ++ "/" ++ fileName);
    });
}