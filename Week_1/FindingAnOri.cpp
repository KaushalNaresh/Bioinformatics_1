#include<bits/stdc++.h>

using namespace std;

int main(){

    string text = "GACCATCAAAACTGATAAACTACTTAAAAATCAGT";
    string pattern = "AAA";

    int count = 0;

    for(int i = 0; i <= text.size()-pattern.size(); i++){
        if(text.substr(i, pattern.size()) == pattern){
            count += 1;
        }
    }

    cout<<count;
}