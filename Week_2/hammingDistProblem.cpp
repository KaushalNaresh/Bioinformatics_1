#include<bits/stdc++.h>

using namespace std;

int main(){

    string s1 = "TACGCATTACAAAGCACA", s2 = "AA";
    int hamDist = 0;

    for(int i= 0; i < s1.size(); i++){

        if(s1[i] != s2[i]){
            hamDist += 1;
        }
    }

    cout<< hamDist;
}