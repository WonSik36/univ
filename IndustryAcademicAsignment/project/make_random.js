// DB에 임의의 값을 저장하는 프로그램
"use strict";
var mongojs = require('mongojs');

var db = mongojs('localhost/test', ['realtime_1']);

setInterval(insertRandom, 5000);

function insertRandom(){
	var input = Math.floor(Math.random()*900) + 100;
	var time = new Date().getTime();

	db.realtime_1.insert({'timestamp':time, 'activePower':input, 'positiveEnergy':input*input});
	console.log("Insert time: "+time+", value1: "+input + " value2: "+input*input);
}