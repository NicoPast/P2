#include "PlayState.h"
PlayState::PlayState(LoremIpsum* game) : State(game) {
	init();
};
void PlayState::init() {
	Entity* t = entityManager_->addEntity();
	t->addComponent<TextTest>("En un lugar de la Mancha2, de cuyo nombre no quiero acordarme3, no ha mucho tiempo que viv�a un hidalgo de los de lanza en astillero, adarga antigua, roc�n flaco y galgo corredor4. Una olla de algo m�s vaca que carnero, salpic�n las m�s noches5, duelos y quebrantos los s�bados6, lantejas los viernes7, alg�n palomino de a�adidura los domingos8, consum�an las tres partes de su hacienda9. El resto della conclu�an sayo de velarte10, calzas de velludo para las fiestas, con sus pantuflos de lo mesmo11, y los d�as de entresemana se honraba con su vellor� de lo m�s fino12. Ten�a en su casa una ama que pasaba de los cuarenta y una sobrina que no llegaba a los veinte, y un mozo de campo y plaza que as� ensillaba el roc�n como tomaba la podadera13. Frisaba la edad de nuestro hidalgo con los cincuenta a�os14. Era de complexi�n recia, seco de carnes, enjuto de rostro15, gran madrugador y amigo de la caza. Quieren decir que ten�a el sobrenombre de �Quijada�, o �Quesada�, que en esto hay alguna diferencia en los autores que deste caso escriben, aunque por conjeturas veris�milesII se deja entender que se llamaba �Quijana�III, 16. Pero esto importa poco a nuestro cuento: basta que en la narraci�n d�l no se salga un punto de la verdad.", 100);

	Entity* e = entityManager_->addEntity();
	Transform* te = e->addComponent<Transform>();
	e->addComponent<Rectangle>();
	e->addComponent<DragDrop>();
	te->setPos(200, 200);
	te->setWH(20, 20);
}