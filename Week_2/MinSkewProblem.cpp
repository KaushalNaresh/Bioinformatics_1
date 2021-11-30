#include<bits/stdc++.h>

using namespace std;

int main(){

    string genome;
    vector<int> idx;
    int currSkew = 0, minSkewSoFar = INT_MAX;

    fstream myfile;

    myfile.open("MinSkewGenome.txt");

    getline(myfile, genome);

    for(int i = 0; i < genome.size(); i++){
        if(genome[i] == 'G')
            currSkew += 1;
        else if(genome[i] == 'C')
            currSkew -= 1;

        if(minSkewSoFar > currSkew){
            minSkewSoFar = currSkew;

            idx = {i+1};

        }    
        else if(minSkewSoFar == currSkew){
            idx.push_back(i+1);
        }
    }

    for(auto i : idx){
        cout<<i<<" ";
    }
}