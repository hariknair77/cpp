#include <bits/stdc++.h>
using namespace std;

int main(){
    map<string, vector<int>> optab{
        {"ADD",{1,2}},
        {"SUB",{13,14}},
        {"MUL",{15,6}},
    };
    for (auto &x : optab){
        cout << x.first << " " <<hex<< x.second.at(0) << " ";
        cout<<dec<< x.second.at(1) << endl;
    }
}