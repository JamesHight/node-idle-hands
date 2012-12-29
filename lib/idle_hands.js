/**
 * Emits an 'idle' event when the main event loop is idle
 **/
 
var ih = require('../build/Release/idle_hands'),
	events = require('events');

var started = false;

function IdleHands() {
	events.EventEmitter.call(this);
}
IdleHands.prototype = new events.EventEmitter();    

IdleHands.prototype.start = function() {
	var self = this;

	if (started) return;
	started = true;

	ih.start(function() {
		self.emit('idle');
	});
};

IdleHands.prototype.stop = function() {
	if (!started) return;
	started = false;

	ih.stop();
};

module.exports = new IdleHands();