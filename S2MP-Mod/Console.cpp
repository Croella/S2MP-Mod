#include "pch.h"
#include "Console.h"
#include <string>
#include <algorithm>
#include "ExtConsole.h"
#include <iostream>
#include "ExtConsoleGui.h"
#include <sstream>
#include <array>
#include "FuncPointers.h"

#include "structs.h"
#include <regex>
#include "GameUtil.hpp"
#include "Noclip.hpp"
#include "CustomCommands.hpp"

uintptr_t t9base = (uintptr_t)GetModuleHandle(NULL);

void Console::print(std::string text) {
	//External CLI
	std::cout << text << std::endl;
	//External Console Window
	ExternalConsoleGui::print(text);
	//Internal Console
	//.....
}
void Console::labelPrint(std::string label, std::string text) {
	std::string s = "[" + label + "] " + text;
	//External CLI
	ExtConsole::coutCustom(label, text);
	//External Console Window
	ExternalConsoleGui::print(s);
	//Internal Console
	//.....
}

void Console::infoPrint(std::string text) {
	std::string s = "[INFO] " + text;
	//External CLI
	ExtConsole::coutInfo(text);
	//External Console Window
	ExternalConsoleGui::print(s);
	//Internal Console
	//.....
}

void Console::initPrint(std::string text) {
	std::string s = "[INIT] " + text;
	//External CLI
	ExtConsole::coutInit(text);
	//External Console Window
	ExternalConsoleGui::print(s);
	//Internal Console
	//.....
}

std::vector<std::string> Console::parseCmdToVec(const std::string& cmd) {
	std::vector<std::string> components;
	std::regex pattern(R"((\"[^\"]*\"|\S+))");
	auto words_begin = std::sregex_iterator(cmd.begin(), cmd.end(), pattern);
	auto words_end = std::sregex_iterator();

	for (auto it = words_begin; it != words_end; ++it) {
		std::string match = it->str();
		if (match.size() > 1 && match.front() == '"' && match.back() == '"') {
			match = match.substr(1, match.size() - 2);
		}
		components.push_back(match);
	}

	return components;
}

constexpr uint32_t hash32(const char* str) {
	uint32_t hash = 0x4B9ACE2F;

	for (const char* data = str; *data; data++) {
		char c = *data >= 'A' && *data <= 'Z' ? (*data - 'A' + 'a') : *data;
		hash = ((c + hash) ^ ((c + hash) << 10)) + (((c + hash) ^ ((c + hash) << 10)) >> 6);
	}

	return 0x8001 * ((9 * hash) ^ ((9 * hash) >> 11));
}

//move to gameutil
std::string toHex(uint32_t value) {
	std::stringstream ss;
	ss << std::hex << value;
	return ss.str();
}

bool execCustomCmd(std::string& cmd) {
	std::transform(cmd.begin(), cmd.end(), cmd.begin(), GameUtil::asciiToLower);
	std::vector<std::string> p = Console::parseCmdToVec(cmd);
	if (p.size() < 1) {
		return false;
	}
	if (p[0] == "trans") {
		if (p.size() == 2) {
			Console::print("Translated String: " + std::string(Functions::_SEH_SafeTranslateString(p[1].c_str())));
		}
		return true;
	}

	if (p[0] == "noclip") {
		Noclip::toggle();
		return true;
	}

	if (p[0] == "god") {
		CustomCommands::toggleGodmode();
		return true;
	}
	
	if (p[0] == "quit") {
		Functions::_Sys_Quit();
		return true;
	}

	if (p[0] == "cg_drawlui") {
		if (p.size() >= 2) {
			CustomCommands::toggleHud(GameUtil::stringToBool(p[1]));
		}
	}
	
	if (p[0] == "r_fog") {
		if (p.size() >= 2) {
			CustomCommands::toggleFog(GameUtil::stringToBool(p[1]));
		}
	}
	
	if (p[0] == "cg_drawgun") {
		if (p.size() >= 2) {
			CustomCommands::toggleGun(GameUtil::stringToBool(p[1]));
		}
	}

	return false;
}

void Console::execCmd(std::string cmd) {
	if (!execCustomCmd(cmd)) {
		//GameUtil::Cbuf_AddText(LOCAL_CLIENT_0, (char*)cmd.c_str());
	}


	//std::vector<std::string> p = Console::parseCmdToVec(cmd);
	//if (p.size() == 0) {
	//	return;
	//}

}