#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <map>
#include <iterator>
#include <iomanip>
using namespace std;

struct opc{
    int len;
    string hex;
};
struct literal{
    string sym,value,loc;
    int len,flag;
};
vector<literal>littab;
void def_lit(int &locctr){
    for(auto &i:littab)
        if(i.flag == 0){
            i.flag = 1;
            stringstream tohex;
            tohex<<hex<<locctr;
            i.loc = tohex.str();
            locctr += i.len;
        }
}
vector<string> l;
map<string,struct opc> optab;
string label,opcode,operand;
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
map<string,string>symtab;
int main(){
    int e,lc=0,locctr = 0,prev_loc = 0 ;
    string op,op_,len,hexval,file,line;
    ifstream opflie("optab.dat");
    while(opflie>>op>>len>>hexval){
        struct opc op_;
        op_.len = stoi(len);
        op_.hex = hexval;
        optab[op] = op_;
    }
    ofstream temp("temp",ios::trunc);
    loop : cout<<"Enter file name: ";
    cin>>file;
    ifstream input(file);
    if(!input){
        cout<<"file not found\n";
        goto loop;
    }
    getline(input,line);    
    lc++;
    split(line);
    if(opcode == "START"){
        temp<<label<<" "<<opcode<<" ";
        temp<<setfill('0')<<setw(5)<<operand<<endl;
        label.clear();
        opcode.clear();
        operand.clear();
    }
    while(getline(input,line)){  
        lc++;
        e=0;
        if(line[0] == '.')
            continue;  
        split(line);
        if(opcode[0] == '+'){
            e = 1;
            op_ = opcode.substr(1);
        }
        else
            op_ = opcode;
        auto found = optab.find(op_);
        if(found!=optab.end()){
            locctr += found->second.len;    
            if(e==1)
                locctr++;
            if(operand[0] == '='){
                literal lit;
                lit.sym = operand;
                lit.flag = 0;
                lit.value = operand.substr(3,operand.length()-3);
                if(operand[1]=='W')
                    lit.len = 3;
                else if(operand[1]=='C')
                    lit.len = operand.length()-4;
                else if(operand[1]=='X')
                    lit.len = (operand.length()-4)/2;
                else{
                    cout<<"invalid literal on line:"<<lc<<endl;
                    continue;
                }
                littab.push_back(lit);  
            }
        }
        else if(opcode == "WORD")
            locctr += 3;
        else if(opcode == "BYTE"){        
            if(operand[0] == 'X')
                locctr += (operand.length()-3)/2;
            else
                locctr += (operand.length()-3);
        }
        else if(opcode == "RESW")
            locctr += 3*stoi(operand);
        else if(opcode == "RESB")
            locctr += stoi(operand);
        else if(opcode == "LTORG"){
            def_lit(locctr);
            prev_loc = locctr;
            continue;
        }
        else if(opcode == "END"){
            def_lit(locctr);
            temp<<setfill('0')<<setw(5)<<hex<<prev_loc<<" ";
            temp<<opcode<<" "<<operand<<endl;
            break;
        }
        else
            cout<<"Invalid opcode on line "<<lc;
        if(!label.empty()){
            auto sym = symtab.find(label);
            if(sym == symtab.end()){
                stringstream tohex;
                tohex<<hex<<prev_loc;
                symtab[label] = tohex.str();
            }
        }
        temp<<setfill('0')<<setw(5)<<hex<<prev_loc<<" ";
        temp<<opcode<<" "<<operand<<endl;
        prev_loc = locctr;
    }

    ofstream lit_tab("littab",ios::trunc);
    for(auto &i:littab)
        lit_tab<<i.sym<<" "<<i.loc<<endl;
    
    ofstream sym_tab("symtab",ios::trunc);
    for(auto &i:symtab)
        sym_tab<<i.first<<" "<<i.second<<endl;

    ofstream prg_len("prglen");
        prg_len<<setfill('0')<<setw(4)<<hex<<locctr;
    return 0;
}

