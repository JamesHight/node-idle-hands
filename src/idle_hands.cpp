#ifndef BUILDING_NODE_EXTENSION
#define BUILDING_NODE_EXTENSION
#endif

#include <node.h>
#include <uv.h>

using namespace v8;

bool running = false;
Persistent<Function> cb;
uv_idle_t idler;

/**
 * callback for idle watcher
 **/
void idle_event(uv_idle_t* handle, int status) {
	const unsigned argc = 1;
	Local<Value> argv[argc] = {Local<Value>::New(Number::New(status))};
	cb->Call(Context::GetCurrent()->Global(), argc, argv);
}

/**
 * start idle watcher
 * usage: start(js_callback)
 **/
Handle<Value> start(const Arguments& args) {
	HandleScope scope;

	if (!args.Length() || !args[0]->IsFunction()) {
		return ThrowException(Exception::TypeError(String::New("First argument must be a function")));
	}

	// Don't start if already running
	if (running) {
		return ThrowException(Exception::TypeError(String::New("Already started")));
	}
	running = true;

	cb = Persistent<Function>::New(Handle<Function>::Cast(args[0]));

	uv_idle_init(uv_default_loop(), &idler);
	uv_idle_start(&idler, idle_event);

	return scope.Close(Undefined());
}

/**
 * stop idle watcher
 **/
Handle<Value> stop(const Arguments& args) {
	HandleScope scope;

	if (!running) {
		return ThrowException(Exception::TypeError(String::New("Already stopped")));
	}
	running = false;

	uv_idle_stop(&idler);

	return scope.Close(Undefined());
}

void Init(Handle<Object> target) {
  target->Set(String::NewSymbol("start"),
      FunctionTemplate::New(start)->GetFunction());

  target->Set(String::NewSymbol("stop"),
      FunctionTemplate::New(stop)->GetFunction());
}

NODE_MODULE(idle_hands, Init)
