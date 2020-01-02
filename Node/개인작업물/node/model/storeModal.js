var db = require('../lib/database');
var dbFunc = require('../lib/dbFunction');

var storeModel = {
    Buy:Buy,
    Bill:Bill,
    BuyCashShop:BuyCashShop
 }

 function Buy(member_id, Id, priceValue, price_type, myitem_cnt, myitem_str, buyalbum_cnt, buyalbum_str, soldoutpkg_cnt, soldoutpkg_str) {
    return new Promise((resolve,reject) => {
        let sql = `SET @oResult=0;`;
        sql += `CALL sp_buy_myroom_items (?,?,?,?,?,?,?,?,?,?,@oResult);`;
        sql += `select @oResult;`;
        db.query(sql, [member_id, Id, priceValue, price_type, myitem_cnt, myitem_str, buyalbum_cnt, buyalbum_str, soldoutpkg_cnt, soldoutpkg_str], function (error, rows, fields) {
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

function BuyCashShop(member_id, gold, heart, film) {
    return new Promise((resolve,reject) => {
        let sql = `SET @oResult=0;`;
        sql += `CALL sp_buy_cashshop_items (?,?,?,?,@oResult);`;
        sql += `select @oResult;`;
        db.query(sql, [member_id, gold, heart, film], function (error, rows, fields) {
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

function Bill(member_id, Id, store, shoptype, sale_price, key, trans){
    return new Promise((resolve,reject) => {
        trans = JSON.stringify(trans);
        let sql = `SET @oResult=0;`;
        sql += `CALL sp_insert_user_store_bill (?,?,?,?,?,?,?,@oResult);`;
        sql += `select @oResult;`;
        db.query(sql, [member_id, Id, store, shoptype, sale_price, key, trans], function (error, rows, fields) {
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



module.exports = storeModel;