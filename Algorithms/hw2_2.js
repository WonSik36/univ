function some(m, n){
	let arr = [];
	for (let i=0;i<m;i++) {
    	arr[i] = [];
  	}

	for(let i=0;i<m;i++){
		for(let j=0;j<n;j++){
			if(i==0||j==0){
				arr[i][j] = 1;
			}else{
				arr[i][j] = arr[i-1][j] + arr[i][j-1] + arr[i-1][j-1];
			}
		}
	}

	let result = arr[m-1][n-1]
	return result;
}

start = new Date().getTime();
console.log(some(10,10));
end = new Date().getTime();
console.log(end-start);

// some(10,10) = 1462563, time = 9ms