// Ivan Carvalho
// Solution to https://www.spoj.com/problems/BDOI16D/
#include <bits/stdc++.h>
using namespace std;
typedef pair<int,int> ii;
const int MAXN = 1e5 + 10;
const int MAXK = 51;
int dp[MAXN][MAXK];
int N,R,K;
int soma[MAXN],proximo[MAXN];
vector<int> compressao;
vector<ii> entrada;
int solve(int pos,int restam){
	if(pos > N || restam <= 0) return 0;
	if(dp[pos][restam] != -1) return dp[pos][restam];
	return dp[pos][restam] = max(solve(proximo[pos]+1,restam-1) + soma[proximo[pos]] - soma[pos-1],solve(pos+1,restam));
}
int main(){
	int TC;
	scanf("%d",&TC);
	for(int tc = 1;tc<=TC;tc++){
		scanf("%d %d %d",&N,&R,&K);
		R *= 2;
		memset(dp,-1,sizeof(dp));
		compressao.clear();entrada.clear();
		for(int i = 1;i<=N;i++){
			soma[i] = proximo[i] = 0;
			int r,xi;
			scanf("%d %d",&xi,&r);
			entrada.push_back(ii(xi,r));
			compressao.push_back(xi);
		}
		sort(compressao.begin(),compressao.end());
		compressao.erase(unique(compressao.begin(),compressao.end()),compressao.end());
		sort(entrada.begin(),entrada.end());
		vector<ii> temp;
		for(int i = 0;i<N;i++){
			if(!temp.empty() && temp.back().first == entrada[i].first){
				temp.back().second += entrada[i].second;
			}
			else{
				temp.push_back(entrada[i]);
			}
		}
		entrada = temp;
		N = compressao.size();
		for(int i = 0;i<N;i++){
			soma[i+1] = soma[i] +  entrada[i].second;
			proximo[i+1] = prev(upper_bound(compressao.begin(),compressao.end(),entrada[i].first + R)) - compressao.begin() + 1;
		}
		printf("Case %d: %d\n",tc,solve(1,K));
	}
	return 0;
}