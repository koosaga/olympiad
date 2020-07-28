// Ivan Carvalho
// Solution to https://dmoj.ca/problem/dmopc14c2p6
#include <cstdio>
#include <vector>
#define MAXN 100010
#define MAXM 20010
#define LSOne(S) (S & (-S))
using namespace std;
vector<int> esq[MAXN],dir[MAXN],val[MAXN];
int n,q,segIt[MAXN];
void update_seg(int id,int pos,int left,int right,int x,int delta){
	if(left == right){
		val[id][pos] += delta;
		return;
	}
	val[id][pos] += delta;
	int mid = (left+right)/2;
	if(x<=mid){
		if(esq[id][pos] == -1){
			esq[id].push_back(-1);
			dir[id].push_back(-1);
			val[id].push_back(0);
			esq[id][pos] = ++segIt[id];
		}
		update_seg(id,esq[id][pos],left,mid,x,delta);
	}
	else{
		if(dir[id][pos] == -1){
			esq[id].push_back(-1);
			dir[id].push_back(-1);
			val[id].push_back(0);
			dir[id][pos] = ++segIt[id];
		}
		update_seg(id,dir[id][pos],mid+1,right,x,delta);
	}
}
int query_seg(int id,int pos,int left,int right,int i,int j){
	if(left>=i&&right<=j){
		return val[id][pos];
	}
	int mid = (left+right)/2;
	if(j <= mid){
		return (esq[id][pos] == -1) ? 0 : query_seg(id,esq[id][pos],left,mid,i,j);
	}
	else if(i >= mid + 1){
		return (dir[id][pos] == -1) ? 0 : query_seg(id,dir[id][pos],mid+1,right,i,j);
	}
	else{
		return ((esq[id][pos] == -1) ? 0 : query_seg(id,esq[id][pos],left,mid,i,j)) + ((dir[id][pos] == -1) ? 0 : query_seg(id,dir[id][pos],mid+1,right,i,j));
	}
}
void update_bit(int posx,int posy){
	while(posx <= n){
		update_seg(posx,0,1,MAXM,posy,posy);
		posx += LSOne(posx);
	}
}
int read_bit(int posx,int posy){
	int ans = 0;
	while(posx > 0){
		ans += query_seg(posx,0,1,MAXM,posy,MAXM);
		posx -= LSOne(posx);
	}
	return ans;
}
int query_bit(int a,int b,int c){
	return read_bit(b,c) - read_bit(a-1,c);
}
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		esq[i].push_back(-1);
		dir[i].push_back(-1);
		val[i].push_back(0);
	}
	for(int i=1;i<=n;i++){
		int davez;
		scanf("%d",&davez);
		update_bit(i,davez);
	}
	scanf("%d",&q);
	while(q--){
		int a,b,c;
		scanf("%d %d %d",&a,&b,&c);
		printf("%d\n",query_bit(a+1,b+1,c));
	}
	return 0;
}	}
	return 0;
}