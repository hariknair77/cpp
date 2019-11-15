//Program to illustrate input stream
#include <iostream>
#include <string>
using namespace std;
int main(){
    string name;
    int age;
    loop: cout<<"Age :";
    if(cin>>age);
    else{
        cout<<"\ninteger pls..\n";
        cin.clear();
        cin.ignore(10000,'\n');
        goto loop;
    }
    cin.ignore();
    cout<<"Enter your name :";
    getline(cin,name);
    
    cout<<"\nname: "<<name<<"\n"<<"age: "<<age<<endl;
    return 0;
}