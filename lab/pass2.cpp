#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
using namespace std;

string label,opcode,operand;
vector<string>l;
void split(string line){
    string tok;
    stringstream line_(line);
    l.clear();
    label.clear();
    opcode.clear();
    operand.clear();
    while(line_>>tok)
        l.push_back(tok);
    if(l.size() == 3){
        label = l.at(0);
        opcode = l.at(1);
        operand = l.at(2);
    }
    else if(l.size() == 2){
        opcode = l.at(0);
        operand = l.at(1);
    }
    else
        opcode = l.at(0);
}
int main(){
    ofstream obj("obj");
    ifstream f_len("prglen");
    string line,prg_len;
    f_len>>prg_len;
    ifstream temp("temp");
    getline(temp,line);
    split(line);
    if(!label.empty()){
        obj<<'H'<<'^'<<label<<'^'<<operand<<'^'<<prg_len<<endl;
    }
    else
        obj<<'H'<<'^'<<"------"<<'^'<<operand<<'^'<<prg_len<<endl;

    while(getline(temp,line)){
        split(line);
    }
    obj.close();
    f_len.close();
    temp.close();   
    return 0;
}