#include <iostream>
using namespace std;
inline void swap(int &i,int &j){
    int temp = i;
    i = j;
    j = temp;
}
inline void swap(double &i,double &j){
    double temp = i;
    i = j;
    j = temp;
}
int main(){
    double a,b;
    
    cout<<"enter 2 numbers:";
    cin>>a>>b;
    cout<<a<<" "<<b<<endl;
    swap(a,b);
    cout<<a<<" "<<b<<endl;
    return 0;
}