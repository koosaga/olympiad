// Ivan Carvalho
// Solution to https://dmoj.ca/problem/coci17c1p3
#include <bits/stdc++.h>
using namespace std;
map<string,int> mapa;
int resposta,n;
string entradas[20010];
int main(){
	cin.tie(0);ios_base::sync_with_stdio(0);
	cin >> n;
	for(int idx = 1;idx<=n;idx++){
		cin >> entradas[idx];
		vector<string> subs;
		for(int ini = 0;ini<entradas[idx].size();ini++){
			string davez;
			for(int i = ini;i<entradas[idx].size();i++){
				davez.push_back(entradas[idx][i]);
				subs.push_back(davez);
			}
		}
		sort(subs.begin(),subs.end());
		subs.erase(unique(subs.begin(),subs.end()),subs.end());
		for(string s : subs) mapa[s]++;
	}
	for(int idx = 1;idx<=n;idx++){
		resposta += mapa[entradas[idx]];
	}
	cout << resposta - n << endl;
	return 0;
}
