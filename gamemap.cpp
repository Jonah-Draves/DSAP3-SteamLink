#include <map>
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
    if (appIDStr.empty())
        return;

	// might be inappropriate game
    int age = 17;
    if (stoi(data[2]) > age)
        return;

    // name may be empty?
    string nameStr;
    if (!data[1].empty())
        nameStr = data[1].substr(0,data[1].size());
    else
        return; // dont add empty name games


    string catStr;
    string tagsStr;
    string genreStr;
    if (!data[3].empty() || !data[4].empty() || !data[5].empty()) {
        catStr = data[3];
        genreStr = data[4];
        tagsStr = data[5];
    }
    else
        return; // dont add game if tag AND screenshot empty

	vector<string> catVec = splitList(catStr);
    vector<string> genVec = splitList(genreStr);
    vector<string> tagVec = splitList(tagsStr);
    vector<string> censor = {"Hentai","Sexual Content"};

    for (auto nonoword : censor) {
        if (find(catVec.begin(),catVec.end(),nonoword)!=catVec.end() ||
            find(genVec.begin(),genVec.end(),nonoword)!=genVec.end() ||
            find(tagVec.begin(),tagVec.end(),nonoword)!=tagVec.end())
            return;
    }

    node.appID = appIDStr;
    node.name = nameStr;
    node.category = catVec;
    node.genre = genVec;
    node.tags = tagVec;

    map[appIDStr] = node;

    name2id[nameStr] = appIDStr;
}

bool GameMap::isNameIn(string name) {
    return isIn(name2id[name]);
}

bool GameMap::isIn(string appID) {
    return map.find(appID) != map.end();
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
        similarity--;
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

vector<pair<string, int>> GameMap::similarityList(string name)
{
    vector<pair<string, int>> similarityList;
    vector<string> basetraits = getAllTraits(name);
    for(auto game = map.begin(); game != map.end(); game++)//iterate through data points and add to list
        {
	    //cout << game->second.name;
            if (game->second.name != name)//if the game is not a duplicate of the one requested, then compare the two and store in the vector
            {
		        vector<string> comparetraits = getAllTraits(game->second.name);

		        int similarity = getSimilarity(basetraits, comparetraits);

                similarityList.push_back(make_pair(game->second.name, similarity));//average the similarity for all 3 similarity metrics and push to similarity list
            }
        }

    return similarityList;
}

vector<pair<string, int>> GameMap::nClosest(string targetID, int n, bool useHeap) {
    /*
    Given a string game ID, int number of closest games, and a bool to choose the number of closest games,
    returns the n closest games in terms of similarity score to that of the target.
    */
    vector<pair<string, int>> sorted;
    if (useHeap) {
        vector<pair<string, int>> sList = similarityList(targetID);
         sorted = heapSort(sList);
    }
    else {
        sorted = similarityList(targetID);
        quickSort(sorted);
    }
    vector<pair<string, int>> nClosest;
    for (int i = 0; i < n; i++) {
        nClosest.push_back(sorted[i]);
    }
    return nClosest;
}
