//fix : infinite loop... 
#include <bits/stdc++.h>
using namespace std;
int main(){
    map<int,int>m{{1,2},{2,2},{3,2},{4,2}};
    int size = m.size()*2*sizeof(int);

    ofstream out("bin",ios::binary|ios::trunc);
    for(auto &x:m)
        out.write((char*)&x,size);    
    out.close();

    // cout<<sizeof(m)<<endl;
    // cout<<m.size()*2*sizeof(int)<<endl;
    map<int,int>m1;
    ifstream in("bin",ios::binary);
    in.read((char *)&m1,size);
    in.close();

    for(auto &x:m)
        cout<<x.first<<' '<<x.second<<endl;
    string stuff(10,'-');
    cout<<stuff<<endl;

    for(auto &x:m1)
        cout<<x.first<<' '<<x.second<<endl;
    return 0;
}