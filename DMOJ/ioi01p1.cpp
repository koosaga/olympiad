// Ivan Carvalho
// Solution to https://dmoj.ca/problem/ioi01p1
#include <cstdio>
#define MAXN 1030
#define LSOne(S) (S&(-S))
int bit[MAXN][MAXN];
void update(int posx,int posy,int delta){
	for(int i=posx;i<MAXN;i+=LSOne(i)){
		for(int j=posy;j<MAXN;j+=LSOne(j)){
			bit[i][j] += delta;
		}
	}
}
int read(int posx,int posy){
	int ans = 0;
	for(int i = posx;i>0;i-=LSOne(i)){
		for(int j = posy;j>0;j-=LSOne(j)){
			ans += bit[i][j];
		}
	}
	return ans;
}
int query(int x1,int y1,int x2,int y2){
	return read(x2,y2) - read(x2,y1-1) - read(x1-1,y2) + read(x1-1,y1-1);
}
int main(){
	int op,n,x,y,z,w;
	scanf("%d %d",&op,&n);
	while(scanf("%d",&op) && op != 3){
		if(op == 1){
			scanf("%d %d %d",&x,&y,&z);
			update(x+1,y+1,z);
		}
		else{
			scanf("%d %d %d %d",&x,&y,&z,&w);
			printf("%d\n",query(x+1,y+1,z+1,w+1));
		}
	}
	return 0;
}