const util = require('util');
const events = require('events');
const express = require('express');
//const Promise = require('bluebird');
const config = require('config');

const error = require('../common/error');
const type = require('../common/type');
// var authController = require('../controller/authController');
// var userController = require('../controller/userController');
// var storeController = require('../controller/storeController');

var router = express.Router();
var emitter = new events.EventEmitter();

// //
// // 정의 되지않는 메시지 및 오류 처리
// //
 emitter.on('error', function (action, res, errorCode, msg = null) {
     if (msg !== null) {
         return res.json({ klass: action, result: errorCode, msg: msg });
     } else {
         return res.json({ klass: action, result: errorCode });
     }
 });

 //
 // 사용자 로그인 처리
 //
 emitter.on('ActionLogin', function (body, sess, res) {

    console.log("ActionLogin Fun");

    res.json({klass: "hello"});

    console.log("ActionLogin Fun");
    
    return true;
});

// //
// // 사용자 로그아옷
// //
// emitter.on('ActionLogout', function (body, sess, res) {
//     authController.Logout(sess, res);
//     return true;
// });

// //
// // 사용자 등록
// //
// emitter.on('ActionRegister', (body, sess, res) => {
//     authController.Register(body, sess, res);
//     return true;
// });

// //
// // 캐릭터 변경 요청
// //
// emitter.on('ActionCharSelect', (body, sess, res) => {
//     if (!authController.IsAuth(sess) ) {
//         return res.json({ klass: 'ActionCharSelectResult', result: error.Fail });
//     }
//     userController.CharSelect(body, sess, res);
//     return true;
// });




//
//  시스템 사용자 검색
//

//
// 사용자 요청을 분석하고 처리합니다.
//
router.post('/', function (req, res) {
    var sess = req.session;
    var body = req.body;
    sess.remoteAddress = req.connection.remoteAddress;
    //
    // 메시지에 해당하는 코드를 처리합니다.
    //
   
   
    if (typeof body.klass !== 'undefined') {
        var now = new Date();

        console.log(body.klass);

        if (config.get('log.level') <= type.Log.Level.Debug) {
            console.log(now.toLocaleString() + ', "' + req.connection.remoteAddress + '", ' + JSON.stringify(body));
        }
        if (!emitter.emit(body.klass, body, sess, res))
            emitter.emit('error', 'ActionResult', res, error.UnknownAction, null);
    } else {
        emitter.emit('error', 'ActionResult', res, error.UnknownAction, null);
    }
});

module.exports = router;
