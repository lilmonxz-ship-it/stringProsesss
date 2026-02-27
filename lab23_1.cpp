#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<cstdlib>

using namespace std;

char score2grade(int score){
    if(score >= 80) return 'A';
    if(score >= 70) return 'B';
    if(score >= 60) return 'C';
    if(score >= 50) return 'D';
    else return 'F';
}

string toUpperStr(string x){
    string y = x;
    for(unsigned i = 0; i < x.size();i++) y[i] = toupper(x[i]);
    return y;
}

void importDataFromFile(string filename, vector<string> &names, vector<int> &scores, vector<char> &grades){
    ifstream file(filename);
    string name;
while(getline(file, name, ':')){
        names.push_back(name);
        
       
        int s1, s2, s3;
        file >> s1 >> s2 >> s3;
        
        int total = s1 + s2 + s3;
        scores.push_back(total);
        grades.push_back(score2grade(total));
        
        string temp;
        getline(file, temp); 
    }
}



void getCommand(string &command, string &key){
    cout << "Please input your command:\n";
    cin >> command;
    getline(cin, key);
    
    size_t firstChar = key.find_first_not_of(" \t");
    
    if(firstChar != string::npos) {
        key = key.substr(firstChar);
    } else {
        key = "";
    }
}

void searchName(const vector<string> &names, const vector<int> &scores, const vector<char> &grades, string key){

cout << "---------------------------------\n";
    bool found = false;
    for(size_t i = 0; i < names.size(); i++) {
        
        if(toUpperStr(names[i]) == key) {
            cout << names[i] << "'s score = " << scores[i] << "\n";
            cout << names[i] << "'s grade = " << grades[i] << "\n";
            found = true;
        }
    }
    if(!found) cout << "Cannot found.\n";
    cout << "---------------------------------\n";




}

void searchGrade(const vector<string> &names, const vector<int> &scores, const vector<char> &grades, string key){
    cout << "---------------------------------\n";
    bool found = false;
    char targetGrade = key.empty() ? ' ' : key[0]; 
    
    for(size_t i = 0; i < names.size(); i++) {
        if(grades[i] == targetGrade) {
            cout << names[i] << " (" << scores[i] << ")\n";
            found = true;
        }
    }
    if(!found) cout << "Cannot found.\n";
    cout << "---------------------------------\n";
}


int main(){
    string filename = "name_score.txt";
    vector<string> names;
    vector<int> scores;
    vector<char> grades; 
    importDataFromFile(filename, names, scores, grades);
    
    do{
        string command, key;
        getCommand(command,key);
        command = toUpperStr(command);
        key = toUpperStr(key);
        if(command == "EXIT") break;
        else if(command == "GRADE") searchGrade(names, scores, grades, key);
        else if(command == "NAME") searchName(names, scores, grades, key);
        else{
            cout << "---------------------------------\n";
            cout << "Invalid command.\n";
            cout << "---------------------------------\n";
        }
    }while(true);
    
    return 0;
}
