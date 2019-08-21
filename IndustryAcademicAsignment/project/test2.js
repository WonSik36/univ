// 데이터 타당성을 확인하는 검증 프로그램
// 에너톡 클라우드에서 한달동안 시간당 사용량을 구한다
// 디비에 저장된 시간당 사용량을 구한다
// 둘을 비교한다
"use strict";
// access token 입력
var access_token = "1cc8cf336708c58272c468de9e3a068c67270b266bae7c1993d7d75e23d713ebf71cb8bd268505ac15f132534806afcd1c574eda6013522afc596075f7a3f5c7";
var mongojs = require('mongojs');
var moment = require('moment');
var request = require('request');
//var db = mongojs('localhost/test', ['realtime_1']);
//원격 db 접속
var db = mongojs('wonsik:energy@192.168.0.34:27017/Enertalk', ['realtime_1','realtime_2','realtime_3','realtime_4','realtime_5']);

// 콜렉션 배열
var cols = [db.realtime_1, db.realtime_2, db.realtime_3, db.realtime_4, db.realtime_5];

//요청 url
var curl1 = "https://api2.enertalk.com/sites/";
var curl2 = "/usages/periodic?period=hour";
var floor = ['d4996c06','737e0393','7f0fee20','a511f50a','a4b291b2'];
var start = "&start=";
var end = "&end=";

//cArr: 에너톡 클라우드 데이터
//dbArr: 자체 스토리지 데이터
var cArr = new Array(floor.length);
var dbArr  = new Array();

//set start time and end time
var sTime = moment().subtract(1, 'months');
sTime.set({'minute':0, 'second':0, 'millisecond':0});
var sTimestamp = sTime.format("x"); //millisecond
var eTime = moment().set({'minute':0, 'second':0, 'millisecond':0});
var eTimestamp = eTime.format("x"); //millisecond

// dbArr에 비동기적으로 site수에 따른 배열을 넣어줌
var setConfig = () => new Promise((resolve)=>{
	for(let i=0;i<floor.length;i++){
		dbArr.push([]);
	}
	resolve();
});

// Enertalk cloud 에 한시간 주기 한달간 사용량 요청
var getUsageCloud = () => new Promise(function(resolve, reject){
	let headers = {
		'Authorization':'Bearer '+access_token,
		'accept-version':'2.0.0'
	};

	// get usage from cloud
	let j=0; //for loop -> global
	for(let i=0; i<floor.length; i++){
		let options = {
			url: curl1+floor[i]+curl2+start+sTimestamp+end+eTimestamp,
			method: 'GET',
			headers: headers
		};
		request(options, function (error,response,body) {
			if (!error && response.statusCode == 200){
				cArr[i] = JSON.parse(body)["items"];
				//console.log(cArr[i]);
				//5층의 정보를 모두 받아온 경우 함수 종료
				if(++j == floor.length){
					console.log("getUsageCloud Done");
					resolve();
				}
			}else{
				reject(Error(body));
			}
		});
	}
});

// 자체 스토리지에 한시간 주기 한달간 사용량 요청
var getUsageDB = () => new Promise(function(resolve,reject){
	// 예상되는 한달동안 데이터 수
	let k1 = (Number(eTimestamp)-Number(sTimestamp))/3600000;
	// 층수
	let k2 = floor.length;
	//let j = new Array(5); j.fill(0);
	let searched1 = 0;
	for(let i=0;i<floor.length;i++){
		let searched2 = 0;
		for(let t=Number(sTimestamp), j=0; t<=Number(eTimestamp); t+=3600000, j++){
			cols[i].find({"timestamp":{$gt:t-5000, $lt:t+5000}},{"_id":false, "timestamp":true, "activePower":true, "positiveEnergy":true},(err, data)=>{
				if(err){
					reject(Error(err));
				//데이터가 없을경우
				}else if(!data[0]){
					//console.log("i: "+i+" j: "+j);
					//console.log("searched1: "+searched1+" searched2: "+searched2);
					dbArr[i][j] = null;
					// 어느 한층이 예상되는 한달동안 데이터 수만큼 데이터를 받아왔을시
					if(++searched2 == k1){
						// 모든 층이 데이터를 받아오면 함수 종료
						if(++searched1 == k2){
							//console.log("i: "+i+" j: "+j);
							console.log("getUsageDB Done");
							setTimeout(resolve, 1000);
						}
					}
				//데이터가 있는경우
				}else{
					//console.log("time: "+t);
					//console.log("before");
					//console.log(data);
					//절대값 기준으로 오름차순 정렬
					data.sort(function(a,b){
						return Math.abs(t-Number(a.timestamp)) - Math.abs(t-Number(b.timestamp));
					});
					//console.log("after");
					//console.log(data);
					dbArr[i][j] = data[0];
					//console.log("i: "+i+" j: "+j);
					//console.log("searched1: "+searched1+" searched2: "+searched2);
					// 어느 한층이 예상되는 한달동안 데이터 수만큼 데이터를 받아왔을시
					if(++searched2 == k1){
						// 모든 층이 데이터를 받아오면 함수 종료
						if(++searched1 == k2){
							//console.log("i: "+i+" j: "+j);
							console.log("getUsageDB Done");
							setTimeout(resolve, 1000);
						}
					}
				}
			});
		}
	}
});

// 클라우드 데이터와 스토리지 데이터 비교 함수
function compareData(){
	// 데이터를 *-*-*-* 와 같이 봤을때 (*: 시간, -:시간 사이)
	// cArr의 경우 - (시간 사이) 사용량 데이터를 가지고 있음
	// dbArr의 경우 * (시간) 일때 누적 사용량 데이터를 가지고 있음
	// 따라서 dbArr의 개수가 하나더 많아야하며 시간 사이 사용량 데이터를 구하기 위해 누적 사용량 데이터를 빼준다

	//데이터 수 비교
	for(let i=0; i<floor.length; i++){
		console.log("cArr["+i+"]: "+cArr[i].length+" dbArr["+i+"]: "+dbArr[i].length);
		if(cArr[i].length+1 != dbArr[i].length){
			throw Error("line:"+i+" cloud data number is not matched to db data number");
		}
	}
	let index = new Array(floor.length); index.fill(-1);

	//db에 있는 데이터중 첫번째로 유효한 값 검색
	for(let i=0; i<floor.length; i++){
		for(let j=0; j<dbArr[i].length-1; j++){
			//console.log(dbArr[i][j]);
			if(dbArr[i][j] != null){
				index[i] = j;
				break;
			}
		}
	}
	// debug code
	for(let i=0;i<floor.length;i++){
		console.log(i+" "+index[i]);
	}

	for(let i=0; i<floor.length; i++){
		for(let j=index[i]+1; j<dbArr[i].length-1; j++){
			//console.log(dbArr[i][j]);
			if(dbArr[i][j] != null){
				console.log("i: "+i+" j: "+j+" data: "+dbArr[i][j].positiveEnergy+" "+dbArr[i][index[i]].positiveEnergy);
				let dbData = dbArr[i][j].positiveEnergy - dbArr[i][index[i]].positiveEnergy;
				let cData = 0;
				for(let k=index[i];k<j;k++){
					//console.log("timestamp: "+cArr[i][k].timestamp+" positiveEnergy: "+cArr[i][k].positiveEnergy);
					cData += Number(cArr[i][k].usage);
				}
				console.log(moment(cArr[i][index[i]].timestamp,"x").format("YYYY MMM Do, k:mm")+" - "+moment(cArr[i][j].timestamp,"x").format("YYYY MMM Do, k:mm"));
				console.log("Cloud Data: "+cData+" DB Data: "+dbData)
				index[i] = j;
			}
		}
	}

}

async function test(){
	try{
		console.log("Start time: "+sTime.format("YYYY MMM Do, k:mm")+" "+sTimestamp/1000);
		console.log("End time: "+eTime.format("YYYY MMM Do, k:mm")+" "+eTimestamp/1000);
		await setConfig();
		await getUsageCloud();
		await getUsageDB();
		db.close();
		compareData();
	}catch(e){
		console.log(e);
	}
}

test();