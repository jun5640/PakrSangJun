var db = require('../lib/database');
var dbFunc = require('../lib/dbFunction');

var userModel = {
    StoryEnd:StoryEnd,
    UserConnect:UserConnect,
    CharSelect:CharSelect,
    CmdInsertQuery:CmdInsertQuery,
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

function UserConnect(member_id) {
    return new Promise((resolve,reject) => {
        let sql = `SET @oResult=0, @oUserData='';`;
        sql += `CALL sp_load_userdata (?,@oResult,@oUserData);`;
        sql += `select @oResult,@oUserData;`;
        db.query(sql, [member_id], function (error, rows, fields) {
            if(!!error) {
                dbFunc.connectionRelease;
                reject(error);
            } else {
                dbFunc.connectionRelease;
                let result = {};
                rows.forEach(element => {
                    if(element.constructor == Array)    {
                        result = element[0];
                    }
                });
                resolve(result);
            }
        });
    });
}

function StoryEnd(params) {
    return new Promise((resolve,reject) => {
        let sql = `SET @oResult=0;`;
        sql += `CALL sp_story_end (?,?,?,?,?,?,@oResult);`;
        sql += `select @oResult;`;
        db.query(sql, [params.member_id, params.film, params.cur_story, params.actor_id, params.scene_id, params.tutorial_clear], function (error, rows, fields) {
            if(!!error) {
                dbFunc.connectionRelease;
                reject(error);
            } else {
                dbFunc.connectionRelease;
                let result = {};
                rows.forEach(element => {
                    if(element.constructor == Array)    {
                        result = element[0];
                    }
                });
                resolve(result);
            }
        });
    });
}

function CharSelect(params) {
    return new Promise((resolve,reject) => {
        let sql = `SET @oResult=0;`;
        sql += `CALL sp_char_select (?,?,?,@oResult);`;
        sql += `select @oResult;`;
        db.query(sql, [params.member_id, params.cur_story, params.actor_id], function (error, rows, fields) {
            if(!!error) {
                dbFunc.connectionRelease;
                reject(error);
            } else {
                dbFunc.connectionRelease;
                let result = {};
                rows.forEach(element => {
                    if(element.constructor == Array)    {
                        result = element[0];
                    }
                });
                resolve(result);
            }
        });
    });
}

function CmdInsertQuery(cmd_query_str) {
    return new Promise((resolve,reject) => {
        db.query(cmd_query_str, function (error, rows, fields) {
            if(!!error) {
                dbFunc.connectionRelease;
                reject(error);
            } else {
                dbFunc.connectionRelease;
                resolve(rows);
            }
        });
    });
}

function NameChange(params) {
    return new Promise((resolve,reject) => {
        let sql = `SET @oResult=0;`;
        sql += `CALL sp_name_change (?,?,?,@oResult);`;
        sql += `select @oResult;`;
        db.query(sql, [params.member_id, params.firstName, params.lastName], function (error, rows, fields) {
            if(!!error) {
                dbFunc.connectionRelease;
                reject(error);
            } else {
                dbFunc.connectionRelease;
                let result = {};
                rows.forEach(element => {
                    if(element.constructor == Array)    {
                        result = element[0];
                    }
                });
                resolve(result);
            }
        });
    });
}

function StartQuiz(params) {
    return new Promise((resolve,reject) => {
        let sql = `SET @oResult=0;`;
        sql += `CALL sp_start_quiz (?,?,@oResult);`;
        sql += `select @oResult;`;
        db.query(sql, [params.member_id, params.heart], function (error, rows, fields) {
            if(!!error) {
                dbFunc.connectionRelease;
                reject(error);
            } else {
                dbFunc.connectionRelease;
                let result = {};
                rows.forEach(element => {
                    if(element.constructor == Array)    {
                        result = element[0];
                    }
                });
                resolve(result);
            }
        });
    });
}

function FinishQuiz(params) {
    return new Promise((resolve,reject) => {
        let sql = `SET @oResult=0;`;
        sql += `CALL sp_finish_quiz (?,?,?,@oResult);`;
        sql += `select @oResult;`;
        db.query(sql, [params.member_id, params.actor_id, params.quiz_id], function (error, rows, fields) {
            if(!!error) {
                dbFunc.connectionRelease;
                reject(error);
            } else {
                dbFunc.connectionRelease;
                let result = {};
                rows.forEach(element => {
                    if(element.constructor == Array)    {
                        result = element[0];
                    }
                });
                resolve(result);
            }
        });
    });
}

function ChangeWear(params) {
    return new Promise((resolve,reject) => {
        let sql = `SET @oResult=0;`;
        sql += `CALL sp_change_wear (?,?,?,?,@oResult);`;
        //sql += `CALL sp_change_wear_lists (?,?,@oResult);`;
        sql += `select @oResult;`;
        //db.query(sql, [params.member_id, params.lists_str], function (error, rows, fields) {
        db.query(sql, [params.member_id, params.cloth, params.shoes, params.accessary], function (error, rows, fields) {    
            if(!!error) {
                dbFunc.connectionRelease;
                reject(error);
            } else {
                dbFunc.connectionRelease;
                let result = {};
                rows.forEach(element => {
                    if(element.constructor == Array)    {
                        result = element[0];
                    }
                });
                resolve(result);
            }
        });
    });
}

function Favor(params) {
    return new Promise((resolve,reject) => {
        let sql = `SET @oResult=0;`;
        sql += `CALL sp_update_favor (?,?,?,?,@oResult);`;
        sql += `select @oResult;`;
        db.query(sql, [params.actor_id, params.member_id, params.happy_pt, params.passion_pt], function (error, rows, fields) {
            if(!!error) {
                dbFunc.connectionRelease;
                reject(error);
            } else {
                dbFunc.connectionRelease;
                let result = {};
                rows.forEach(element => {
                    if(element.constructor == Array)    {
                        result = element[0];
                    }
                });
                resolve(result);
            }
        });
    });
}


function Cost(params){
    return new Promise((resolve,reject) => {
        let sql = `SET @oResult=0;`;
        sql += `CALL sp_update_cost (?,?,?,@oResult);`;
        sql += `select @oResult;`;
        db.query(sql, [params.member_id, params.type, params.cost], function (error, rows, fields) {
            if(!!error) {
                dbFunc.connectionRelease;
                reject(error);
            } else {
                dbFunc.connectionRelease;
                let result = {};
                rows.forEach(element => {
                    if(element.constructor == Array)    {
                        result = element[0];
                    }
                });
                resolve(result);
            }
        });
    });
}


function ResetStory(params){
    return new Promise((resolve,reject) => {
        let sql = `SET @oResult=0;`;
        sql += `CALL sp_story_reset (?,?,@oResult);`;
        sql += `select @oResult;`;
        db.query(sql, [params.member_id, params.type], function (error, rows, fields) {
            if(!!error) {
                dbFunc.connectionRelease;
                reject(error);
            } else {
                dbFunc.connectionRelease;
                let result = {};
                rows.forEach(element => {
                    if(element.constructor == Array)    {
                        result = element[0];
                    }
                });
                resolve(result);
            }
        });
    });
}

function SaveEnding(params){
    return new Promise((resolve,reject) => {
        let sql = `SET @oResult=0;`;
        sql += `CALL sp_story_save_ending (?,?,?,@oResult);`;
        sql += `select @oResult;`;
        db.query(sql, [params.member_id, params.type, params.scene_id], function (error, rows, fields) {
            if(!!error) {
                dbFunc.connectionRelease;
                reject(error);
            } else {
                dbFunc.connectionRelease;
                let result = {};
                rows.forEach(element => {
                    if(element.constructor == Array)    {
                        result = element[0];
                    }
                });
                resolve(result);
            }
        });
    });
}

function LoginReward(params){
    return new Promise((resolve,reject) => {
        let sql = `SET @oResult=0, @oRewardCount=0;`;
        sql += `CALL sp_login_reward (?,?,@oResult,@oRewardCount);`;
        sql += `select @oResult,@oRewardCount;`;
        db.query(sql, [params.member_id, params.max_reward_count], function (error, rows, fields) {
            if(!!error) {
                dbFunc.connectionRelease;
                reject(error);
            } else {
                dbFunc.connectionRelease;
                let result = {};
                rows.forEach(element => {
                    if(element.constructor == Array)    {
                        result = element[0];
                    }
                });
                resolve(result);
            }
        });
    });
}
  
module.exports = userModel;