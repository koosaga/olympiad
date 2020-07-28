// Ivan Carvalho
// Solution to https://www.spoj.com/problems/ILKQUERY/
#include <cstdio>
#include <unordered_map>
#include <set>
#include <algorithm>
#include <vector>
#define MP make_pair
#define MAXN 100011
#define LSOne(S) (S & (-S))
#define gc getchar_unlocked
void getint(int &x){
    register int c = gc();
    x = 0;
    int neg = 0;
    for(;((c<48 || c>57) && c != '-');c = gc());
    if(c=='-') {neg=1;c=gc();}
    for(;c>47 && c<58;c = gc()) {x = (x<<1) + (x<<3) + c - 48;}
    if(neg) x=-x;
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
typedef pair<int,iii> iiii;
int vetor[MAXN],n,q,contador,minimo[MAXN],maximo[MAXN],bit[MAXN],resposta[MAXN],atualizacao = -1;
set<int> conjunto;
unordered_map<int,int> compressao;
vector<int> aparicao[MAXN];
vector<iiii> roubei;
void update(int pos){
	while(pos <= n){
		bit[pos]++;
		pos += LSOne(pos);
	}
}
int query(int pos){
	int sum = 0;
	while(pos > 0){
		sum += bit[pos];
		pos -= LSOne(pos);
	}
	return sum;
}
int busca(int idx){
	int ini = minimo[atualizacao], fim = maximo[atualizacao], meio, resp;
	while(ini <= fim){
		int meio = (ini+fim)/2;
		int soma = query(meio);
		//printf("INI %d FIM %d MEIO %d SOMA %d\n",ini,fim,meio,soma);
		if (soma >= idx){
			fim = meio - 1;
			resp = meio;
		}
		else ini = meio + 1;
	}
	return resp;
}
int main(){
	getint(n);
	getint(q);
	for(int i=0;i<n;i++){
		getint(vetor[i]);
		conjunto.insert(vetor[i]);
	}
	for(set<int>::iterator it = conjunto.begin(); it != conjunto.end(); it++){
		compressao[*it] = ++ contador;
	}
	for(int i=0;i<n;i++){
		vetor[i] = compressao[vetor[i]];
		aparicao[vetor[i]].push_back(i);
	}
	minimo[0] = maximo[0] = vetor[0];
	for(int i=1;i<n;i++){
		minimo[i] = min(minimo[i-1],vetor[i]);
		maximo[i] = max(vetor[i],maximo[i-1]);
	}
	for(int j = 0; j <q;j++){
		int i,k,l;
		getint(k);
		getint(i);
		getint(l);
		if (k == 0){
			resposta[j] = -1;
			continue;
		}
		if (i == n) i = n-1;
		roubei.push_back(MP(i,MP(j,MP(k,l))));
	}
	sort(roubei.begin(),roubei.end());
	for(int davez= 0; davez < roubei.size();davez++){
		iiii temp = roubei[davez];
		int i = temp.first, j = temp.second.first, k = temp.second.second.first, l = temp.second.second.second;
		while(atualizacao < i){
			update(vetor[++atualizacao]);
		}
		int achamos = busca(k);
		if (l > aparicao[achamos].size()){
			resposta[j] = -1;
			continue;
		}
		resposta[j] = aparicao[achamos][l-1];
	}
	for(int i=0;i<q;i++) print(resposta[i]);
	return 0;
}