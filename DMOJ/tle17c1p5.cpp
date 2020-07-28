// Ivan Carvalho
// Solution to https://dmoj.ca/problem/tle17c1p5
#include <bits/stdc++.h>
#define LSOne(S) (S & (-S))
using namespace std;
typedef tuple<int,int,int> tripla;
const int MAXN = 1e5 + 2;
int bit[MAXN],r,c,G1[MAXN],G2[MAXN];
vector<tripla> atualizacoes;
void update(int idx,int val){
	while(idx < MAXN){
		bit[idx] += val;
		idx += LSOne(idx);
	}
}
int read(int idx){
	int ans = 0;
	while(idx > 0){
		ans += bit[idx];
		idx -= LSOne(idx);
	}
	return ans;
}
int query(int a,int b){
	return read(b) - read(a-1);
}
void exibe(){
	for(int i = 1;i<=c;i++) printf("%d ",query(i,i));
	printf("\n");
}
int main(){
	scanf("%d %d",&r,&c);
	for(int row = 1;row <= r;row++){
		int ini,fim;
		scanf("%d %d",&ini,&fim);
		G1[row] = ini;
		G2[row] = fim;
	}
	for(int column = 1;column <= c;column++){
		int ini,fim;
		scanf("%d %d",&ini,&fim);
		atualizacoes.push_back(make_tuple(ini,1,column));
		atualizacoes.push_back(make_tuple(fim+1,-1,column));
	}
	sort(atualizacoes.begin(),atualizacoes.end());
	int ptr = 0;
	for(int i = 1;i<=r;i++){
		while(ptr < atualizacoes.size() && get<0>(atualizacoes[ptr]) <= i){
			update(get<2>(atualizacoes[ptr]),get<1>(atualizacoes[ptr]));
			ptr++;
		}
		//exibe();
		if(query(G1[i],G2[i]) == G2[i] - G1[i] + 1 && query(1,c) == G2[i] - G1[i] + 1) continue;
		printf("nonsense\n");
		for(int j = G1[i];j <= G2[i];j++){
			if(query(j,j) != 1){
				printf("%d %d\n",i,j);
				return 0;
			}
		}
		for(int j = 1;j < G1[i];j++){
			if(query(j,j) != 0){
				printf("%d %d\n",i,j);
				return 0;
			}
		}
		for(int j = G2[i]+1;j <= c;j++){
			if(query(j,j) != 0){
				printf("%d %d\n",i,j);
				return 0;
			}
		}
	}
	for(int i = 1;i + 1 <= r;i++){
		int x1 = max(G1[i],G1[i+1]);
		int x2 = min(G2[i],G2[i+1]);
		//printf("X1 %d X2 %d\n",x1,x2);
		if(x1 > x2){
			printf("nonsense\n");
			printf("unconnected\n");
			return 0;
		}
	}
	printf("sense\n");
	return 0;
});
	return 0;
}