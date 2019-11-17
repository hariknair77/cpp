//Program to illustrate input stream
#include <iostream>
#include <string>
using namespace std;
int main(){
    string name;
    int age;
    loop: cout<<"Age :";
    if(cin>>age); //goodbit 
    else{ // bad bit as u have entered the wrong data
        cout<<"\ninteger pls..\n";
        cin.clear(); //to clear the internal states 
        cin.ignore(10000,'\n'); // remove wood blocks from stream 
        goto loop;
    }
    cin.ignore(); //getline default delim is '\n' so ignore it igonre(1,'\n')
    cout<<"Enter your name :";
    getline(cin,name); //space seperated data 
    
    cout<<"\nname: "<<name<<"\n"<<"age: "<<age<<endl;
    return 0;
}