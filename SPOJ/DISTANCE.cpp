// Ivan Carvalho
// Solution to https://www.spoj.com/problems/DISTANCE/
#include <cstdio>
#include <algorithm>
#define gc getchar_unlocked
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
using namespace std;
int main(){
	int a[6];
	int n,dimensoes;
	getint(n);
	getint(dimensoes);
	int pot = (1<<(dimensoes-1));
	int minimos[32];
	int maximos[32];
	for(int bitmask = 0;bitmask<pot;bitmask++){
		minimos[bitmask] = 2000000;
		maximos[bitmask] = -minimos[bitmask];
	}
	for(int vez=0;vez<n;vez++){
		for(int i=0;i<dimensoes;i++) getint(a[i]);
		for(int bitmask=0;bitmask<pot;bitmask++){
			int qtd = a[0];
			for(int i =0;i<dimensoes-1;i++){
				if(bitmask & (1<<i)) qtd+=a[i+1];
				else qtd -= a[i+1];
			}
			minimos[bitmask] = min(minimos[bitmask],qtd);
			maximos[bitmask] = max(maximos[bitmask],qtd);
		}
	}
	int ans = 0;
	for(int bitmask=0;bitmask<pot;bitmask++){
		ans = max(ans,maximos[bitmask]-minimos[bitmask]);
	}
	printf("%d\n",ans);
	return 0;
}