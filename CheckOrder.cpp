#include "CheckOrder.h"


void CheckOrder::CreateTable(){
    table_state = vector<vector<int>>(AMOUNT_STATES,vector<int>(AMOUNT_STATES,0));
    for(int i=0;i<AMOUNT_STATES;i++){
        for(int j=0;j<AMOUNT_STATES;j++){
            table_state[i][j]=j;
        }
    }
    table_state[S_CMP][S_CMP]=S_ERROR;
    table_state[S_CMP][S_ASS]=S_ERROR;
    table_state[S_CMP][S_KEY]=S_ERROR;

    table_state[S_ASS][S_CMP]=S_ERROR;
    table_state[S_ASS][S_ASS]=S_ERROR;
    table_state[S_ASS][S_KEY]=S_ERROR;

    table_state[S_KEY][S_ASS]=S_ERROR;
    table_state[S_KEY][S_CMP]=S_ERROR;
}



CheckOrder::CheckOrder(){
    CreateTable();
    curr_state=S0;
}

bool CheckOrder::Analyse(vector<int> vec){
    for(auto e:vec){
        curr_state=table_state[curr_state][e];
        prev_state=curr_state;
        if(curr_state==S_ERROR)
            throw runtime_error("Compile unable! Wrong order!");
    }
    return true;
};