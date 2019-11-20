#include <bits/stdc++.h>
#include <boost/algorithm/string.hpp>
using namespace std;
using namespace boost::algorithm;
struct opcode{
    string len,code;
};
int main(){
    map<string,opcode>optab;
    vector<string>l;
    ifstream fin("optab.dat");
    string line;
    int c=0;
    while(getline(fin,line)){
        l.clear();
        split(l,line,is_any_of(" "),token_compress_on);
        opcode op;
        op.code = to_string(c);
        op.len = l.at(1);
        optab[l.at(0)] = op;
        c++;
    }
    for(auto &x:optab)
        cout<<x.first<<" "<<x.second.code<<" "<<x.second.len<<endl;
    return 0;
}
