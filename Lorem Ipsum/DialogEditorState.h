#pragma once
#include "State.h"
class LoremIpsum;




class DialogEditorState :
	public State
{
public:
	const string FILEDIR = "../assets/dialogs/";

	DialogEditorState(LoremIpsum* li) : State(li) { init(); };
	virtual ~DialogEditorState() {};

	void init();
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
		DialogOption() {  };
		DialogOption(string startLine, vector<DialogLine> lines, bool active=true, string nextdialog="") :
			startLine_(startLine), lines_(lines), active_(active), nextDialog_(nextdialog){}
	public:
		string startLine_;
		vector<DialogLine> lines_;
		bool active_=true;
		string nextDialog_ = "";
	};
	class DialogInfo
	{
	public:
		DialogInfo() {};
		DialogInfo(vector<DialogOption>& p) : options_(p) {};
		vector<DialogOption> options_;
	};

};

