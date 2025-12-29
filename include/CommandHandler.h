#pragma once
#include "LineData.h"
#include <string>
#include <functional>
#include <vector>
#include <map>

namespace CommandHandler {
	inline LineList* text_ref{};
	inline std::vector<std::string> args{};
	inline bool quit {false};

	void ProcessCommands(std::string input);

	void HandleInsertion();

	void HandleRemoval();

	void HandleAppendment();

	void HandleReplacement();

	void HelpMessage();

	const std::map<std::string, std::function<void()>> CMDS {
		{"ins", []() { HandleInsertion(); }},
		{"insert", []() { HandleInsertion(); }},
		{"rem", []() { HandleRemoval(); }},
		{"remove", []() { HandleRemoval(); }},
		{"app", []() { HandleAppendment(); }},
		{"append", []() { HandleAppendment(); }},
		{"rep", []() { HandleReplacement(); }},
		{"replace", []() { HandleReplacement(); }},
		{"pri", []() { (*text_ref).print(); }},
		{"print", []() { (*text_ref).print(); }},
		{"cle", []() { (*text_ref).clear(); }},
		{"clear", []() { (*text_ref).clear(); }},
		{"hel", []() { HelpMessage(); }},
		{"help", []() { HelpMessage(); }},
		{"qui", []() { quit = true; }},
		{"quit", []() { quit = true; }},
		{"close", []() { quit = true; }}
	};
}