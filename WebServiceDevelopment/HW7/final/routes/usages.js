var express = require('express');
var router = express.Router();
var util = require('../config/util');
var mysql = require('mysql');
var client = mysql.createConnection({
	host : 'localhost',
	user : 'root',
	port : '3306',
	password : 'tmfl3fkdzk4',
	database : 'class_web'
});

// -------------- router part ----------------


router.get('/', function(req, res, next){
	res.redirect('/usages/month_usages');
});

router.get('/week_usages', util.isLoggedIn, function(req, res, next) {
	res.render('usages/week_usages.ejs', {user: res.locals.userInformation, total: 20000, data: [1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,30,31]});
});

router.get('/week_usages_pie', util.isLoggedIn, function(req, res, next) {
	res.render('usages/week_usages_pie.ejs', {user: res.locals.userInformation});
});

router.get('/month_usages', util.isLoggedIn, function(req, res, next) {
	var month=new Date().getMonth() + 1;
	var year=new Date().getFullYear();
	if(req.params.month){
		month = parseInt(req.params.month)-1;
	}

	if(req.params.year){
		year = parseInt(req.params.year);
	}
	client.query(util.uid_query,res.locals.userInformation, function(err, result){
			var total=0;
			var uid = result[0].id;
			client.query(util.month_total_query,[uid,year,month],function(err,result){
				if(err){
					res.send(err);
				}else if(!result){
					res.redirect('../pages/insert');
				}else{
					total = result[0].total;
				}
			});
			client.query(util.month_bar_query, [uid,year,month],function(err, result){
				console.log(result);
				if(err){
					res.send(err);
				}else if(!result){
					res.redirect('../pages/insert');
				}else{
					console.log(uid,year,month);
					var labels=[], datas=[];

					for(var i=0;i<result.length;i++){
						labels.push(result[i].day);
						datas.push(result[i].total);
					}

					res.render('usages/month_usages.ejs', {user: uid, total: total, data: datas, label: labels, message: month+"월"});
				}
			});
	});
});

router.get('/month_usages_pie', util.isLoggedIn, function(req, res, next) {
	var month=new Date().getMonth() + 1;
	var year=new Date().getFullYear();
	if(req.params.month){
		month = parseInt(req.params.month)-1;
	}

	if(req.params.year){
		year = parseInt(req.params.year);
	}
	client.query(util.uid_query,res.locals.userInformation, function(err, result){
			var total=0;
			var uid = result[0].id;

			client.query(util.month_total_query,[uid,year,month],function(err,result){
				if(err){
					res.send(err);
				}else if(!result){
					res.redirect('../pages/insert');
				}else{
					total = result[0].total;
				}
			});
			client.query(util.month_pie_query, [uid,year,month],function(err, result){
				console.log(result);
				if(err){
					res.send(err);
				}else if(!result){
					res.redirect('../pages/insert');
				}else{
					console.log("uid: ",uid,"year",year,"month",month);
					var labels=[], datas=[];

					for(var i=0;i<result.length;i++){
						labels.push(result[i].class);
						datas.push(result[i].total);
					}

					res.render('usages/month_usages_pie.ejs', {user: uid, total: total, data: datas, label: labels, message: month+"월"});
				}
			});
	});
});

router.get('/week_usages', util.isLoggedIn, function(req, res, next) {
	res.render('usages/week_usages.ejs', {user: res.locals.userInformation});
});

router.get('/week_usages_pie', util.isLoggedIn, function(req, res, next) {
	res.render('usages/week_usages_pie.ejs', {user: res.locals.userInformation});
});

module.exports = router;
