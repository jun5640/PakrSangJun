'use strict';

const extension = require('../common/extension');
const error = require('../common/error');
const type = require('../common/type');
const authModal = require("../model/authModal");

function setting_userdata(data)
{
    let user = {
        data: Create(),
    };   
    
    if( data.clearmaps !== null )    {
        user.data.clearmaps = str_to_array(data.clearmaps);
    }


    return user;
}

//
// 사용자 데이터를 생성합니다.
//
function Create()
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



var authController = {
    Register:Register,
    Login:Login,
}

function Register(body, sess, res) {

    let userId = body.userId.trim();
    let userPassWord = body.userPassWord.trim();


    authModal.Register(userId, userPassWord, sess).then((data)=>{
        console.log(data);
        if (data.length != 0) {
            let resultCode = data['@oResult'];
            if( resultCode == error.Success )   {               
                res.end(JSON.stringify({ klass : 'ActionRegisterResult', data: 'Success' }));
            }
            else {
                console.log("ActionRegisterResult - return value = %d", resultCode);
                res.json({ klass: 'ActionRegisterResult', result: error.Fail });    
            }
            //res.json({ klass: 'ActionRegisterResult', result: value });
        }
        else {
            console.log("ActionRegisterResult - return 3");
            res.json({ klass: 'ActionRegisterResult', result: error.Fail });
        }
    }).catch((err) => {
        console.error(err);
        res.json({ klass: 'ActionRegisterResult', result: error.Fail });
    })
}

function Login(body, sess, res) {

    let userId = body.userId.trim();
    let userPassWord = body.userPassWord.trim();

    authModal.Login(userId, userPassWord, sess).then((data)=>{
        console.log(data);
        if (data.length != 0) {
            let resultCode = data['@oResult'];
            if( resultCode == error.Success )   {      
                
                let set_userdata = setting_userdata(JSON.parse(data['@oUserData']));

                console.log(set_userdata);

                let json_data = JSON.stringify(set_userdata.data);
                
                res.end(JSON.stringify({ klass : 'ActionLoginResult', result: 'Success', data:json_data }));
            }
            else {
                console.log("ActionLoginResult - return value = %d", resultCode);
                res.json({ klass: 'ActionLoginResult', result: error.Fail });    
            }
            //res.json({ klass: 'ActionRegisterResult', result: value });
        }
        else {
            console.log("ActionLoginResult - return 3");
            res.json({ klass: 'ActionLoginResult', result: error.Fail });
        }
    }).catch((err) => {
        console.error(err);
        res.json({ klass: 'ActionLoginResult', result: error.Fail });
    })
}



module.exports = authController;