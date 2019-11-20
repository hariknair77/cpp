#include <bits/stdc++.h>
using namespace std;
int main(){
    //string to hex
    string num = "F";
    cout<<stoi(num,0,16)<<endl;

    //string to int
    string num2 = "12";
    cout<<stoi(num2)<<endl;
    
    //binary string to integer
    string num4 = "111111111111";
    cout<<stoi(num4,0,2)<<endl;
    
    //int to string
    auto s = to_string(42);
    cout<<s<<endl;
    
    //int to binary
    int num3 = 10;
    string bin = bitset<4>(num3).to_string();
    cout<<bin<<endl;

    //int to hex
    int num5 = 15;
    stringstream stream;
    stream<<hex<<num5;
    cout<<stream.str()<<endl;

    //hex to int
    int num6;
    cout<<"Enter hex : ";
    cin>>hex>>num6;
    cout<<num6<<endl;
    return 0;
}