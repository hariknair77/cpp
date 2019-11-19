#include <bits/stdc++.h>
using namespace std;
int main(){
    vector<int>data {1,2,3,4,5};
    ofstream f("bin",ios::binary);
    size_t size = data.size();
    cout<<sizeof(size);
    f.write((char *)&size,sizeof(size));
    // f.seekg(0);
    // vector<int>out;
    // f.read((char *)&out,data.size()*sizeof(int));
    // for(auto &x:out)
    //     cout<<x<<endl;
    f.close();
    return 0;
}