// Ivan Carvalho
// Solution to https://dmoj.ca/problem/tsoc16c2p4
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 10010;
bitset<MAXN> crivo, dp,temp,outro;
vector<int> primos;
int mi[MAXN];
int main(){
	crivo.set(0);
	crivo.set(1);
	dp.set(0);
	for(int i=2;i<MAXN;i++){
		if(crivo.test(i)) continue;
		primos.push_back(i);
		for(int j = i*i;j<MAXN;j+=i){
			crivo.set(j);
		}
	}
	int n,m;
	cin >> n >> m;
	for(int i=0;i<m;i++){
		cin >> mi[i];
		n -= 2*mi[i];
	}
	for(int i = 0;i < m;i++){
		int v = mi[i];
		temp = dp;
		for(int j : primos){
			if((j - 2) * v > n) break;
			outro = dp;
			outro |= (j-2)*v;
			temp |= outro;
		}
		dp = temp;
	}
	for(int j : primos){
		if(j > n){
			break;
		}
		if(dp.test(j)){
			printf("its primetime\n");
			return 0;
		}
	}
	printf("not primetime\n");
	return 0;
}