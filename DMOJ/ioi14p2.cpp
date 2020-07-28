// Ivan Carvalho
// Solution to https://dmoj.ca/problem/ioi14p2
#include <cstdio>
#include <cstring>
#include <algorithm>
#define MAXN 2000010
#define esq(S) ((S << 1) + 1)
#define dir(S) (esq(S) + 1)
#define mid(A,B) (((A+B) >> 1))
using namespace std;
typedef struct node{
	int minimo,maximo;
}no;
int aumentar[4*MAXN], diminuir[4*MAXN],N,K;
no arvore[4*MAXN];
void build(int pos, int left, int right){
	if (left == right){
		arvore[pos].minimo = 0;
		arvore[pos].maximo = 0;
		return;
	}
	build(esq(pos),left,mid(left,right));
	build(dir(pos),mid(left,right)+1,right);
	arvore[pos].minimo = 0;
	arvore[pos].maximo = 0;
}
void update_subir(int pos, int left, int right, int i, int j, int val){
	if (aumentar[pos] != -1){
		arvore[pos].maximo = aumentar[pos];
		arvore[pos].minimo = aumentar[pos];
		if (left != right){
			diminuir[esq(pos)] = -1;
			diminuir[dir(pos)] = -1;
			aumentar[esq(pos)] = aumentar[pos];
			aumentar[dir(pos)] = aumentar[pos];
		}
		aumentar[pos] = -1;
	}
	if (diminuir[pos] != -1){
		arvore[pos].maximo = diminuir[pos];
		arvore[pos].minimo = diminuir[pos];
		if (left != right){
			diminuir[esq(pos)] = diminuir[pos];
			diminuir[dir(pos)] = diminuir[pos];
			aumentar[esq(pos)] = -1;
			aumentar[dir(pos)] = -1;
		}
		diminuir[pos] = -1;
	}
	if (left > right || left > j || right < i) return;
	if (left >= i && right <= j && arvore[pos].minimo == arvore[pos].maximo){
		if (val <= arvore[pos].maximo) return;
		arvore[pos].maximo = val;
		arvore[pos].minimo = val;
		if (left != right){
			diminuir[esq(pos)] = -1;
			diminuir[dir(pos)] = -1;
			aumentar[esq(pos)] = val;
			aumentar[dir(pos)] = val;
		}
		return;
	}
	if (left >= i && right <= j && arvore[pos].maximo <= val){
		arvore[pos].maximo = val;
		arvore[pos].minimo = val;
		diminuir[esq(pos)] = -1;
		diminuir[dir(pos)] = -1;
		aumentar[esq(pos)] = val;
		aumentar[dir(pos)] = val;
		return;
	}
	update_subir(esq(pos),left,mid(left,right),i,j,val);
	update_subir(dir(pos),mid(left,right)+1,right,i,j,val);
	arvore[pos].maximo = max(arvore[esq(pos)].maximo,arvore[dir(pos)].maximo);
	arvore[pos].minimo = min(arvore[esq(pos)].minimo,arvore[dir(pos)].minimo);
}
void update_descer(int pos, int left, int right, int i, int j, int val){
	if (aumentar[pos] != -1){
		arvore[pos].maximo = aumentar[pos];
		arvore[pos].minimo = aumentar[pos];
		if (left != right){
			diminuir[esq(pos)] = -1;
			diminuir[dir(pos)] = -1;
			aumentar[esq(pos)] = aumentar[pos];
			aumentar[dir(pos)] = aumentar[pos];
		}
		aumentar[pos] = -1;
	}
	if (diminuir[pos] != -1){
		arvore[pos].maximo = diminuir[pos];
		arvore[pos].minimo = diminuir[pos];
		if (left != right){
			diminuir[esq(pos)] = diminuir[pos];
			diminuir[dir(pos)] = diminuir[pos];
			aumentar[esq(pos)] = -1;
			aumentar[dir(pos)] = -1;
		}
		diminuir[pos] = -1;
	}
	if (left > right || left > j || right < i) return;
	if (left >= i && right <= j && arvore[pos].minimo == arvore[pos].maximo){
		if (val >= arvore[pos].minimo) return;
		arvore[pos].maximo = val;
		arvore[pos].minimo = val;
		if (left != right){
			diminuir[esq(pos)] = val;
			diminuir[dir(pos)] = val;
			aumentar[esq(pos)] = -1;
			aumentar[dir(pos)] = -1;
		}
		return;
	}
	if (left >= i && right <= j && arvore[pos].minimo >= val){
		arvore[pos].maximo = val;
		arvore[pos].minimo = val;
		diminuir[esq(pos)] = val;
		diminuir[dir(pos)] = val;
		aumentar[esq(pos)] = -1;
		aumentar[dir(pos)] = -1;
		return;
	}
	update_descer(esq(pos),left,mid(left,right),i,j,val);
	update_descer(dir(pos),mid(left,right)+1,right,i,j,val);
	arvore[pos].maximo = max(arvore[esq(pos)].maximo,arvore[dir(pos)].maximo);
	arvore[pos].minimo = min(arvore[esq(pos)].minimo,arvore[dir(pos)].minimo);
}
int query(int pos, int left, int right, int idx){
	if (aumentar[pos] != -1){
		arvore[pos].maximo = aumentar[pos];
		arvore[pos].minimo = aumentar[pos];
		if (left != right){
			diminuir[esq(pos)] = -1;
			diminuir[dir(pos)] = -1;
			aumentar[esq(pos)] = aumentar[pos];
			aumentar[dir(pos)] = aumentar[pos];
		}
		aumentar[pos] = -1;
	}
	if (diminuir[pos] != -1){
		arvore[pos].maximo = diminuir[pos];
		arvore[pos].minimo = diminuir[pos];
		if (left != right){
			diminuir[esq(pos)] = diminuir[pos];
			diminuir[dir(pos)] = diminuir[pos];
			aumentar[esq(pos)] = -1;
			aumentar[dir(pos)] = -1;
		}
		diminuir[pos] = -1;
	}
	if (left > right || left > idx || right < idx) return 0;
	if (left >= idx && right <= idx && arvore[pos].minimo == arvore[pos].maximo){
		return arvore[pos].minimo;
	}
	return query(esq(pos),left,mid(left,right),idx) + query(dir(pos),mid(left,right)+1,right,idx);
}
void buildWall(int n, int k, int op[], int left[], int right[], int height[], int finalHeight[]){
	memset(aumentar,-1,sizeof(aumentar));
	memset(diminuir,-1,sizeof(diminuir));
	N = n;
	K = k;
	build(0,0,N-1);
	for(int vez=0;vez<k;vez++){
		int a,b,c,d;
		a = op[vez];
		b = left[vez];
		c = right[vez];
		d = height[vez];
		if (a == 1){
			update_subir(0,0,N-1,b,c,d);
		}
		if (a == 2){
			update_descer(0,0,N-1,b,c,d);
		}
	}
	for(int i=0;i<n;i++) finalHeight[i] = query(0,0,n-1,i);
}
int main(){
	return 0;
},0,N-1,b,c,d);
		}
	}
	for(int i=0;i<n;i++) finalHeight[i] = query(0,0,n-1,i);
}
int main(){
	return 0;
}