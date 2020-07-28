// Ivan Carvalho
// Solution to https://www.urionlinejudge.com.br/judge/problems/view/1348
#include <cstdio>
#include <vector>
#include <stack>
#define MAXN 20001
#define PB push_back
using namespace std;
int processado1[MAXN],processado2[MAXN],componente[MAXN],n,p,ID,possivel;
stack<int> pilha;
vector<int> grafo[MAXN],transposto[MAXN];
inline int neg(int x){
	if(x <= n) return x+n;
	return x-n;
}
void dfs1(int x){
	processado1[x] = 1;
	for(int i=0;i<grafo[x].size();i++){
		int v = grafo[x][i];
		if(!processado1[v]){
			dfs1(v);
		}
	}
	pilha.push(x);
}
void dfs2(int x){
	processado2[x] = 1;
	componente[x] = ID;
	for(int i=0;i<transposto[x].size();i++){
		int v = transposto[x][i];
		if(!processado2[v]){
			dfs2(v);
		}
	}
}
#define gc getchar_unlocked
void getint(int &x){
    register int c = gc();
    x = 0;
    for(;(c<48 || c>57);c = gc());
    for(;c>47 && c<58;c = gc()) {x = (x<<1) + (x<<3) + c - 48;}
}
int main(){
	while(true){
		getint(p);
		getint(n);
		if(n == 0 && p == 0) break;
		for(int i=1;i<=2*n;i++){
			grafo[i].clear();
			transposto[i].clear();
			processado1[i] = 0;
			processado2[i] = 0;
			componente[i] = 0;
		}
		possivel = 1;
		ID = 0;
		while(!pilha.empty()) pilha.pop();
		while(p--){
			int a,b,c,d;
			getint(a);
			getint(b);
			getint(c);
			getint(d);
			if(a || b){
				if(a == 0) a = b;
				if(b == 0) b = a;
				grafo[neg(a)].PB(b);
				transposto[b].PB(neg(a));
				grafo[neg(b)].PB(a);
				transposto[a].PB(neg(b));
			}
			if(c || d){
				if(c == 0) c = d;
				if(d == 0) d = c;
				c = neg(c);
				d = neg(d);
				grafo[neg(c)].PB(d);
				transposto[d].PB(neg(c));
				grafo[neg(d)].PB(c);
				transposto[c].PB(neg(d));
			}
		}
		for(int i=1;i<=2*n;i++){
			if(!processado1[i]) dfs1(i);
		}
		while(!pilha.empty()){
			int i = pilha.top();
			pilha.pop();
			if(!processado2[i]){
				ID++;
				dfs2(i);
			}
		}
		for(int i=1;i<=2*n;i++){
			if(componente[i] == componente[neg(i)]){
				possivel = 0;
				break;
			}
		}
		if(possivel) printf("yes\n");
		else printf("no\n");
	}
	return 0;
}
