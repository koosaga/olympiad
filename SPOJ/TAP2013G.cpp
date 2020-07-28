// Ivan Carvalho
// Solution to https://www.spoj.com/problems/TAP2013G/
#include <iostream>
#include <set>
#define endl '\n'
using namespace std;
typedef multiset<int>::iterator miit;
int main(){
	cin.tie(0);
	ios_base::sync_with_stdio(0);
	int s,resposta = 0;
	cin >> s;
	multiset<int> nlogonia, quadradonia;
	for(int i=0;i < s;i++){
		int davez;
		cin >> davez;
		quadradonia.insert(davez);
	}
	for(int i=0;i < s;i++){
		int davez;
		cin >> davez;
		nlogonia.insert(davez);
	}
	for(miit n2 = quadradonia.begin();n2 != quadradonia.end();n2++){
		miit nlogn;
		nlogn = nlogonia.upper_bound((*n2));
		if (nlogn == nlogonia.end()){
			//cout << "N2: " << (*(n2)) << " NLOGN: " << *(nlogonia.begin()) << endl;
			nlogonia.erase(nlogonia.begin());
		}
		else{
			//cout << "N2: " << (*(n2)) << " NLOGN: " << *(nlogn) << endl;
			resposta++;
			nlogonia.erase(nlogn);
		}
	}
	cout << resposta << endl;
	return 0;
}