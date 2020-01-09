var db = require('../lib/database');
var dbFunc = require('../lib/dbFunction');

var authModel = {
    Register:Register,
 }



function Register(userId, userPassWord, sess) {
    return new Promise((resolve,reject) => {

        let sql = `SET @oResult=0;`;
        sql += `CALL sp_create_user (?,?,@oResult);`;
        sql += `select @oResult;`;
        db.query(sql, [userId, userPassWord], function (error, rows, fields) {
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


module.exports = authModel;