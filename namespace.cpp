#include <iostream>
using namespace std;

namespace hari{
	int cout = 9;
}
int main(){
	hari::cout = 100;
	std::cout<<hari::cout;

}
