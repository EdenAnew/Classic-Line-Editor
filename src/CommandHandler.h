#pragma once
#include "LineData.h"
#include <string>
#include <functional>
#include <vector>
#include <map>

namespace CommandHandler {
	LineList* text_ref{};
	std::vector<std::string> args{};

	void ProcessCommands();

	void HandleInsertion();

	void HandleRemoval();

	void HandleAppendment();

	void HandleReplacement();

	void HelpMessage();

	void QuitHandling();

	const std::map<std::string, std::function<void()>> CMDS {
		{"-ins", []() { HandleInsertion(); }},
		{"-insert", []() { HandleInsertion(); }},
		{"-rem", []() { HandleRemoval(); }},
		{"-remove", []() { HandleRemoval(); }},
		{"-app", []() { HandleAppendment(); }},
		{"-append", []() { HandleAppendment(); }},
		{"-rep", []() { HandleReplacement(); }},
		{"-replace", []() { HandleReplacement(); }},
		{"-pri", []() { (*text_ref).print(); }},
		{"-print", []() { (*text_ref).print(); }},
		{"print", []() { (*text_ref).print(); }},
		{"-cle", []() { (*text_ref).clear(); }},
		{"-clear", []() { (*text_ref).clear(); }},
		{"clear", []() { (*text_ref).clear(); }},
		{"-hel", []() { HelpMessage(); }},
		{"-help", []() { HelpMessage(); }},
		{"help", []() { HelpMessage(); }},
		{"-qui", []() { QuitHandling(); }},
		{"-quit", []() { QuitHandling(); }},
		{"quit", []() { QuitHandling(); }}
	};
}