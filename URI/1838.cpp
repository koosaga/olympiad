// Ivan Carvalho
// Solution to https://www.urionlinejudge.com.br/judge/problems/view/1838
#include <cstdio>
#include <algorithm>
#define MAXN 1010
#define MAXK 3601
#define gc getchar_unlocked
void getint(int &x){
    register int c = gc();
    x = 0;
    for(;(c<48 || c>57);c = gc());
    for(;c>47 && c<58;c = gc()) {x = (x<<1) + (x<<3) + c - 48;}
}
using namespace std;
typedef pair<int,int> ii;
int n,dp[MAXN][MAXK],visitado[MAXN][MAXK];
ii vetor[MAXN];
int solve(int pesquisador, int minuto){
	if (pesquisador > n) return 0;
	if (visitado[pesquisador][minuto]) return dp[pesquisador][minuto];
	visitado[pesquisador][minuto] = 1;
	int nao_usa = solve(pesquisador+1,minuto);
	if(vetor[pesquisador].first >= minuto){
		int usa = vetor[pesquisador].second - vetor[pesquisador].first + solve(pesquisador+1,vetor[pesquisador].second);
		return dp[pesquisador][minuto] = max(nao_usa,usa);
	}
	return dp[pesquisador][minuto] = nao_usa;
}
int main(){
	getint(n);
	for(int i=1;i<=n;i++){
		getint(vetor[i].first);
		getint(vetor[i].second);
	}
	sort(vetor+1,vetor+n+1);
	printf("%d\n",solve(1,0));
	return 0;
}
