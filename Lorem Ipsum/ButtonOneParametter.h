#pragma once
#include "Button.h"
#include <functional>

template <typename T>
class ButtonOneParametter : Button
{
public:
	ButtonOneParameter() : Button() {};
	ButtonOneParameter(std::function<void* (T)> f, T param) : Button() {setCallback(f,param)};
	virtual ~ButtonOneParameter() {};

	void setCallback(std::function<void* (T)> f, T param) { f_ = f; param_=param };
protected:
	void callback() override
	{
		f_(param_);
	}
	std::function<void* (T)> f_;
	T param_;
};