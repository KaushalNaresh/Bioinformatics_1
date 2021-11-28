#include<bits/stdc++.h>

using namespace std;

map<string, int> getFreqTable(string s, int k){  // O(L-k+1)

    map<string, int> m;

    for(int i = 0; i <= s.size()-k; i++){

        string pattern = s.substr(i, k);
        if(m.find(pattern) == m.end()){
            m[pattern] = 1;
        }
        else{
            m[pattern] += 1;
        }
    }

    return m;
}

void gettMostFreqKmer(map<string, int> m, set<string> &s, int t){

    for(auto itr = m.begin(); itr != m.end(); itr++){
        if(t <= itr->second){
            s.insert(itr->first);
        }
    }
}

int main(){

    string genome;
    int k = 9, L = 500, t = 3;

    fstream imyfile;
    imyfile.open("E_coli.txt");

    getline(imyfile, genome);
    
    set<string> s;

    string window = genome.substr(0, L);
    map<string, int> m = getFreqTable(window, k);
    gettMostFreqKmer(m, s, t);

    for(int i = 1; i <= genome.size()-L; i++){  // O(n-L)

        string kmerToDel = genome.substr(i-1, k);
        int endIdx = (i+L-1)-k+1;
        string kmerToAdd = genome.substr(endIdx, k);

        m[kmerToDel] -= 1;

        if(m.find(kmerToAdd) == m.end()){
            m[kmerToAdd] = 1;
        }
        else{
            m[kmerToAdd] += 1;
        }

        if(m[kmerToAdd] >= t)
            s.insert(kmerToAdd);

    }

    ofstream myfile;
    myfile.open("clumps.txt");

    for(auto itr = s.begin(); itr != s.end(); itr ++){
        myfile << *itr+" ";
    }
}