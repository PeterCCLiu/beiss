const express = require('express')
const router = express.Router()

router.get('/', (req, res) => {
    res.send("device lists");
})

router.post('/new', (req, res) => {
    res.send("new device");
})

module.exports = router