#include "FollowedByCamera.h"
#include "SDL_macros.h"
#include "Entity.h"


void FollowedByCamera::init()
{
	tr_ = GETCMP1_(Transform);
}

void FollowedByCamera::update()
{
	//if(esta en el margen izquierdo o derecho de la CAMARA, NO DEL MUNDO) mueve la camara
	if (tr_->getPos().getX() < cam_->getLeftMargin() + cam_->getPosX() && tr_->getVel().getX() < 0 ||
		tr_->getPos().getX() >= cam_->getRightMargin() + cam_->getPosX() && tr_->getVel().getX() > 0) {
		cam_->move(tr_->getVel());
	}

}

