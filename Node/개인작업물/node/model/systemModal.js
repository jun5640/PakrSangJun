var db = require('../lib/database');
var dbFunc = require('../lib/dbFunction');

var systemModel = {
    UserSearch:UserSearch
}

function UserSearch(firstName, lastName) {
    return new Promise((resolve,reject) => {
        let sql = `select a.* from user_data u, account a where u.first_name = '{0}' and u.last_name = '{1}' and u.member_id = a.member_id;`;
        let query = sql.format(firstName, lastName);
        db.query(query, function (error, rows, fields) {
            if(!!error) {
                dbFunc.connectionRelease;
                reject(error);
            } else {
                dbFunc.connectionRelease;
                resolve(rows);
            }
        });
    });
}

module.exports = systemModel;