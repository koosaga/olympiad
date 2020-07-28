// Ivan Carvalho
// Solution to https://www.spoj.com/problems/MULTQ3/
#include <cstdio>
#define MAXN 100010
int lazy[4*MAXN];
typedef struct No{
	int restozero;
	int restoum;
	int restodois;
}no;
no arvore[4*MAXN];
void build(int pos, int left, int right){
	if (left == right){
		arvore[pos].restozero = 1;
		arvore[pos].restoum = 0;
		arvore[pos].restodois = 0;
		return;
	}
	int mid = (left+right)/2;
	build(2*pos+1,left,mid);
	build(2*pos+2,mid+1,right);
	arvore[pos].restozero = arvore[2*pos+1].restozero + arvore[2*pos+2].restozero;
	arvore[pos].restoum = arvore[2*pos+1].restoum + arvore[2*pos+2].restoum;
	arvore[pos].restodois = arvore[2*pos+1].restodois + arvore[2*pos+2].restodois;
}
int query(int pos, int left, int right, int i, int j){
	if (lazy[pos] != 0){
		if (lazy[pos] == 1){
			int temp0 = arvore[pos].restozero;
			int temp1 = arvore[pos].restoum;
			int temp2 = arvore[pos].restodois;
			arvore[pos].restozero = temp2;
			arvore[pos].restoum = temp0;
			arvore[pos].restodois = temp1;
		}
		if (lazy[pos] == 2){
			int temp0 = arvore[pos].restozero;
			int temp1 = arvore[pos].restoum;
			int temp2 = arvore[pos].restodois;
			arvore[pos].restozero = temp1;
			arvore[pos].restoum = temp2;
			arvore[pos].restodois = temp0;
		}
		if (left != right){
			lazy[2*pos+1]+= lazy[pos];
			lazy[2*pos+1] %= 3;
			lazy[2*pos+2]+= lazy[pos];
			lazy[2*pos+2] %= 3;
		}
		lazy[pos] = 0;
	}
	if (left > right || left > j || right < i) return 0;
	if (left >= i && right <= j){
		return arvore[pos].restozero;
	}
	int mid = (left+right)/2;
	int p1 = query(2*pos+1,left,mid,i,j);
	int p2 = query(2*pos+2,mid+1,right,i,j);
	return p1 + p2;
}
void update(int pos, int left, int right, int i, int j){
	if (lazy[pos] != 0){
		if (lazy[pos] == 1){
			int temp0 = arvore[pos].restozero;
			int temp1 = arvore[pos].restoum;
			int temp2 = arvore[pos].restodois;
			arvore[pos].restozero = temp2;
			arvore[pos].restoum = temp0;
			arvore[pos].restodois = temp1;
		}
		if (lazy[pos] == 2){
			int temp0 = arvore[pos].restozero;
			int temp1 = arvore[pos].restoum;
			int temp2 = arvore[pos].restodois;
			arvore[pos].restozero = temp1;
			arvore[pos].restoum = temp2;
			arvore[pos].restodois = temp0;
		}
		if (left != right){
			lazy[2*pos+1]+= lazy[pos];
			lazy[2*pos+1] %= 3;
			lazy[2*pos+2]+= lazy[pos];
			lazy[2*pos+2] %= 3;
		}
		lazy[pos] = 0;
	}
	if (left > right || left > j || right < i) return;
	if (left >= i && right <= j){
		int temp0 = arvore[pos].restozero;
		int temp1 = arvore[pos].restoum;
		int temp2 = arvore[pos].restodois;
		arvore[pos].restozero = temp2;
		arvore[pos].restoum = temp0;
		arvore[pos].restodois = temp1;
		if (left != right){
			lazy[2*pos+1]++;
			lazy[2*pos+1] %= 3;
			lazy[2*pos+2]++;
			lazy[2*pos+2] %= 3;
		}
		return;
	}
	int mid = (left+right)/2;
	update(2*pos+1,left,mid,i,j);
	update(2*pos+2,mid+1,right,i,j);
	arvore[pos].restozero = arvore[2*pos+1].restozero + arvore[2*pos+2].restozero;
	arvore[pos].restoum = arvore[2*pos+1].restoum + arvore[2*pos+2].restoum;
	arvore[pos].restodois = arvore[2*pos+1].restodois + arvore[2*pos+2].restodois;
}
int main(){
	int n,q;
	scanf("%d %d",&n,&q);
	build(0,0,n-1);
	while(q--){
		int op,x,y;
		scanf("%d %d %d",&op,&x,&y);
		if (op == 0) update(0,0,n-1,x,y);
		if (op == 1) printf("%d\n",query(0,0,n-1,x,y));
	}
	return 0;
} 