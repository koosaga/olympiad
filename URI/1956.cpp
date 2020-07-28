// Ivan Carvalho
// Solution to https://www.urionlinejudge.com.br/judge/problems/view/1956
#include <cstdio>
#include <queue>
#define MAXN 10010
#define MP make_pair
#define gc getchar_unlocked
void getint(int &x){
    register int c = gc();
    x = 0;
    for(;(c<48 || c>57);c = gc());
    for(;c>47 && c<58;c = gc()) {x = (x<<1) + (x<<3) + c - 48;}
}
using namespace std;
typedef pair<int,int> ii;
typedef pair<int,ii> iii;
int n,pai[MAXN],peso[MAXN],conjuntos;
long long resposta;
priority_queue<iii, vector<iii>, greater<iii> > kruskal;
int find(int x){
	if (x==pai[x]) return x;
	return pai[x] = find(pai[x]);
}
void join(int x, int y){
	x = find(x);
	y = find(y);
	if (x==y) return;
	conjuntos--;
	if (peso[x]<peso[y]) pai[x] = y;
	if (peso[x]>peso[y]) pai[y] = x;
	else{
		pai[x] = y;
		peso[y]++;
	}
}
int main(){
	getint(n);
	conjuntos = n;
	pai[n] = n;
	for(int i=1;i<n;i++) {
		pai[i] = i;
		int pares;
		getint(pares);
		while(pares--){
			int j,peso;
			getint(j);
			getint(peso);
			kruskal.push(MP(peso,MP(i,j)));
		}
	}
	while(conjuntos > 1 && !kruskal.empty()){
		iii davez = kruskal.top();
		kruskal.pop();
		if (find(davez.second.first)!=find(davez.second.second)){
			join(davez.second.first,davez.second.second);
			resposta += davez.first;
		}
	}
	printf("%d %lld\n",conjuntos,resposta);
	return 0;
}
