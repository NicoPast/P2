#pragma once
#include <string>
#include <vector>
#include "jute.h"
#include <filesystem>

namespace fs = std::filesystem;
using namespace std;
using namespace jute;

class DialogLine
{
public:
	DialogLine() {};
	DialogLine(string name, string line) :actorName_(name), line_(line) {};
	string actorName_;
	string line_;
};
class DialogOption
{
public:
	DialogOption() {};
	DialogOption(string startLine, vector<DialogLine> lines, bool active = true, string nextdialog = "") :
		startLine_(startLine), lines_(lines), active_(active), nextDialog_(nextdialog) {}
public:
	string startLine_;
	vector<DialogLine> lines_;
	bool active_ = true;
	string nextDialog_ = "";
};
class Dialog
{
public:
	Dialog() {};
	Dialog(vector<DialogOption>& p) : options_(p) {};
	Dialog(fs::directory_entry f);

	string actorName_ = "";
	string dialogName_ = "";
	vector<DialogOption> options_;
}; 