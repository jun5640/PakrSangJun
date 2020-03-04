const config = require('config');
const path = require('path');
var domain = require('domain').create();
var engine = require('ejs-locals');
var ejs = require('ejs');
var bodyParser = require('body-parser');
var express = require('express');
var session = require('express-session');
var compression = require('compression');
var morgan = require('morgan');

//const dbPool = require("./lib/mysql.js")
//const memStore = require('./lib/memcached');
const type = require('./common/type.js');
var api = require('./routes/api.js');
var routes = require('./routes/routes.js');
var dbfunc = require('./lib/dbFunction');



domain.on('error', function (err) {
    console.error('error : ' + err);
});

domain.run(function () {
    console.log('BaseDB Server starting...');

    dbfunc.connectionCheck.then((data) =>{
        //console.log(data);
     }).catch((err) => {
         console.log(err);
     });

    // 웹서버 설정.
    var app = express();
    app.use(session({
        secret : 'BaseDBSecret',
        //store: memStore,
        resave : false,
        saveUninitialized : true,
        cookie: { secure: false, maxAge: 1 * 60 * 60 * 1000 } // 1시간
    }));
    app.use(compression());
    
    app.use(express.static(path.join(__dirname, 'public')));
    app.set('view engine', 'ejs');  // 렌러링 엔진 선택
    app.engine('ejs', engine);      // 렌더링 엔진 설정
    app.disable('x-powered-by');    // 헤더 비활성화

    let env = config.util.getEnv('NODE_ENV');
    console.log('Envronment : ' + env);

    // 로그 출력 
    if (config.get('log.level') <= type.Log.Level.Debug) {
        // 데이타를 json으로 취득 (application/json)
        app.use(bodyParser.json({
            // 데이터가 타당한지 검증하는 함수 
            verify: function (req, res, buf, encoding) {
                if (buf && buf.length) {
                    req.rawBody = buf.toString(encoding || 'utf8');
                } else {
                    req.rawBody = '';
                }
            }
        }));
        app.use(function (req, res, next) {
            var oldWrite = res.write,
                oldEnd = res.end;

            var chunks = [];

            res.write = function (chunk) {
                if (chunk != null && Buffer.isBuffer(chunk)) chunks.push(chunk);
                oldWrite.apply(res, arguments);
            };

            res.end = function (chunk) {
                if (chunk != null && Buffer.isBuffer(chunk)) chunks.push(chunk);
                res.body = Buffer.concat(chunks).toString('utf8');
                oldEnd.apply(res, arguments);
            };

            next();
        });
        morgan.token('date', function () {
            var now = new Date();
            return now.toLocaleString();
        });
        morgan.token('body', function (req, res) {
            if (req._body && res._hasBody) {
                return '{0} => {1}'.format(req.rawBody, res.body);
            } else {
                return '';
            }
        });
        app.use(morgan(':date [:remote-addr :method :url :status :res[content-length]] [:response-time ms] - :body'));
    } else {
        app.use(bodyParser.json());
    }
/*
    // connecting route to database
    app.use(function(req, res, next) {
        req.dbPool = dbPool;
        next();
    })
*/
    app.use('/', api);
    app.use('/', routes); 

    app.listen(config.get('port'), '0.0.0.0', function () {
        console.log('Server startup !');
    });
    
    process.stdin.resume(); // so the program will not close instantly
    
    function exitHandler(options, err) {
        if (options.cleanup) {
            console.log('Server stop !');
        }
        if (err) console.log(err.stack);
        if (options.exit) process.exit();
    }
    
    // do something when app is closing
    process.on('exit', exitHandler.bind(null, { cleanup: true }));
    
    // catches ctrl+c event
    process.on('SIGINT', exitHandler.bind(null, { exit: true }));
});
