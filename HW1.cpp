#include<iostream>
#include<fstream>
#include<vector>
#include<string>
using namespace std;
vector<string> openFile();
vector<int> splitString(string, char);

int main() {
    vector<string>data = openFile();
    vector<vector<int>> intDataMatrix;
    for(int i = 0; i < data.size(); i++) {
        
        intDataMatrix.push_back(splitString(data[i], ' '));
    }
   
    return 0;
}

vector<string> openFile() {
    vector<string> data; 
    ifstream inputFile("readfile.txt");
    if (inputFile.is_open())
    {
        int i = 0;   
        string line;
        while (getline(inputFile,line, '\n'))
        {
            data.push_back(line);
            i++;
        }
        inputFile.close();
    }
    
    return data;
}
vector<int> splitString(string strToSplit, char splitChar) {
    vector<int> splitInt;
    string tmpS;
    int tmpI = 0;
  
    for(int i = 0; i <= strToSplit.length(); i++) {
        cout << i << "index" << endl;      
        if(strToSplit[i] == '\n' || strToSplit[i] == splitChar) {
            
            tmpS = strToSplit.substr(tmpI, i-tmpI);
            cout << tmpS << "kkk" << endl;
            //splitInt.push_back(stoi(tmpS, nullptr));
            
            tmpI = i+1;
        }
    
    }
    return splitInt;

}
