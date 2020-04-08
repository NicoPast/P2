#include "DialogSystem.h"
#include "StoryManager.h"

Dialog::Dialog(fs::directory_entry f)
{

	parser p;
	jValue json = p.parse_file(f.path().string());

	string actor = json["actor"].as_string();
	auto optionsJute = json["options"];
	vector<DialogOption> options;
	for (int i = 0; i < optionsJute.size(); i++)
	{
		vector<DialogLine> lines;
		string startLine = optionsJute[i]["startLine"].as_string();
		auto linesJute = optionsJute[i]["dialog"];
		for (int i = 0; i < linesJute.size(); i++)
		{
			DialogLine dl(linesJute[i]["actor"].as_string(), linesJute[i]["line"].as_string());
			lines.emplace_back(dl);
		}
		DialogOption option(startLine, lines);
		options.push_back(option);
	};

	actorName_ = actor;
	options_ = options;
}

