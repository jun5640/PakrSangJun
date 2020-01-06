'use strict';

const extension = require('../common/extension');
const error = require('../common/error');
const type = require('../common/type');
const authModal = require("../model/authModal");
const memSession = require('../lib/memcached');
var userController = require('./userController');

var authController = {
    IsAuth:IsAuth,
    Login:Login,
    Logout:Logout,
    Register:Register,
    Unregister:Unregister
}

/**
 * 인증 여부 체크
 *
 */
function IsAuth(sess) {
    return sess.hasOwnProperty('auth') &&
        sess.hasOwnProperty('user') &&
        sess.auth !== null &&
        sess.user !== null;
}

/**
 * 사용자 접속 승인
 *
 */
function Login(body, sess, res)  {
    if (!body.hasOwnProperty('account') || !body.hasOwnProperty('type')) {
        console.log("ActionLogin - return 1");
        res.json({ klass: 'ActionLoginResult', result: error.NeedProperty });
        return;
    }

    let account = body.account.trim();
    if (extension.IsEmpty(account) || extension.IsBlank(account)) {
        console.log("ActionLogin - return 2");
        res.json({ klass: 'ActionLoginResult', result: error.NeedProperty });
        return;
    }

    let authType = body.type;
    if (type.AuthType.Min > authType || type.AuthType.Max < authType) {
        console.log("ActionLogin - return 3");
        res.json({ klass: 'ActionLoginResult', result: error.NeedProperty });
        return;
    }

    authModal.getAccount(account, authType, sess.remoteAddress, sess.id).then((data)=>{
        var resultCode = error.Fial;
        console.log(data);
        if (data.length != 0) {
            resultCode = data['@oResult'];
            sess.auth = { type: 'account', account, authType, state: data['@oStatus'], authority: data['@oAuthority'], block: data['@oBlock'], sessId: sess.id, memberId: data['@oMemberId'] };
            sess.user = null;

            if (data['@oBlock'] != type.AuthState.Normal) {  // type.AuthState.Normal = 0
                resultCode = error.BlockUser;
            } else if (!extension.IsEmpty(data['@oSessionId']) && data['@oSessionId'] != sess.id) {
                authModal.updateAccount(data['@oMemberId'], "").then((data)=>{
                    console.log(data);
                }).catch((err) => {
                    console.log(err);
                })
                resultCode = error.UserDuplication;
                sess.auth = null;
                sess.destroy();
                memSession.destroy(data['@oSessionId']);
            } else if ( data['@oStatus'] == 0) { //플레이어 등록 상태(0:미등록)
                resultCode = error.NewUser;
            }

            res.end(JSON.stringify({ klass : 'ActionLoginResult', result : resultCode }));
        }
    }).catch((err) => {
        console.log("query in return");
        res.json({ klass: 'ActionLoginResult', result: err.DbQuery });
        console.error('error running query', err);
    })
}

/**
 * 사용자 접속 종료.
 */
function Logout(sess, res) {
    if (sess.hasOwnProperty('auth') && sess.auth != null) {
        // auth table update 
        let memberId = sess.auth.memberId;
        authModal.updateAccount(memberId, "").then((data)=>{
            console.log(data);
            res.end(JSON.stringify({ klass : 'ActionLogoutResult', result : error.Success }));
        }).catch((err) => {
            res.end(JSON.stringify({ klass : 'ActionLogoutResult', result : error.Fail }));
        })
    } else {
        res.end(JSON.stringify({ klass : 'ActionLogoutResult', result : error.Fail }));
    }
}

/**
 * 사용자 등록
 *
 */
function Register(body, sess, res) {
    if (!sess.hasOwnProperty('auth') ||
        sess.auth === null ||
        sess.auth.state !== 0 ||
        sess.user !== null) {
        res.json({ klass: 'ActionRegisterResult', result: error.Fail });
        console.log("ActionRegisterResult fail return");
        return true;
    }

    let firstName = body.firstName.trim();
    let lastName = body.lastName.trim();
    if (extension.IsEmpty(firstName) || extension.IsBlank(lastName)) {
        console.log("ActionRegisterResult - return 2");
        res.json({ klass: 'ActionRegisterResult', result: error.Fail });
        return;
    }

    authModal.Register(firstName, lastName, sess).then((data)=>{
        console.log(data);
        if (data.length != 0) {
            let resultCode = data['@oResult'];
            if( resultCode == error.Success )   {
                let user = {
                    type:"user",
                    firstName,
                    lastName,
                    time: new Date(),
                    data: userController.Create(),
                };

                console.log(user);

                sess.user = user;
                sess.auth.state = 1;

                let member_id = sess.auth.memberId;
                let json = JSON.stringify(user.data);
                let json_data = Buffer.from(json, 'utf8').toString('base64');
                //console.log(json_data);    
                res.end(JSON.stringify({ klass : 'ActionRegisterResult', result : resultCode, user : sess.user , firstName:firstName, lastName:lastName, uId: member_id, data:json_data }));
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

/**
 * 사용자 탈퇴
 *
 */
function Unregister(sess)  {
    if (!sess.hasOwnProperty('auth') || sess.auth === null ) {
        res.json({ klass: 'ActionUnregisterResult', result: error.Fail });
        console.log("ActionUnregisterResult fail return");
        return true;
    }

    let member_id = sess.auth.memberId;
    let auth_state = type.AuthState.Unregister;
    authModal.Unregister(member_id, auth_state).then((data)=>{
        console.log(data);
        res.end(JSON.stringify({ klass : 'ActionUnregisterResult', result : error.Success }));
    }).catch((err) => {
        res.end(JSON.stringify({ klass : 'ActionUnregisterResult', result : error.Fail }));
    })
}


module.exports = authController;