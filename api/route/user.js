const express = require('express')
const router = express.Router()

router.get('/', (req, res) => {
    res.send("user lists");
})

router.post('/new', (req, res) => {
    res.send("new user");
})

router.get('/:id', (req, res) => {
    const id = req.params.id;
    console.log(id);
    res.send("Device Information " + id);
})

module.exports = router