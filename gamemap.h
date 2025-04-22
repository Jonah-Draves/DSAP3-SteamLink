#include <vector>
#include <unordered_map>
#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
#include <set>
#include <utility>
#include <map>
#include <algorithm>

#include "sorts.h"

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

    std::map<string,string> name2id;

    vector<string> splitList(string& str);

public:

    void insert(vector<string> data);

    int getCount();

    vector<string> getAllTraits(string title);

    vector<pair<string, int>> similarityList(string appid);

    vector<pair<string, int>> nClosest(string ID, int n, bool heapSort = true);
};

vector<string> splitRow(string& str);

GameMap generateMap(string filename);

vector<pair<string, int>> similarityList(string appid);

