// Ivan Carvalho
// Solution to https://www.urionlinejudge.com.br/judge/problems/view/1138
#include <bits/stdc++.h>
using namespace std;
typedef vector<int> vi;
const int MAXN = 12;
vi dp[MAXN][2];
vi digitos;
int vis[MAXN][2];
vi solve(int pos,int flag){
	if(vis[pos][flag]) return dp[pos][flag];
	vis[pos][flag] = 1;
	if(pos == digitos.size() - 1){
		if(flag){
			vi retorna;
			retorna.assign(10,0);
			retorna.push_back(0);
			for(int i = 0;i<=digitos[pos];i++){
				retorna[i]++;
				retorna.back()++;
			}
			return dp[pos][flag] = retorna;
		}
		else{
			vi retorna;
			retorna.assign(10,1);
			retorna.push_back(10);
			return dp[pos][flag] = retorna;
		}
	}
	if(flag){
		vi retorna;
		retorna.assign(11,0);
		for(int i = 0;i<digitos[pos];i++){
			vi temp = solve(pos+1,0);
			for(int j = 0;j<=9;j++) retorna[j] += temp[j];
			retorna.back() += temp.back();
			retorna[i] += temp.back(); 
		}
		vi temp = solve(pos+1,1);
		for(int j = 0;j<=9;j++) retorna[j] += temp[j];
		retorna.back() += temp.back();
		retorna[digitos[pos]] += temp.back(); 
		return dp[pos][flag] = retorna;
	}
	else{
		vi retorna;
		retorna.assign(11,0);
		for(int i = 0;i<=9;i++){
			vi temp = solve(pos+1,0);
			for(int j = 0;j<=9;j++) retorna[j] += temp[j];
			retorna.back() += temp.back();
			retorna[i] += temp.back(); 
		}
		return dp[pos][flag] = retorna;
	}
}
vi calcula(int val){
	if(val == 0){
		vi ret;
		ret.assign(11,0);
		ret[0] = 1;
		return ret;
	}
	for(int i = 0;i<MAXN;i++){
		dp[i][0].clear();dp[i][1].clear();
		vis[i][0] = vis[i][1] = 0;
	}
	digitos.clear();
	while(val != 0){
		digitos.push_back(val%10);
		val /= 10;
	}
	reverse(digitos.begin(),digitos.end());
	vi davez = solve(0,1);
	int copia = 0,pot10 = 1;
	for(int i = digitos.size() - 1;i>=0;i--){
		copia += pot10*digitos[i];
		pot10 *= 10;
	}
	int truque = 9;
	for(int i = 1;i<digitos.size();i++){
		truque = min(truque,copia);
		davez[0] -= (truque+1);
		truque = (truque*10) + 9;
	}
	return davez;
}
int main(){
	int A,B;
	while(scanf("%d %d",&A,&B) && (A || B)){
		vi vet1 = calcula(B);
		vi vet2 = calcula(A-1);
		printf("%d",vet1[0] - vet2[0]);
		for(int i = 1;i<=9;i++) printf(" %d",vet1[i] - vet2[i]);
		printf("\n");
	}
	return 0;
}
