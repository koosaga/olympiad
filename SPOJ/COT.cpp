// Ivan Carvalho
// Solution to https://www.spoj.com/problems/COT/
#include <cstdio>
#include <vector>
#include <algorithm>
#include <set>
#include <map>
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
const int MAXN = 121111;
const ii NULO = MP(MAXN,MAXN);
vector<int> grafo[MAXN],esq,dir,val;
set<int> conjunto;
map<int,int> compressao;
vector<int> reverso;
int dfsNum,cnt,segIt,nivel[MAXN],pai[MAXN],numero[MAXN],vetor[MAXN],raiz[MAXN],n,m;
ii arvore[8*MAXN],vetorzao[2*MAXN];
void update_persistent(int novo,int velho,int left,int right,int x){
	if(left == right){
		val[novo] = val[velho] + 1;
		//printf("Novo %d Velho %d L %d R %d X %d Esq %d Dir %d Val %d\n",novo,velho,left,right,x,esq[n]vo),dir[n]vo),val(novo));
		return;
	}
	int mid = (left + right)/2;
	if(x <= mid){
		segIt++;
		esq.push_back(0);
		dir.push_back(0);
		val.push_back(0);
		esq[novo] = segIt;
		dir[novo] = dir[velho];
		val[novo] = val[velho] + 1;
		//printf("Novo %d Velho %d L %d R %d X %d Esq %d Dir %d Val %d\n",novo,velho,left,right,x,esq[n]vo),dir[n]vo),val(novo));
		update_persistent(esq[novo],esq[velho],left,mid,x);
	}
	else{
		segIt++;
		esq.push_back(0);
		dir.push_back(0);
		val.push_back(0);
		esq[novo] = esq[velho];
		dir[novo] = segIt;
		val[novo] = val[velho] + 1;
		//printf("Novo %d Velho %d L %d R %d X %d Esq %d Dir %d Val %d\n",novo,velho,left,right,x,esq[n]vo),dir[n]vo),val(novo));
		update_persistent(dir[novo],dir[velho],mid+1,right,x);
	}
}
//int query_persistent(int pos,int left,int right,int i,int j){
//	if(left > right || left > j || right < i || pos == -1) return 0;
//	if(left >= i && right <= j){
//		return val[pos]; 
//	}
//	int mid = (left+right)/2;
//	int sinistra = (esq[pos] == -1) ? 0 : query_persistent(esq[pos],left,mid,i,j);
//	int destra = (dir[pos] == -1) ? 0 : query_persistent(dir[pos],mid+1,right,i,j);
//	return sinistra + destra;
//}
int kth(int a,int b,int c,int d,int left,int right,int count){
	//printf("%d %d %d %d %d L %d R %d C %d ",val(a) + val(b) - val(c) - val(d),a,b,c,d,left,right,count);
	if(left == right){
		return left;
	}
	int mid = (left+right)/2;
	int davez = val[esq[a]] + val[esq[b]] - val[esq[c]] - val[esq[d]];
	//printf("%d\n",davez);
	if(count <= davez) return kth(esq[a],esq[b],esq[c],esq[d],left,mid,count);
	return kth(dir[a],dir[b],dir[c],dir[d],mid+1,right,count - davez);
}
void dfs(int x,int p){
	vetor[x] = ++dfsNum;
	vetorzao[dfsNum] = MP(nivel[x],x);
	for(int i = 0;i < grafo[x].size();i++){
		int v = grafo[x][i];
		if(v == p) continue;
		pai[v] = x;
		nivel[v] = nivel[x] + 1;
		raiz[v] = ++segIt;
		dir.push_back(0);
		esq.push_back(0);
		val.push_back(0);
		update_persistent(segIt,raiz[x],1,cnt,numero[v]);
		dfs(v,x);
		vetorzao[++dfsNum] = MP(nivel[x],x);
	}
}
void build_lca(int pos,int left,int right){
	if(left == right){
		arvore[pos] = vetorzao[left];
		return;
	}
	int mid = (left+right)/2;
	build_lca(2*pos,left,mid);
	build_lca(2*pos+1,mid+1,right);
	arvore[pos] = min(arvore[2*pos],arvore[2*pos+1]);
}
ii query_lca(int pos,int left,int right,int i,int j){
	if(left > right || left > j || right < i) return NULO;
	if(left >= i && right <= j){
		return arvore[pos];
	}
	int mid = (left+right)/2;
	return min(query_lca(2*pos,left,mid,i,j),query_lca(2*pos+1,mid+1,right,i,j));
}
int LCA(int u,int v){
	return query_lca(1,1,dfsNum,min(vetor[u],vetor[v]),max(vetor[u],vetor[v])).second;
}
int doQuery(int u,int v,int count){
	int ancestor = LCA(u,v);
	//for(int i=1;i<=cnt;i++) //printf("%d ",query_persistent(raiz[u],1,cnt,i,i));
	//printf("\n");
	//for(int i=1;i<=cnt;i++) //printf("%d ",query_persistent(raiz[v],1,cnt,i,i));
	//printf("\n");
	//for(int i=1;i<=cnt;i++) //printf("%d ",query_persistent(raiz[ancestor],1,cnt,i,i));
	//printf("\n");
	//for(int i=1;i<=cnt;i++) //printf("%d ",query_persistent(raiz[pai[ancestor]],1,cnt,i,i));
	//printf("\n");
	return reverso[kth(raiz[u],raiz[v],raiz[ancestor],raiz[pai[ancestor]],1,cnt,count)];
}
int main(){
	scanf("%d %d",&n,&m);
	for(int i=1;i<=n;i++){
		scanf("%d",&numero[i]);
		conjunto.insert(numero[i]);
	}
	reverso.push_back(0);
	for(set<int>::iterator it = conjunto.begin();it != conjunto.end();it++){
		compressao[*it] = ++cnt;
		reverso.push_back(*it);
	}
	for(int i=1;i<=n;i++) numero[i] = compressao[numero[i]];
	//for(int i=1;i<=n;i++) //printf("%d ",numero[i]);
	//printf("\n");
	for(int i=1;i<n;i++){
		int u,v;
		getint(u);
		getint(v);
		grafo[u].push_back(v);
		grafo[v].push_back(u);
	}
	esq.push_back(0);
	dir.push_back(0);
	val.push_back(0);
	esq.push_back(0);
	dir.push_back(0);
	val.push_back(0);
	segIt++;
	pai[1] = 0;
	raiz[1] = 1;
	raiz[0] = 0;
	update_persistent(raiz[1],0,1,cnt,numero[1]);
	dfs(1,0);
	build_lca(1,1,dfsNum);
	while(m--){
		int u,v,count;
		getint(u);
		getint(v);
		getint(count);
		print(doQuery(u,v,count));
	} 
	return 0;
}