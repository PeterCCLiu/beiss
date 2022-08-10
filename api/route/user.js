const express = require('express')
const {User} = require('../dbOperations')
const router = express.Router()

router.get('/', (req, res) => {
    User.find({}, (err, result) =>{
        res.send(result)
    })
})

router.post('/new', (req, res) => {
    let newUser = new User(req.body)
    newUser.save(err => {
        if (err) {
            console.log(err)
            res.send({success:false})
        }
        res.send({success:true})
    })
})

router.get('/:id', (req, res) => {
    User.find({id: req.params.id}, (err, result) =>{
        res.send(result)
    })
})

module.exports = router