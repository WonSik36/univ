// 토큰 관리모듈
// 사용X
var request = require('request');
var EventEmitter = require('events');

var accessToken = null;
var refreshToken = null;
var refreshTime = 19800000;

// access token 요청
exports.getAccessToken = function(code){
	var headers = {
		'Content-Type':'application/json'
	};

	var options = {
		url: 'https://auth.enertalk.com/token',
		method: 'POST',
		headers: headers,
		form: {
			'client_id': 'Y3dzMDE3M0BnbWFpbC5jb21fSEdVaW90', // insert your client_id
			"client_secret": "vt1gp54g0x354l6id5426p534t1b91838t16cb7", // insert your client_secret
			"grant_type" : "authorization_code",
			"code": //type your auth code
		}
	};

	request(options, function (error, response, body) {
		if (!error && response.statusCode == 200) {
		// Print out the response body
			accessToken = JSON.parse(body)["access_token"];
			refreshToken = JSON.parse(body)["refresh_token"];
			console.log("Succeed Get Access Token");
			console.log("Access Token: " + accessToken);
			console.log("Refresh Token: " + refreshToken);
			return accessToken;
		}else{
			console.log("Failed to Get Access Token");
			console.log(body);
			process.exit();
		}
	});
};

//token refresh 상황 발생시 사용하는 이벤트 생성
exports.refreshAccessToken = new EventEmitter();

//token refresh function
setInterval(function(){
	var headers = {
		//Authorizaiton : Basic encoded string
		//encoded string = Basic base64 encode clientID:clientSecret
		'Authorization':'Basic WTNkek1ERTNNMEJuYldGcGJDNWpiMjFmU0VkVmFXOTA6dnQxZ3A1NGcweDM1NGw2aWQ1NDI2cDUzNHQxYjkxODM4dDE2Y2I3',
		'Content-Type':'application/json'
	};

	var options = {
		url: 'https://auth.enertalk.com/token',
		method: 'POST',
		headers: headers,
		form: {
			"grant_type" : "refresh_token",
			"refresh_token": refreshToken
		}
	};

	request(options, function (error, response, body) {
		if (!error && response.statusCode == 200) {
		// Print out the response body
			accessToken = JSON.parse(body)["access_token"];
			refreshToken = JSON.parse(body)["refresh_token"];
			console.log("Succeed Refresh Access Token");
			console.log("Access Token: " + accessToken);
			console.log("Refresh Token: " + refreshToken);

			exports.refreshAccessToken.emit('refresh', accessToken);
		}else{
			console.log("Failed to Refresh Access Token");
			console.log(body);
			process.exit();
		}
	});
}, refreshTime);