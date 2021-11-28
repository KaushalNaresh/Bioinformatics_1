#include<bits/stdc++.h>

using namespace std;

int main(){

    string text = "CGCCTAAATAGCCTCGCGGAGCCTTATGTCATACTCGTCCT";
    int k = 3;

    map<string, int> m;

    for(int i = 0; i <= text.size()-k + 1; i++){

        string pattern = text.substr(i, k);

        if(m.find(pattern) == m.end())
            m[pattern] = 1;
        else
            m[pattern] += 1;
    }

    int max = INT_MIN;

    for(auto itr = m.begin(); itr != m.end(); itr++){
        if(max < itr->second)
            max = itr->second;
    }

    string ans = "";

    for(auto itr = m.begin(); itr != m.end(); itr++){

        if(itr->second == max){
            ans += itr->first+" ";
        }
    }

    cout<<ans;
}