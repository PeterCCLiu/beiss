const mongoose = require('mongoose')

const hostName = "mongo";
const port = "27017";
const dbName = 'beiss';

const dbUrl = `mongodb://${hostName}:${port}/${dbName}`;

async function dbStart(){
    await mongoose.connect(dbUrl).then(r => {
        console.log("db connection status: " + r);
        // have your mongo running in local terminal :27017
    })
}

const deviceSchema = mongoose.Schema({
    id: String
});

const userSchema = mongoose.Schema({
    id: String,
    name: String
});

const Device = mongoose.model('Device', deviceSchema);
const User = mongoose.model('User', userSchema);

module.exports = { dbStart, Device, User }