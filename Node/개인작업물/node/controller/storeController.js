'use strict';

const config = require('config');
const extension = require('../common/extension');
const error = require('../common/error');
const type = require('../common/type');
const storeModal = require("../model/storeModal");
const IAPVerifier = require('iap_verifier');
const IABVerifier = require('iab_verifier');
const tableManager = require('../common/table');
var appStore = new IAPVerifier(config.get('apple.key'));
var playStore = new IABVerifier(config.get('google.key'));

const TRANS_KEY = 'trans:{0}';

var storeController = {
    Buy:Buy
}

// 상품 구매
function Buy(body, sess, res) {
    if (!sess.hasOwnProperty('auth') ||
        !body.hasOwnProperty('Id') ||
        !body.hasOwnProperty('store') ||
        !body.hasOwnProperty('data') ||
        !body.hasOwnProperty('sign')) {
        console.log("failed");
        return res.json({ klass: 'BuyResult', result: error.Fail });
    }

    verify(body, sess)
        .then(() => {
            console.log("verify");
            process(body, sess)
                .then((value) => {
                    console.log("process value = "+value);
                    let resultdata = JSON.stringify(value);
                    let data = Buffer.from(resultdata, 'utf8').toString('base64');
                    res.end(JSON.stringify({ klass : 'BuyResult', result : error.Success, data : data }));   
                }).catch((err) => {
                    console.log(err);
                    return res.json({ klass: 'BuyResult', result: error.Fail });
                });
        }).catch((err) => {
            console.log(err);
            return res.json({ klass: 'BuyResult', result: error.Fail });
        });
}

/**
 * 구매 인증 
 *
 */
function verify(body, sess) {
    return new Promise((resolve, reject) => {
        let Id = body.Id;
        let store = body.store;
        let data = body.data;
        let signature = body.sign;
        let shoptype = body.shoptype;
        let sale_price = body.sale_price;

        let userdata = sess.user.data;
        
        console.log("verify, Id=%d, store=%d, shoptype=%d, sale_price=%d", Id, store, shoptype, sale_price );

        let tbShop;
        if(shoptype == type.ShopType.CashShop)
        {
            tbShop = tableManager.Shop.find(Id);
        }
        else
        {
            tbShop = tableManager.MyRoomShop.find(Id);
        }

        if (typeof tbShop === 'undefined') {
            reject(new Error('not found in shop table. "{0}"'.format(Id)));
            return;
        }

        // 구매 가능 기간 체크(기간제 상품)
        if (tbShop.peroid_use === type.Shop.Period.Use) {
            let now = new Date();
            let start = new Date(tbShop.peroid_start);
            let end = new Date(tbShop.peroid_end);
            if (start < now && end < now) {
                reject(new Error('This purchase is not possible period.'));
                return;
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
                var tbPro = tableManager.Product.find(tbShop.product);
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
                    reject(new Error('sale price match fail.'));
                    return;
                }
            }
            else
            {
                priceValue = extension.toInteger(tbShop.price_value);
            }
        }
        switch (tbShop.price_type) {
            case type.Price.Cash:
                if (config.util.getEnv('NODE_ENV') === 'development') {
                    if (data == null && signature == null) {
                        resolve();
                        return;
                    }
                } else {
                    if (data == null && signature == null) {
                        reject('receipt is invalid.');
                        return;
                    }
                }
                switch (store) {
                    case type.Shop.Type.Google:
                        {
                            let valid = playStore.verifyReceipt(data, signature);
                            if (valid) {
                                let form = JSON.parse(data);

                                // 상품 식별자 검사
                                if (form.productId !== tbShop.store_key.trim()) {
                                    reject(new Error('productId is invalid.'));
                                    return;
                                }

                                // 앱의 팩키지 이름 검사
                                if (form.packageName !== config.get('google.packageName')) {
                                    reject(new Error('packageName is invalid.'));
                                    return;
                                }

                                let member_id = sess.auth.memberId;
                                let key = TRANS_KEY.format(form.orderId);
                                let trans = {
                                    type: "trans",
                                    store,
                                    Id: member_id,
                                    time: new Date(),
                                    data,
                                    sign: signature
                                };

                                console.log(key);
                                console.log(trans);

                                storeModal.Bill(member_id, Id, store, shoptype, sale_price, key, trans).then((data)=>{
                                    let resultCode = data['@oResult'];
                                    if( resultCode == error.Success )   {
                                        resolve(userdata);
                                    }
                                    else {
                                        console.log("Database Querry Fail = %d", resultCode);
                                        reject(new Error('Database Querry Fail!!'));
                                    }

                                }).catch((err) => {
                                    console.error(err);
                                    reject(new Error('Database Querry Fail!!'));
                                })
                                
                            } else {
                                reject(new Error('receipt is invalid.'));
                            }
                        }
                        return;
                    case type.Shop.Type.One:
                        {
                            reject(new Error('unkown store type.'));
                        }
                        return;
                    case type.Shop.Type.Apple:
                        appStore.verifyReceipt(signature, function (valid, msg, data) {
                            if (valid) {
                                resolve();
                            } else {
                                reject(new Error(msg));
                            }
                        });
                        return;
                    default:
                        reject(new Error('unkown store type.'));
                        return;
                }
            case type.Price.Gold:
                if (userdata.point.gold < priceValue) {
                    console.log(userdata.point.gold);
                    console.log(priceValue);
                    reject(new Error('There is not enough gold.'));
                    return;
                }
                break;
            case type.Price.Gem:
                if (userdata.point.gem < priceValue) {
                    reject(new Error('There is not enough gem.'));
                    return;
                }
                break;
            case type.Price.Heart:
                if (userdata.point.heart < priceValue) {
                    reject(new Error('There is not enough heart.'));
                    return;
                }
                break;
            case type.Price.None: // 무료 구매 상품
                break;
            default:
                reject(new Error('mismatch of shop price type.'));
                return;
        }

        resolve();

    });
}

/**
 * 구매 처리 
 *
 */
function process(body, sess) {
    return new Promise((resolve, reject) => {
        let Id = body.Id;
        let store = body.store;
        let data = body.data;
        let sign = body.sign;
        let shoptype = body.shoptype;
        let sale_price = body.sale_price;
        let userdata = sess.user.data;
        console.log("process, Id=%d, store=%d, shoptype=%d, sale_price=%d", Id, store, shoptype, sale_price );

        let tbShop;
        if(shoptype == type.ShopType.CashShop)
        {
            tbShop = tableManager.Shop.find(Id);
        }
        else
        {
            tbShop = tableManager.MyRoomShop.find(Id);
        }

        if (typeof tbShop === 'undefined') {
            reject(new Error('not found in shop table. "{0}"'.format(Id)));
            return;
        }

        const tbProduct = tableManager.Product.find(tbShop.product);
        if (typeof tbProduct === 'undefined') {
            reject(new Error('not found in product table. "{0}"'.format(tbShop.product)));
            return;
        }

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
                var tbPro = tableManager.Product.find(tbShop.product);
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
                    reject(new Error('sale price match fail.'));
                    return;
                }
            }
            else
            {
                priceValue = extension.toInteger(tbShop.price_value);
            }
        }
        console.log(tbProduct);	
        console.log("상품지급");	
        // 상품 지급
        let add_items = {
            mypages : [],
            buyalbum : [],
            soldoutpackage : [],
        };

        let userdata_bak = JSON.parse(JSON.stringify(userdata));

        let count = tbProduct.item.length;
        for (let i = 0; i < count; i++) {
            let itemId = tbProduct.item[i];
            console.log(itemId);
            let itemCount = tbProduct.count[i];
            if (itemId === 0) continue;
            const tbItem = tableManager.Item.find(itemId);
            if (typeof tbItem === 'undefined') {
                console.log("Item Table undefined");
                reject(new Error('process - not found in product for item table. "{0}"'.format(itemId)));
                return;
            }
            var temp;
            temp = ItemCreate(userdata_bak, tbItem, itemCount, add_items);
            if(temp == "AlreadyBuy")
            {
                if(tbShop.category != type.MyRoomShopCategory.Package)
                {
                    console.log("Already Buy This Item");
                    reject(new Error('Already Buy This Item'));
                    return;
                }
            }
        }

        let member_id = sess.auth.memberId;
        let myitem_cnt = add_items.mypages.length;
        let myitem_str = '';
        if( myitem_cnt > 0) {
            for(var i = 0; i < myitem_cnt; i++)
            {
                if( i == 0 ) myitem_str += add_items.mypages[i];
                else {
                    myitem_str += ","+add_items.mypages[i];
                }
            }
        }
        let buyalbum_cnt = add_items.buyalbum.length;
        let buyalbum_str = '';
        if( buyalbum_cnt > 0) {
            for(var i = 0; i < buyalbum_cnt; i++)
            {
                if( i == 0 ) buyalbum_str += add_items.buyalbum[i];
                else {
                    buyalbum_str += ","+add_items.buyalbum[i];
                }
            }
        }
        let soldoutpkg_cnt = add_items.soldoutpackage.length;
        let soldoutpkg_str = '';
        if( soldoutpkg_cnt > 0) {
            for(var i = 0; i < soldoutpkg_cnt; i++)
            {
                if( i == 0 ) soldoutpkg_str += add_items.soldoutpackage[i];
                else {
                    soldoutpkg_str += ","+add_items.soldoutpackage[i];
                }
            }
        }

        if(shoptype == type.ShopType.CashShop)
        {
            //
            // 캐시 샵은 오로지 재화만 판매하는 것을 가정해서 한다.
            //

            switch (tbShop.price_type) {
                case type.Price.Cash:
                    break;
                case type.Price.None:
                    break;
                case type.Price.Gold:
                    userdata_bak.point.gold -= priceValue;
                    break;
                case type.Price.Gem:
                    userdata_bak.point.gem -= priceValue;
                    break;
                case type.Price.Heart:
                    userdata_bak.point.heart -= priceValue;
                    break;
            }

            storeModal.BuyCashShop(member_id, userdata_bak.point.gold, userdata_bak.point.heart, userdata_bak.point.film).then((data)=>{
                if (data.length != 0) {
                    let resultCode = data['@oResult'];
                    if( resultCode == error.Success )   {

                        //
                        // sess 데이터 날아가서 다시 한 번 저장.
                        //
                        userdata = userdata_bak;
                        sess.user.data = userdata;
                        resolve(userdata);
                    }
                    else {
                        console.log("Database Querry Fail = %d", resultCode);
                        reject(new Error('Database Querry Fail!!'));
                    }
                }
                else {
                    console.log("Database Querry Fail");
                    reject(new Error('Database Querry Fail!!'));
                }
            }).catch((err) => {
                console.error(err);
                reject(new Error('Database Querry Fail!!'));
            })
        }
        else
        {
            storeModal.Buy(member_id, Id, priceValue, tbShop.price_type, myitem_cnt, myitem_str, buyalbum_cnt, buyalbum_str, soldoutpkg_cnt, soldoutpkg_str).then((data)=>{
                if (data.length != 0) {
                    let resultCode = data['@oResult'];
                    if( resultCode == error.Success )   {
                        // item처리 
                        userdata = userdata_bak;
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

                        //
                        // sess 데이터 날아가서 다시 한 번 저장.
                        //

                        sess.user.data = userdata;
                        resolve(userdata);
                    }
                    else {
                        console.log("Database Querry Fail = %d", resultCode);
                        reject(new Error('Database Querry Fail!!'));
                    }
                }
                else {
                    console.log("Database Querry Fail");
                    reject(new Error('Database Querry Fail!!'));
                }
            }).catch((err) => {
                console.error(err);
                reject(new Error('Database Querry Fail!!'));
            })
        }
    });
}

function ItemCreate(userdata, tbItem, count, add_items)  {
    console.log(">>> ItemCreate, tbItem="+JSON.stringify(tbItem));
    let data = userdata;
    switch (tbItem.type) {
        case type.ItemType.Gold:
            data.point.gold += count;
            break;
        case type.ItemType.Heart:
            data.point.heart += count;
            break;
        case type.ItemType.Film:
            data.point.film += count;
            break;
        default:
            if(tbItem.packnum != 0)
            {
                var tbProduct = tableManager.Product.find(tbItem.packnum);
                var len = tbProduct.item.length;
                var packItemLen = 0;
                var count =0;
                var IsGet = false;

                for(let i = 0; i < len; i++)
                {
                    var tbItem2 = tableManager.Item.find(tbProduct.item[i]);
                    if(tbItem2.type == type.ItemType.Cloth || tbItem2.type == type.ItemType.Shose || tbItem2.type == type.ItemType.Accessories )
                    {
                        packItemLen++;
                        console.log("packItemLen");
                        console.log(packItemLen);
                    }
                }

                for(let i = 0; i < len; i++)
                {
                    for(let n =0; n < data.mypage.length; n++)
                    {
                        if(data.mypage[n] == tbProduct.item[i])
                        {
                            count++;
                        }
                        if(data.mypage[n] == tbItem.Id)
                        {
                            IsGet = true;
                            return "AlreadyBuy";
                        }
                    }
                }

                if(count + 1 == packItemLen && IsGet == false)
                {
                    data.soldoutpackage[data.soldoutpackage.length] = extension.toInteger(tbItem.packnum);
                    console.log("soldoutpackage - {0}".format(extension.toInteger(tbItem.packnum)));
                    add_items.soldoutpackage.push(extension.toInteger(tbItem.packnum));
                }

                if(!IsGet)
                {
                    if(tbItem.type == type.ItemType.CGillust)
                    {
                        var IsBuyCG = false;
                        for(let i=0; i < data.buyalbum.length; i++)
                        {
                            if(data.buyalbum[i] == tbItem.Id)
                            {
                                IsBuyCG = true;
                                break;
                            }
                        }
                        if(!IsBuyCG)
                        {
                            data.buyalbum[data.buyalbum.length] = tbItem.Id;
                            console.log("buyalbum - {0}".format(tbItem.Id));
                            add_items.buyalbum.push(tbItem.Id);
                        }
                    }
                    else
                    {
                        data.mypage[data.mypage.length] = tbItem.Id;
                        add_items.mypages.push(tbItem.Id);
                        console.log("mypage 1 - {0}".format(tbItem.Id));
                    }
                }
            }
            else
            {
                for(let n =0; n < data.mypage.length; n++)
                {
                    if(data.mypage[n] == tbItem.Id)
                    {
                        IsGet = true;
                        return "AlreadyBuy";
                    }
                }

                if(!IsGet)
                {
                    if(tbItem.type == type.ItemType.CGillust)
                    {
                        var IsBuyCG = false;
                        for(let i=0; i < data.buyalbum.length; i++)
                        {
                            if(data.buyalbum[i] == tbItem.Id)
                            {
                                IsBuyCG = true;
                                break;
                            }
                        }
                        if(!IsBuyCG)
                        {
                            data.buyalbum[data.buyalbum.length] = tbItem.Id;
                            add_items.buyalbum.push(tbItem.Id);
                            console.log("buyalbum 2 - {0}".format(tbItem.Id));
                        }
                    }
                    else
                    {
                        data.mypage[data.mypage.length] = tbItem.Id;
                        add_items.mypages.push(tbItem.Id);
                        console.log("mypage 2 - {0}".format(tbItem.Id));
                    }
                }
            }
            break;
    }
    return data;
}

module.exports = storeController;