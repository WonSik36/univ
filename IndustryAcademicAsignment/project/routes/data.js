var express = require('express');
var router = express.Router();
var mongojs = require('mongojs');
// DB서버와 웹서버가 동일한 경우
//var db = mongojs('localhost/test', ['realtime_1']);
//원격 DB서버 접속방법
var db = mongojs('wonsik:energy@192.168.0.34:27017/Enertalk', ['realtime_1','realtime_2','realtime_3','realtime_4','realtime_5']);

router.get('/', function(req, res, next) {
  res.send('respond with a data');
});

// 1층 사용량
router.get('/1/:period', function(req, res, next) {
	var period = req.params.period

	//현재시간 보다 60초전 시간 구함
	var timePeriod = 60000 // 60 seconds
	var time = new Date().getTime() - timePeriod;

	console.log("site:1, period: "+period + ", timestamp: "+time);
	// db에 데이터 요청(60초 전부터 현재까지 데이터)
	db.realtime_1.find({"timestamp":{$gte: time}}, {"_id":false, "timestamp":true, "activePower": true}).sort({'timestamp':1}, function(error, data){
		if(error == true){
			console.log(error);
		}else{
			/* chart.js 폼에 맞게 배열 생성
			chart.js 에서는 데이터가 {(x1,y1), (x2,y2), ...} 형식이 아닌
			{x1,x2,x3,...}, {y1,y2,y3,...} 형식임
			*/
			var timestamp = [];
			var value = [];

			for(var i=0; i<data.length;i++){
	        	var obj = data[i];
	        	timestamp.push(obj.timestamp);
	        	value.push(obj.activePower/1000000);
	        }
	        var form = {'timestamp':timestamp, 'value': value};
			res.send(form);
		}
	});
});

// 2층 사용량
router.get('/2/:period', function(req, res, next) {
	var period = req.params.period

	var timePeriod = 60000 // 60 seconds
	var time = new Date().getTime() - timePeriod;

	console.log("site:2, period: "+period + ", timestamp: "+time);

	db.realtime_2.find({"timestamp":{$gte: time}}, {"_id":false, "timestamp":true, "activePower": true}).sort({'timestamp':1}, function(error, data){
		if(error == true){
			console.log(error);
		}else{
			var timestamp = [];
			var value = [];

			for(var i=0; i<data.length;i++){
	        	var obj = data[i];
	        	timestamp.push(obj.timestamp);
	        	value.push(obj.activePower);
	        }
	        var form = {'timestamp':timestamp, 'value': value};
			res.send(form);
		}
	});
});

// 3층 사용량
router.get('/3/:period', function(req, res, next) {
	var period = req.params.period

	var timePeriod = 60000 // 60 seconds
	var time = new Date().getTime() - timePeriod;

	console.log("site:3, period: "+period + ", timestamp: "+time);

	db.realtime_3.find({"timestamp":{$gte: time}}, {"_id":false, "timestamp":true, "activePower": true}).sort({'timestamp':1}, function(error, data){
		if(error == true){
			console.log(error);
		}else{
			var timestamp = [];
			var value = [];

			for(var i=0; i<data.length;i++){
	        	var obj = data[i];
	        	timestamp.push(obj.timestamp);
	        	value.push(obj.activePower);
	        }
	        var form = {'timestamp':timestamp, 'value': value};
			res.send(form);
		}
	});
});

// 4층 사용량
router.get('/4/:period', function(req, res, next) {
	var period = req.params.period

	var timePeriod = 60000 // 60 seconds
	var time = new Date().getTime() - timePeriod;

	console.log("site:4, period: "+period + ", timestamp: "+time);

	db.realtime_4.find({"timestamp":{$gte: time}}, {"_id":false, "timestamp":true, "activePower": true}).sort({'timestamp':1}, function(error, data){
		if(error == true){
			console.log(error);
		}else{
			var timestamp = [];
			var value = [];

			for(var i=0; i<data.length;i++){
	        	var obj = data[i];
	        	timestamp.push(obj.timestamp);
	        	value.push(obj.activePower);
	        }
	        var form = {'timestamp':timestamp, 'value': value};
			res.send(form);
		}
	});
});

// 5층 사용량
router.get('/5/:period', function(req, res, next) {
	var period = req.params.period

	var timePeriod = 60000 // 60 seconds
	var time = new Date().getTime() - timePeriod;

	console.log("site:5, period: "+period + ", timestamp: "+time);

	db.realtime_5.find({"timestamp":{$gte: time}}, {"_id":false, "timestamp":true, "activePower": true}).sort({'timestamp':1}, function(error, data){
		if(error == true){
			console.log(error);
		}else{
			var timestamp = [];
			var value = [];

			for(var i=0; i<data.length;i++){
	        	var obj = data[i];
	        	timestamp.push(obj.timestamp);
	        	value.push(obj.activePower);
	        }
	        var form = {'timestamp':timestamp, 'value': value};
			res.send(form);
		}
	});
});

module.exports = router;
