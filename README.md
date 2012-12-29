Idle Hands
----------

Run background or low priority tasks while Node.js is idle. 
Hooks the idle watcher in the Node.js main event loop.

````bash
	npm install idle-hands
````


Usage:

````javascript
	var idleHands = require('idle-hands');

	idleHands.on('idle', function() {
		// do stuff
	});

	// start idle watcher
	idleHands.start();

	// stop idle watcher
	idleHands.stop();
````