const path = require('path');
const config = require('../config.js');
//const Promise = require('bluebird');
//const session = require('./session');
const type = require('./type');
const error = require('./error');
const extension = require('./extension');
const userManager = require('./user');

exports.IsAuth = function (sess) {
    return sess.hasOwnProperty('auth') &&
        //sess.hasOwnProperty('user') &&
        sess.auth !== null ;//&&
        s//ess.user !== null;
}