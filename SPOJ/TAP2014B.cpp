// Ivan Carvalho
// Solution to https://www.spoj.com/problems/TAP2014B/
#include <iostream>
#include <algorithm>
#include <string>
#include <map>
using namespace std;
map<int,string> mapa;
const int MAXL = 7;
int pot3[13];
void solve(int val, int pos,string referencia){
	if(pos > MAXL) return;
	int valplus = val + pot3[pos];
	string refplus = referencia;
	refplus.push_back('+');
	mapa[valplus] = refplus;
	solve(valplus,pos+1,refplus);
	int valminus = val - pot3[pos];
	string refminus = referencia;
	refminus.push_back('-');
	mapa[valminus] = refminus;
	solve(valminus,pos+1,refminus);
	referencia.push_back('0');
	solve(val,pos+1,referencia);
}
int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	pot3[0] = 1;
	for(int i=1;i<=MAXL;i++){
		pot3[i] = 3*pot3[i-1];
	}
	string vazio;
	solve(0,0,vazio);
	int TC;
	cin >> TC;
	while(TC--){
		int a;
		cin >> a;
		string exibir = mapa[a];
		reverse(exibir.begin(),exibir.end());
		cout << exibir << '\n';
	}
	return 0;
}