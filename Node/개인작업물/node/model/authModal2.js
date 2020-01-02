var pool = require('../lib/mysql');

module.exports = {
  
    getById: function( id, type, callback) {
        pool.getConnection(function(err, con){
            console.log('connected as id ' + con.threadId);
            var sql = `SELECT * FROM auth WHERE account = '${id}' AND type = ${type}`;
            con.query(sql, function (err, result, fields) {
                con.release();
                if (err) return callback(err);
                callback(null, result);
            });
        });
    },

    getAccount: function( id, type, ipaddr, session_id, callback) {
        pool.getConnection(function(err, con){
            var sql = `CALL checkingAccount (?,?,?,?, @oResult,@oMemberId,@oStatus,@oAuthority,@oBlock); select @oResult,@oMemberId,@oStatus,@oAuthority,@oBlock;`;
            //var sql = `CALL checkingAccount (?,?,?,?, @oResult,@oMemberId,@oStatus,@oAuthority,@oBlock);`;
            con.query(sql, [id,type,ipaddr, session_id], function (err, result, fields) {
                con.release();
                if (err) return callback(err);
                result.forEach(element => {
                    if(element.constructor == Array)    {
                        console.log(element[0]);
                    }
                });
                //console.log(result[1]);
                callback(null, result);
            });
        });
    },
  
    create: function(sessId, id, type, state, callback) {
        pool.getConnection(function(err, con){
            var sql = `INSERT INTO auth (account, type, state, userId, sessId) VALUES('${id}',${type},${state},0,'${sessId}' `;
            con.query(sql, function (err, result, fields) {
                con.release();
                if (err) return callback(err);
                callback(null, result);
            });
        }); 
    },
  
    update: function(sessId, id, type, callback) {
        pool.getConnection(function(err, con){
            var sql = `UPDATE auth SET sessId = '${sessId}' WHERE account = '${id}' AND type = ${type}`;
            con.query(sql, function (err, result, fields) {
                con.release();
                if (err) return callback(err);
                callback(null, result);
            });
        });  
    },
  
    destroy: function(id, type, callback) {
        pool.getConnection(function(err, con){
            var sql = `DELETE FROM auth WHERE account = '${id}' AND type = ${type}`;
            con.query(sql, function (err, result, fields) {
                con.release();
                if (err) return callback(err);
                callback(null, result);
            });
        });  
    }
  }
  