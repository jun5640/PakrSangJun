const mysql = require('mysql');
const config = require('config');

module.exports = mysql.createPool({
    host: config.get('mysql').host,
    user: config.get('mysql').username,
    password: config.get('mysql').password,
    port: config.get('mysql').port,
    database: config.get('mysql').database,
    connectionLimit : config.get('mysql').limit,
    multipleStatements: true
})
