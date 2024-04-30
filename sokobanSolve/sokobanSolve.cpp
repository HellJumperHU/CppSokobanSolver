// sokobanSolve.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include<Windows.h>
#include <iostream>
#include "state.h"
#include "SokoMap.h"
#include "mapInputHandler.h"
#include "solve.h"

int main()
{
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    
    bool isErrorPresent = false;
    SokoMap sokoMap;
    std::string filepath;
    std::cout << "The .skb file could be opened the following ways\n";
    std::cout << "1. By entering full path of the .skb file (e.g. E:\foldername1\foldername2\\sokomap.skb\n";
    std::cout << "2. By entering the file name (e.g. sokomap.skb)\n";
    std::cout << "In case of the 2nd option. The .skb file should be placed in the same directory as this .exe file\n";
    std::cin >> filepath;

    SokobanMapReader(sokoMap, isErrorPresent, filepath);
    if (isErrorPresent) {
        SokobanMapDelete(sokoMap);
        return 1;
    }
    sokoMap.GatherTargetPositions();
    Solve(sokoMap);
    SokobanMapDelete(sokoMap);
    std::cout << "\n";
    system("pause");
}