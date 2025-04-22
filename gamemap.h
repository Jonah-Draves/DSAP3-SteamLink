#include <vector>
#include <unordered_map>
#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
#include <set>

using namespace std;

class GameMap {

    struct GameNode {
        string appID;
        string name;
        vector<std::string> genre;
        vector<std::string> tags;
        vector<std::string> traits;

    };

    unordered_map<string,GameNode> map;

    vector<string> splitList(string& str);

public:

    void insert(vector<string> data);

    int getCount();

    vector<string> getAllTraits(string appID_);

};

vector<string> splitRow(string& str);

GameMap generateMap(string filename);
