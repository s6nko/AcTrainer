// dllmain.cpp : Définit le point d'entrée de l'application DLL.
#include "pch.h"
#include <Windows.h>
#include <iostream>
#include <TlHelp32.h>


struct Vector3 { float x, y, z; };

class ent
{
public:
    Vector3 headPos; //0x0004
    char pad_0010[36]; //0x0010
    Vector3 bodyPos; //0x0034
    Vector3 angle; //0x0040
    char pad_004C[172]; //0x004C
    int32_t health; //0x00F8
    int32_t armor; //0x00FC
    char pad_0100[628]; //0x0100
    class weapon* currentWeapon; //0x0374
    char pad_0378[1248]; //0x0378

    virtual void Function0();
    virtual void Function1();
    virtual void Function2();
    virtual void Function3();
    virtual void Function4();
    virtual void Function5();
    virtual void Function6();
    virtual void Function7();
    virtual void Function8();
    virtual void Function9();
}; //Size: 0x0858
static_assert(sizeof(ent) == 0x858);

class weapon
{
public:
    char pad_0000[4]; //0x0000
    int32_t Id; //0x0004
    char pad_0008[12]; //0x0008
    class ammoClip* ammoPtr; //0x0014
    char pad_0018[40]; //0x0018
}; //Size: 0x0040
static_assert(sizeof(weapon) == 0x40);

class N0000028A
{
public:
    char pad_0000[68]; //0x0000
}; //Size: 0x0044
static_assert(sizeof(N0000028A) == 0x44);

class ammoClip
{
public:
    int32_t ammo; //0x0000
    char pad_0004[64]; //0x0004
}; //Size: 0x0044
static_assert(sizeof(ammoClip) == 0x44);

DWORD WINAPI TrainerThread(HMODULE hModule) 
{
    //Creating the console
    AllocConsole();
    
    bool bHealth = 0, bArmor = 0, bAmmo = 0;
    
    FILE* f;
    freopen_s(&f, "CONOUT$", "w", stdout);
    std::cout << "USED TO SIT ON THIS THRONE\n MADE BY SENKO\n";
    std::cout << std::endl;
    std::cout << "NUMPAD1 - UNLIMITED HEALTH" << std::endl;
    std::cout << "NUMPAD2 - UNLIMITED ARMOR"<< std::endl;
    std::cout << "NUMPAD3 - UNLIMITED AMMO"<< std::endl;
    std::cout << "PRESS END TO EJECT";

    //Get module base
    uintptr_t moduleBase = (uintptr_t)GetModuleHandle(NULL);
    

    //Hack Loop
    while(true)
    {
        //keyInput
        if (GetAsyncKeyState(VK_NUMPAD1) & 1)
        {
            bHealth = !bHealth;
        }

        if (GetAsyncKeyState(VK_NUMPAD2) & 1)
        {
            bArmor = !bArmor;
        }

        if (GetAsyncKeyState(VK_NUMPAD3) & 1)
        {
            bAmmo = !bAmmo;
        }

        if (GetAsyncKeyState(VK_END) & 1) 
        {
            break;
        }

        //need to use uintptr_t for pointer arithmetic later
        ent* localPlayer = *(ent**)(moduleBase + 0x10F4F4);
        localPlayer = (ent*)*(uintptr_t*)(moduleBase + 0x10f4f4);

        if (localPlayer) 
        {
            if (bHealth) 
            {
                localPlayer->health = 9999;
            }

            if (bArmor) 
            {
                localPlayer->armor = 9999;
            }

            if (bAmmo) 
            {
                localPlayer->currentWeapon->ammoPtr->ammo = 9999;
            }
        }
        Sleep(10);
    }
    fclose(f);
    FreeConsole();
    FreeLibraryAndExitThread(hModule, 0);
    return 0;

    
}



BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH: 
    {
        CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)TrainerThread, hModule, 0, nullptr);
    }
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

