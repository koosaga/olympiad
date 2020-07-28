// Ivan Carvalho
// Solution to https://www.spoj.com/problems/TAP2014G/
#include <cstdio>
#include <algorithm>
#include <vector>
#include <unordered_map>
using namespace std;
vector<int> ordenado, absoluto;
int pt1,pt2,pt,n,tam;
unordered_map<int,int> dp[1001];
int solve(int obj,int peso){
	if(obj == tam) return 0;
	if(dp[obj].count(peso)) return dp[obj][peso];
	int nao_coloca = solve(obj+1,peso);
	if(absoluto[obj] <= peso){
		int coloca = 1 + solve(obj + 1, peso - absoluto[obj]);
		//printf("Dp[%d][%d] = %d\n",obj,peso,max(nao_coloca,coloca));
		return dp[obj][peso] = max(coloca,nao_coloca);
	}
	//printf("Dp[%d][%d] = %d\n",obj,peso,nao_coloca);
	return dp[obj][peso] = nao_coloca;
}
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		int davez;
		scanf("%d",&davez);
		ordenado.push_back(davez);
	}
	sort(ordenado.rbegin(),ordenado.rend());
	for(int i=0;i < n;i += 2){
		pt1 += ordenado[i];
		pt2 += ordenado[i+1];
		absoluto.push_back(2*(ordenado[i] - ordenado[i+1]));
	}
	if(pt1 == pt2){
		printf("-1\n");
		return 0;
	}
	pt = pt1 - pt2 - 1;
	tam = absoluto.size();
	printf("%d\n",solve(0,pt));
	return 0;
}