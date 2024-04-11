#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <unordered_set>
#include <set>
#include <queue>
#include "algorithm"
using namespace std;

enum State1{
    S0,           //0
    S_KEY,        //1
    S_CMP,        //2
    S_VAR,        //3
    S_FLOAT,      //4
    S_INT,        //5
    S_ASS,        //6
    S_ERROR       //7
};
class CheckOrder {


    const int AMOUNT_STATES=8;
    vector<vector<int>> table_state;
    int curr_state;
    int prev_state;

public:
    void CreateTable();
    CheckOrder();
    bool Analyse(vector<int>);

};



