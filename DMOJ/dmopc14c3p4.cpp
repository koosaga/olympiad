// Ivan Carvalho
// Solution to https://dmoj.ca/problem/dmopc14c3p4
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 100001;
vector<int> K[MAXN];
int fatores[MAXN];
int main(){
	for(int i=1;i<MAXN;i++) fatores[i] = 1;
	for(int i = 2;i < MAXN;i++){
		for(int j = i;j<MAXN;j+=i){
			fatores[j]++;
		}
	}
	for(int i=1;i<MAXN;i++) K[fatores[i]].push_back(i);
	int T;
	scanf("%d",&T);
	while(T--){
		int k,a,b;
		scanf("%d %d %d",&k,&a,&b);
		if(K[k].empty()){
			printf("0\n");
			continue;
		}
		if(K[k].back() < a){
			printf("0\n");
			continue;
		}
		vector<int>::iterator it1 = lower_bound(K[k].begin(),K[k].end(),a);
		vector<int>::iterator it2 = prev(upper_bound(K[k].begin(),K[k].end(),b));
		int resp = it2 - it1 + 1;
		printf("%d\n",resp);
	}
	return 0;
}