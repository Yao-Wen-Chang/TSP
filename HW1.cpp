#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<cmath>
#include<algorithm>
#include<ctime>
using namespace std;

vector<string> openFile();
vector<int> splitString(string, char);
void TSP(vector<vector<int>>, vector<int>, int, int, int, vector<int>);
int calculateDistance(int, int, int, int);

int minVal = 30000;
vector<int> minPath;

int main() {
    vector<string>data = openFile();
    
    vector<vector<int>> intDataMatrix;
    for(int i = 0; i < data.size(); i++) {
        intDataMatrix.push_back(splitString(data[i], ' '));
    }
    
    vector<int> notYetPass;
    
    for(int i = 1; i < data.size(); i++) 
        notYetPass.push_back(i);
         
    vector<int> path;
    path.push_back(0);
    std::clock_t c_start = std::clock();
    TSP(intDataMatrix, notYetPass, 0, intDataMatrix[0][1], intDataMatrix[0][2], path);
    std::clock_t c_end = std::clock();
    for(int i = 0; i < minPath.size(); i++) { // the path 
        cout << minPath[i]+1 << "->";
    }
    cout << endl << minVal << endl;
    cout << "consuming time: " << (c_end-c_start)/ CLOCKS_PER_SEC << " /s" << endl;
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
  
    for(int i = 0; i < strToSplit.length(); i++) {
          
        if(strToSplit[i] == splitChar) {
            tmpS = strToSplit.substr(tmpI, i-tmpI);
            
            splitInt.push_back(stoi(tmpS, nullptr));
            tmpI = i+1;
        }
	    else if(i == strToSplit.length()-1) {
	        tmpS = strToSplit.substr(tmpI, i-tmpI+1);
	        splitInt.push_back(stoi(tmpS, nullptr));
	        
	    }

    
    }
    return splitInt;

}

void TSP(vector<vector<int>> intDataMatrix, vector<int> notYetPass, int sum, int prevX, int prevY, vector<int>path) {
    if(notYetPass.size() == 0) {   
        sum += calculateDistance(prevX, prevY, intDataMatrix[0][1], intDataMatrix[0][2]);
        path.push_back(0);
        if(sum < minVal) {
            minVal = sum;            
            minPath = path;
        }    
        
    }
    else {
        for(int i = 0; i < notYetPass.size(); i++) {
            int distance = calculateDistance(prevX, prevY, intDataMatrix[notYetPass[i]][1], intDataMatrix[notYetPass[i]][2]);
            path.push_back(notYetPass[i]);
            int tmp = notYetPass[i];
            vector<int>::iterator iter = find(notYetPass.begin(), notYetPass.end(), notYetPass[i]);            
            notYetPass.erase(iter);
            
            TSP(intDataMatrix, notYetPass, sum+distance, intDataMatrix[tmp][1], intDataMatrix[tmp][2], path);
            /* retrieve the value */
            notYetPass.push_back(tmp);
            path.pop_back();
            
            
        }
    }    
    
    
    



}

int calculateDistance(int startX, int startY, int endX, int endY) {
    return sqrt(pow(startX-endX, 2)+pow(startY-endY, 2));
}
