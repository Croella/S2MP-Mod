#pragma once
#include <string>
class CustomCommands {
public:
	static uintptr_t base;
	static uintptr_t rawBase;
	static void toggleGodmode();
	static void toggleHud(bool b);
	static void toggleGun(bool b);
	static void toggleFog(bool b);
private:
	static bool isGodmode;
};