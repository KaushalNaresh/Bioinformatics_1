#include<bits/stdc++.h>

using namespace std;

int main(){

    string s = "CCAGATC", ans = "";

    ofstream myfile;

    myfile.open("reverseComplement.txt");

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

    myfile << ans;

    myfile.close();
}