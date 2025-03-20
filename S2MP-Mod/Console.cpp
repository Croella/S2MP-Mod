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
#include "DvarInterface.hpp"

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

//TODO: add preprocessor directive for developer like in t6sp-mod
void Console::devPrint(std::string text) {
	std::string s = "[DEV] " + text;
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

//TODO: move to gameutil
std::string toHex(uint32_t value) {
	std::stringstream ss;
	ss << std::hex << value;
	return ss.str();
}

//Gonna have to run the commands externally like this for now
bool execCustomCmd(std::string& cmd) {
	std::transform(cmd.begin(), cmd.end(), cmd.begin(), GameUtil::asciiToLower);
	std::vector<std::string> p = Console::parseCmdToVec(cmd);

	if (p[0] == "trans") {
		if (p.size() == 2) {
			Console::print("Translated String: " + std::string(Functions::_SEH_SafeTranslateString(p[1].c_str())));
		}
		return true;
	}
	
	if (p[0] == "send") {
		if (p.size() == 2) {
			std::string str = "%c \"" + p[1] + "\"";
			Functions::_SV_SendServerCommand(0i64, 0, str.c_str(), 101i64);
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
		return true;
	}
	
	if (p[0] == "r_fog") {
		if (p.size() >= 2) {
			CustomCommands::toggleFog(GameUtil::stringToBool(p[1]));
		}
		return true;
	}
	
	if (p[0] == "cg_drawgun") {
		if (p.size() >= 2) {
			CustomCommands::toggleGun(GameUtil::stringToBool(p[1]));
		}
		return true;
	}

	return false;
}

bool setEngineDvar(std::string cmd) {
	std::transform(cmd.begin(), cmd.end(), cmd.begin(), GameUtil::asciiToLower);
	std::vector<std::string> p = Console::parseCmdToVec(cmd);

	return DvarInterface::setDvar(p[0], p);
}

void Console::execCmd(std::string cmd) {
	if (cmd.length() == 0) {
		return;
	}
	if (!execCustomCmd(cmd) && !setEngineDvar(cmd)) {
		//GameUtil::Cbuf_AddText(LOCAL_CLIENT_0, (char*)cmd.c_str());
	}

}