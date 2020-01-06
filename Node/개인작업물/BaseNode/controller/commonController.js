'use strict';

const config = require('config');
const extension = require('../common/extension');
const error = require('../common/error');
const type = require('../common/type');
const storeModal = require("../model/storeModal");
const tableManager = require('../common/table');

const TRANS_KEY = 'trans:{0}';

var commonController = {
    UserPointCreate:UserPointCreate
}

function UserPointCreate(userdata, tbItem, count)  {
    console.log(">>> UserPointCreate, tbItem="+JSON.stringify(tbItem));

    let data = userdata;

    switch (tbItem.type) {
        case type.ItemType.Gold:
            data.point.gold += count;
            break;
        case type.ItemType.Heart:
            data.point.heart += count;
            break;
        case type.ItemType.Film:
            data.point.film += count;
            break;
    }
    return data;
}

module.exports = commonController;