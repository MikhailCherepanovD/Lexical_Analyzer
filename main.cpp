#include <iostream>
#include <vector>
#include <map>
#include <unordered_set>
#include <set>
#include <queue>
#include "algorithm"
#include "LexicalAnalyzer.h"
#include "fstream"
using namespace std;
void PrintVP( vector<pair<string,string>>  sp){
    for(auto p:sp ) {
        cout << p.first << ":  " << p.second;
        cout<<endl;
    }
    cout<<endl<<endl;

}
void PrintVP( set<pair<string,string>>  sp){
    for(auto p:sp ) {
        cout << p.first << ":  " << p.second;
        cout<<endl;
    }
    cout<<endl<<endl;

}
string ReadFile(string file_name){
    ifstream fin(file_name);

    string strh;
    string str;

    while(!fin.eof()){
        getline(fin, strh);
        str += strh;
        if (!fin.eof()){
            str += '\n';
        }
    }
    return str;
}



void OutputMD(const set<std::pair<std::string, std::string>>& data, string filename) {
    std::ofstream markdownFile(filename);

    // Записываем заголовки таблицы
    markdownFile << "| Type | Value |\n";
    markdownFile << "| --------- | -------- |\n";

    // Записываем данные в таблицу
    for (const auto& pair : data) {
        markdownFile << "| " << pair.first << " | " << (pair.second == ">" ? "\\>" : pair.second) << " |\n";

    }
}
int main() {
    LexicalAnalyzer LA;

    //string test_str=ReadFile("input.txt");
    string test_str=ReadFile("input1.txt");
    //string test_str=ReadFile("input2.txt");
    cout<<LA.Preproccessing(test_str)<<endl;
    vector<pair<string,string>>  vp=LA.Analyse(test_str);
    PrintVP(vp);
    vector<int> order=LA.GetOrderTypes(vp);
    CheckOrder Chek;
    Chek.Analyse(order);
    set<pair<string,string>>mp(vp.begin(),vp.end());
    cout<<"map:\n\n\n";
    OutputMD(mp,"output.md");

    return 0;
}
