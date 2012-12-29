var assert = require('assert'),
	idleHands = require('../lib/idle_hands');

var count = 0;
idleHands.on('idle', function() {
	console.log('Idling...');
	count ++;
	if (count == 10) {
		idleHands.stop();
		console.log('Stopped idle watcher...');
		setTimeout(checkStop, 100);
	}
});

function checkStop() {
	assert(count == 10);
	console.log('OK');
	process.exit(0);
}

idleHands.start();
console.log('Started idle watcher...');