#include <list>
#include <iostream>
using namespace std;
//Tamaño de la textura
const int TAMAÑO = 100;
//Esto ni va a ser constante ni hostias: es por si hacemos que scrollee para hacer el calculo bien
const int SCROLL = 200;
//Esto hay que ver si cada evento tiene evento 1 o si se mantienen los numeros
const int EVENTO_INI = 1;
const int NUM_EVENTOS = 5;


bool meteEvento(list<int>& eventos, int x, int posx) {
	bool fin = false;
	int aux = 0;
	//Calcula en que posicion va
	if (posx - SCROLL <= TAMAÑO / 2) fin = 0;
	else aux = ((posx - SCROLL - TAMAÑO / 2) / TAMAÑO) + 1;

	//Si está en la lista lo elimina
	eventos.remove(x);
	//Lo inserta en su posición
	if (aux > eventos.size()) eventos.push_back(x);
	else {
		list<int>::iterator it = eventos.begin();
		advance(it, aux);
		eventos.insert(it, x);
	}
	//Comprueba si la timeline esta llena y bien ordenada
	if (eventos.size() == NUM_EVENTOS) {
		int a = 0;
		list<int>::iterator it = eventos.begin();
		while (it != eventos.end() && a < *it) { a = *it; it++; }
		if (it == eventos.end()) fin = true;
	}
	return fin;
}

//CÓMO FUNCIONA ESTO:
//Al formar un evento en el chinchetario se pushea a una lista de eventos en un TLmanager
//El TLmanager tiene tambien otra lista con los eventos que estan en la timeline
//Solo le importa la textura del evento (si hay) y su numero respecto a los demas
//Al arrastrar un evento a la timeline, su funcion onDrop llama a TLmanager.meteEvento() con el numero de evento que es y la posicion en la que se ha soltado
//El onDrop tambien borra el evento de la primera lista, y no va a volver a ella



int main() {
	int n;
	list<int> eventos;
	eventos.push_back(1);
	eventos.push_back(3);
	eventos.push_back(4);
	eventos.push_back(5);
	cin >> n;
	while (n != -1) {
		cout << meteEvento(eventos, 2, n) << endl;
		for (int x : eventos) cout << x;
		cout << endl;
		cin >> n;
	}
	return 0;
}