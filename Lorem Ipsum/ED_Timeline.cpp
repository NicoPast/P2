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


bool meteEvento(list<int> &eventos, int x, int posx) {
	bool aux = false;
		//Calcula en que posicion va
	if (posx - SCROLL <= TAMAÑO / 2) aux =  0;
	else aux = ((posx - SCROLL - TAMAÑO/2) / TAMAÑO) + 1;

		//Si está en la lista lo elimina
	eventos.remove(x);
		//Lo inserta en su posición
	if (aux > eventos.size()) eventos.push_back(x);
	else {
		list<int>::iterator it = eventos.begin();
		advance(it, aux);
		eventos.insert(it, x);
	}
	if (eventos.size() == NUM_EVENTOS) {
		int i = EVENTO_INI;
		list<int>::iterator it = eventos.begin();
		while (it != eventos.end && *it == i) { it++; i++; }
		if (i == NUM_EVENTOS) aux = true;
	}
	return aux;
}

int Test(){
	int n;
	list<int> eventos;
	eventos.push_back(3);
	eventos.push_back(4);
	eventos.push_back(7);
	eventos.push_back(9);
	cin >> n;
	while (n != -1){
		cout << meteEvento(eventos, 2, n) << endl;
		for (int x : eventos) cout << x;
		cout << endl;
		cin >> n;
	}
	return 0;
}