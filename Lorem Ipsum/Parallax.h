#pragma once
#include "Component.h"
#include "StoryManager.h"
#include "Entity.h"

/*
	El componente pinta las capas en el orden que están y las mueve su speed con respecto al jugador.
	Por cada pixel X que se mueve el jugador las capas se N*X siendo n la velocidad de la capa.
	Velocidad negativa hace que se mueven en la dirección contraria al jugador.
*/

class Parallax : public Component
{
public:
	//Pasar la pos_ al crear será la posición inicial
	struct parallaxLayer
	{
		parallaxLayer(Texture* t, Vector2D p, double speed) : tex_(t), pos_(p), speed_(speed) { sourceRect_ = { 0,0,t->getWidth()/3, t->getHeight() }; };
		Texture* tex_;
		SDL_Rect sourceRect_;
		Vector2D pos_;
		double speed_;
	};
	Parallax(SDL_Rect& clip) : Component(ecs::Parallax), clip_(clip), player_(nullptr){};
	virtual ~Parallax() { for (auto l : layers_) delete l; };
	void init()
	{

	}
	virtual void update() override
	{
		//Si se mueve
		if (lastPlayerPos_.getX() != player_->getPos().getX() || lastPlayerPos_.getY() != player_->getPos().getY())
		{
			//Guardamos los cambios en X e Y
			int dispX = player_->getPos().getX() - lastPlayerPos_.getX();
			lastPlayerPos_ = player_->getPos();
			//Y los aplicamos a cada capa multiplciado por su velocidad particular
			for (parallaxLayer* layer : layers_)
			{
				layer->pos_.setX((layer->pos_.getX() + dispX * layer->speed_));
				//layer.pos_.setY(layer.speed_ * (layer.pos_.getY() + dispY));
			}
		}	
	}

	virtual void draw() override
	{
		for (parallaxLayer* layer : layers_)
		{
			SDL_Rect sourc = layer->sourceRect_;
			sourc.x += layer->pos_.getX();
			//sourc.x = layer->tex_->getWidth();
			sourc.x -= sourc.x % 8;
			SDL_Rect res;
			layer->tex_->render(clip_,0,sourc);
		}
	};
	void setLayers(vector<parallaxLayer*>& layers) { layers_ = layers; };
	void addLayer(parallaxLayer* layer) { layers_.push_back(layer); };
	void setPlayer(Transform* tr) {
		player_ = tr;
		lastPlayerPos_ = player_->getPos();
	};
	vector<parallaxLayer*>& getLayers() { return layers_; };
private:
	SDL_Rect clip_;
	Transform* player_;
	Vector2D lastPlayerPos_;
	//El orden es el orden de pintado, si quieres una imagen estática velocidad 0
	vector<parallaxLayer*> layers_;
};