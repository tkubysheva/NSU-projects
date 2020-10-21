// include guard!!!!!!111111oneoneoneoneone
// в каждом заголовном файле

// clang-format
#include <conio.h> // ???
#include <iomanip> //  ??
#include <string>
#include <set>
#include <memory>

#include "factory.h" // ??
#include "table.h" // ???



void OneGame(std::unique_ptr<Unit>& ,
             std::unique_ptr<Unit>& ,
             std::unique_ptr<Unit>& ,
             std::vector<std::vector<char>>&,
             bool ,
             std::string& ,
             std::string& ,
             std::string& );

void fast(std::set<std::string>&, int );

void detailed(std::set<std::string>&);

void tour(const std::string& ,const std::string& ,const std::string& , std::map<std::string, int>& );

void tournament(std::set<std::string>& );
