async function testFn(){
	await fetch('http://10.0.0.24:3000/', {
		method: 'POST',
		headers: {
			'Content-Type': 'text/plain'
		}
		body: "this is a test"
	});
}

testFn();