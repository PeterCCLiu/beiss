const express = require('express')
const router = express.Router()

router.get('/', (req, res) => {
    res.send("user lists");
})

router.post('/new', (req, res) => {
    res.send("new user");
})

app.get('/:getDeviceByUserId', (req, res) => {
    console.log(req.params.info);
    // const request = JSON.stringify(req.params);
    res.send("Device Information");
})

module.exports = router