// Ivan Carvalho
// Solution to https://dmoj.ca/problem/tle16c3p5
#include <bits/stdc++.h>
#define MP make_pair
#define gc getchar_unlocked
inline void getint(int &x){
    int c = gc();
    x = 0;
    for(;(c<48 || c>57);c = gc());
    for(;c>47 && c<58;c = gc()) {x = (x<<1) + (x<<3) + c - 48;}
}
using namespace std;
const int MAXN = 351;
typedef pair<int,int> point;
typedef pair<point,point> rectangle;
const rectangle NULO = MP(MP(-1,-1),MP(-1,-1));
int matriz[MAXN][MAXN],soma[MAXN][MAXN],linear[MAXN],R,C,resp,M;
rectangle atual;
inline void calc_line(int r){
	for(int c  = 1;c<=C;c++) soma[r][c] = soma[r][c-1] + matriz[r][c];
}
inline int custo(int i,int j){
	return linear[j] - linear[i-1];
}
inline rectangle solve(int l){
	for(int ini = 1,fim = l;fim <= C;ini++,fim++){
		for(int i =1;i<=R;i++) linear[i] = ((soma[i][fim] - soma[i][ini-1]) == l) + linear[i-1];
		for(int outroini = 1,outrofim = l;outrofim <= R;outroini++,outrofim++){
			if(custo(outroini,outrofim) == l){
				return MP(MP(outroini,ini),MP(outrofim,fim));
			}
		}
	}
	return NULO;
}
inline int in_rectangle(int x,int y){
	return atual.first.first <= x && x <= atual.second.first && atual.first.second <= y && y <= atual.second.second;
}
inline void bs(){
	rectangle truque = solve(resp);
	if(truque != NULO){
		atual = truque;
		return;
	}
	truque = solve(resp - 1);
	if(truque != NULO){
		atual = truque;
		resp--;
		return;
	}
	int ini = max(resp-1,0)/4,fim = resp-2,meio,maior = -1;
	rectangle candidato;
	while(ini <= fim){
		meio = (ini+fim)/2;
		rectangle temp = solve(meio);
		if(temp != NULO){
			maior = meio;
			ini = meio + 1;
			candidato = temp;
		}
		else fim = meio - 1;
	}
	resp = maior;
	atual = candidato;
}
int main(){
	getint(R);
	getint(C);
	getint(M);
	for(int i=1;i<=R;i++){
		for(int j=1;j<=C;j++) matriz[i][j] = 1;
		calc_line(i);
	}
	resp = min(R,C);
	atual = solve(resp);
	while(M--){
		int x,y;
		getint(x);
		getint(y);
		matriz[x][y] = 0;
		calc_line(x);
		if(in_rectangle(x,y)) bs();
		printf("%d\n",resp);
	}
	return 0;
}	}
	return 0;
}