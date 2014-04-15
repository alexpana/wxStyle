#pragma once

namespace wxstyle {

template <typename T>
class Maybe<T> {
public:
	Maybe(T val) : _v(val), _init(true) {}
	Maybe() : _init(false) {}

	T get() {
		return _v;
	}

	bool init() {
		return _init();
	}

private:
	T _v;
	bool _init;
};

}