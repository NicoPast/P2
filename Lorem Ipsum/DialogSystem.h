#pragma once
#include <string>
#include <vector>
#include "jute.h"
#include <filesystem>
#include "Resources.h"
namespace fs = std::filesystem;
using namespace std;
using namespace jute;

class DialogLine
{
public:
	DialogLine() {};
	DialogLine(size_t id, string line);
	size_t actorID_=0;
	string line_="Escribir texto";
};
class DialogOption
{
public:
	DialogOption() {};
	DialogOption(string startLine, vector<DialogLine> lines, bool active = true, string nextdialog = "") :
		startLine_(startLine), lines_(lines), active_(active), nextDialog_(nextdialog) {}
public:
	string startLine_="";
	vector<DialogLine> lines_;
	bool active_ = true;
	//Marca si el jugador la ha leído
	bool read_ = false; 
	string nextDialog_ = "";
};
class Dialog
{
public:
	Dialog() :id_(0), actorName_(""), dialogName_(""), actorID_(0), listPosition_(-1), active_(true) {};
	Dialog(vector<DialogOption>& p) : options_(p) {};
	Dialog(string path, size_t id);
	jValue toJSON();

	size_t id_ = 0; //Todo el sistema se comunicará entre dialogos con identificadores para poder cambiar nombre sin que pete nada
	string actorName_ = "";
	string dialogName_ = "";
	int actorID_ = 0;
	int listPosition_ = -1;
	vector<DialogOption> options_;
	bool active_=true;
}; 
