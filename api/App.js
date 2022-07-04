const express = require('express');
const app = express();
const {dbStart} = require('./dbOperations');
const userRouter = require('./route/user');
const deviceRouter = require('./route/device');
const {loadWebAssembly} = require('./testWasm');

let adder;
let result;
const address = './PBC/adder.wasm'


app.get('/', (req, res) => {
    res.sendStatus(200)
})

app.get('/healthcheck', (req, res) => {
    res.status(200).send('System live')
})

app.get('/dbSetup', (req, res) => {
    dbStart().then(r => {
        res.send(r)
    });
})

app.get('/testWasm', (req, res) => {
    loadWebAssembly(address)
        .then(module => {
            adder = module.instance.exports.adder;
            result = adder(2, 3);
            console.log('finished successfully' + result);
            res.status(200).send('WASM succeeded with result: ' + result);
        })
})

app.use('/user', userRouter);
app.use('/device', deviceRouter);

app.listen(3000, "localhost");
