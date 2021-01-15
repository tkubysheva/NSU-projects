#pragma once
#include <iostream>
#include "strategy.h"
#include <vector>
#include <string>
#include <dirent.h>
#include <windows.h>

void(*CreateStr)();

void sign_up_for_strategies() {
    std::string path = "C:\\Users\\hp\\CLionProjects\\PrisonerDilemma\\strategies\\dll\\";
    DIR *dir;
    struct dirent *ent;
    if ((dir = opendir(path.c_str())) != nullptr) {
        while ((ent = readdir(dir)) != nullptr) {
            if(std::string(ent->d_name) == "." or std::string(ent->d_name) == ".." or std::string(ent->d_name) == "a"){
                continue;
            }
            HINSTANCE hModule=NULL;
            typedef  BOOL (WINAPI MESS)(UINT);
            MESS* me=NULL;
            hModule=::LoadLibrary((path +ent->d_name).c_str());
            if (hModule!=NULL)
            {
                me=(MESS*)::GetProcAddress((HMODULE)hModule,"create");
                if (me!=NULL)
                {
                    UINT type=1;
                    BOOL result;
                    result=(*me)(type);
                    std::cout << result << std::endl;
                }
                else std::cout << "Error Load function" << std::endl;
                ::FreeLibrary(hModule);
            }
            else std::cout << "error load Dll" << std::endl;
        }
        closedir(dir);
    }
}
