#include<bits/stdc++.h>

using namespace std;

int getHamDist(string motif, string pattern){

    int hamDist = 0;

    for(int i=0; i < motif.size(); i++){
        if(motif[i] != pattern[i])
            hamDist += 1;
    }

    return hamDist;
}

int main(){

    string pattern, input, temp;
    vector<string> DNA;

    int itr = 0;

    fstream infile;
    infile.open("dataset_5164_1.txt");


    while(getline(infile, input)){
        stringstream ss(input);
        while(ss >> temp){
            if(itr == 0){
                pattern = temp;
            }
            else{
                DNA.push_back(temp);
            }
        }
        itr += 1;
    }

    int count = 0, k = pattern.size();

    for(auto text : DNA){
        int currCount = INT_MAX;
        string motif;
        for(int i = 0; i <= text.size()-k; i++){
            int hamDist = getHamDist(text.substr(i, k), pattern);
            if(currCount > hamDist){
                currCount = hamDist;
                motif = text.substr(i, k);
            }
        }
        count += currCount;
    }

    cout<<count;
}