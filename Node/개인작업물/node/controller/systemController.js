'use strict';

const extension = require('../common/extension');
const error = require('../common/error');
const type = require('../common/type');
const systemModal = require("../model/systemModal");
const userModal = require("../model/userModal");
var userController = require('./userController');

var systemController = {
    UserSearch:UserSearch,
    UserDataDetails:UserDataDetails
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
        data: userController.Create(),
    };   
    
    // account
    //let account_data = JSON.parse(data.account);
    //user.account_data = account_data;
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
    user.data.favor.passion = user_data.passion;
    user.data.favor.happy = user_data.happy;

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

    return user;
}

function UserSearch(body, sess, res)  {
    if (!body.hasOwnProperty('firstName') || !body.hasOwnProperty('lastName')) {
        console.log("System - UserSearch - return 1");
        res.json({ result: error.Fail });
        return;
    }

    let firstName = body.firstName.trim();
    let lastName = body.lastName.trim();
    if (extension.IsEmpty(firstName) || extension.IsBlank(lastName)) {
        console.log("System - UserSearch - return 2");
        res.json({ result: error.Fail });
        return;
    }

    systemModal.UserSearch(firstName, lastName).then((data)=>{
        console.log(data);
        if (data.length != 0) {
            res.json({ result: error.Success, users: data });
            /*
            let resultCode = data['@oResult'];
            if( resultCode == error.Success )   {
                let set_userdata = setting_userdata(JSON.parse(data['@oUserData']));
                console.log(set_userdata);
                let json = JSON.stringify(set_userdata.data);
                //console.log(json_data);    
                res.json({ result: error.Success, users: set_userdata });
            }
            else {
                console.log("System - UserSearch - return 3");
                res.json({ result: error.Fail });    
            }
            */
        }
        else {
            console.log("System - UserSearch - return 3");
            res.json({ result: error.Fail });        
        }
    }).catch((err) => {
        console.log("query in return");
        console.error(err);
        res.json({ result: error.Fail });
    })
}

function UserDataDetails(body, sess, res)  {
    if (!body.hasOwnProperty('Id') ) {
        console.log("System - UserDataDetails - return 1");
        res.json({ result: error.Fail });
        return;
    }

    let member_id = body.Id;
    if (extension.IsEmpty(member_id)) {
        console.log("System - UserDataDetails - return 2");
        res.json({ result: error.Fail });
        return;
    }

    userModal.UserConnect(member_id).then((data)=>{
        console.log(data);
        if (data.length != 0) {
            //res.json({ result: error.Success, users: data });
            let resultCode = data['@oResult'];
            if( resultCode == error.Success )   {
                let set_userdata = setting_userdata(JSON.parse(data['@oUserData']));
                console.log(set_userdata);
                let json = JSON.stringify(set_userdata.data);
                //console.log(json_data);    
                res.json({ result: error.Success, data: set_userdata });
            }
            else {
                console.log("System - UserDataDetails - return 3");
                res.json({ result: error.Fail });    
            }
        }
        else {
            console.log("System - UserDataDetails - return 3");
            res.json({ result: error.Fail });        
        }
    }).catch((err) => {
        console.log("query in return");
        console.error(err);
        res.json({ result: error.Fail });
    })
}

module.exports = systemController;