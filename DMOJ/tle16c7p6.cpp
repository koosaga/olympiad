// Ivan Carvalho
// Solution to https://dmoj.ca/problem/tle16c7p6
#include <cstdio>
#include <cstring>
#include <vector>
#define MAXN 100010
#define ALPHABET_SIZE 26
using namespace std;
vector<vector<int> > Trie;
vector<int> passam,terminam;
int raiz[MAXN];
int ptr,n,m;
char entrada[MAXN];
int main(){
	scanf("%d %d",&n,&m);
	vector<int> modelo;
	modelo.assign(ALPHABET_SIZE,0);
	Trie.push_back(modelo);
	passam.push_back(0);
	terminam.push_back(0);
	for(int vez = 1;vez<=n;vez++){
		scanf("%s",entrada);
		int tam = strlen(entrada);
		raiz[vez] = ++ptr;
		passam.push_back(0);
		terminam.push_back(0);
		Trie.push_back(Trie[raiz[vez-1]]);
		int novoatual = raiz[vez];
		int velhoatual = raiz[vez-1];
		for(int i=0;i<tam;i++){
			//printf("%d %d : %d %d; %d %d\n",velhoatual,novoatual,passam[velhoatual],passam[novoatual],terminam[velhoatual],terminam[novoatual]);
			int c = entrada[i] - 'a';
			int novoprox = ++ptr;
			int velhoprox = Trie[velhoatual][c];
			Trie[novoatual][c] = novoprox;
			Trie.push_back(Trie[velhoprox]);
			passam.push_back(passam[velhoprox]+1);
			terminam.push_back(terminam[velhoprox]);
			novoatual = novoprox;
			velhoatual = velhoprox;
		}
		terminam[novoatual]++;
		//printf("%d %d : %d %d; %d %d\n",velhoatual,novoatual,passam[velhoatual],passam[novoatual],terminam[velhoatual],terminam[novoatual]);
	}
	for(int vez = 1;vez<=m;vez++){
		int a,b;
		scanf("%s %d %d",entrada,&a,&b);
		int lo = raiz[a-1];
		int hi = raiz[b];
		int tam = strlen(entrada);
		int resp = 0;
		for(int i=0;i<tam && hi;i++){
			//printf("%d %d : %d %d; %d %d\n",lo,hi,passam[lo],passam[hi],terminam[lo],terminam[hi]);
			resp += terminam[hi] - terminam[lo];
			int c = entrada[i] - 'a';
			lo = Trie[lo][c];
			hi = Trie[hi][c];
		}
		//printf("%d %d : %d %d; %d %d\n",lo,hi,passam[lo],passam[hi],terminam[lo],terminam[hi]);
		resp += passam[hi] - passam[lo];
		printf("%d\n",resp);
	}
	return 0;
}