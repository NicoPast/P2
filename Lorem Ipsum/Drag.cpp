#include "Drag.h"
#include "Chinchetario.h"
Drag::Drag(Chinchetario* ch, CallBackDD* cb) : Component(ecs::Drag), tr_(nullptr), ch_(ch), f_(cb) {
}
void Drag::init() {
	tr_ = GETCMP1_(Transform);
}
void Drag::update() {
	InputHandler* ih = InputHandler::instance();
}