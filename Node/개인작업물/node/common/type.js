'use strict';

const fs = require('fs');
const path = require('path');

// 자료 구조 정의
exports = module.exports = {};

// 로그
exports.Log = {
    Level: {
        All: 0,
        Debug: 1,
        Infomation: 2,
        Warning: 3,
        Error: 4,
    }
};

exports.EndTutorial = 10109;
// 인증 종류
exports.AuthType = {
    None: 0,
    FaceBook: 1,
    Google: 2,
    GameCenter: 3,
    Device: 4,
    Min: 0,
    Max: 5
};

exports.Actor = {
    Kangtaejun: 0,
    Backhyeonseong: 1,
    Jeonjaemin: 2,
    Kimdongju: 3,
    Jeonseockhwan: 4,
    Special: 5,
};

exports.StartScene = {
    Kangtaejun: 10110,
    Backhyeonseong: 10200,
    Jeonjaemin: 10400,
    Kimdongju: 10500,
    Jeonseockhwan: 10300,
};


exports.QuizScene = {
    Kangtaejun: 10185,
    Backhyeonseong: 10275,
    Jeonseockhwan: 10375,
    Jeonjaemin: 10475,
    Kimdongju: 10575,
};

// 인증 상태
exports.AuthState = {
    Normal: 0,
    Block: 1,
    Unregister : 2
};

// 별명
exports.NickName = {
    Min: 3,
    Max: 20,
};


// 비용
exports.Price = {
    None: 0,        // 무료
    Gold: 1,        // 골드
    Heart: 2,       // 하트
    Film: 3,        // 필름
    Cash: 4,        // 현금
};

//아이템 종류
exports.ItemType = {
    Gold: 1,
    Heart: 2,
    Film: 3,
    Cloth: 10,
    Shose: 100,
    Accessories: 101,
    CGillust: 1000,

};

//상점 종류
exports.ShopType = {
    CashShop: 1,
    MyRoomShop: 2,
};

exports.MyRoomShopCategory = {
    NoShow: 0,
    Package: 1,
    NoPackage: 2,
}

// 최대 보유량 정의
exports.Max = {
    Mail: 200,
    Gold: 100000000,
    Film: 100,
};

exports.RANDOM_MAX = 65535;   // WORD MAX VALUE

exports.Max_Free_Film = 5;

exports.QuizCost = 2;

exports.Shop = {
    Type: {
        Google: 1,              // 구글 스토어
        One: 2,                 // 원 스토어
        Apple: 3                // 애플 스토어
    },
    Period: {                   // 기간제 상품
        None: 0,
        Use: 1
    },
    Product: {
        Post: 0,                // 우편 지급
        Immediate: 1,           // 즉시 지급
    }
};

exports.WorkingFolder = path.join(path.dirname(fs.realpathSync(__filename)), '..');
