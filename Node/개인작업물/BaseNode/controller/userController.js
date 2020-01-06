'use strict';

const config = require('config');
const extension = require('../common/extension');
const error = require('../common/error');
const type = require('../common/type');
const userModal = require("../model/userModal");
const memSession = require('../lib/memcached');
const tableManager = require('../common/table');
const commonController = require('./commonController');
const commonModal = require("../model/commonModal");

var userController = {
    Create:Create,
    StoryEnd:StoryEnd,
    UserConnect:UserConnect,
    CharSelect:CharSelect,
    CGGet:CGGet,
    NameChange:NameChange,
    StartQuiz:StartQuiz,
    FinishQuiz:FinishQuiz,
    ChangeWear:ChangeWear,
    Favor:Favor,
    Cost:Cost,
    ResetStory:ResetStory,
    SaveEnding:SaveEnding,
    LoginReward:LoginReward,
}

function convert_actor_data(string, data)  {
    var retArray = [];
    // 문자열에 배열로 나눌 기준 문자 존재여부 확인
    if (string.match("|")) {
        // 기준 문자가 있을 경우 나눔
        var strArray = string.split("|");
        let actor = [];
        let lists = [];
        for( var i=0; i<strArray.length; i++) {
            actor = JSON.parse(strArray[i]); 
            lists = str_to_array(actor.lists);
            data[actor.actor_id] = lists;
        }
    } else {
        // 한개의 데이터가 있을 경우
        if( string.length > 0) {
            let actor = [];
            let lists = [];
            actor = JSON.parse(strArray[0]); 
            lists = str_to_array(actor.lists);
            data[actor.actor_id] = lists;
        }
    }
    return retArray;
}

function convert_reset_check_data(string, data)  {
    var retArray = str_to_array(string);

    for( var i=0; i<retArray.length; i++)
    {
        data[retArray[i]][0] = 1;
    }

    return retArray;
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

function setting_userdata(data)
{
    let user = {
        type:"user",
        firstName:"",
        lastName:"",
        time: new Date(),
        data: Create(),
    };   
    
    // user_data
    let user_data = JSON.parse(data.user_data);
    user.firstName = user_data.first_name;
    user.lastName = user_data.last_name;
    user.data.tutorialclear = user_data.tutorial_clear;
    user.data.selectactor = user_data.select_actor;
    user.data.curstory = user_data.cur_story;
    user.data.point.gold = user_data.gold;
    user.data.point.film = user_data.film;
    user.data.point.heart = user_data.heart;
        
    // album : [[],[],[],[],[],[]]
    if( data.album !== null )    {
        convert_actor_data(data.album, user.data.album);
    }

    // buyalbum:[]
    if( data.buyalbum !== null )    {
        user.data.buyalbum = str_to_array(data.buyalbum);
    }

    // mypage:[]
    if( data.mypage !== null )    {
        user.data.mypage = str_to_array(data.mypage);
    }

    // quizscene:[[],[],[],[],[],[],[]]
    if( data.quizscene !== null )    {
        convert_actor_data(data.quizscene, user.data.quizscene);
    }

    //clearscene:[[],[],[],[],[],[],[10100,10101,10102,10103,10104,10105,10106,10107,10108,10109]]
    if( data.clearscene !== null )    {
        convert_actor_data(data.clearscene, user.data.clearscene);
    }
    //soldoutpackage:[]
    if( data.soldoutpackage !== null )    {
        user.data.soldoutpackage = str_to_array(data.soldoutpackage);
    }
    //wearing:[100,200,300]
    if( data.wearing !== null )    {
        user.data.wearing = str_to_array(data.wearing);
    }

    // endingscene:[[],[],[],[],[],[],[]]
    if(data.endingscene !== null)   {
        convert_actor_data(data.endingscene, user.data.endingscene);
    }

    // resetcheck:[[0],[0],[0],[0],[0],[0],[0]]
    if(data.resetcheck !== null)    {
        convert_reset_check_data(data.resetcheck, user.data.resetcheck);
    }

    if(data.passion !== null)   {
        convert_actor_data(data.passion, user.data.passion);
    }

    if(data.happy !== null)   {
        convert_actor_data(data.happy, user.data.happy);
    }

    return user;
}

/**
 * 사용자 정보를 생성합니다.
 *
 */
function Create()
{
    var data = {
        tutorialclear: false,
        point: {
            gold: 10000,        // 골드
            film: 10000,        // 필름
            heart: 10000,       // 하트
        },
        passion:[[],[],[],[],[],[],[]],
        happy:[[],[],[],[],[],[],[]],
        curstory: 10100,    // 현재 진행할 스토리
        album: [[],[],[],[],[],[]],
        buyalbum:[],
        mypage: [],
        selectanswer: [],
        selectactor:6,
        quizscene:[[],[],[],[],[],[],[]],
        clearscene:[[],[],[],[],[],[],[]],
        resetcheck:[[0],[0],[0],[0],[0],[0],[0]],
        endingscene:[[],[],[],[],[],[],[]],
        soldoutpackage:[],
        wearing:[100,200,300],
        basewearing:[100,200,300],
        
    };

    return data;
}

/**
 * 사용자 정보 요청
 *
 */
function UserConnect(sess, res) {
    if (!sess.hasOwnProperty('auth') ||
        sess.auth === null ||
        extension.IsEmpty(sess.auth.memberId)) {
        res.json({ klass: 'ActionConnectResult', result: error.Fail });
        return true;
    }

    let member_id = sess.auth.memberId;

    userModal.UserConnect(member_id).then((data)=>{
        console.log(data);
        if (data.length != 0) {
            let resultCode = data['@oResult'];
            if( resultCode == error.Success )   {
                let set_userdata = setting_userdata(JSON.parse(data['@oUserData']));
                
                console.log(set_userdata);
                sess.user = set_userdata;

                let json = JSON.stringify(set_userdata.data);
                let json_data = Buffer.from(json, 'utf8').toString('base64');
                //console.log(json_data);    
                res.json({ klass : 'ActionConnectResult', result: error.Success, firstName:set_userdata.firstName, lastName:set_userdata.lastName, uId: member_id, data:json_data });
            }
            else {
                console.log("ActionConnectResult - return value = %d", resultCode);
                res.json({ klass: 'ActionConnectResult', result: error.Fail });    
            }
        }
        else {
            console.log("ActionConnectResult - return 3");
            res.json({ klass: 'ActionConnectResult', result: error.Fail });
        }
    }).catch((err) => {
        console.error(err);
        res.json({ klass: 'ActionConnectResult', result: error.Fail });
    })
}

/**
 * 사용자 스토리 완료 요청
 *
 */
function StoryEnd(body, sess, res) {
    if (!sess.hasOwnProperty('user') || sess.user === null ) {
        res.json({ klass: 'ActionStoryEndResult', result: err.Fail });
        return;
    }

    let auth = sess.auth;
    let user = sess.user;
    let userdata = user.data;
    let curscene = tableManager.Scene.find(userdata.curstory);
    let clearActorScene = userdata.clearscene[userdata.selectactor];
    let clearSceneId = 0;

    if(userdata.point.film <= 0)
    {
        if(userdata.resetcheck[userdata.selectactor][0] != 1)
        {
            console.log("user film not enought");
            res.json({ klass: 'ActionStoryEndResult', result: err.Fail });
            return;
        }
    }
    else
    {
        //
        //  필름 감소 하는데 해당 캐릭터가 리셋 표시면 필름 감소 x
        //
    }

    var findresult = false;
    if(clearActorScene != null)
    {
        findresult = clearActorScene.find((x)=>{

            if(x == userdata.curstory)
            {
                return true;
            }
        });
    }

    if(findresult != true)
    {
        clearSceneId = userdata.curstory;
        clearActorScene.push(clearSceneId);
    }


    if(userdata.curstory == type.EndTutorial)
    {
        userdata.tutorialclear = true;
    }

    //
    // 필름 갯수 차감 및 리셋 캐릭터 확인.
    //
    if(userdata.point.film > 0)
    {
        if(userdata.resetcheck[userdata.selectactor][0] != 1)
        {
            userdata.point.film--;
        }
    }

    if(curscene.nextId != 0)
    {
        if(userdata.curstory == type.EndTutorial)
        {
            userdata.tutorialclear = true;
        }
        userdata.curstory = curscene.nextId;
    }

    let params = {
        member_id:auth.memberId, 
        film:userdata.point.film, 
        cur_story:userdata.curstory, 
        actor_id:userdata.selectactor, 
        scene_id:clearSceneId, 
        tutorial_clear:userdata.tutorialclear 
    }
    userModal.StoryEnd(params).then((data)=>{
        if (data.length != 0) {
            let resultCode = data['@oResult'];
            if( resultCode == error.Success )   {
                let json = JSON.stringify(userdata);
                let json_data = Buffer.from(json, 'utf8').toString('base64');
                res.json({ klass : 'ActionStoryEndResult', result: error.Success, data:json_data});
            }
            else {
                console.log("ActionStoryEndResult - return value = %d", resultCode);
                res.json({ klass : 'ActionStoryEndResult', result: error.Fail});
            }
        }
        else {
            console.log("ActionStoryEndResult - return 3");
            res.json({ klass : 'ActionStoryEndResult', result: error.Fail});
        }
    }).catch((err) => {
        console.error(err);
        res.json({ klass : 'ActionStoryEndResult', result: error.Fail});
    })
}

/**
 * 사용자 스토리 완료 요청
 *
 */
function CharSelect(body, sess, res) {
    let userdata = sess.user.data;
    let select_actor = body.actorNum;
    let zeroclear = false;
    userdata.selectactor = select_actor;

    console.log(userdata.clearscene[select_actor].length);

    if(userdata.clearscene[select_actor].length == 0)
    {
        zeroclear = true;
    }

    if(zeroclear == true)
    {
        if(select_actor == type.Actor.Kangtaejun)
        {
            userdata.curstory = type.StartScene.Kangtaejun;
        }
        if(select_actor == type.Actor.Backhyeonseong)
        {
            userdata.curstory = type.StartScene.Backhyeonseong;
        }
        if(select_actor == type.Actor.Jeonseockhwan)
        {
            userdata.curstory = type.StartScene.Jeonseockhwan;
        }
        if(select_actor == type.Actor.Jeonjaemin)
        {
            userdata.curstory = type.StartScene.Jeonjaemin;
        }
        if(select_actor == type.Actor.Kimdongju)
        {
            userdata.curstory = type.StartScene.Kimdongju;
        }
    }
    else
    {
        let last_scene_num = userdata.clearscene[select_actor][userdata.clearscene[select_actor].length - 1];
        let curscene = tableManager.Scene.find(last_scene_num);
        userdata.curstory = curscene.nextId;
    }

    let params = {
        member_id:sess.auth.memberId, 
        cur_story:userdata.curstory, 
        actor_id:userdata.selectactor
    }
    userModal.CharSelect(params).then((data)=>{
        if (data.length != 0) {
            let resultCode = data['@oResult'];
            if( resultCode == error.Success )   {
                let json = JSON.stringify(userdata);
                let json_data = Buffer.from(json, 'utf8').toString('base64');
                res.json({ klass : 'ActionCharSelectResult', result: error.Success, data:json_data});
            }
            else {
                console.log("ActionCharSelectResult - return value = %d", resultCode);
                res.json({ klass : 'ActionCharSelectResult', result: error.Fail});
            }
        }
        else {
            console.log("ActionCharSelectResult - return 3");
            res.json({ klass : 'ActionCharSelectResult', result: error.Fail});
        }
    }).catch((err) => {
        console.error(err);
        res.json({ klass : 'ActionCharSelectResult', result: error.Fail});
    })
}

// 사용자 CG 일러스트 획득 요청
function CGGet(body, sess, res) {
    let userdata = sess.user.data;
    let find_result = false;
    let is_insert = false;

    let member_id = sess.auth.memberId;
    let inset_query_str = '';
    let album_id = 0;
    let album_idx = 0;

    for(var outindex = 0; outindex < body.CGIndex.length; outindex++)
    {
        if(body.CGIndex[outindex] == null)
        {
            continue;
        }

        for(var inindex = 0; inindex < body.CGIndex[outindex].length; inindex++)
        {
            userdata.album[outindex].find((x)=>{

                if(x == body.CGIndex[outindex][inindex])
                {
                    find_result = true;
                    return true;
                }
            });

            if(find_result == true)
            {
                find_result = false; // 이미 있는 컷신 이므로 추가 x
            }
            else
            {
                if(body.CGIndex[outindex][inindex] != 0) // 없는 컷신이므로 추가
                {
                    album_idx = userdata.album[outindex].length;
                    album_id = body.CGIndex[outindex][inindex];
                    userdata.album[outindex][album_idx] = album_id;
                    is_insert = true;

                    inset_query_str += "insert into user_album (member_id,actor_id,album_id,reg_date) values ("+member_id+"," +outindex+","+album_id+", NOW() ); "
                }
            }
        }
    }

    // 추가 할 컷신을 있다면 insert 
    if( is_insert ) {
        userModal.CmdInsertQuery(inset_query_str).then((data)=>{
            if (data.length != 0) {
                let json = JSON.stringify(userdata);
                let json_data = Buffer.from(json, 'utf8').toString('base64');
                res.json({ klass : 'ActionCGGetResult', result: error.Success, data:json_data});
            }
            else {
                console.log("ActionCGGetResult - return 3");
                res.json({ klass : 'ActionCGGetResult', result: error.Fail});
            }
        }).catch((err) => {
            console.error(err);
            res.json({ klass : 'ActionCGGetResult', result: error.Fail});
        })
    }
    else {
        let json = JSON.stringify(userdata);
        let json_data = Buffer.from(json, 'utf8').toString('base64');
        res.json({ klass : 'ActionCGGetResult', result: error.Success, data:json_data});
    }
}

// 사용자 닉네임 변경
function NameChange(body, sess, res) {
    let userdata = sess.user.data;
    let firstName = body.firstName.trim();
    let lastName = body.lastName.trim();
    if (extension.IsEmpty(firstName) || extension.IsBlank(lastName)) {
        console.log("ActionNameChangeResult - return 1");
        res.json({ klass: 'ActionNameChangeResult', result: error.Fail });
        return;
    }

    let params = {
        member_id:sess.auth.memberId, 
        firstName:firstName, 
        lastName:lastName
    }
    userModal.NameChange(params).then((data)=>{
        if (data.length != 0) {
            let resultCode = data['@oResult'];
            if( resultCode == error.Success )   {
                res.json({ klass : 'ActionNameChangeResult', result : error.Success ,firstName:firstName, lastName:lastName});
            }
            else {
                console.log("ActionNameChangeResult - return value = %d", resultCode);
                res.json({ klass : 'ActionNameChangeResult', result: error.Fail});
            }
        }
        else {
            console.log("ActionNameChangeResult - return 3");
            res.json({ klass : 'ActionNameChangeResult', result: error.Fail});
        }
    }).catch((err) => {
        console.error(err);
        res.json({ klass : 'ActionNameChangeResult', result: error.Fail});
    })
}

// Quiz 이벤트
function StartQuiz(body, sess, res) {
    let userdata = sess.user.data;
    let heart = userdata.point.heart;
    if(heart < type.QuizCost)   {
        console.log("ActionStartQuizResult - heart point =%d", heart);
        res.json({ klass : 'ActionStartQuizResult', result: error.Fail});
    }
    let params = {
        member_id:sess.auth.memberId, 
        heart:userdata.point.heart
    }
    userModal.StartQuiz(params).then((data)=>{
        if (data.length != 0) {
            let resultCode = data['@oResult'];
            if( resultCode == error.Success )   {
                // 하트 point 차감
                userdata.point.heart = userdata.point.heart - type.QuizCost;
                let json = JSON.stringify(userdata);
                let json_data = Buffer.from(json, 'utf8').toString('base64');
                res.json({ klass : 'ActionStartQuizResult', result: error.Success, data:json_data});
            }
            else {
                console.log("ActionStartQuizResult - return value = %d", resultCode);
                res.json({ klass : 'ActionStartQuizResult', result: error.Fail});
            }
        }
        else {
            console.log("ActionStartQuizResult - return 3");
            res.json({ klass : 'ActionStartQuizResult', result: error.Fail});
        }
    }).catch((err) => {
        console.error(err);
        res.json({ klass : 'ActionStartQuizResult', result: error.Fail});
    })
}

// Quiz 종료 이벤트
function FinishQuiz(body, sess, res) {
    let userdata = sess.user.data;

    // 성공 실패 유무 획득 성공 or 실패 보상 부여.
    let chartype = body.chartype;
    if (type.Actor.Kangtaejun > chartype || type.Actor.Jeonseockhwan < chartype) {
        res.json({ klass: 'ActionFinishQuizResult', result: error.InvalidParam });
        return true;
    }

    let finish_quiz_id = 0;
    if(chartype == type.Actor.Kangtaejun)
    {
        finish_quiz_id = type.QuizScene.Kangtaejun;
    }
    else if(chartype == type.Actor.Backhyeonseong)
    {
        finish_quiz_id = type.QuizScene.Backhyeonseong;
    }
    else if(chartype == type.Actor.Jeonjaemin)
    {
        finish_quiz_id = type.QuizScene.Jeonjaemin;
    }
    else if(chartype == type.Actor.Kimdongju)
    {
        finish_quiz_id = type.QuizScene.Kimdongju;
    }
    else if(chartype == type.Actor.Jeonseockhwan)
    {
        finish_quiz_id = type.QuizScene.Jeonseockhwan;
    }


    let params = {
        member_id:sess.auth.memberId, 
        actor_id:chartype,
        quiz_id:finish_quiz_id
    }
    userModal.FinishQuiz(params).then((data)=>{
        if (data.length != 0) {
            let resultCode = data['@oResult'];
            if( resultCode == error.Success )   {
                // 성공일 경우에만 
                userdata.quizscene[chartype].push(finish_quiz_id);
                let json = JSON.stringify(userdata);
                let json_data = Buffer.from(json, 'utf8').toString('base64');
                res.json({ klass : 'ActionFinishQuizResult', result: error.Success, data:json_data});
            }
            else {
                console.log("ActionFinishQuizResult - return value = %d", resultCode);
                res.json({ klass : 'ActionFinishQuizResult', result: error.Fail});
            }
        }
        else {
            console.log("ActionFinishQuizResult - return 3");
            res.json({ klass : 'ActionFinishQuizResult', result: error.Fail});
        }
    }).catch((err) => {
        console.error(err);
        res.json({ klass : 'ActionFinishQuizResult', result: error.Fail});
    })
}

// 의상 변경
function ChangeWear(body, sess, res) {
    let userdata = sess.user.data;
    let wearing = body.wear;

    let wearing_len = wearing.length;
    if( wearing_len <= 0 || wearing_len > 3)    {
        console.log("ActionChangeWearResult - return 1");
        res.json({ klass : 'ActionChangeWearResult', result: error.Fail});
        return true;
    }
    //let lists_str = '';
    for(var i = 0; i < wearing_len; i++)
    {
        if( wearing[i] <= 0 )    {
            console.log("ActionChangeWearResult - return 3");
            res.json({ klass : 'ActionChangeWearResult', result: error.Fail});
            return true;
        }
        //if( i == 0 ) lists_str += wearing[i];
        //else {
        //    lists_str += ","+wearing[i];
        //}
    }

    let params = {
        member_id:sess.auth.memberId, 
        cloth:wearing[0],
        shoes:wearing[1],
        accessary:wearing[2]
        //lists_str:lists_str
    }
    userModal.ChangeWear(params).then((data)=>{
        if (data.length != 0) {
            let resultCode = data['@oResult'];
            if( resultCode == error.Success )   {
                // 성공일 경우에만 
                userdata.wearing = wearing;
                let json = JSON.stringify(userdata);
                let json_data = Buffer.from(json, 'utf8').toString('base64');
                res.json({ klass : 'ActionChangeWearResult', result: error.Success, data:json_data});
            }
            else {
                console.log("ActionChangeWearResult - return value = %d", resultCode);
                res.json({ klass : 'ActionChangeWearResult', result: error.Fail});
            }
        }
        else {
            console.log("ActionChangeWearResult - return 3");
            res.json({ klass : 'ActionChangeWearResult', result: error.Fail});
        }
    }).catch((err) => {
        console.error(err);
        res.json({ klass : 'ActionChangeWearResult', result: error.Fail});
    })
}

// 정열 행복 포인트 관련.
function Favor(body, sess, res) {
    let userdata = sess.user.data;
    let favor = body.favor;
    let actor_id = body.actor_id;
    let happy_pt = favor.happy;
    let passion_pt = favor.passion;

    let params = {
        member_id:sess.auth.memberId, 
        happy_pt:happy_pt,
        passion_pt:passion_pt,
        actor_id:actor_id
    }
    userModal.Favor(params).then((data)=>{
        if (data.length != 0) {
            let resultCode = data['@oResult'];
            if( resultCode == error.Success )   {
                // 성공일 경우에만 
                userdata.happy[actor_id][0] += happy_pt;
                userdata.favor[actor_id][0] += passion_pt;

                let json = JSON.stringify(userdata);
                let json_data = Buffer.from(json, 'utf8').toString('base64');
                res.json({ klass : 'ActionFavorResult', result: error.Success, data:json_data});
            }
            else {
                console.log("ActionFavorResult - return value = %d", resultCode);
                res.json({ klass : 'ActionFavorResult', result: error.Fail});
            }
        }
        else {
            console.log("ActionFavorResult - return 3");
            res.json({ klass : 'ActionFavorResult', result: error.Fail});
        }
    }).catch((err) => {
        console.error(err);
        res.json({ klass : 'ActionFavorResult', result: error.Fail});
    })
}

function Cost(body,sess,res) {
    let data = Buffer.from(body.data, 'base64').toString('utf8');

    let revdata = JSON.parse(data);

    let userdata = sess.user.data;
    let pricetype = revdata.pricetype;
    let cost = revdata.cost;

    switch (pricetype) 
    {
        case type.Price.Gold:
            if(userdata.point.gold < cost)
            {
                res.end(JSON.stringify({ klass : 'ActionCostResult', result : error.Fail }));
                return;
            }
            break;
        case type.Price.Film:
            if(userdata.point.film < cost)
            {
                res.end(JSON.stringify({ klass : 'ActionCostResult', result : error.Fail }));
                return;
            }
            break;
        case type.Price.Heart:
            if(userdata.point.heart < cost)
            {
                res.end(JSON.stringify({ klass : 'ActionCostResult', result : error.Fail }));
                return;
            }
            break;
    }

    let params = {
        member_id:sess.auth.memberId, 
        type:pricetype,
        cost:cost
    }
    userModal.Cost(params).then((data)=>{
        if (data.length != 0) {
            let resultCode = data['@oResult'];
            if( resultCode == error.Success )   {
                // 성공일 경우에만 
                switch (pricetype) 
                {
                    case type.Price.Gold:
                        if(userdata.point.gold >= cost)
                        {
                            userdata.point.gold -= cost;
                        }
                        break;
                    case type.Price.Film:
                        if(userdata.point.film >= cost)
                        {
                            userdata.point.film -= cost;
                        }
                        break;
                    case type.Price.Heart:
                        if(userdata.point.heart >= cost)
                        {
                            userdata.point.heart -= cost;
                        }
                        break;
                }
                let json = JSON.stringify(userdata);
                let json_data = Buffer.from(json, 'utf8').toString('base64');
                res.json({ klass : 'ActionCostResult', result: error.Success, data:json_data});
            }
            else {
                console.log("ActionCostResult - return value = %d", resultCode);
                res.json({ klass : 'ActionCostResult', result: error.Fail});
            }
        }
        else {
            console.log("ActionCostResult - return 3");
            res.json({ klass : 'ActionCostResult', result: error.Fail});
        }
    }).catch((err) => {
        console.error(err);
        res.json({ klass : 'ActionCostResult', result: error.Fail});
    })

}

function ResetStory(body,sess,res) {

    let data = Buffer.from(body.data, 'base64').toString('utf8');

    let revdata = JSON.parse(data);

    let userdata = sess.user.data;
    let chartype = revdata.chartype;

    let params = {
        member_id:sess.auth.memberId, 
        type:chartype,
    }
    userModal.ResetStory(params).then((data)=>{
        if (data.length != 0) {
            let resultCode = data['@oResult'];
            if( resultCode == error.Success )   {
                // 성공일 경우에만 

                userdata.resetcheck[chartype][0] = 1;

                let json = JSON.stringify(userdata);
                let json_data = Buffer.from(json, 'utf8').toString('base64');
                res.json({ klass : 'ActionResetStoryResult', result: error.Success, data:json_data});
            }
            else {
                console.log("ActionResetStoryResult - return value = %d", resultCode);
                res.json({ klass : 'ActionResetStoryResult', result: error.Fail});
            }
        }
        else {
            console.log("ActionResetStoryResult - return 3");
            res.json({ klass : 'ActionResetStoryResult', result: error.Fail});
        }
    }).catch((err) => {
        console.error(err);
        res.json({ klass : 'ActionResetStoryResult', result: error.Fail});
    })

}

function SaveEnding(body,sess,res) {

    let data = Buffer.from(body.data, 'base64').toString('utf8');

    let revdata = JSON.parse(data);

    let userdata = sess.user.data;
    let chartype = revdata.chartype;
    let scene_id = revdata.scene_id;

    let params = {
        member_id:sess.auth.memberId, 
        type:chartype,
        scene_id:scene_id,
    }
    userModal.SaveEnding(params).then((data)=>{
        if (data.length != 0) {
            let resultCode = data['@oResult'];
            if( resultCode == error.Success )   {
                // 성공일 경우에만 

                userdata.endingscene[chartype][userdata.endingscene[chartype].length] = scene_id;

                let json = JSON.stringify(userdata);
                let json_data = Buffer.from(json, 'utf8').toString('base64');
                res.json({ klass : 'ActionSaveEndingResult', result: error.Success, data:json_data});
            }
            else {
                console.log("ActionSaveEndingResult - return value = %d", resultCode);
                res.json({ klass : 'ActionSaveEndingResult', result: error.Fail});
            }
        }
        else {
            console.log("ActionSaveEndingResult - return 3");
            res.json({ klass : 'ActionSaveEndingResult', result: error.Fail});
        }
    }).catch((err) => {
        console.error(err);
        res.json({ klass : 'ActionSaveEndingResult', result: error.Fail});
    })

}


function LoginReward(body,sess,res) {
    let userdata = sess.user.data;
    let max_reward_count = type.MAX_LOGIN_REWARD;

    let params = {
        member_id:sess.auth.memberId, 
        max_reward_count:max_reward_count,
    }
    userModal.LoginReward(params).then((data)=>{
        if (data.length != 0) {
            let resultCode = data['@oResult'];
            
            // rewardCount 
            // -1 error 보상없음
            //  0 출석체크 보상 x 무료 재화만 추가
            //  else 출석체크 보상 및 무료 재화 추가
            let rewardCount = data['@oRewardCount'];

            if( resultCode == error.Success )   {
                // 성공일 경우에만 

                if(rewardCount == 0)
                {

                    if(userdata.point.film < type.Max_Free_Film)
                    {
                        userdata.point.film = type.Max_Free_Film;   
                    }

                    let json = JSON.stringify(userdata);
                    let json_data = Buffer.from(json, 'utf8').toString('base64');
                    res.json({ klass : 'ActionLoginRewardResult', result: error.Success, data:json_data, reward_count:rewardCount});
                }
                else if(rewardCount > 0)
                {
                    //
                    // 출석 보상에 따른 리워드
                    //
                    
                    
                    let tbDailyReward = tableManager.DailyReward.find(rewardCount);
                    let tbItem = tableManager.Item.find(tbDailyReward.item);

                    commonController.UserPointCreate(userdata, tbItem, tbDailyReward.count);

                    if(userdata.point.film < type.Max_Free_Film)
                    {
                        userdata.point.film = type.Max_Free_Film;   
                    }

                    if(rewardCount == 7)
                    {
                        tbDailyReward = tableManager.DailyReward.find(rewardCount + 1);
                        tbItem = tableManager.Item.find(tbDailyReward.item);
    
                        commonController.UserPointCreate(userdata, tbItem, tbDailyReward.count);
                    }

                    commonModal.UpdateUserPoint(sess.auth.memberId, userdata.point.gold, userdata.point.film, userdata.point.heart).then((data)=>
                    {
                        if (data.length != 0) {
                            let resultCode = data['@oResult'];
                            if( resultCode == error.Success )   {
                                // 성공일 경우에만 
                
                                let json = JSON.stringify(userdata);
                                let json_data = Buffer.from(json, 'utf8').toString('base64');
                                res.json({ klass : 'ActionLoginRewardResult', result: error.Success, data:json_data, reward_count:rewardCount});
                            }
                            else {
                                console.log("ActionLoginRewardResult - return value = %d", resultCode);
                                res.json({ klass : 'ActionLoginRewardResult', result: error.Fail});
                            }
                        }
                        else {
                            console.log("ActionLoginRewardResult - return 3");
                            res.json({ klass : 'ActionLoginRewardResult', result: error.Fail});
                        }
                    }).catch((err) => {
                        console.error(err);
                        res.json({ klass : 'ActionLoginRewardResult', result: error.Fail});
                    })
                }
            }
            else {
                console.log("ActionLoginRewardResult - return value = %d", resultCode);
                res.json({ klass : 'ActionLoginRewardResult', result: error.Fail, reward_count:rewardCount});
            }
        }
        else {
            console.log("ActionLoginRewardResult - return 3");
            res.json({ klass : 'ActionLoginRewardResult', result: error.Fail});
        }
    }).catch((err) => {
        console.error(err);
        res.json({ klass : 'ActionLoginRewardResult', result: error.Fail});
    })

}

module.exports = userController;