var express = require('express');
var router = express.Router();
var mongojs = require('mongojs');

router.get('/', function(req, res, next) {
  	res.send('respond with a usage');
});
// 실시간 사용량
router.get('/realtimeUsage', function(req, res, next) {
  	res.render('usage/real_chart.ejs');
});

// 하루 사용량
router.get('/dayUsage', function(req, res, next) {
  	res.render('usage/day_chart.ejs', {
  		label:[1513638439000,1513648439000,1513658439000,1513668439000,1513678439000,1513688439000,1513698439000,1513702039000,1513705639000],
  		data:[6800, 7200, 7000,6800, 7200, 7000]
  	});
});

module.exports = router;
