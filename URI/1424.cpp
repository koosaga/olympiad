// Ivan Carvalho
// Solution to https://www.urionlinejudge.com.br/judge/problems/view/1424
#include <cstdio>
#include <vector>
#include <set>
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
#define PB push_back
typedef vector<int> vi;
vi rujia[1000001];
int tamanho[1000001];
int main(){
	int n,q;
	set<int> limpar;
	while(scanf("%d %d",&n,&q)!=EOF){
		for(set<int>::iterator it = limpar.begin();it!=limpar.end();it++){
			rujia[*it].clear();
			tamanho[*it] = 0;
		}
		limpar.clear();
		for(int i=1;i<=n;i++){
			int x;
			getint(x);
			rujia[x].PB(i);
			tamanho[x]++;
			limpar.insert(x);
		}
		while(q--){
			int x,y;
			getint(x);
			getint(y);
			print((x<=tamanho[y]) ? rujia[y][x-1] : 0);
		}
	}
	return 0;
}
