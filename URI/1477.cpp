// Ivan Carvalho
// Solution to https://www.urionlinejudge.com.br/judge/problems/view/1477
#include <cstdio>
#include <cstring>
#define MAXN 100010
int homem[3*MAXN],elefante[3*MAXN],rato[3*MAXN],lazy[3*MAXN];
void build(int pos, int left, int right){
	if (left == right){
		homem[pos] = 1;
		return ;
	}
	int mid = (left+right)/2;
	build(2*pos,left,mid);
	build(2*pos+1,mid+1,right);
	homem[pos] = homem[2*pos]+homem[2*pos+1];
}
void update(int pos, int left, int right, int i, int j){
	if(lazy[pos]!=0){
		if (lazy[pos] == 1){
			int oldhomem = homem[pos];
			int oldelefante = elefante[pos];
			int oldrato = rato[pos];
			homem[pos] = oldrato;
			elefante[pos] = oldhomem;
			rato[pos] = oldelefante;
		}
		if (lazy[pos] == 2){
			int oldhomem = homem[pos];
			int oldelefante = elefante[pos];
			int oldrato = rato[pos];
			homem[pos] = oldelefante;
			elefante[pos] = oldrato;
			rato[pos] = oldhomem;
		}
		if (left != right){
			lazy[2*pos] += lazy[pos];
			lazy[2*pos] %= 3;
			lazy[2*pos+1] += lazy[pos];
			lazy[2*pos+1] %= 3;
		}
		lazy[pos] = 0;
	}
	if (left > right || left > j || right < i) return;
	if(left >= i && right <= j){
		int oldhomem = homem[pos];
		int oldelefante = elefante[pos];
		int oldrato = rato[pos];
		homem[pos] = oldrato;
		elefante[pos] = oldhomem;
		rato[pos] = oldelefante;
		if (left != right){
			lazy[2*pos]++;
			lazy[2*pos] %= 3;
			lazy[2*pos+1]++;
			lazy[2*pos+1] %= 3;
		}
		return ;
	}
	int mid = (left+right)/2;
	update(2*pos,left,mid,i,j);
	update(2*pos+1,mid+1,right,i,j);
	homem[pos] = homem[2*pos]+homem[2*pos+1];
	elefante[pos] = elefante[2*pos]+elefante[2*pos+1];
	rato[pos] = rato[2*pos]+rato[2*pos+1];
}
int query_homem(int pos, int left, int right, int i, int j){
	if(lazy[pos]!=0){
		if (lazy[pos] == 1){
			int oldhomem = homem[pos];
			int oldelefante = elefante[pos];
			int oldrato = rato[pos];
			homem[pos] = oldrato;
			elefante[pos] = oldhomem;
			rato[pos] = oldelefante;
		}
		if (lazy[pos] == 2){
			int oldhomem = homem[pos];
			int oldelefante = elefante[pos];
			int oldrato = rato[pos];
			homem[pos] = oldelefante;
			elefante[pos] = oldrato;
			rato[pos] = oldhomem;
		}
		if (left != right){
			lazy[2*pos] += lazy[pos];
			lazy[2*pos] %= 3;
			lazy[2*pos+1] += lazy[pos];
			lazy[2*pos+1] %= 3;
		}
		lazy[pos] = 0;
	}
	if (left > right || left > j || right < i) return 0;
	if(left >= i && right <= j){
		return homem[pos];
	}
	int mid = (left+right)/2;
	return query_homem(2*pos,left,mid,i,j) + query_homem(2*pos+1,mid+1,right,i,j);
}
int query_elefante(int pos, int left, int right, int i, int j){
	if(lazy[pos]!=0){
		if (lazy[pos] == 1){
			int oldhomem = homem[pos];
			int oldelefante = elefante[pos];
			int oldrato = rato[pos];
			homem[pos] = oldrato;
			elefante[pos] = oldhomem;
			rato[pos] = oldelefante;
		}
		if (lazy[pos] == 2){
			int oldhomem = homem[pos];
			int oldelefante = elefante[pos];
			int oldrato = rato[pos];
			homem[pos] = oldelefante;
			elefante[pos] = oldrato;
			rato[pos] = oldhomem;
		}
		if (left != right){
			lazy[2*pos] += lazy[pos];
			lazy[2*pos] %= 3;
			lazy[2*pos+1] += lazy[pos];
			lazy[2*pos+1] %= 3;
		}
		lazy[pos] = 0;
	}
	if (left > right || left > j || right < i) return 0;
	if(left >= i && right <= j){
		return elefante[pos];
	}
	int mid = (left+right)/2;
	return query_elefante(2*pos,left,mid,i,j) + query_elefante(2*pos+1,mid+1,right,i,j);
}
int query_rato(int pos, int left, int right, int i, int j){
	if(lazy[pos]!=0){
		if (lazy[pos] == 1){
			int oldhomem = homem[pos];
			int oldelefante = elefante[pos];
			int oldrato = rato[pos];
			homem[pos] = oldrato;
			elefante[pos] = oldhomem;
			rato[pos] = oldelefante;
		}
		if (lazy[pos] == 2){
			int oldhomem = homem[pos];
			int oldelefante = elefante[pos];
			int oldrato = rato[pos];
			homem[pos] = oldelefante;
			elefante[pos] = oldrato;
			rato[pos] = oldhomem;
		}
		if (left != right){
			lazy[2*pos] += lazy[pos];
			lazy[2*pos] %= 3;
			lazy[2*pos+1] += lazy[pos];
			lazy[2*pos+1] %= 3;
		}
		lazy[pos] = 0;
	}
	if (left > right || left > j || right < i) return 0;
	if(left >= i && right <= j){
		return rato[pos];
	}
	int mid = (left+right)/2;
	return query_rato(2*pos,left,mid,i,j) + query_rato(2*pos+1,mid+1,right,i,j);
}
int main(){
	int n,q;
	while(scanf("%d %d",&n,&q) != EOF){
		memset(homem,0,sizeof(homem));
		memset(lazy,0,sizeof(lazy));
		memset(rato,0,sizeof(rato));
		memset(elefante,0,sizeof(elefante));
		build(1,1,n);
		while(q--){
			char op;
			int a,b;
			getchar();
			scanf("%c %d %d",&op,&a,&b);
			if (op == 'M') update(1,1,n,a,b);
			if (op == 'C') printf("%d %d %d\n",query_homem(1,1,n,a,b),query_elefante(1,1,n,a,b),query_rato(1,1,n,a,b));
		}
		printf("\n");
	}
	return 0;
}
