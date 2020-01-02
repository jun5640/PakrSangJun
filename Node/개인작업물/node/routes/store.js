'use strict';

//const Promise = require('bluebird');
const config = require('../config.js');
//const IAPVerifier = require('iap_verifier');
const IABVerifier = require('iab_verifier');
const table = require('./table');
const type = require('./type');
const extension = require('./extension');
const userManager = require('./user');
//const mail = require('./mail');

//var appStore = new IAPVerifier(config.get('apple.key'));
var playStore = new IABVerifier(config.google.key);

const TRANS_KEY = 'trans:{0}';

exports = module.exports = {};

/**
 * 상품 구매
 *
 * @public
 * @param {Number} Id - 상품의 고유번호
 * @param {String} receipt - 영수증 정보
 * @param {Object} sess - 섹션 정보
 * @param {Number} store - 스토어
 * @param {String} data - 구매정보 1
 * @param {String} signature - 구매정보 2
 * @return {Object} - 상품 구매 결과
 */
exports.Buy = (Id, sess, store, data, signature, db, userdata, shoptype, sale_price) => {

    let key;
    let trans;

    var tbShop;
    if(shoptype == type.ShopType.CashShop)
    {
        tbShop = table.Shop.find(Id);
    }
    else
    {
        tbShop = table.MyRoomShop.find(Id);
    }
    let auth = sess.auth;

    if (typeof tbShop === 'undefined') {
        console.log('not found in shop table. "{0}"'.format(Id));
        return null;
    }

    // 구매 가능 기간 체크
    if (tbShop.peroid_use === type.Shop.Period.Use) {
        let now = new Date();
        let start = new Date(tbShop.peroid_start);
        let end = new Date(tbShop.peroid_end);
        if (start < now && end < now) {
            console.log('This purchase is not possible period.');
            return null;
        }
    }
    // 상품 가격 및 영수증 검사
    var priceValue;
    if(shoptype == type.ShopType.CashShop)
    {
        priceValue = extension.toInteger(tbShop.price_value);
    }
    else
    {
        priceValue = extension.toInteger(tbShop.price_value);
        console.log(tbShop);
        if(tbShop.category == type.MyRoomShopCategory.Package)
        {
            var tbPro = table.Product.find(tbShop.product);
            let count = tbPro.item.length;
            for (let i = 0; i < count; i++) 
            {
                for(let n = 0; n < userdata.mypage.length; n++)
                {
                    if(userdata.mypage[n] == tbPro.item[i])
                    {
                        priceValue = priceValue - tbPro.discount[i];
                    }
                }
            }

            if(priceValue != sale_price)
            {
                console.log(priceValue);
                console.log(sale_price);
                console.log("sale price match fail");
                return null;
            }
        }
        else
        {
            priceValue = extension.toInteger(tbShop.price_value);
        }
    }
    switch (tbShop.price_type) {
        case type.Price.Cash:
                if (data == null && signature == null) {
                    console.log('receipt is invalid.');
                    return null;
                }
            switch (store) {
                case type.Shop.Type.Google:
                    {
                        let valid = playStore.verifyReceipt(data, signature);
                        if (valid) {
                            let form = JSON.parse(data);

                            // 상품 식별자 검사
                            if (form.productId !== tbShop.store_key.trim()) {
                                console.log('productId is invalid.');
                                return null;
                            }

                            // 앱의 팩키지 이름 검사
                            if (form.packageName !== config.google.packageName) {
                                console.log('packageName is invalid.');
                                return null;
                            }

                            // key = TRANS_KEY.format(form.orderId);
                            // trans = {
                            //     type: "trans",
                            //     store,
                            //     Id: auth.userId,
                            //     time: new Date(),
                            //     data,
                            //     sign: signature
                            // };

                            // console.log(key);
                            // console.log(trans);
                        
                        } else {
                            console.log('receipt is invalid.');
                        }

                        //    db.insert(key, trans, (err, result) => {
                        //        if (err) {
                        //            console.log('duplicate receipt.');
                        //        } else {
                        //            //resolve();
                        //        }
                        //    });
			            break;
                    }
                //    return;
                case type.Shop.Type.One:
                    {
                        console.log('unkown store type.');
                        return null;                            //reject(new Error());
                    }
                //    return;
                case type.Shop.Type.Apple:
                    appStore.verifyReceipt(signature, function (valid, msg, data) {
                        if (valid) {
                            resolve();
                        } else {
                            console.log(msg);
                        }
                    });
               //     return;
                default:
                    console.log('unkown store type.');
                    return;
            }
        case type.Price.Gold:
            if (userdata.point.gold < priceValue) {
                console.log(userdata.point.gold);
                console.log(priceValue);
                console.log('There is not enough gold.');
                return null;
            }
            break;
        case type.Price.Gem:
            if (userdata.point.gem < priceValue) {
                console.log('There is not enough gem.');
                return null;
            }
            break;
        case type.Price.Heart:
            if (userdata.point.heart < priceValue) {
                console.log('There is not enough heart.');
                return null;
            }
            break;
        case type.Price.None: // 무료 구매 상품
            break;
        default:
            console.log('mismatch of shop price type.');
            return null;
    }


        if (typeof tbShop === 'undefined') {
            reject(new Error('not found in shop table. "{0}"'.format(Id)));
            return null;
        }

        const tbProduct = table.Product.find(tbShop.product);
        if (typeof tbProduct === 'undefined') {
            reject(new Error('not found in product table. "{0}"'.format(tbShop.product)));
            return null;
        }


	console.log("상품지급");	
    // 상품 지급

    let count = tbProduct.item.length;
    for (let i = 0; i < count; i++) {
        
        let itemId = tbProduct.item[i];

        console.log(itemId);

        let itemCount = tbProduct.count[i];

        if (itemId === 0) continue;

        const tbItem = table.Item.find(itemId);

        if (typeof tbItem === 'undefined') {

            console.log("Item Table undefined");
            return null;
        }
        var temp;
        temp = userManager.ItemCreate(userdata, tbItem, itemCount);
        if(temp == "AlreadyBuy")
        {
            if(tbShop.category != type.MyRoomShopCategory.Package)
            {
                console.log("Already Buy This Item");
                return null;
            }
        }
        else
        {
            userdata = temp;
        }
    }
    // 가격 차감 처리.

    

    switch (tbShop.price_type) {
        case type.Price.Cash:
            break;
        case type.Price.None:
            break;
        case type.Price.Gold:
            userdata.point.gold -= priceValue;
            break;
        case type.Price.Gem:
            userdata.point.gem -= priceValue;
            break;
        case type.Price.Heart:
            userdata.point.heart -= priceValue;
            break;
    }

    return userdata;

}

