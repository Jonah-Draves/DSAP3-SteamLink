#include "gamemap.h"


vector<string> GameMap::splitList(string& tagStr) {
    istringstream ss(tagStr);

    vector<string> tagsVec;
    string line;
    while(getline(ss,line,',')){
        tagsVec.push_back(line);
    }

    return tagsVec;
}

vector<string> splitRow(string& str) {
    vector<string> result;
    string cell;
    bool inQuotes = false;

    for (size_t i = 0; i < str.length(); ++i) {
        char c = str[i];

        if (c == '"') {
            if (inQuotes && i + 1 < str.length() && str[i + 1] == '"') {
                // Escaped double quote ("")
                cell += '"';
                ++i;
            } else {
                inQuotes = !inQuotes;
            }
        } else if (c == ',' && !inQuotes) {
            result.push_back(cell);
            cell.clear();
        } else {
            cell += c;
        }
    }

    result.push_back(cell); // Add the last cell
    return result;
}


void GameMap::insert(vector<string> data) {
    GameNode node;

    if (data.size()!=6) {
        cerr << "Warning: Data parsing error" << endl;
        return;
    }

    // appID never empty hopefully, since it's in the csv file
    string appIDStr = data[0];

    // name may be empty?
    string nameStr;
    if (!data[1].empty())
        nameStr = data[1].substr(0,data[1].size());
    else
        return; // dont add empty name games


    string tagsStr;
    string genreStr;
    string traitStr;
    if (!data[2].empty() || !data[3].empty() || !data[4].empty()) {
        genreStr = data[2];
        tagsStr = data[3];
        traitStr = data[4];
    }
    else
        return; // dont add game if tag AND screenshot empty

    node.appID = appIDStr;
    node.name = nameStr;
    node.genre = splitList(genreStr);
    node.tags = splitList(tagsStr);
    node.traits = splitList(traitStr);

    map[appIDStr] = node;
}

int GameMap::getCount() {
    return map.size();
}

GameMap generateMap(string filename) {
    GameMap gameMap;

    ifstream file(filename);

    if (!file.is_open()) {
        cerr << "Games file did not open." << endl;
        return gameMap;
    }

    int count = 0;
    string line;
    while(getline(file,line)) {
        vector<string> data = splitRow(line);

        if (count != 0) {
            gameMap.insert(data);
        }
        count++;
    }

    cout << "Loaded " << gameMap.getCount() << " games." << endl;

    return gameMap;
}

vector<string> GameMap::getAllTraits(string appID_) {
    set<string> traitSet;
    vector<string> traitVec;

    for (string tag : map[appID_].tags)
        traitSet.insert(tag);
    for (string cat : map[appID_].category)
        traitSet.insert(cat);
    for (string genre : map[appID_].genre)
        traitSet.insert(genre);

    for (string trait : traitSet)
        traitVec.push_back(trait);

    return traitVec;
}
