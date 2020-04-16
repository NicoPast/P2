#include "SDL_macros.h"
#include "Entity.h"
#include "Component.h"
#include "Transform.h"
class Chinchetario;
using CallBackDD = void(Chinchetario*, Entity*);

class Drag : public Component {
public:
	Drag(Chinchetario* ch, CallBackDD* cb);
	~Drag() {};
	void init() override;
	void update() override;
	bool getDragging() { return dragging_; }
	void deactivateDrag() { dragging_ = false; }
private:
	void func() { f_(ch_, entity_); }

	CallBackDD* f_;
	Transform* tr_;
	Chinchetario* ch_;
	bool dragging_ = false;
};