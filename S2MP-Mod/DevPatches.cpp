//Development Patches
//temporary patches for testing stuff

#include "pch.h"
#include "DevPatches.hpp"
#include "Console.h"
#include <MinHook.h>
#include "FuncPointers.h"

uintptr_t DevPatches::base = (uintptr_t)GetModuleHandle(NULL) + 0x1000;

void DevPatches::init() {
    Console::infoPrint("DevPatches::init()");

    
}