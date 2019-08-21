some = function(m, n){
	if(n==1 || m==1)
		return 1;

	let str1 = "N = %d, M = %d";
	let str2 = "SOME(%d, %d) + SOME(%d, %d) + SOME(%d, %d)";
	console.log(str1,n,m);
	console.log(str2,n,m-1,n-1,m,n-1,m-1);
	return some(n, m-1) + some(n-1, m) + some(n-1, m-1);
}

var m = 10, n = 10;
start = new Date().getTime();
console.log("SOME RESULT of %d, %d: " + some(m,n), m,n);
end = new Date().getTime();
console.log("Total Caluculation time: "+(end-start));

// some(10,10) = 1462563, time = 144271 ms