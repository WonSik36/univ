// 데이터 수를 검증하는 테스트 프로그램
"use strict";
var mongojs = require('mongojs');
var moment = require('moment');
var async = require('async');
var db = mongojs('localhost/test', ['realtime_1','realtime_2','realtime_3','realtime_4','realtime_5']);
//원격 DB서버 접속방법
//var db = mongojs('wonsik:energy@192.168.0.21:27017/Enertalk', ['realtime_1','realtime_2','realtime_3','realtime_4','realtime_5']);

// 콜렉션 배열
var cols = [db.realtime_1, db.realtime_2, db.realtime_3, db.realtime_4, db.realtime_5];

// 현재 시간
var now = moment();

// 현재 기준 시간
const before_1_hour = moment().subtract(1, 'hours');
const before_3_hours = moment().subtract(3, 'hours');
const before_6_hours = moment().subtract(6, 'hours');
const before_12_hours = moment().subtract(12, 'hours');
const before_1_day = moment().subtract(1, 'days');
const before_1_week = moment().subtract(1, 'weeks');
const before_1_month = moment().subtract(1, 'months');

// 기준 개수
const period = 5; // second
const number_1_hour = 1*3600/period;
const number_3_hours = 3*3600/period;
const number_6_hours = 6*3600/period;
const number_12_hours = 12*3600/period;
const number_1_day = 1*24*3600/period;
const number_1_week = 1*7*24*3600/period;
const number_1_month = (now.format("X")-before_1_month.format("X"))/period;

// 시간에 따른 층별 개수 배열
const count_1_hour = new Array(cols.length); count_1_hour.fill(0);
const count_3_hours = new Array(cols.length); count_3_hours.fill(0);
const count_6_hours = new Array(cols.length); count_6_hours.fill(0);
const count_12_hours = new Array(cols.length); count_12_hours.fill(0);
const count_1_day = new Array(cols.length); count_1_day.fill(0);
const count_1_week = new Array(cols.length); count_1_week.fill(0);
const count_1_month = new Array(cols.length); count_1_month.fill(0);

// DB로 데이터 검색은 비동기방식이므로 async 모듈을 이용하여 해결한다.
// async.series 함수를 이용하여 비동기 함수를 차례차례 실행할수 있다.
//
//
var tasks = [
	// 현재로부터 1시간동안 데이터 개수 요청
	function(callback){
		var searched = 0;
		// 지역변수로서의 특징을 가지은 let을 사용
		for(let i=0;i<cols.length;i++){
			cols[i].find({"timestamp":{$gte: Number(before_1_hour.format("x"))}}).count(function(err, data){
				if(err){
					console.log(err);
				}else{
					count_1_hour[i] = data;
					if(++searched == cols.length)
						callback(null)
				}
			});
		}
	},
	// 현재로부터 3시간동안 데이터 개수 요청
	function(callback){
		var searched = 0;
		for(let i=0;i<cols.length;i++){
			cols[i].find({"timestamp":{$gte: Number(before_3_hours.format("x"))}}).count(function(err, data){
				if(err){
					console.log(err);
				}else{
					count_3_hours[i] = data;
					if(++searched == cols.length)
						callback(null)
				}
			});
		}
	},
	// 현재로부터 6시간동안 데이터 개수 요청
	function(callback){
		var searched = 0;
		for(let i=0;i<cols.length;i++){
			cols[i].find({"timestamp":{$gte: Number(before_6_hours.format("x"))}}).count(function(err, data){
				if(err){
					console.log(err);
				}else{
					count_6_hours[i] = data;
					if(++searched == cols.length)
						callback(null)
				}
			});
		}
	},
	// 현재로부터 12시간동안 데이터 개수 요청
	function(callback){
		var searched = 0;
		for(let i=0;i<cols.length;i++){
			cols[i].find({"timestamp":{$gte: Number(before_12_hours.format("x"))}}).count(function(err, data){
				if(err){
					console.log(err);
				}else{
					count_12_hours[i] = data;
					if(++searched == cols.length)
						callback(null)
				}
			});
		}
	},
	// 현재로부터 하루동안 데이터 개수 요청
	function(callback){
		var searched = 0;
		for(let i=0;i<cols.length;i++){
			cols[i].find({"timestamp":{$gte: Number(before_1_day.format("x"))}}).count(function(err, data){
				if(err){
					console.log(err);
				}else{
					count_1_day[i] = data;
					if(++searched == cols.length)
						callback(null)
				}
			});
		}
	},
	// 현재로부터 한주동안 데이터 개수 요청
	function(callback){
		var searched = 0;
		for(let i=0;i<cols.length;i++){
			cols[i].find({"timestamp":{$gte: Number(before_1_week.format("x"))}}).count(function(err, data){
				if(err){
					console.log(err);
				}else{
					count_1_week[i] = data;
					if(++searched == cols.length)
						callback(null)
				}
			});
		}
	},
	// 현재로부터 한달동안 데이터 개수 요청
	function(callback){
		var searched = 0;
		for(let i=0;i<cols.length;i++){
			cols[i].find({"timestamp":{$gte: Number(before_1_month.format("x"))}}).count(function(err, data){
				if(err){
					console.log(err);
				}else{
					count_1_month[i] = data;
					if(++searched == cols.length){
						db.close();
						callback(null)
					}
				}
			});
		}
	},
	function(callback){
		// 배열이 모두 채워졌다면
		// 문장 설정
		var one_hour = "1 hour: "+number_1_hour;
		for(let i=0;i<5;i++){
			one_hour = one_hour+" "+count_1_hour[i];
		}
		var three_hours = "3 hours: "+number_3_hours;
		for(let i=0;i<5;i++){
			three_hours = three_hours+" "+count_3_hours[i];
		}
		var six_hours = "6 hours: "+number_6_hours;
		for(let i=0;i<5;i++){
			six_hours = six_hours+" "+count_6_hours[i];
		}
		var twelve_hours = "12 hours: "+number_12_hours;
		for(let i=0;i<5;i++){
			twelve_hours = twelve_hours+" "+count_12_hours[i];
		}
		var one_day = "1 day: "+number_1_day;
		for(let i=0;i<5;i++){
			one_day = one_day+" "+count_1_day[i];
		}
		var one_week = "1 week: "+number_1_week;
		for(let i=0;i<5;i++){
			one_week = one_week+" "+count_1_week[i];
		}
		var one_month = "1 month: "+number_1_month;
		for(let i=0;i<5;i++){
			one_month = one_month+" "+count_1_month[i];
		}

		// 출력
		console.log("Start test1 code");
		console.log("        criteria   1st    2nd    3rd    4th    5th");
		console.log(one_hour);
		console.log(three_hours);
		console.log(six_hours);
		console.log(twelve_hours);
		console.log(one_day);
		console.log(one_week);
		console.log(one_month);
	}
]
async.series(tasks);