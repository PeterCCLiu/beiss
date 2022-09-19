const express = require('express');
const multipart = require('connect-multiparty');
const bodyParser = require('body-parser')
const {dbStart} = require('./dbOperations');
const userRouter = require('./route/user');
const deviceRouter = require('./route/device');
const Module = require('./PBC/setup.js');

const app = express();
app.use(bodyParser.json())
app.use(bodyParser.urlencoded({extended: false}));
app.use(multipart());

const elementStringLength = 512;
const paramBufferLengthTypeA = 370;

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
    Module._setup();
    console.log('finished successfully with result '+ jsStr);
    res.status(200).send('WASM succeeded with result: ' + jsStr);
})

app.get('/readBuff', (req, res) => {
    var pcStr = Module._reader();
    var jsStr = Module.AsciiToString(pcStr);
    console.log('finished successfully with result '+ jsStr);
    res.status(200).send('WASM succeeded with result: ' + jsStr);
})

app.get('/buffToObj', (req, res) => {
    var pcStr = Module._reader();
    var jsStr = Module.AsciiToString(pcStr);
    console.log('finished reading buffer with result '+ jsStr);

    var obj = new Object();
    obj.par_param_buffer = jsStr.substr(0, paramBufferLengthTypeA);
    obj.g                = jsStr.substr(paramBufferLengthTypeA, elementStringLength);
    obj.P0               = jsStr.substr(paramBufferLengthTypeA+elementStringLength, elementStringLength);

    res.status(200).send(JSON.stringify(obj));
})

app.get('/writeBuff', (req, res) => {
    par_param_buffer = req.query.par_param_buffer.padEnd(paramBufferLengthTypeA);
    g                = req.query.g.padEnd(elementStringLength);
    P0               = req.query.P0.padEnd(elementStringLength);
    mystring = par_param_buffer.concat(g).concat(P0);
    var pcStr = Module._reader();
    Module.writeStringToMemory(mystring, pcStr);
    console.log('wrote '+ mystring + ' to buffer');
    res.status(200).send('done.');
})

app.use('/users', userRouter);
app.use('/device', deviceRouter);

app.listen(4000, function () {
    console.log('server started')
});
