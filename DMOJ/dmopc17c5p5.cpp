// Ivan Carvalho
// Solution to https://dmoj.ca/problem/dmopc17c5p5
#include <bits/stdc++.h>
using namespace std;

typedef vector<int> vi;

const int MAXN = 2*1e5 + 10;
const int MAXL = 30;

int pai[MAXN],val[MAXN],N,M,Q;

int find(int x){
	//printf("Find %d\n",x);
	if(x == pai[x]) return x;
	return pai[x] = find(pai[x]);
}

void join(int x,int y){
	//printf("JOIN %d %d\n",x,y);
	x = find(x);
	y = find(y);
	if(x == y) return;
	if(x > y) swap(x,y);
	pai[y] = x; 
}

void build(vi &S,int k){

	if(k < 0 || S.empty()) return;
	//printf("BUILD %d com |S| %d\n",k,(int)S.size());

	int kth_bit = (M & (1 << k)) != 0; 

	vi L,R;

	for(int i = 0;i<S.size();i++){
		int j = S[i];
		if(val[j] & (1 << k)) R.push_back(j);
		else L.push_back(j);
	}

	if(kth_bit == 1){
		for(int i = 1;i<L.size();i++){
			join(L[0],L[i]);
		}
		for(int i = 1;i<R.size();i++){
			join(R[0],R[i]);
		}
		build(S,k-1);
		return;
	}

	build(L,k-1);
	build(R,k-1);

}

int main(){
	
	scanf("%d %d %d",&N,&M,&Q);
	M++;

	vi G;
	for(int i = 1;i<=N;i++){
		scanf("%d",&val[i]);
		pai[i] = i;
		G.push_back(i);
	}

	build(G,MAXL);

	while(Q--){
		int u,v;
		scanf("%d %d",&u,&v);
		if(find(u) == find(v)) printf("YES\n");
		else printf("NO\n");
	}

	return 0;

}
