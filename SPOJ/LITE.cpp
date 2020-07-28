// Ivan Carvalho
// Solution to https://www.spoj.com/problems/LITE/
#include <cstdio>
#define MAXN 100010
int lazy[4*MAXN];
typedef struct No{
	int turned_on;
	int turned_off;
}no;
no arvore[4*MAXN];
void build(int pos, int left, int right){
	if (left == right){
		arvore[pos].turned_on = 0;
		arvore[pos].turned_off = 1;
		return;
	}
	int mid = (left+right)/2;
	build(2*pos,left,mid);
	build(2*pos+1,mid+1,right);
	arvore[pos].turned_on = arvore[2*pos].turned_on + arvore[2*pos+1].turned_on;
	arvore[pos].turned_off = arvore[2*pos].turned_off + arvore[2*pos+1].turned_off;
}
int query(int pos, int left, int right, int i, int j){
	if (lazy[pos] != 0){
		int temp1 = arvore[pos].turned_on;
		int temp2 = arvore[pos].turned_off;
		arvore[pos].turned_on = temp2;
		arvore[pos].turned_off = temp1;
		if (left != right){
			lazy[2*pos]++;
			lazy[2*pos] %= 2;
			lazy[2*pos+1]++;
			lazy[2*pos+1] %= 2;
		}
		lazy[pos] = 0;
	}
	if (left > right || left > j || right < i) return 0;
	if (left >= i && right <= j){
		return arvore[pos].turned_on;
	}
	int mid = (left+right)/2;
	int p1 = query(2*pos,left,mid,i,j);
	int p2 = query(2*pos+1,mid+1,right,i,j);
	return p1 + p2;
}
void update(int pos, int left, int right, int i,int j){
	if (lazy[pos] != 0){
		int temp1 = arvore[pos].turned_on;
		int temp2 = arvore[pos].turned_off;
		arvore[pos].turned_on = temp2;
		arvore[pos].turned_off = temp1;
		if (left != right){
			lazy[2*pos]++;
			lazy[2*pos] %= 2;
			lazy[2*pos+1]++;
			lazy[2*pos+1] %= 2;
		}
		lazy[pos] = 0;
	}
	if (left > right || left > j || right < i) return;
	if (left >= i && right <= j){
		int temp1 = arvore[pos].turned_on;
		int temp2 = arvore[pos].turned_off;
		arvore[pos].turned_on = temp2;
		arvore[pos].turned_off = temp1;
		if (left != right){
			lazy[2*pos]++;
			lazy[2*pos] %= 2;
			lazy[2*pos+1]++;
			lazy[2*pos+1] %= 2;
		}
		return;
	}
	int mid = (left+right)/2;
	update(2*pos,left,mid,i,j);
	update(2*pos+1,mid+1,right,i,j);
	arvore[pos].turned_on = arvore[2*pos].turned_on + arvore[2*pos+1].turned_on;
	arvore[pos].turned_off = arvore[2*pos].turned_off + arvore[2*pos+1].turned_off;
}
int main(){
	int n,q;
	scanf("%d %d",&n,&q);
	build(1,1,n);
	while(q--){
		int op,x,y;
		scanf("%d %d %d",&op,&x,&y);
		if (op == 0) update(1,1,n,x,y);
		if (op == 1) printf("%d\n",query(1,1,n,x,y));
	}
	return 0;
}