#include<bits/stdc++.h>

using namespace std;

int getHamDist(string motif, string consString){

    int hamDist = 0;

    for(int i=0; i < motif.size(); i++){
        if(motif[i] != consString[i])
            hamDist += 1;
    }

    return hamDist;
}

int score(vector<string> motifs, string consString){

    int count = 0;

    for(auto motif : motifs){
        count += getHamDist(motif, consString);
    }
    return count;
}

vector<vector<float>> getProfileMatrix(vector<string> motifs){

    vector<vector<float>> profMatrix(4);

    float t = motifs.size();

    for(int i = 0; i < motifs[0].size(); i++){
        int countOfA = 0, countOfT = 0, countOfG = 0, countOfC = 0;
        for(int j = 0; j < motifs.size(); j++){
            if(motifs[j][i] == 'A')
                countOfA += 1;
            else if(motifs[j][i] == 'T')
                countOfT += 1;
            else if(motifs[j][i] == 'G')
                countOfG += 1;
            else if(motifs[j][i] == 'C')
                countOfC += 1;
        }
        profMatrix[0].push_back((countOfA+1)/(t+4));
        profMatrix[1].push_back((countOfT+1)/(t+4));
        profMatrix[2].push_back((countOfG+1)/(t+4));
        profMatrix[3].push_back((countOfC+1)/(t+4));
    }

    return profMatrix;
}

string getMostProbableKmer(vector<vector<float>> profMatrix, string text){

    float prob = -1;
    string ans;
    int k = profMatrix[0].size();

    for(int i = 0; i <= text.size()-k; i++){

        string pattern = text.substr(i, k);
        float currProb = 1;

        for(int j = 0; j < pattern.size(); j++){
            if(pattern[j] == 'A'){
                currProb *= profMatrix[0][j];
            }
            else if(pattern[j] == 'T'){
                currProb *= profMatrix[1][j];
            }
            else if(pattern[j] == 'G'){
                currProb *= profMatrix[2][j];
            }
            else if(pattern[j] == 'C'){
                currProb *= profMatrix[3][j];
            }
        }
    
        if(currProb > prob){
            ans = pattern;
            prob = currProb;
        }
    }

    return ans;
}

string getConsensusString(vector<vector<float>> profMatrix){

    int k = profMatrix[0].size();
    int t = profMatrix.size();
    string conString = "";

    for(int i = 0; i < k; i++){
        float min = -1;
        int idx = 0;
        for(int j = 0; j < t; j++){
            if(profMatrix[j][i] > min){
                min = profMatrix[j][i];
                idx = j;
            }
        }
        if(idx == 0)
            conString += "A";
        else if(idx == 1)
            conString += "T";
        else if(idx == 2)
            conString += "G";
        else
            conString += "C";
    }

    return conString;
}

int main(){

    fstream infile;
    infile.open("dataset_161_5.txt");
    string input, temp;
    int itr = 0, itr_1 = 0;

    int k, t;
    vector<string> DNA;

    while(getline(infile, input)){
        stringstream ss(input);
        while(ss >> temp){
            if(itr == 0){
                if(itr_1 == 0)
                    k = stoi(temp);
                else
                    t = stoi(temp);
                itr_1 += 1;
            }
            else{
                DNA.push_back(temp);
            }
        }
        itr += 1;
    }

    int time = 0, outerMin = INT_MAX;
    vector<string> outerBestMotifs;

    while(time < 1000){

        vector<string> bestMotifs;

        for(auto text : DNA){
            int randN = rand()%(text.size()-k);
            bestMotifs.push_back(text.substr(randN, k));
        }

        vector<vector<float>> profMatrix = getProfileMatrix(bestMotifs);

        string consString = getConsensusString(profMatrix);
        int minScore = score(bestMotifs, consString);
        

        while(true){

            vector<string> currMotifs;

            for(auto text : DNA){

                string motif = getMostProbableKmer(profMatrix, text);
                currMotifs.push_back(motif); 
            }

            consString = getConsensusString(profMatrix);
            int currScore = score(currMotifs, consString);
            profMatrix = getProfileMatrix(currMotifs);

            if(currScore < minScore){
                minScore = currScore;
                bestMotifs = currMotifs;
            }
            else{
                break;
            }
        }

        if(outerMin > minScore){
            outerMin = minScore;
            outerBestMotifs = bestMotifs;
        }
    
        time += 1;
    }

    for(auto bestMotif : outerBestMotifs){
            cout<<bestMotif<<" ";
    }
    cout<<endl;

}