#include "LexicalAnalyzer.h"

void LexicalAnalyzer::CreateTable(){
    table_state=vector<vector<int>>(AMOUNT_STATES,vector<int>(AMOUNT_CHARS,S_ERROR));
    for( int i=S0;i<S_ERROR;i++){
        table_state[i][' ']=S0;
        table_state[i][';']=S0;
        table_state[i]['\t']=S0;
        table_state[i]['\n']=S0;
        table_state[i]['\0']=S0;   // возврат
    }

//S0


    for(int i='a';i<='z';i++){
        table_state[S0][i]=S_VAR;
    }
    for(int i='A';i<='Z';i++){
        table_state[S0][i]=S_VAR;
    }
    for(int i='0';i<='9';i++){
        table_state[S0][i]=S_INTEGER;
    }
    table_state[S0]['#']=S_COMMENT;
    table_state[S0][':']=S_ASSIGN;
    table_state[S0]['.']=S_FLOAT_VAL;

    table_state[S0]['<']=S0;
    table_state[S0]['=']=S0;
    table_state[S0]['>']=S0; // возвращаем значение

    table_state[S0]['d']=S_DO1;
    table_state[S0]['w']=S_W1;




//S_DO1,S_DO_FINAL,S_W1,S_W2,S_W3,S_W4,S_WHILE_FINAL
    vector<int> temp_vec_const{ S_DO1,S_DO_FINAL,S_W1,S_W2,S_W3,S_W4,S_WHILE_FINAL};
    for(auto e:temp_vec_const) {
        for (int i = 'a'; i <= 'z'; i++) {
            table_state[e][i] = S_VAR;
        }
        for (int i = 'A'; i <= 'Z'; i++) {
            table_state[e][i] = S_VAR;
        }
        for (int i = '0'; i <= '9'; i++) {
            table_state[e][i] = S_VAR;
        }
    }
    table_state[S_DO1]['o'] = S_DO_FINAL; //S_DO1
    //S_DO_FINAL
    table_state[S_W1]['h'] = S_W2; //S_W1
    table_state[S_W2]['i'] = S_W3; //S_W2
    table_state[S_W3]['l'] = S_W4; //S_W3
    table_state[S_W4]['e'] = S_WHILE_FINAL; //S_W3
    //S_WHILE_FINAL

//S_INTEHER

    for (int i = 'a'; i <= 'z'; i++) {
        table_state[S_INTEGER][i] = S_VAR;
    }
    for (int i = 'A'; i <= 'Z'; i++) {
        table_state[S_INTEGER][i] = S_VAR;
    }
    for (int i = '0'; i <= '9'; i++) {
        table_state[S_INTEGER][i] = S_INTEGER;
    }
    table_state[S_INTEGER]['.'] = S_FLOAT_VAL;
//S_FLOAT_VAL
    for (int i = '0'; i <= '9'; i++) {
        table_state[S_FLOAT_VAL][i] = S_FLOAT_VAL;
    }





// S_VAR

    for (int i = 'a'; i <= 'z'; i++) {
        table_state[S_VAR][i] = S_VAR;
    }
    for (int i = 'A'; i <= 'Z'; i++) {
        table_state[S_VAR][i] = S_VAR;
    }
    for (int i = '0'; i <= '9'; i++) {
        table_state[S_VAR][i] = S_VAR;
    }
//S_comment

    for(int i=0;i<128;i++){
        table_state[S_COMMENT][i] = S_COMMENT;
    }
    table_state[S_COMMENT]['\n'] = S0;
    table_state[S_COMMENT]['\0'] = S0;

//S_assign
    table_state[S_ASSIGN]['='] = S0;
    table_state[S_ASSIGN][' ']=S_ERROR;
    table_state[S_ASSIGN][';']=S_ERROR;
    table_state[S_ASSIGN]['\n']=S_ERROR;
    table_state[S_ASSIGN]['\0']=S_ERROR;

    table_state[S_W1]['h'] = S_W2; //S_W1
};









LexicalAnalyzer::LexicalAnalyzer(){
    CreateTable();
    prev_state=S0;
    curr_str.reserve(16);
};


vector<pair<string,string>>  LexicalAnalyzer::Analyse(string str){
    str= Preproccessing(str);

    vector<pair<string,string>>   ans;
    for(int elem:str){
        if(curr_state==S0){
            pair<string,string> temp_pair= GenerateOutput();
            if(temp_pair.first!="comment" && temp_pair.second!=""){
                ans.push_back(temp_pair);
            }
            curr_str.clear();
        }

        if(elem!='\n' && elem!='\t' && elem!='\0' && elem!=' '&& elem!=';'){
            curr_str.push_back(elem);
        }

        prev_state=curr_state;
        curr_state=table_state[curr_state][elem];
        if(curr_state==S_ERROR)
            throw runtime_error("error!  wrong here "+ curr_str);
    }
    if(!curr_str.empty()) {
        pair<string, string> temp_pair = GenerateOutput();
        if (temp_pair.first != "comment" && temp_pair.second != "") {
            ans.push_back(temp_pair);
        }
    }

    return ans;
};

pair<string,string> LexicalAnalyzer::GenerateOutput(){
    if(curr_str.size()>16){
        throw runtime_error("String size >16! error");
    }
    pair<string,string> ret;
    if(prev_state==S0) {
        ret = make_pair("Compare operator", curr_str);
    }
    if(prev_state==S_WHILE_FINAL ||prev_state==S_DO_FINAL) {
        ret = make_pair("Key word", curr_str);
    }
    if(prev_state==S_W1|| prev_state==S_W2||prev_state==S_W3||prev_state==S_W4||prev_state==S_DO1||prev_state==S_VAR) {
        ret = make_pair("Variable", curr_str);
    }
    if(prev_state == S_FLOAT_VAL ) {
        ret = make_pair("Float value", curr_str);
    }
    if(prev_state==S_INTEGER ) {
        ret = make_pair("Integer value", curr_str);
    }
    if(prev_state==S_ASSIGN ) {
        ret = make_pair("Assignment operator", curr_str);
    }
    if(prev_state==S_COMMENT ) {
        ret = make_pair("comment", "");
    }
    return ret;

}

string LexicalAnalyzer::Preproccessing(string str){
    string ret_str;
    for(int i=0;i<str.size();i++){
        if(str[i]=='>'||str[i]=='<'|| str[i]=='#'){
            if(ret_str.empty() ||ret_str.back()!=' '||ret_str.back()!='\n'||ret_str.back()!='\t'||ret_str.back()!='\0'){
                ret_str.push_back(' ');
                ret_str.push_back(str[i]);
                ret_str.push_back(' ');
            }
        }

        else if(str[i]==':'){
            if(ret_str.empty() ||ret_str.back()!=' '||ret_str.back()!='\n'||ret_str.back()!='\t'||ret_str.back()!='\0'){
                ret_str.push_back(' ');
                ret_str.push_back(str[i]);
            }
        }


        else if(str[i]=='='){
            if(ret_str.empty() ||ret_str.back()!=' '||ret_str.back()!='\n'||ret_str.back()!='\t'||ret_str.back()!='\0' ){
                if(ret_str.back()!=':')
                    ret_str.push_back(' ');
                ret_str.push_back(str[i]);
                ret_str.push_back(' ');
            }
        }
        else {
            ret_str.push_back(str[i]);
        }
    }
    ret_str.push_back(' ');
    return ret_str;
}

vector<int> LexicalAnalyzer::GetOrderTypes(vector<pair<string,string>> vec){
    vector<int> ret;
    for(auto e:vec){
        if(e.first=="Compare operator"){
            ret.push_back(S_CMP);
        }
        if(e.first=="Variable"){
            ret.push_back(S_VAR);
        }
        if(e.first=="Key word"){
            ret.push_back(S_KEY);
        }
        if(e.first=="Float value"){
            ret.push_back(S_FLOAT);
        }
        if(e.first=="Integer value"){
            ret.push_back(S_INT);
        }
        if(e.first=="Assignment operator"){
            ret.push_back(S_ASS);
        }
    }
    return ret;

}






