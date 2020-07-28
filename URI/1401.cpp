// Ivan Carvalho
// Solution to https://www.urionlinejudge.com.br/judge/problems/view/1401
#include <iostream>
#include <algorithm>
#define endl '\n'
using namespace std;
int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	int casos;
	cin >> casos;
	for(int agora=0;agora<casos;agora++){
		string davez;
		cin >> davez;
		sort(davez.begin(),davez.end());
		do{
			for (int i=0;i<davez.size();i++) cout << davez[i];
			cout << endl;
		} while(next_permutation(davez.begin(),davez.end()));
		cout << endl;
	}
	return 0;
}
