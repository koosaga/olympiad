// Ivan Carvalho
// Solution to https://www.urionlinejudge.com.br/judge/problems/view/1431
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cstring>
#define MAXK 1002
#define MAXN 10010
#define gc getchar_unlocked
void getint(int &x){
    register int c = gc();
    x = 0;
    for(;(c<48 || c>57);c = gc());
    for(;c>47 && c<58;c = gc()) {x = (x<<1) + (x<<3) + c - 48;}
}
using namespace std;
int counting_sort[MAXK],soma[MAXN][MAXK],tam[MAXN],n;
int main(){
	while(true){
		getint(n);
		if(n == 0) break;
		for(int i=1;i<=n;i++){
			getint(tam[i]);
			memset(counting_sort,0,sizeof(counting_sort));
			for(int j=1;j<=tam[i];j++){
				int davez;
				getint(davez);
				counting_sort[davez+1]++;
			}
			for(int j=1;j<MAXK;j++){
				soma[i][j] = counting_sort[j] + soma[i][j-1];
			}
		}
		int resp = 1e9;
		for(int j=1;j<MAXK;j++){
			int temp = 0;
			for(int i=1;i<=n;i++){
				int antes = soma[i][j-1];
				int depois = tam[i] - antes;
				temp += abs(antes - depois);
			}
			resp = min(resp,temp);
		}
		printf("%d\n",resp);
	}
	return 0;
}
