function loadWebAssembly(fileName) {
    return fetch(fileName)
        .then(response => response.arrayBuffer())
        .then(buffer => WebAssembly.compile(buffer))
        .then(module => {return new WebAssembly.Instance(module)})
}

module.exports = { loadWebAssembly }