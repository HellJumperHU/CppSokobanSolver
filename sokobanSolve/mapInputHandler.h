//#pragma once
#ifndef MAPINPUTHANDLER_H
#define MAPINPUTHANDLER_H

#include <iostream>
#include <string>
#include <fstream>
#include "sokoMap.h"


bool IsANumber(std::string input);

void GetMapSize(SokoMap& sokoMap, const std::string filepath, std::ifstream& sokobanmapsizereader);

void AllocateMemoryForMap(SokoMap& sokoMap);

bool IsMapElement(const std::string actualrowofmap, unsigned short rowindex, unsigned short& numberofplayercharacter, unsigned short& numberofcrates, unsigned short& numberofdestination);

//void FillTheGapInTheActualRow(std::string& actualrowofmap, const unsigned short column);

void GetMap(SokoMap& sokoMap,State& initialState, const std::string filepath, std::ifstream& sokobanmapreader, bool& iserrorpresent);

void SokobanMapReader(SokoMap& sokoMap, bool& iserrorpresent, const std::string filepath);

bool IsMapBorderedWithWall(SokoMap sokoMap);

void SokobanMapDelete(SokoMap& sokoMap);

//void GiveWallBorderToMap(SokoMap& sokoMap);

//void WriteOutMap(SokoMap sokoMap);

#endif