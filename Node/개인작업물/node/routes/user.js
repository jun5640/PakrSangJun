const type = require('./type');
const extension = require('./extension');
const tableManager = require('./table');

exports = module.exports = {};

/**
 * 사용자 정보를 생성합니다.
 *
 */
exports.Create = function ()
{

    // var data = {
    //     tutorialclear: false,
    //     point: {
    //         gold: 0,        // 골드
    //         film: 0,        // 필름
    //         heart: 0,       // 하트
    //     },
    //     favor: {
    //         passion: 0,     // 정열 포인트
    //         happy: 0,       // 행복 포인트
    //     },
    //     curstory: 10100,    // 현재 진행할 스토리
    //     album: [[],[],[],[],[],[]],
    //     mypage: [],
    //     selectanswer: [],
    //     selectactor:6,
    //     buyscene:[[],[],[],[],[],[],[]],
    //     clearscene:[[],[],[],[],[],[],[]],
    //     soldoutpackage:[],
    //     wearing:[103,104,105],
    //     basewearing:[103,104,105],
        
    // };

    var data = {
        tutorialclear: true,
        point: {
            gold: 10000,        // 골드
            film: 10000,        // 필름
            heart: 10000,       // 하트
        },
        favor: {
            passion: 0,     // 정열 포인트
            happy: 0,       // 행복 포인트
        },
        curstory: 10110,    // 현재 진행할 스토리
        album: [[],[],[],[],[],[]],
        buyalbum:[],
        mypage: [],
        selectanswer: [],
        selectactor:0,
        quizscene:[[],[],[],[],[],[],[]],
        clearscene:[[],[],[],[],[],[],[10100,10101,10102,10103,10104,10105,10106,10107,10108,10109]],
        soldoutpackage:[],
        wearing:[100,200,300],
        basewearing:[100,200,300],
        
    };

    return data;
}

exports.SaveData = (userData,sId,db) => {
    var userquery = 'UPDATE user SET data = ? WHERE  sId = ?';

    db.query(userquery, [ JSON.stringify(userData), sId], function (err) {

        console.log("33333333333333333");
        if (err) {
            console.error('error running query', err);
            return false;
        }
        else
        {
            return true;
        }
    });
}

exports.ItemCreate = (user, tbItem, count,tbProduct) => {
    
    let data = user;
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
                        }
                    }
                    else
                    {
                        data.mypage[data.mypage.length] = tbItem.Id;
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
                        }
                    }
                    else
                    {
                        data.mypage[data.mypage.length] = tbItem.Id;
                    }
                }
            }
        

            break;
    }

    return data;
}