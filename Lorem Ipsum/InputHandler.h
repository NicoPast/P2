#pragma once

#include <SDL.h>
#include <array>
#include "Vector2D.h"
#include <memory>
#include <map>
using namespace std;

class InputHandler {
public:
	enum MOUSEBUTTON : Uint8 {
		LEFT = 0, MIDDLE = 1, RIGHT = 2
	};

	InputHandler(InputHandler&) = delete;
	InputHandler& operator=(InputHandler&) = delete;

	virtual ~InputHandler();

	static InputHandler* instance() {
		if (instance_.get() == nullptr) {
			instance_.reset(new InputHandler());
		}
		return instance_.get();
	}

	// update the state
	void update();

	// keyboard
	inline bool keyDownEvent() {
		return isKeyDownEvent_;
	}
	
	inline bool keyUpEvent() {
		return isKeyUpEvent_;
	}

	inline bool isKeyDown(SDL_Scancode key) {
		return kbState_[key] == 1; 
	}

	inline bool isKeyDown(SDL_Keycode key) {
		return isKeyDown(SDL_GetScancodeFromKey(key));
	}

	inline bool isKeyUp(SDL_Scancode key) {
		return kbState_[key] == 0;
	}

	inline bool isKeyUp(SDL_Keycode key) {
		return isKeyUp(SDL_GetScancodeFromKey(key));
	}

	// mouse
	inline bool mouseMotionEvent() {
		return isMouseMotionEvent_;
	}

	inline bool mouseButtonEvent() {
		return isMouseButtonEvent_;
	}
	
	inline const Vector2D& getMousePos() {
		return mousePos_;
	}

	inline int getMouseButtonState(MOUSEBUTTON b) {
		return mbState_[b];
	}

	inline int getMouseWheelMotion() {
		return mouseWheelScroll_;
	}

	inline string getTextInput() {
		return textInput_;
	}

	inline bool isLocked() {
		return isLocked_;
	}

	inline void lock() {
		isLocked_ = true;
	}

	inline void unlock() {
		isLocked_ = false;
	}
	// Joystick
	// see:
	//   Chapter 4 of 'SDL Game Development' book
	//   Available online via https://biblioteca.ucm.es/
	//
	inline void mouseButtonHandled(){isMouseButtonEvent_ = false;}
private:
	InputHandler();
	void clearState();
	
	inline void onKeyDown(SDL_Event &event) {
		isKeyDownEvent_ = true;
	}
	inline void onKeyUp(SDL_Event &event) {
		isKeyUpEvent_ = true;
	}
	inline void onMouseMotion(SDL_Event &event) {
		isMouseMotionEvent_ = true;
		mousePos_.set(event.motion.x, event.motion.y);
	}
	inline void onMouseButtonChange(SDL_Event &event, bool isDown) {
		isMouseButtonEvent_ = true;
		if (event.button.button == SDL_BUTTON_LEFT) {
			mbState_[LEFT] = isDown;
		} else if (event.button.button == SDL_BUTTON_MIDDLE) {
			mbState_[MIDDLE] = isDown;
		} else if (event.button.button == SDL_BUTTON_RIGHT) {
			mbState_[RIGHT] = isDown;
		}
	}
	inline void onMouseWheeMotion(SDL_Event &event) {
		mouseWheelScroll_ = event.button.x;
	}
	inline void onTextInput(SDL_Event &event)
	{
		textInput_ = event.text.text;
	}

	static unique_ptr<InputHandler> instance_;
	const Uint8 *kbState_;
	bool isKeyUpEvent_ = false;
	bool isKeyDownEvent_ = false;
	bool isMouseMotionEvent_ = false;
	bool isMouseButtonEvent_ = false;
	bool isLocked_ = false;

	Sint32 mouseWheelScroll_ = 0;
	string textInput_ = "";

	Vector2D mousePos_ = Vector2D(0, 0);
	std::array<bool, 3> mbState_ = {false, false, false};

	friend class StateMachine;
};

