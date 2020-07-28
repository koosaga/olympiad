// Ivan Carvalho
// Solution to https://www.spoj.com/problems/KQUERYO/
#include <cstdio>
#include <vector>
#include <algorithm>
#define MAXN 100110
#define MP make_pair
#define LSOne(S) (S & (-S))
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
bool compara(ii x, ii y){
	return x.first > y.first;
}
bool ordena(int x, int y){
	return x > y;
}
int n,last,vetor[MAXN],q;
vector< vector<ii> > bit;
void update(int pos, int id){
	while(pos <= n){
		bit[pos].push_back(MP(id,bit[pos].back().second + 1));
		pos += LSOne(pos);
	}
}
int query(int pos, int id){
	int sum = 0;
	while(pos > 0){
		sum += (*(lower_bound(bit[pos].rbegin(),bit[pos].rend(),MP(id,0),compara))).second;
		pos -= LSOne(pos);
	}
	return sum;
}
int busca(int val){
	if (val >= vetor[1]) return 0;
	if (val < vetor[n]) return n;
	int ini = 1, fim = n, meio,resp;
	while(ini <= fim){
		meio = (ini+fim)/2;
		if (val < vetor[meio]){
			resp = meio;
			ini = meio + 1;
		}
		else fim = meio - 1;
	}
	return resp;
}
int main(){
	getint(n);
	vector<ii> temp;
	temp.push_back(MP(0,0));
	bit.assign(n+10,temp);
	temp.clear();
	for(int i=1;i<=n;i++){
		getint(vetor[i]);
		temp.push_back(MP(vetor[i],i));
	}
	sort(vetor+1,vetor+n+1,ordena);
	sort(temp.rbegin(),temp.rend());
	for(int i=1;i<=n;i++){
		update(temp[i-1].second,i);
	}
	getint(q);
	while(q--){
		int a,b,c;
		getint(a);
		getint(b);
		getint(c);
		a ^= last;
		b ^= last;
		c ^= last;
		if (a < 1) a = 1;
		if (b > n) b = n;
		if (a > b || c >= vetor[1]){
			print(0);
			last = 0;
			continue;
		}
		int atualizacao = busca(c);
		last = query(b,atualizacao) - query(a-1,atualizacao);
		print(last);
	}
	return 0;
}