#include<bits/stdc++.h>

using namespace std;


int hamDist(string s1, string s2){

    int hamDist = 0;

    for(int i = 0; i < s1.size(); i++){
        if(s1[i] != s2[i])
            hamDist+=1;
    }

    return hamDist;
}


int main(){

    string pattern = "AAAAA", genome = "AACAAGCTGATAAACATTTAAAGAG";
    int d = 4;
    vector<int> idx;

    // fstream myfile;

    // myfile.open("approxPattrnMatch.txt");

    // getline(myfile, genome);
    // getline(myfile, genome);

    for(int i = 0; i <= genome.size()-pattern.size(); i++){

        string genomeStrand = genome.substr(i, pattern.size());

        if(hamDist(genomeStrand, pattern) <= d)
            idx.push_back(i);
    }

    ofstream myfile2;
    myfile2.open("idxForApproxPatternMatch.txt");

    for(auto i : idx)
        myfile2 << i <<" ";
}