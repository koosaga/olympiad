// Ivan Carvalho
// Solution to https://www.urionlinejudge.com.br/judge/problems/view/1476
#include <cstdio>
#include <algorithm>
#include <vector>
#define MAXN 100010
#define MP make_pair
#define gc getchar_unlocked
void getint(int &x){
    register int c = gc();
    x = 0;
    for(;(c<48 || c>57);c = gc());
    for(;c>47 && c<58;c = gc()) {x = (x<<1) + (x<<3) + c - 48;}
}
inline void print(int n)
{
	if (n == 0)
	{
		putchar_unlocked('0');
		putchar_unlocked('\n');
	}
	else if (n == -1)
	{
		putchar_unlocked('-');
		putchar_unlocked('1');
		putchar_unlocked('\n');
	}
	else
	{
		char buf[11];
		buf[10] = '\n';
		int i = 9;
		while (n)
		{
			buf[i--] = n % 10 + '0';
			n /= 10;
		}
		while (buf[i] != '\n')
			putchar_unlocked(buf[++i]);
	}
}
using namespace std;
typedef pair<int,int> ii;
typedef pair<int,ii> iii;
int pai[MAXN],nivel[MAXN],ligapai[MAXN],conjunto[MAXN],n,m,s,parar;
vector<ii> grafo[MAXN];
vector<iii> Kruskal;
int find(int x){
	if(conjunto[x] == x) return x;
	return conjunto[x] = find(conjunto[x]);
}
void join(int x, int y){
	x = find(x);
	y = find(y);
	if(x > y) swap(x,y);
	conjunto[y] = x;
}
void dfs(int x){
	for(int i=0;i<grafo[x].size();i++){
		int u = grafo[x][i].first, peso = grafo[x][i].second;
		if(pai[u] == -1){
			pai[u] = x;
			nivel[u] = nivel[x] + 1;
			ligapai[u] = peso;
			dfs(u);
		}
	}
}
int LCA(int u, int v){
	int resp = MAXN;
	while(u != v){
		if(nivel[u] > nivel[v]){
			resp = min(resp,ligapai[u]);
			u = pai[u];
		}
		else{
			resp = min(resp,ligapai[v]);
			v = pai[v];
		}
	}
	return resp;
}
int main(){
	while(scanf("%d %d %d",&n,&m,&s) != EOF){
		for(int i=0;i<=n;i++){
			pai[i] = -1;
			conjunto[i] = i;
			nivel[i] = -1;
			ligapai[i] = MAXN;
			grafo[i].clear();
		}
		Kruskal.clear();
		parar = n - 1;
		for(int i=1;i<=m;i++){
			int u,v,peso;
			getint(u);
			getint(v);
			getint(peso);
			Kruskal.push_back(MP(-peso,MP(u,v)));
		}
		sort(Kruskal.begin(),Kruskal.end());
		for(int i=0;i<m && parar;i++){
			if(find(Kruskal[i].second.first) != find(Kruskal[i].second.second)){
				parar--;
				join(Kruskal[i].second.first,Kruskal[i].second.second);
				grafo[Kruskal[i].second.second].push_back(MP(Kruskal[i].second.first,-Kruskal[i].first));
				grafo[Kruskal[i].second.first].push_back(MP(Kruskal[i].second.second,-Kruskal[i].first));
			}
		}
		nivel[1] = 0;
		pai[1] = 0;
		dfs(1);
		while(s--){
			int u,v;
			getint(u);
			getint(v);
			print(LCA(u,v));
		}
	}
	return 0;
}
