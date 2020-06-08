/*!
 * Acquires the PEB_LDR_DATA_TABLE
 * InLoadOrderModuleList member and
 * loops through its linked list to
 * print information about the modules
 * loaded in memory.
 *
 * Austin Hudson.
 * Cheers to Odzhan.
!*/
#include <windows.h>
#include <stdio.h>
#include "dep/ntlib/ntddk.h"

VOID ListLoadedModules( VOID )
{
    PEB                  * PebPtr = NULL;
    TEB                  * TebPtr = NULL;
    PEB_LDR_DATA         * PebLdr = NULL;
    LDR_DATA_TABLE_ENTRY * LdrEnt = NULL;
    LIST_ENTRY           * LstEnt = NULL;
    LIST_ENTRY           * LstHdr = NULL;

    //
    // 1 ) Acquire the Thread Environment Block ( TEB )
    // 2 ) Acquire the Process Environment Block ( PEB )
    // 3 ) Acquire the PEB_LDR_DATA pointer.
    // 4 ) Acquire the InLoadOrderModuleList linked list pointer.
    // 5 ) Set my list entry to the first entry within the list.
    //
    TebPtr = NtCurrentTeb();
    PebPtr = TebPtr->ProcessEnvironmentBlock;
    PebLdr = PebPtr->Ldr;
    LstHdr = & PebLdr->InLoadOrderModuleList;
    LstEnt = LstHdr->Flink;

    for ( ; LstHdr != LstEnt ; LstEnt = LstEnt->Flink ) {
        LdrEnt = ( LDR_DATA_TABLE_ENTRY * ) LstEnt;
        
        printf("[ ] Name: %ls\n", LdrEnt->BaseDllName.Buffer);
        printf("[ ] Path: %ls\n", LdrEnt->FullDllName.Buffer);
        printf("[ ] Addr: %p\n",  LdrEnt->DllBase);
    };
};

INT WINAPI WinMain( IN HINSTANCE hInstance,
                    IN HINSTANCE hPrevious,
                    IN LPSTR lpCmdLine,
                    IN INT nShowCmd )
{
    ListLoadedModules();

    return 0;
};
