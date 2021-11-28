#include<bits/stdc++.h>

using namespace std;

int main(){

    string pattern = "ATA", ans = "", genome = "GACGATATACGACGATA";

    ofstream omyfile;
    fstream imyfile;

    omyfile.open("patternMatching.txt");
    imyfile.open("Vibrio_cholerae.txt");

    // getline(imyfile, genome);

    // cout<<genome;

    for(int i = 0; i <= genome.size()-pattern.size(); i++){
        
        if(genome.substr(i, pattern.size()) == pattern){
            ans += to_string(i)+" ";
        }
    }

    omyfile << ans;
    omyfile.close();
    imyfile.close();

}