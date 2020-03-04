#include <list>
#include <iostream>
using namespace std;
//Tama�o de la textura
const int TAMA�O = 100;
//Esto ni va a ser constante ni hostias: es por si hacemos que scrollee para hacer el calculo bien
const int SCROLL = 200;


bool meteEvento(list<int> &eventos, int x, int posx) {
	int aux;
		//Calcula en que posicion va
	if (posx - SCROLL <= TAMA�O / 2) aux =  0;
	else aux = ((posx - SCROLL - TAMA�O/2) / TAMA�O) + 1;

		//Si est� en la lista lo elimina
	eventos.remove(x);
		//Lo inserta en su posici�n
	if (aux > eventos.size()) eventos.push_back(x);
	else {
		list<int>::iterator it = eventos.begin();
		advance(it, aux);
		eventos.insert(it, x);
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