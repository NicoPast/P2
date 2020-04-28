#include <iostream>
#include "LoremIpsum.h"
#include "checkML.h"
#pragma execution_character_set("utf-8")


using namespace std;

void start() {
	LoremIpsum g;
	g.start();
}

int main(int ac, char **av) {
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	//locale::global(locale("spanish"));
	setlocale(LC_ALL, "");
	//printf("ø°·¡");
	try {
		start();
	} catch (std::string &e) { // catch errors thrown as strings
		cerr << e << endl;
	} catch (const std::exception &e) { // catch other exceptions
		cerr << e.what();
	} catch (...) {
		cerr << "Caught and exception of unknown type ..";
	}

	return 0;
}
