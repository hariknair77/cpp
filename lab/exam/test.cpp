#include <bits/stdc++.h>
using namespace std;
string int_to_hex(int int_,int width){
    stringstream s;
    s<<setfill('0')<<setw(width)<<hex<<int_;
    return s.str();
}
int main(){
    string op;    
    map<string,string>optab;
    // for(int i=0;i<16;i++){
    //     cin>>op;
    //     optab[op] = int_to_hex(i,2);
    // }
    
    // ofstream file("optab",ios::binary);
    // file.write((char *)&optab,sizeof(optab));
    // file.close();
    ifstream infile("optab",ios::binary);
    infile.read((&optab,sizeof(optab));
    infile.close();
    for(auto &i:optab)
        cout<<i.first<<' '<<i.second<<endl;
    return 0;
}