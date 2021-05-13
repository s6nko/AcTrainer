// dllmain.cpp : Définit le point d'entrée de l'application DLL.
#include "pch.h"
#include <Windows.h>
#include <iostream>
#include <TlHelp32.h>
#include "ent.h"

typedef entity* (__cdecl* tGetCrosshairEnt)();

tGetCrosshairEnt GetCrosshairEnt = { nullptr };

DWORD WINAPI TrainerThread(HMODULE hModule) 
{
    //Creating the console
    AllocConsole();
    
    bool bHealth = 0, bArmor = 0, bAmmo = 0, bTriggerbot = 0;
    
    entity* localPlayerPtr{ nullptr };


    FILE* f;
    freopen_s(&f, "CONOUT$", "w", stdout);


    //Get module base
    uintptr_t moduleBase = (uintptr_t)GetModuleHandle(NULL);
    localPlayerPtr = *(entity**)(moduleBase + 0x10f4f4);
    
    GetCrosshairEnt = (tGetCrosshairEnt)(moduleBase + 0x607c0);

    std::cout << "USED TO SIT ON THIS THRONE\n MADE BY SENKO\n";
    std::cout << std::endl;
    std::cout << "NUMPAD1 - UNLIMITED HEALTH" << std::endl;
    std::cout << "NUMPAD2 - UNLIMITED AMMO" << std::endl;
    std::cout << "NUMPAD3 - TRIGGERBOT" << std::endl;
    std::cout << "PRESS END TO EJECT";

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
            bAmmo = !bAmmo;
        }

        if (GetAsyncKeyState(VK_NUMPAD3) & 1)
        {
            bTriggerbot = !bTriggerbot;
        }

        if (GetAsyncKeyState(VK_END) & 1) 
        {
            break;
        }

        if (localPlayerPtr)
        {
            if (bHealth) 
            {
                localPlayerPtr->health = 9999;
            }

            if (bAmmo) 
            {
                localPlayerPtr->currWeapon->ammoClip->ammo = 9999;
                localPlayerPtr->currWeapon->ammoReserve->ammo = 9999;
            }

            if (bTriggerbot) 
            {
                entity* crosshairEnt = GetCrosshairEnt();

                if (crosshairEnt)
                {
                    if (localPlayerPtr->currTeam != crosshairEnt->currTeam) 
                    {
                        localPlayerPtr->bAttack = 1;
                    }

                    else 
                    {
                        localPlayerPtr->bAttack = 0;
                    }

                }
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

