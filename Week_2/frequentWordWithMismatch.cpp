#include<bits/stdc++.h>

using namespace std;

vector<string> getNeighbours(string pattern, int d){

    if(d == 0)
        return {pattern};

    if(pattern.size() == 1){
        return {"A", "T", "G", "C"};
    }

    vector<string> neighbours_1 = getNeighbours(pattern.substr(1, pattern.size()-1), d);
    vector<string> neighbours_2 = getNeighbours(pattern.substr(1, pattern.size()-1), d-1);

    vector<string> neighbours;

    for(int i = 0; i < neighbours_1.size(); i++){
        string temp = pattern[0]+neighbours_1[i];
        neighbours.push_back(temp);
    }

    vector<char> var = {'A', 'T', 'G', 'C'};

    for(auto c : var){
        if(c != pattern[0]){
            for(int i = 0; i < neighbours_2.size(); i++){
                string temp = c+neighbours_2[i];
                neighbours.push_back(temp);
            }
        }
    }

    return neighbours;
}

int getMaxFreq(map<string, int> m){

    int maxSoFar = INT_MIN;
    for(auto itr = m.begin(); itr != m.end(); itr++){
        if(itr->second > maxSoFar){
            maxSoFar = itr->second;
        }
    }

    return maxSoFar;
}

int main(){

    string text = "TGGACTATTCATAGCTCATTGGACTATAGCAGCTGGATCATTCATCTATGGGGGGTGGATCATCTATAGCAGCCTATGGGTCATGGGAGCTCATCTATAGCTCATTGGATGGAGGGGGGAGCTGGAGGGTGGATGGATGGATCATGGGGGGAGCTGGACTATGGGCTATGGGTCATAGCTGGATCATGGGTCATCTATAGCTGGAAGCTGGAAGCGGGTCATCTATTCATAGCGGGCTATTGGACTATTCATAGCTGGACTATCTATTGGATGGACTATAGCTCATAGCTGGAAGCGGGAGCGGGAGCTGGATGGAAGCGGGGGGAGCTGGAAGCCTATAGCAGCGGGTGGACTATTCATCTAT";
    int k = 6, d = 2;

    map<string, int> m;

    for(int i = 0; i <= text.size()-k; i++){

        string pattern = text.substr(i, k);

        vector<string> neighbours = getNeighbours(pattern, d);

        for(int i = 0; i < neighbours.size(); i++){
            if(m.find(neighbours[i]) == m.end()){
                m[neighbours[i]] = 1;
            }
            else{
                m[neighbours[i]] += 1;
            }
        }
    }

    int maxFreq = getMaxFreq(m);
    
    ofstream myfile;
    myfile.open("freqWordWithMismatch.txt");

    for(auto itr = m.begin(); itr != m.end(); itr++){

        if(itr->second == maxFreq){
            myfile << itr->first<<" ";
        }
    }

}