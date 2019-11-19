#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <map>
#include <iterator>
#include <iomanip>
#include <ctype.h>
#include <boost/algorithm/string.hpp>

using namespace std;
using namespace boost::algorithm;

//decimal to hex..
string toHex(int n){
    stringstream s;
    s<<setfill('0')<<setw(5)<<hex<<n;
    return s.str();
}

//opcode structure
struct opc{
    int len;
    string hex;
};
//literal structure
struct literal{
    string sym,value,loc;
    int len,flag;
};
struct symbol{
    string loc;
    char flag;
};
map<string,opc> optab;   //opcode table
map<string,symbol>symtab; //symbol table

//define literal....
vector<literal>littab;
void def_lit(int &locctr){
    for(auto &i:littab)
        if(i.flag == 0){
            i.flag = 1;
            i.loc = toHex(locctr);
            locctr += i.len;
        }
}
//split line...
vector<string> tokens;
string label,opcode,operand;
void split(string line){
    tokens.clear();
    label.clear();
    opcode.clear();
    operand.clear();

    // string tok;
    // stringstream line_(line);
    // while(line_>>tok)
    //     tokens.push_back(tok);

    trim(line);
    split(tokens,line,is_any_of(" "),token_compress_on);

    if(tokens.size() == 3){
        label = tokens.at(0);
        opcode = tokens.at(1);
        operand = tokens.at(2);
    }
    else if(tokens.size() == 2){
        opcode = tokens.at(0);
        operand = tokens.at(1);
    }
    else
        opcode = tokens.at(0);
}

int main(){
    int e,lc=0,locctr = 0,prev_loc = 0 ;
    string op,op_,len,hexval,file,line;
    ifstream opflie("optab.dat");
    while(opflie>>op>>len>>hexval){
        opc op_;
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
        temp<<label<<" "<<opcode<<" "<<setfill('0')<<setw(5)<<operand<<endl;
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
            temp<<toHex(prev_loc)<<' '<<opcode<<" "<<operand<<endl;
            break;
        }
        else
            cout<<"Invalid opcode on line "<<lc;
        if(!label.empty()){
            auto sym = symtab.find(label);
            if(sym == symtab.end()){
                symtab[label].loc = toHex(prev_loc);
                if(opcode == "EQU"){
                    auto sym = symtab.find(operand);
                    if(sym == symtab.end()){
                        symtab[label].flag = symtab[operand].flag;
                        symtab[label].loc = symtab[operand].loc;
                    }
                    else if(isdigit(operand[0])){
                        symtab[label].flag = 'A';
                        symtab[label].loc = operand;
                    }
                    else
                        cout<<"invalid label on "<<lc;
                }
                    else
                        symtab[label].flag = 'R';
            }
        }
        temp<<toHex(prev_loc)<<' '<<opcode<<" "<<operand<<endl;
        prev_loc = locctr;
    }

    ofstream lit_tab("littab",ios::trunc);
    for(auto &i:littab)
        lit_tab<<i.sym<<" "<<i.loc<<endl;
    
    ofstream sym_tab("symtab",ios::trunc);
    for(auto &i:symtab)
        sym_tab<<i.first<<" "<<i.second.flag<<" "<<i.second.loc<<endl;

    ofstream prg_len("prglen");
        prg_len<<toHex(locctr);
    return 0;
}

