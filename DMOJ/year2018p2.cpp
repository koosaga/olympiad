// Ivan Carvalho
// Solution to https://dmoj.ca/problem/year2018p2
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 1e5 + 10;
bool crivo[MAXN];
int main(){
	crivo[0] = true;
	crivo[1] = true;
	for(int i = 2;i<MAXN;i++){
		if(crivo[i]) continue;
		for(int j = 2*i;j<MAXN;j+=i) crivo[j] = true;
	}
	int N,resposta = 0;
	cin >> N;
	while(N--){
		int x;
		cin >> x;
		if(!crivo[x]) resposta++;
	}
	cout << resposta << endl;
	return 0;
}