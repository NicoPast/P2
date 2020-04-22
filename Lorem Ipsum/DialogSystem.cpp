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

jValue Dialog::toJSON()
{
	jValue porfavoh;
	porfavoh.set_type(JOBJECT);
	jValue options;
	options.set_type(JARRAY);
	for (auto option : options_)
	{
		jValue startLine;
		startLine.set_type(JSTRING);
		startLine.set_string(option.startLine_);

		jValue lines;
		lines.set_type(JARRAY);
		for (auto line : option.lines_)
		{
			jValue actor;
			actor.set_type(JSTRING);
			actor.set_string(line.actorName_);
			jValue jline;
			jline.set_type(JSTRING);
			jline.set_string(line.line_);

			jValue property;
			property.set_type(JOBJECT);
			property.add_property("actor", actor);
			property.add_property("line", jline);
			lines.add_element(property);

		}
		jValue nOption;
		nOption.set_type(JOBJECT);
		nOption.add_property("startLine", startLine);
		nOption.add_property("dialog", lines);


		options.add_element(nOption);
	}
	jValue name;
	name.set_type(JSTRING);
	name.set_string(actorName_);
	porfavoh.add_property("actor", name);
	porfavoh.add_property("options", options);
	return porfavoh;
}

