// Ivan Carvalho
// Solution to https://www.spoj.com/problems/CVJETICI/
#include <bits/stdc++.h>
#define LSOne(S) (S & (-S))
using namespace std;

const int MAXN = 1e5 + 10;

int bit[MAXN],N;

void update(int idx,int delta){
	while(idx < MAXN){
		bit[idx] += delta;
		idx += LSOne(idx);
	}
}

void update_range(int a,int b,int delta){
	if(a > b) return;
	update(a,delta);
	update(b+1,-delta);
}

int query(int idx){
	int ans = 0;
	while(idx > 0){
		ans += bit[idx];
		idx -= LSOne(idx);
	}
	return ans;
}

void zero(int pos){
	int v = query(pos);
	update_range(pos,pos,-v);
}

int main(){

	scanf("%d",&N);

	for(int i = 1;i<=N;i++){
		int a,b;
		scanf("%d %d",&a,&b);
		int exibe = query(a);
		zero(a);
		exibe += query(b);
		zero(b);
		printf("%d\n",exibe);
		update_range(a+1,b-1,1);
	}

	return 0;
}