const Bluebird = require('bluebird');
const addon = require('../build/Release/addon');
global.Promise = Bluebird;

const response = new Promise(async (resolve, reject) => {
    addon.hello();
    resolve();
});

console.log("After a call");