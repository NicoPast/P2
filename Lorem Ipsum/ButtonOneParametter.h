#pragma once
#include "Button.h"
#include <functional>

template <typename T>
class ButtonOneParametter : public Button
{
public:
	ButtonOneParametter(std::function<void(T)> f, T param) : Button(), f_(f), param_(param){};
	virtual ~ButtonOneParametter() {};

	void setCallback(std::function<void(T)> f, T param) { f_ = f; param_ = param; };
protected:
	void callback() override
	{
		f_(param_);
	}
	std::function<void(T)> f_;
	T param_;
};