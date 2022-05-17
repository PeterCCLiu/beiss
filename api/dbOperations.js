// const mongo = require('mongoose')
const { MongoClient } = require('mongodb')
const dbUrl = 'mongodb://localhost:27017';

async function dbStart(){
    const db = new MongoClient(dbUrl);
    await db.connect().then(r => {
        console.log("db connection status: " + r);
        // have your mongo running in local terminal :27017
    })
}

module.exports = { dbStart }