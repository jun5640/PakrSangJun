const mysql = require("mysql");
const config = require('config');

const dbConfig = {
    host: config.get('mysql').host,
    user: config.get('mysql').username,
    password: config.get('mysql').password,
    port: config.get('mysql').port,
    database: config.get('mysql').database,
    connectionLimit : config.get('mysql').limit,
    multipleStatements: true
};

module.exports = function () {
  var pool = mysql.createPool(dbConfig);
  pool.on('connection', function (connection) {
    console.log('SET SESSION auto_increment_increment=1')
  });
  
  pool.on('enqueue', function () {
    console.log('Waiting for available connection slot');
  });
 
  return {
    getConnection: function (callback) {    // connection pool을 생성하여 리턴합니다
      pool.getConnection(callback);
    },
    end: function(callback){
      pool.end(callback);
    }
  }
}();