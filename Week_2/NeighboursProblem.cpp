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

int main(){

    string text = "CGACCTGGCGGT";
    int d = 2;

    ofstream myfile;

    myfile.open("Neighbours.txt");

    vector<string> neighbours = getNeighbours(text, d);

    for(auto neigh : neighbours){
        myfile<<neigh<<" ";
    }

    myfile.close();
}

/*               AAC, 1  [AAT, AAA, AAG, ATC, AGC, ACC, TAC, GAC, CAC]
        AC, 1 [AT,AA,AG,TC,GC,CC]          AC, 0 [AC]
C, 1 [T,A,G]                   C, 0 [C]                          
*/
