// chart.js 관련 데이터 추가,제거 함수
function addData(chart, label, data) {
    chart.data.labels.push(label);
    chart.data.datasets.forEach((dataset) => {
        dataset.data.push(data);
    });
    chart.update();
}
function addDataset(chart, data, label_name){
	var colorNames = ['Aqua', 'Black', 'BlueViolet', 'Chartreuse', 'DeepPink', 'GreenYellow', 'OrangeRed', 'YellowGreen', 'SpringGreen', 'RoyalBlue'];
	var newColor = colorNames[chart.data.datasets.length % colorNames.length];
    var newDataset = {
        label: label_name,
        backgroundColor: newColor,
        borderColor: newColor,
        data: [],
        fill: false
    };

    newDataset.data = data;
    chart.data.datasets.push(newDataset);
    chart.update();
}
function removeData(chart) {
    chart.data.labels.pop();
    chart.data.datasets.forEach((dataset) => {
        dataset.data.pop();
    });
    chart.update();
}
function removeFirstData(chart) {
    chart.data.labels.shift();
    chart.data.datasets.forEach((dataset) => {
        dataset.data.shift();
    });
    chart.update();
}
function removeDataset(chart, label_name){
	for (var i = 0; i < chart.data.labels.length; ++index) {
		if(chart.data.labels[i] == label_name)
			chart.data.labels.splice(i,1);
    }
	chart.update();
}