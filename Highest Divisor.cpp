#include <iostream>
using namespace std;

int main() {
	int n,i,d=10;
	cin>>n;
	while(n%d!=0) d--;
	cout<<d;
	return 0;
}
