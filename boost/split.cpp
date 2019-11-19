#include<iostream>
#include <string>
#include<vector>
#include <boost/algorithm/string.hpp>

using namespace std;
using namespace boost::algorithm;
int main(){
    string test = "  I    am   hari and i love cpp  ";
    trim(test);
    vector<string>res;
    split(res,test,is_any_of(" "),token_compress_on);
    for(auto &x:res)
        cout<<x<<endl;
    return 0;
}