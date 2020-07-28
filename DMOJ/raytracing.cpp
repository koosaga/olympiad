// Ivan Carvalho
// Solution to https://dmoj.ca/problem/raytracing
#include <bits/stdc++.h>
#define LSOne(S) (S & (-S))
using namespace std;
const int MAXN = (1 << 13) + 5;
int bit[MAXN][MAXN],H[MAXN],N,Q;
inline void update(int posx,int posy,int delta){
	for(int i = posx;i<MAXN;i += LSOne(i)){
		for(int j = posy;j < MAXN;j += LSOne(j)){
			bit[i][j] += delta;
		}
	}
}
inline int query(int posx,int posy){
	int ans = 0;
	for(int i = posx;i>0;i -= LSOne(i)){
		for(int j = posy;j > 0;j -= LSOne(j)){
			ans += bit[i][j];
		}
	}
	return ans;
}
inline int query(int x1,int x2,int y1,int y2){
	return query(x2,y2) - query(x1-1,y2) - query(x2,y1-1) + query(x1-1,y1-1);
}
int main(){
	scanf("%d",&N);
	for(int i = 1;i<=N;i++){
		scanf("%d",&H[i]);
		H[i]++;
		update(i,H[i],1);
	}
	scanf("%d",&Q);
	for(int q = 1;q<=Q;q++){
		int op;
		scanf("%d",&op);
		if(op == 1){
			int i,j,a,b;
			scanf("%d %d %d %d",&i,&j,&a,&b);
			printf("%d\n",query(i+1,j+1,a+1,b+1));
		}
		else{
			int i,h;
			scanf("%d %d",&i,&h);
			i++;
			update(i,H[i],-1);
			H[i] = h + 1;
			update(i,H[i],1);
		}
	}
	return 0;
}