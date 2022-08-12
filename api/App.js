const express = require('express');
const multipart = require('connect-multiparty');
const bodyParser = require('body-parser')
const {dbStart} = require('./dbOperations');
const userRouter = require('./route/user');
const deviceRouter = require('./route/device');
const {loadWebAssembly} = require('./testWasm');

const app = express();
app.use(bodyParser.json())
app.use(bodyParser.urlencoded({extended: false}));
app.use(multipart());

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

app.use('/users', userRouter);
app.use('/device', deviceRouter);

app.listen(4000, function () {
    console.log('server started')
});
