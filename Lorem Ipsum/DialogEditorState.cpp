#include "LoremIpsum.h"
#include "DialogEditorState.h"
#include "Dialog.h"
#include "jute.h"


void DialogEditorState::init()
{
	jute::parser p;
	auto a = p.parse_file(DialogEditorState::FILEDIR+"dialogTest.dialog");
	a;
	string actor = a["actor"].to_string();
	auto optionsJute = a["options"];
	vector<DialogOption> options;
	for (int i =0; i<optionsJute.size(); i++)
	{
		vector<DialogLine> lines;
		string startLine = optionsJute[i]["startLine"].to_string();
		auto linesJute = optionsJute[i]["dialog"];
		for (int i = 0; i < linesJute.size();i++)
		{
			DialogLine dl(linesJute[i]["actor"].to_string(), linesJute[i]["line"].to_string());
			lines.emplace_back(dl);
		}
		DialogOption option(startLine, lines);
		options.push_back(option);
	}
	auto e = entityManager_->addEntity(1);
	e->addComponent<Transform>(0,0,game_->getGame()->getWindowWidth(), 400);
	Actor* c = new Actor(game_->getStoryManager(), Resources::actors_[Resources::Profesor], Resources::calleProfesor);
	Dialog* d = e->addComponent<Dialog>(game_->getStoryManager()->getPlayer(), c);
	DialogInfo dialogInfo(options);
	d->setDialog(dialogInfo);
	d->interact();
}