const mongoose = require('mongoose')

const hostName = "mongo"; //If running locally, hostName should be changed to "localhost", and "mongo" if in docker.
const port = "27017";
const dbName = 'beiss';

const dbUrl = `mongodb://${hostName}:${port}/${dbName}`;

mongoose.connect(dbUrl).then(res => {
    console.log("db connection status: " + res);
})


const deviceSchema = mongoose.Schema({
    id: String
});

const userSchema = mongoose.Schema({
    id: String,
    name: String
});

const Device = mongoose.model('Device', deviceSchema);
const User = mongoose.model('User', userSchema);

module.exports = { Device, User }