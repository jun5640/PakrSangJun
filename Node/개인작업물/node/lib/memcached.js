const config = require('config');
var expressSession = require('express-session');

var session = require('connect-memcached')(expressSession);
var store = new session({ hosts: config.get('memcached.hosts') });

exports = module.exports = store;
