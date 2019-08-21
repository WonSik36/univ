var mysql = require('mysql');
var express = require('express');
var router = express.Router();
var passport = require('passport');
var util = require('../config/util');

var client = mysql.createConnection({
	host : 'localhost',
	user : 'root',
	port : '3306',
	password : 'tmfl3fkdzk4',
	database : 'class_web'
});

router.get('/signin', function(req, res, next) {
	res.render('pages/signin.ejs', {'message' : req.flash('signinMessage')});
});

router.post('/signin', passport.authenticate('signin', {
	successRedirect: '../usages/month_usages',
	failureRedirect: 'signin',
	failureFlash : true
}));

router.get('/signup', function(req, res, next) {
	res.render('pages/signup.ejs', {'message' : req.flash('signupMessage')});
});

router.post('/signup', passport.authenticate('signup', {
	successRedirect: '../usages/month_usages',
	failureRedirect: 'signup',
	failureFlash : true
}));

router.get('/insert', util.isLoggedIn, function(req, res, next) {
	res.render('pages/insert.ejs');
});

router.post('/insert', function(req, res, next) {
	var body = req.body;
	client.query(util.uid_query,res.locals.userInformation, function(err, result){
		var uid = result[0].id;
		var date = body.year+"-"+body.month+"-"+body.day;
		client.query(util.insertQuery,[uid,date,body.money,body.detail,body.class]);

		res.redirect('../usages/month_usages');
	});
});

router.get('/edit/:id', util.isLoggedIn, function(req, res, next) {
	client.query(util.uid_query,res.locals.userInformation, function(err, result){
		if(result[0]){
			var uid = result[0].id;
			client.query(util.searchQuery,[req.params.id,uid], function(error, result){
					res.render('pages/edit.ejs', {money: result[0].money,detail: result[0].detail});
			});
		}
	});
});

router.post('/edit/:id', function(req, res, next) {
	client.query(util.uid_query,res.locals.userInformation, function(err, result){
		var body = req.body;
		var uid = result[0].id;
		var date = body.year+"-"+body.month+"-"+body.day;
		client.query(util.updateQuery,[date,body.money,body.detail,body.class,req.params.id, uid]);

		res.redirect('/usages/month_usages');
	});
});

router.get('/delete/:id', util.isLoggedIn, function(req, res, next) {
	client.query(util.uid_query,res.locals.userInformation, function(err, result){
		var uid = result[0].id;
		client.query(util.deleteQuery,[req.params.id, uid]);
		res.redirect('/usages/month_usages');
	});
});

router.get('/logout', function(req, res, next) {
	req.logout();
	res.redirect('/');
});

module.exports = router;
