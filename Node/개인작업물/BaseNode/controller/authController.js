'use strict';

const extension = require('../common/extension');
const error = require('../common/error');
const type = require('../common/type');
const authModal = require("../model/authModal");

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
                res.end(JSON.stringify({ klass : 'ActionLoginResult', data: 'Success' }));
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