'use strict';

var express = require('express');
const config = require('config');

var router = express.Router();

var bodyOption = { title: config.get('title') };
    
//
// 초기 페이지
// 
router.get('/', function (req, res) {
    res.render('Pages/index', bodyOption);
})

//
// 기타 모든 요청을 화이트 페이지로 처리합니다.
//
router.get('*', function (req, res) {
    res.render('Pages/error', bodyOption);
})

module.exports = router;
