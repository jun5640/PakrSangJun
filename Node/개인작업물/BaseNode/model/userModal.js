var db = require('../lib/database');
var dbFunc = require('../lib/dbFunction');

var userModel = {
    MapClear:MapClear,
 }



function MapClear(userId, mapId, sess) {
    return new Promise((resolve,reject) => {

        let sql = `SET @oResult=0;`;
        sql += `CALL sp_map_clear (?,?,@oResult,@oUserData);`;
        sql += `select @oResult,@oUserData;`;
        db.query(sql, [userId, mapId], function (error, rows, fields) {
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



module.exports = userModel;