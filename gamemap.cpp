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


    string catStr;
    string tagsStr;
    string genreStr;
    if (!data[2].empty() || !data[3].empty() || !data[4].empty()) {
        catStr = data[2];
	genreStr = data[3];
        tagsStr = data[4];
        
    }
    else
        return; // dont add game if tag AND screenshot empty

    node.appID = appIDStr;
    node.name = nameStr;
    node.category = splitList(catStr);
    node.genre = splitList(genreStr);
    node.tags = splitList(tagsStr);

    map[appIDStr] = node;

    name2id[nameStr] = appIDStr;
}

int GameMap::getCount() {
    return map.size();
}

int getSimilarity(const vector<string>& baseTags, const vector<string>& targetTags) {
    /*
    Given two vectors of string game tags, returns an int representing how many strings were
    found in both vectors.

    Assumptions:
    Both vectors are in alphabetical order, as is default for our dataset.
    */
    int similarity = 0;
    auto baseIter = baseTags.begin();
    auto targetIter = targetTags.begin();
    while (baseIter != baseTags.end() && targetIter != targetTags.end()) {
        if ((*baseIter).size() == (*targetIter).size()) {
            if (*baseIter == *targetIter) {
                similarity++;
                baseIter++;
                targetIter++;
                continue;
            }
        }
        if (*baseIter < *targetIter) {
            baseIter++;
        }
        else {
            targetIter++;
        }
    }
    return similarity;
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

vector<string> GameMap::getAllTraits(string title) {
	
    string id = name2id[title];
	
    set<string> traitSet;
    vector<string> traitVec;

    for (string tag : map[id].tags)
        traitSet.insert(tag);
    for (string genre : map[id].genre)
        traitSet.insert(genre);
    for (string cat : map[id].category)
        traitSet.insert(cat);

    for (string trait : traitSet)
        traitVec.push_back(trait);

    return traitVec;
}

vector<pair<string, int>> GameMap::similarityList(string appid)
{
    vector<pair<string, int>> similarityList;

    for(auto game = map.begin(); game != map.end(); game++)//iterate through data points and add to list
        {
	    //cout << game->second.name;
            if (game->second.appID != appid)//if the game is not a duplicate of the one requested, then compare the two and store in the vector
            {
                vector<string> basetraits = getAllTraits(appid);
		vector<string> comparetraits = getAllTraits(game->second.appID);

		int similarity = getSimilarity(basetraits, comparetraits);

                similarityList.push_back(make_pair(game->second.name, similarity));//average the similarity for all 3 similarity metrics and push to similarity list
            }
        }

    return similarityList;
}
