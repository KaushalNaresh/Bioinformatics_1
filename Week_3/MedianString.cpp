#include<bits/stdc++.h>

using namespace std;

int findHamDist(string pattern1, string pattern2){

    int count = 0;

    for(int i = 0; i < pattern1.size(); i++){
        if(pattern1[i] != pattern2[i])
            count += 1;
    }

    return count;
}

int d(string text, string pattern){

    int min = INT_MAX;

    for(int i = 0; i <= text.size()-pattern.size(); i++){
        string pattern_dash = text.substr(i, pattern.size());
        int hamDist = findHamDist(pattern_dash, pattern);

        if(hamDist < min)
            min = hamDist;
    }

    return min;
}

vector<string> generateAllKmers(int k){

    vector<string> kmers = {};

    vector<string> neuc = {"A", "G", "T", "C"};

    for(int i = 0; i < k; i++){
        int size = kmers.size();
        vector<string> newVec;
        for(int j = 0; j < 4; j++){
            if(size == 0){
                newVec.push_back(neuc[j]);
                continue;
            }
            for(int k = 0; k < size; k++){
                string temp = kmers[k]+neuc[j];
                newVec.push_back(temp);
            }
        }
        kmers = newVec;
    }

    return kmers;
}

// set<string> getAllKmers(vector<string> DNA, int k){

//     set<string> Kmers;

//     for(auto text: DNA){
//         for(int i = 0; i <= text.size()-k; i++){
//             Kmers.insert(text.substr(i, k));
//         }
//     }

//     return Kmers;
// }

int main(){

    int k = 6;
    vector<string> DNA = {"AGATAAGCTGATCCGCTTGAAAGGGTTAGGTCTTATGCGGGA",
                        "AATTTATCTTCAAAGAGCGCAAGTACTGATCGCAGCCCTAGG",
                        "AGCGGTACCAACCTATATTCTGCCAAACGATCCCCAGCTGAT",
                        "GGACGATAGACCGACGTCAAATCTCCTGATATATGCGCACCA",
                        "CAAAACCTTGGCGTCGCTACTCCGGCGGTTGGACACACTGAT",
                        "TCGTCAGCACGGGCTTCAGTCCTATAGTACCCCATCGCTGAT",
                        "TTGATATCTGATAATTCGAGAGTCCGAGGCAGAATCATGTGG",
                        "GGCAGCAAGGTTCCGCCTTCTGATGGACACGGATGCAGCCTA",
                        "ACGGTATTGGACCCCGCCGGCGTCTCTGATATGTTGCAAAAA",
                        "GATATAAACGTCGGGCCTTCAATAGGTCCGCTCGCCTCTGAT"};

    int min = INT_MAX;

    vector<string> Kmers = generateAllKmers(k);
    // set<string> Kmers = getAllKmers(DNA, k);

    // for(auto kmer : Kmers){
    //     cout<<kmer<<endl;
    // }
    // set<string> s(Kmers.begin(), Kmers.end());
    // cout<<Kmers.size()<<" "<<s.size();

    set<string> patterns;

    for(auto kmer : Kmers){
        int currMin = 0;
        for(auto text : DNA){
            currMin += d(text, kmer);
        }
        //cout<<currMin<<endl;

        if(min > currMin){
            min = currMin;
            patterns = {};
            patterns.insert(kmer);
        }
        if(min == currMin){
            patterns.insert(kmer);
        }
    }

    for(auto pattern: patterns){
        cout<<pattern<<endl;
    }

}