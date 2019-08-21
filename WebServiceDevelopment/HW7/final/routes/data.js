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

router.get('/', function(req, res, next) {
  res.send('wrong direction');
});

router.get('/week', function(req, res, next) {
  res.send('wrong direction');
});

router.get('/month', function(req, res, next) {
  	var month=new Date().getMonth() + 1;
	var year=new Date().getFullYear();
	if(req.params.month){
		month = parseInt(req.params.month)-1;
	}
	if(req.params.year){
		year = parseInt(req.params.year);
	}
	console.log("data requirement:",year,month);
	client.query(util.uid_query,res.locals.userInformation, function(err, result){
			var total=0;
			var uid = result[0].id;
			client.query(util.month_table_query, [uid,year,month],function(err, result){
				console.log(result);
				if(err){
					res.send(err);
				}else if(!result){
					res.redirect('../pages/insert');
				}else{
					res.send(result);
				}
			});
	});
});

router.get('/year', function(req, res, next) {
  res.send('wrong direction');
});

module.exports = router;
