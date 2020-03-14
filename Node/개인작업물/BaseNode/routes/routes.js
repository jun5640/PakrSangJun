'use strict';

var express = require('express');
const config = require('config');
var router = express.Router();
var bodyOption = { title: config.get('title') };
    

var PIXI = require('pixi.js');

//
// 초기 페이지
// 
router.get('/', function (req, res) {

   // document.body.appendChild(app.view);
 
// load the texture we need
    PIXI.loader.add('bunny', 'bunny.png').load((loader, resources) => {
 
    // This creates a texture from a 'bunny.png' image.
    const bunny = new PIXI.Sprite(resources.bunny.texture);
 
    // Setup the position of the bunny
    bunny.x = app.renderer.width / 2;
    bunny.y = app.renderer.height / 2;
 
    // Rotate around the center
    bunny.anchor.x = 0.5;
    bunny.anchor.y = 0.5;
 
    // Add the bunny to the scene we are building.
    app.stage.addChild(bunny);
 
    // Listen for frame updates
    app.ticker.add(() => {
         // each frame we spin the bunny around a bit
        bunny.rotation += 0.01;
    });
});

})

//
// 기타 모든 요청을 화이트 페이지로 처리합니다.
//
router.get('*', function (req, res) {
    res.render('Pages/error', bodyOption);
})

module.exports = router;
