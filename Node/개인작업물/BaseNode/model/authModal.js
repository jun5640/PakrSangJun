var db = require('../lib/database');
var dbFunc = require('../lib/dbFunction');

var authModel = {
    getAccount:getAccount,
    updateAccount:updateAccount,
    Register:Register,
    Unregister:Unregister
 }

 function getAccount(id, type, ipaddr, session_id) {
    return new Promise((resolve,reject) => {
        let sql = `SET @oResult=0,@oMemberId=0,@oStatus=0,@oAuthority=0,@oBlock=0,@oSessionId='';`;
        sql += `CALL checkingAccount (?,?,?,?, @oResult,@oMemberId,@oStatus,@oAuthority,@oBlock,@oSessionId);`;
        sql += `select @oResult,@oMemberId,@oStatus,@oAuthority,@oBlock,@oSessionId;`;
        db.query(sql, [id,type,ipaddr, session_id], function (error, rows, fields) {
            if(!!error) {
                dbFunc.connectionRelease;
                reject(error);
            } else {
                dbFunc.connectionRelease;
                let result = {};
                rows.forEach(element => {
                    if(element.constructor == Array)    {
                        console.log(element[0]);
                        result = element[0];
                    }
                });
                resolve(result);
            }
       });
    });
}

function updateAccount(member_id, session_id) {
    return new Promise((resolve,reject) => {
        let sql = `UPDATE account SET session_id = '${session_id}' WHERE member_id = ${member_id} `;
        db.query(sql, function (error, result, fields) {
            if(!!error) {
                dbFunc.connectionRelease;
                reject(error);
            } else {
                dbFunc.connectionRelease;
                resolve(result);
            }
        });
    });
}

function Register(firstName, lastName, sess) {
    return new Promise((resolve,reject) => {
        let auth = sess.auth;
        let member_id = auth.memberId;
        let sql = `SET @oResult=0;`;
        sql += `CALL sp_create_user (?,?,?,@oResult);`;
        sql += `select @oResult;`;
        db.query(sql, [member_id, firstName, lastName], function (error, rows, fields) {
            if(!!error) {
                dbFunc.connectionRelease;
                reject(error);
            } else {
                dbFunc.connectionRelease;
                let result = {};
                rows.forEach(element => {
                    if(element.constructor == Array)    {
                        console.log(element[0]);
                        result = element[0];
                    }
                });
                resolve(result);
            }
        });
    });
}

function Unregister(member_id, state) {
    return new Promise((resolve,reject) => {
        let sql = `UPDATE account SET block = '${state}' WHERE member_id = ${member_id} `;
        db.query(sql, function (error, result, fields) {
            if(!!error) {
                dbFunc.connectionRelease;
                reject(error);
            } else {
                dbFunc.connectionRelease;
                resolve(result);
            }
        });
    });
}

module.exports = authModel;