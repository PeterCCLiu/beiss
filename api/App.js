const express = require('express');
const app = express();
const { dbStart } = require('./dbOperations');
const userRouter = require('./route/user')
const deviceRouter = require('./route/device')


app.get('/', (req, res) => {
    res.sendStatus(200)
})

app.get('/healthcheck', (req, res) => {
    res.status(200).send('System live')
})

app.get('/dbSetup', (req, res) => {
    dbStart().then(r => {res.send(r)});
})

app.use('/user', userRouter);
app.use('/device', deviceRouter);

app.listen(3000, "localhost");
