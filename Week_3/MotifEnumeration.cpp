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

int hamDist(string pattern_1, string pattern_2){

    int count = 0;

    for(int i = 0; i < pattern_1.size(); i++){

        if(pattern_1[i] != pattern_2[i]){
            count += 1;
        }
    }

    return count;
}

bool isPresent(string text, string pattern, int k, int d){

    for(int i = 0; i <= text.size()-k; i++){
        string pattern_dash = text.substr(i, k);

        if(hamDist(pattern_dash, pattern) <= d)
            return true;
    }

    return false;
}

int main(){

    int k = 5, d = 1;
    vector<string> text = {"CAAGATATTATTACTCCAGCCCTTC", "GACATACCTCGTCCGGCAACCTAGC", "GAGTCGGTAGCCAGCCCAGCCCGTC", "CTCACCTAGCTTATGCCAGGAAGCT", "CTTTAGCTTATTAGCCTGTTCTAGC", "CTAACCGCATCGAGCTCCCGGCCAA"};

    set<string> patterns;

    bool add;

    for(auto DNA : text){

        for(int i = 0; i <= DNA.size()-k; i++){
            string kmer = DNA.substr(i, k);
            vector<string> neighbours = getNeighbours(kmer, d);
            for(auto neighbour : neighbours){
                add = true;
                for(auto sequence : text){
                    if(!isPresent(sequence, neighbour, k, d)){
                        add = false;    
                        break;
                    }
                }
                if(add)
                    patterns.insert(neighbour);
            }
        }
    }


    for(auto pattern : patterns)
        cout<<pattern<<" "; 

}