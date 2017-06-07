let checkbox = document.getElementById('checkbox');

function init() {
	get('/sonoff', response => {
		checkbox.checked = response != 0;
		console.log(`Got power: ${response}`);
	}, onError);
}

function onToggleClicked(element) {
	let power = checkbox.checked ? 1 : 0;

	post('/sonoff', power, () => {
		console.log(`Power set: ${power}`)
	}, (status, statusText) => {
		checkbox.checked = !checkbox.checked;
		onError(status, statusText);
	});
}

function onError(status, statusText) {
	console.log(`${status} ${statusText}`);
}

function get(url, success, error) {
	request(url, 'GET', success, error).send();
}

function post(url, data, success, error) {
	request(url, 'POST', success, error).send(data);
}

function request(url, method, success, error) {
	let xhr = window.XMLHttpRequest ? new XMLHttpRequest() : new ActiveXObject('Microsoft.XMLHTTP');
	xhr.open(method, url);

	xhr.onreadystatechange = () => {
		if (xhr.readyState === 4) {
			if (xhr.status == 200) {
				success(xhr.response);
			} else {
				error(xhr.status, xhr.statusText);
			}
		}
	};

	xhr.onerror = () => {
		error(xhr.status, xhr.statusText);
	}

	return xhr;
}

window.onload = init();
