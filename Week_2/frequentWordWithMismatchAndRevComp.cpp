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

string revComp(string s){

    string ans = "";

    for(int i = s.size()-1; i >= 0; i--){

        if(s[i] == 'A')
            ans += "T";
        else if(s[i] == 'T')
            ans += "A";
        else if(s[i] == 'G')
            ans += "C";
        else if(s[i] == 'C')
            ans += "G";
    }

    return ans;
}

int main(){

    string text = "TTGTTTCATGTTTTTTTTTCATTTGATTGAGACATCATCATTTGAGACATTTTTTTGAGATTGAGAGATTTTGATTTTCATTTGACATGTGAGATTTTCATCATGAGATTGTTTCATTTGAGATTTTCATTTTTCATGTGAGATTGTGTTTTTGATTGTTTTTTTTTGTGATTCATTTTTTTCATCATCATGTTTGACATTTTTGA";
    int k = 6, d = 3;

    map<string, int> m;

    for(int i = 0; i <= text.size()-k; i++){

        string pattern = text.substr(i, k);

        vector<string> neighbours_1 = getNeighbours(pattern, d);
        vector<string> neighbours_2 = getNeighbours(revComp(pattern), d);

        for(int i = 0; i < neighbours_1.size(); i++){
            if(m.find(neighbours_1[i]) == m.end()){
                m[neighbours_1[i]] = 1;
            }
            else{
                m[neighbours_1[i]] += 1;
            }
        }

        for(int i = 0; i < neighbours_2.size(); i++){
            if(m.find(neighbours_2[i]) == m.end()){
                m[neighbours_2[i]] = 1;
            }
            else{
                m[neighbours_2[i]] += 1;
            }
        }
    }

    int maxFreq = getMaxFreq(m);
    
    ofstream myfile;
    myfile.open("freqWordWithMismatchAndRevComp.txt");

    for(auto itr = m.begin(); itr != m.end(); itr++){

        if(itr->second == maxFreq){
            myfile << itr->first<<" ";
        }
    }
}