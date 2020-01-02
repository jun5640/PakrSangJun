'use strict';

const path = require('path');
const fs = require('fs');
const bs = require("binary-search");
const config = require('../config.js');
const type = require('./type');

let tableFolder = path.join(type.WorkingFolder, config.table);

exports = module.exports = {};

//
// 사용하는 테이블 정의
//
var tables = [
    'Scene',
    'Shop',
    'MyRoomShop',
    'Product',
    'Item'
];


tables.forEach(function (_name_) {
    Object.defineProperty(exports, _name_, {
        value: {
            name: _name_,
            data: [],
            load: function () {
                let filePath = path.join(tableFolder, this.name.toLowerCase() + '.json');
                if (fs.existsSync(filePath)) {
                    this.data = JSON.parse(fs.readFileSync(filePath, 'utf8'));
                    this.data.sort(function (a, b) { return a.Id - b.Id; });
                    return true;
                }
                return false;
            },
            find: function (Id) {
                if (typeof Id === 'undefined') return; 
                let index = bs(this.data, Id, function (a, b) { return a.Id - b; });
                if (index >= 0) return this.data[index];
            },
            search: function (callback) {
                let result = [];
                this.data.forEach((value) => {
                    if (callback(value)) result.push(value);
                });

                if (result.length > 1) return result;
                else if (result.length > 0) return result[0];
            }
        }
    });
});

exports.Load = function () {
    var start = process.hrtime();
    tables.forEach(function (name) {
        if (config.log.level <= type.Log.Level.Debug) {
            var hrstart = process.hrtime();
            if (!exports[name].load()) console.error(name + ' load faild.');
            var hrend = process.hrtime(hrstart);
            console.log('%s load this table. (%ds %dms)', name, hrend[0], hrend[1] / 1000000);
        } else {
            if (!exports[name].load()) console.error(name + ' load faild.');
        }
    });
    var end = process.hrtime(start);

    if(config.log.level <= type.Log.Level.Infomation)
        console.log('Table load time : %ds %dms.', end[0], end[1] / 1000000);
}

exports.Reload = function () {
    var start = process.hrtime();
    tables.forEach(function (name) {
        if (config.log.level <= type.Log.Level.Debug) {
            var hrstart = process.hrtime();
            exports[name].data = [];
            if (!exports[name].load()) console.error(name + ' load faild.');
            var hrend = process.hrtime(hrstart);
            console.log('%s reload this table. (%ds %dms)', name, hrend[0], hrend[1] / 1000000);
        } else {
            exports[name].data = [];
            if (!exports[name].load()) console.error(name + ' load faild.');
        }
    });
    var end = process.hrtime(start);
    if (config.log.level <= type.Log.Level.Infomation)
        console.log('Table reload time : %ds %dms.', end[0], end[1] / 1000000);
}

//
// 테이블 로딩.
//
exports.Load();
