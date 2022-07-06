const fs = require('fs')
function loadWebAssembly(fileName) {
    let wasmBuffer = fs.readFileSync(fileName);
    let mod =  WebAssembly.instantiate(wasmBuffer);
    return mod
}

module.exports = { loadWebAssembly }