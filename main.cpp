#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include <cmath>
#include <sstream>
#include <iomanip>
#include <jsoncpp/json/json.h> 

using namespace std;


long long convertToDecimal(string val, int base) {
    long long result = 0;
    for (char c : val) {
        int digit;
        if (isdigit(c)) digit = c - '0';
        else digit = tolower(c) - 'a' + 10;
        result = result * base + digit;
    }
    return result;
}


long long lagrangeInterpolationAtZero(vector<pair<int, long long>>& points) {
    long double result = 0;
    int k = points.size();

    for (int i = 0; i < k; ++i) {
        long double term = points[i].second;
        for (int j = 0; j < k; ++j) {
            if (i != j) {
                term *= -points[j].first;
                term /= (points[i].first - points[j].first);
            }
        }
        result += term;
    }

    return llround(result);  
}

long long solveTestCase(const string& filename) {
    ifstream file(filename);
    Json::Value root;
    file >> root;

    int k = root["keys"]["k"].asInt();
    vector<pair<int, long long>> points;

    for (const auto& key : root.getMemberNames()) {
        if (key == "keys") continue;

        int x = stoi(key);
        int base = stoi(root[key]["base"].asString());
        string value = root[key]["value"].asString();
        long long y = convertToDecimal(value, base);
        points.emplace_back(x, y);

        if (points.size() == k) break;
    }

    return lagrangeInterpolationAtZero(points);
}

int main() {
    long long secret1 = solveTestCase("testcase1.json");
    long long secret2 = solveTestCase("testcase2.json");

    cout << "Secret 1: " << secret1 << endl;
    cout << "Secret 2: " << secret2 << endl;

    return 0;
}
