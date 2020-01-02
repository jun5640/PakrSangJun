var db = require('../lib/database');
var dbFunc = require('../lib/dbFunction');

var commonModal = {
    UpdateUserPoint:UpdateUserPoint
 }

 function UpdateUserPoint(member_id, gold, film, heart) {
    return new Promise((resolve,reject) => {
        let sql = `SET @oResult=0;`;
        sql += `CALL sp_update_user_point (?,?,?,?,@oResult);`;
        sql += `select @oResult;`;
        db.query(sql, [member_id, gold, film, heart], function (error, rows, fields) {
            if(!!error) {
                dbFunc.connectionRelease;
                reject(new Error('database insert fail'));
                return;
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



module.exports = commonModal;