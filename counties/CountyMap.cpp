#include "CountyMap.h"
#include <stdexcept>

CountyMap::CountyMap(vector<County> countiesInput, vector<vector<bool>> adjacencyMatrix) {
    counties = countiesInput;
    int n = counties.size();
    adjacency.resize(n);

    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (adjacencyMatrix[i][j]) {
                adjacency[i].insert(j);
                adjacency[j].insert(i);
            }
        }
    }
}

CountyMap::CountyMap(const CountyMap& other) {
    counties = other.counties;
    adjacency = other.adjacency;
}

CountyMap::~CountyMap() {
}

County CountyMap::getCounty(int countyID) {
    if (countyID < 0 || countyID >= (int)counties.size()) {
        throw out_of_range("Invalid county ID");
    }
    return counties[countyID];
}

bool CountyMap::countyAdjacency(int countyID1, int countyID2) {
    if (countyID1 < 0 || countyID1 >= (int)counties.size()) return false;
    if (countyID2 < 0 || countyID2 >= (int)counties.size()) return false;
    return adjacency[countyID1].count(countyID2) > 0;
}

int CountyMap::getNumCounties() {
    return counties.size();
}

vector<int> CountyMap::getAdjacentCounties(int countyID) {
    if (countyID < 0 || countyID >= (int)counties.size()) {
        throw out_of_range("Invalid county ID");
    }
    return vector<int>(adjacency[countyID].begin(), adjacency[countyID].end());
}

bool CountyMap::checkValidItinerary(vector<int> itinerary) {
    for (int i = 0; i + 1 < (int)itinerary.size(); i++) {
        if (!countyAdjacency(itinerary[i], itinerary[i + 1])) {
            return false;
        }
    }
    return true;
}
