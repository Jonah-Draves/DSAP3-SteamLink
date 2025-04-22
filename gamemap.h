#include <vector>
#include <unordered_map>
#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
#include <set>
#include <utility>
#include <map>

using namespace std;

class GameMap {

    struct GameNode {
        string appID;
        string name;
        vector<std::string> category;
        vector<std::string> genre;
        vector<std::string> tags;
    };

    unordered_map<string,GameNode> map;

    map<string,string> name2id;

    vector<string> splitList(string& str);

public:

    void insert(vector<string> data);

    int getCount();

    vector<string> getAllTraits(string appID_);

    vector<pair<string, int>> similarityList(string appid);
};

vector<string> splitRow(string& str);

GameMap generateMap(string filename);

vector<pair<string, int>> similarityList(string appid);
