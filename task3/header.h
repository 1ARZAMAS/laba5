#pragma once
void createPlane(std::vector<std::string>& towns, std::vector<std::string>& planes, std::map <std::string, std::vector <std::string>>& route);
void planesForTown(std::map<std::string, std::vector<std::string>>& route);
void townsForPlane(std::map<std::string, std::vector<std::string>>& route);
void displayPlanes(std::vector<std::string>& planes, std::map<std::string, std::vector<std::string>>& route);