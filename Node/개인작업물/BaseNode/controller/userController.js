'use strict';

const extension = require('../common/extension');
const error = require('../common/error');
const type = require('../common/type');
const userModal = require("../model/userModal");

function setting_mapdata(data)
{
    let user = {
        data: MapCreate(),
    };   
    
    if( data.clearmaps !== null )    {
        user.data.clearmaps = str_to_array(data.clearmaps);
    }


    return user;
}

//
// 사용자 맵 클리어 데이터를 생성합니다.
//
function MapCreate()
{
    var data = {
        clearmaps:[],    
    };

    return data;
}

function str_to_array(string)  {
    var retArray = [];
    // 문자열에 배열로 나눌 기준 문자 존재여부 확인
    if (string.match(",")) {
        // 기준 문자가 있을 경우 나눔
        var strArray = string.split(",");
        for( var i=0; i<strArray.length; i++) {
            retArray.push(Number(strArray[i]));
        }
    } else {
        // 한개의 데이터가 있을 경우
        if( string.length > 0) {
            retArray.push(Number(string));
        }
    }
    return retArray;
}

var userController = {
    MapClear:MapClear,
}

function MapClear(body, sess, res) {

    let userId = body.userId.trim();
    let mapId = body.mapId.trim();

    userModal.MapClear(userId, mapId, sess).then((data)=>{
        console.log(data);
        if (data.length != 0) {
            let resultCode = data['@oResult'];
            if( resultCode == error.Success )   {            
                
                let set_mapdata = setting_mapdata(JSON.parse(data['@oUserData']));

                console.log(set_mapdata);

                let json_data = JSON.stringify(set_mapdata.data);

                res.end(JSON.stringify({ klass : 'ActionMapClearResult', result:'Success',data: json_data }));
            }
            else {
                console.log("ActionMapClearResult - return value = %d", resultCode);
                res.json({ klass: 'ActionMapClearResult', result: error.Fail });    
            }
            //res.json({ klass: 'ActionMapClearResult', result: value });
        }
        else {
            console.log("ActionMapClearResult - return 3");
            res.json({ klass: 'ActionMapClearResult', result: error.Fail });
        }
    }).catch((err) => {
        console.error(err);
        res.json({ klass: 'ActionMapClearResult', result: error.Fail });
    })
}



module.exports = userController;