// Ivan Carvalho
// Solution to https://www.urionlinejudge.com.br/judge/problems/view/1511
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#define MAXN 1010
#define CONV 501
using namespace std;
int arvore[(MAXN+10)][4*(MAXN+10)],tem[(MAXN+10)][4*(MAXN+10)];
char entrada[MAXN];
int Q;
int gcd(int x,int y){
	if(x < y) swap(x,y);
	if(y == 0) return x;
	return gcd(y,x % y);
}
void update(int id,int pos,int left,int right,int y,int val){
	//printf("Update(%d,%d,%d,%d,%d,%d)\n",id,pos,left,right,y,val);
	if(left > right || left > y || right < y) return;
	if(left == y && right == y){
		arvore[id][pos] = val;
		tem[id][pos] = (val != 0);
		//printf("Arvore[%d][%d] = %d\n",id,pos,arvore[id][pos]);
		return;
	}
	int mid = (left+right)/2;
	update(id,2*pos,left,mid,y,val);
	update(id,2*pos+1,mid+1,right,y,val);
	arvore[id][pos] = gcd(arvore[id][2*pos],arvore[id][2*pos+1]);
	tem[id][pos] = tem[id][2*pos]+tem[id][2*pos+1];
	//printf("Arvore[%d][%d] = %d\n",id,pos,arvore[id][pos]);
}
int query(int id,int pos,int left,int right,int i,int j){
	if(left > right || left > j || right < i) return 0;
	if(tem[id][pos] == 0) return 0;
	if(left >= i && right <= j){
		//printf("Query(%d,%d,%d,%d,%d,%d) = %d\n",id,pos,left,right,i,j,arvore[id][pos]);
		return arvore[id][pos];
	}
	int mid = (left+right)/2;
	int val = gcd(query(id,2*pos,left,mid,i,j),query(id,2*pos+1,mid+1,right,i,j));
	//printf("Query(%d,%d,%d,%d,%d,%d) = %d\n",id,pos,left,right,i,j,val);
	return val;
}
int main(){
	while(scanf("%d",&Q) != EOF){
		memset(arvore,0,sizeof(arvore));
		memset(tem,0,sizeof(arvore));
		while(Q--){
			int x,y,d;
			scanf("%s %d %d %d",entrada,&x,&y,&d);
			if(entrada[0] == 'Q'){
				int resp = 0;
				x += CONV;
				y += CONV;
				int x1 = max(1,x - d);
				int x2 = min(MAXN,x + d);
				for(int meux = x1;meux <= x2 && resp != 1;meux++){
					int dlinha = d - abs(meux - x);
					int y1 = max(1,y - dlinha);
					int y2 = min(MAXN,y + dlinha);
					resp = gcd(resp, query(meux,1,1,MAXN,y1,y2) );
				}
				printf("%d\n",resp);
			}
			if(entrada[0] == 'S'){
				x += CONV;
				y += CONV;
				update(x,1,1,MAXN,y,d);
			}
		}
	}
	return 0;
}
