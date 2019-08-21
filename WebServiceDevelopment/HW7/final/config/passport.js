var mysql = require('mysql');
var express = require('express');
var LocalStrategy = require('passport-local').Strategy
var client = mysql.createConnection({
	host : 'localhost',
	user : 'root',
	port : '3306',
	password : 'tmfl3fkdzk4',
	database : 'class_web'
});

module.exports = function(passport){
	// done(null, user); 호출시 user 객체를 전달받아 세션(req.session.passport.user)에 저장
	passport.serializeUser(function(user, done) {
        console.log(user.uid+" was Serialized");
        done(null, user.uid);
    });

	// 세션 정보를 실제 DB의 데이터와 비교,
	// 해당하는 유저 정보가 있으면 done의 두번째 인자를 req.user에 저장
	// 후에 req.user 사용하여 렌더링
    passport.deserializeUser(function(uid, done) {
        console.log(uid+" was Deserialized");
        client.query("SELECT * FROM users WHERE uid=?",[uid], function(err, user){
			done(err, user[0]);
		});
    });

    passport.use('signup', new LocalStrategy({
        usernameField : 'uid',
        passwordField : 'pw',
        passReqToCallback : true
    }, function(req, uid, pw, done) {
    	console.log(uid+" sign up");
    	client.query("SELECT * FROM users WHERE uid=?",[uid], function(err, user){
			if(err) {console.log(err); return done(err);}
			if(user[0]){
                return done(null, false, req.flash('signupMessage', '이메일이 존재합니다.'));
            }else{
            	client.query("INSERT INTO users (uid, password) VALUES(?,?)",[uid, pw], function(err, result){
        			var newUser = {'uid':uid, 'password':pw};
        			req.flash('signupMessage', null);
            		return done(null, newUser);
            	});
            }
		});
    }));

    passport.use('signin', new LocalStrategy({
            usernameField : 'uid',
            passwordField : 'pw',
            passReqToCallback : true
        },
        function(req, uid, pw, done) {
            console.log(uid+" sign in");
        	client.query("SELECT * FROM users WHERE uid=?",[uid], function(err, user){

                if (err)
                    return done(err);
                if (!user[0]){
                	console.log("no users found");
                    return done(null, false, req.flash('signinMessage', '사용자를 찾을 수 없습니다.'));
                }
                if (user[0].password != pw)
                    return done(null, false, req.flash('signinMessage', '비밀번호가 다릅니다.'));

                req.flash('signinMessage', null);
                return done(null, user[0]);
            });
        }));
};