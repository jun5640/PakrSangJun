const util = require('util');
const events = require('events');
const express = require('express');
//const Promise = require('bluebird');
const config = require('config');

const error = require('../common/error');
const type = require('../common/type');
var authController = require('../controller/authController');
var userController = require('../controller/userController');
var storeController = require('../controller/storeController');

var router = express.Router();
var emitter = new events.EventEmitter();

//
// 정의 되지않는 메시지 및 오류 처리
//
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
    authController.Login(body, sess, res);
    return true;
});

//
// 사용자 로그아옷
//
emitter.on('ActionLogout', function (body, sess, res) {
    authController.Logout(sess, res);
    return true;
});

//
// 사용자 등록
//
emitter.on('ActionRegister', (body, sess, res) => {
    authController.Register(body, sess, res);
    return true;
});

//
// 사용자 등록 해제
//
emitter.on('ActionUnregister', (body, sess, res) => {
    authController.Unregister(body, sess, res);
    return true;
});

//
// 사용자 정보 요청
//
emitter.on('ActionConnect', (body, sess, res) => {
    userController.UserConnect(sess, res);
    return true;
});

//
// 사용자 스토리 완료 요청
//
emitter.on('ActionStoryEnd', (body, sess, res) => {
    if (!authController.IsAuth(sess) ) {
        return res.json({ klass: 'ActionStoryEndResult', result: error.Fail });
    }
    userController.StoryEnd(body, sess, res);
    return true;
});

//
// 캐릭터 변경 요청
//
emitter.on('ActionCharSelect', (body, sess, res) => {
    if (!authController.IsAuth(sess) ) {
        return res.json({ klass: 'ActionCharSelectResult', result: error.Fail });
    }
    userController.CharSelect(body, sess, res);
    return true;
});

//
// 사용자 CG 일러스트 획득 요청
//
emitter.on('ActionCGGet', (body, sess, res) => {
    if (!authController.IsAuth(sess) ) {
        return res.json({ klass: 'ActionCGGetResult', result: error.Fail });
    }
    userController.CGGet(body, sess, res);
    return true;
});

//
// 클라이언트 연결 유지 관련.
//
emitter.on('ActionPing', (body, sess, res) => {
    var resultCode = error.Fial;
    if (sess.hasOwnProperty('auth') && sess.auth != null) {
        resultCode = error.Success;
    } else {
        resultCode = error.Reboot;
    }
    res.end(JSON.stringify({ klass : 'ActionPingResult', result : resultCode }));
});

//
// 사용자 닉네임 변경
//
emitter.on('ActionNameChange', (body, sess, res) => {
    if (!authController.IsAuth(sess) ) {
        return res.json({ klass: 'ActionNameChangeResult', result: error.Fail });
    }
    userController.NameChange(body, sess, res);
    return true;
});

//
// Quiz 이벤트
//
emitter.on('ActionStartQuiz', (body, sess, res) => {
    if (!authController.IsAuth(sess) ) {
        return res.json({ klass: 'ActionStartQuizResult', result: error.Fail });
    }
    userController.StartQuiz(body, sess, res);
    return true;
});

//
// Quiz 종료 이벤트
//
emitter.on('ActionFinishQuiz', (body, sess, res) => {
    if (!authController.IsAuth(sess) ) {
        return res.json({ klass: 'ActionFinishQuizResult', result: error.Fail });
    }
    userController.FinishQuiz(body, sess, res);
    return true;
});

//
// 이밴트 정보 요청
//
emitter.on('ActionEvent', (body, sess, res) => {
    if (!authController.IsAuth(sess) ) {
        return res.json({ klass: 'ActionEventResult', result: error.Fail });
    }
    //userController.Event(body, sess, res);
    return true;
});

//
// 상품 구매
//
emitter.on('Buy', (body, sess, res) => {
    if (!authController.IsAuth(sess) ) {
        return res.json({ klass: 'BuyResult', result: error.Fail });
    }

    console.log("apiBuy");
    console.log(sess);
    storeController.Buy(body, sess, res);
    return true;
});

//
// 의상 변경
//
emitter.on('ActionChangeWear', (body, sess, res) => {
    if (!authController.IsAuth(sess) ) {
        return res.json({ klass: 'ActionChangeWearResult', result: error.Fail });
    }
    userController.ChangeWear(body, sess, res);
    return true;
});

//
// 정열 행복 포인트 관련.
//
emitter.on('ActionFavor', (body, sess, res) => {
    if (!authController.IsAuth(sess) ) {
        return res.json({ klass: 'ActionFavorResult', result: error.Fail });
    }
    userController.Favor(body, sess, res);
    return true;
});

//
// 사용자 재화 소모
//
emitter.on('ActionCost', (body, sess, res) => {
    if (!authController.IsAuth(sess) ) {
        return res.json({ klass: 'ActionCostResult', result: error.Fail });
    }
    userController.Cost(body, sess, res);
    return true;
});

//
// 스토리 초기화 요청
//
emitter.on('ActionResetStory', (body, sess, res) => {
    if (!authController.IsAuth(sess) ) {
        return res.json({ klass: 'ActionResetStoryResult', result: error.Fail });
    }
    userController.ResetStory(body, sess, res);
    return true;
});

//
// 엔딩 씬 저장
//

emitter.on('ActionSaveEnding', (body, sess, res) => {
    if (!authController.IsAuth(sess) ) {
        return res.json({ klass: 'ActionSaveEndingResult', result: error.Fail });
    }
    userController.SaveEnding(body, sess, res);
    return true;
});

//
// 출석 체크 보상 획득
//

emitter.on('ActionLoginReward', (body, sess, res) => {
    if (!authController.IsAuth(sess) ) {
        return res.json({ klass: 'ActionLoginRewardResult', result: error.Fail });
    }
    userController.LoginReward(body, sess, res);
    return true;
});


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
