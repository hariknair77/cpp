#include <iostream>
#include <string>
using namespace std;
int main(){
    string name;
    cin>>name;
    cin.ignore();
    string name1;
    getline(cin,name1);
    cout<<name1<<"\n";
    // if(cin>>name) //cant read space separared data
    //     cout<<"fine\n";
    // cout<<name<<"\n";

    // getline(cin,name);
    // cout<<name<<"\n";
    // string name; //line 1
    // cout << "Give me your name and surname:"<<endl;//line 2
    // cin >> name;//line 3
    // int age;//line 4
    // cout << "Give me your age:" <<endl;//line 5
    // cin.ignore(10000,'\n');
    // cin >> age;//line 6
    // cout<<age;
    // cout<<"\n"<<cin.rdstate();
    return 0;
}