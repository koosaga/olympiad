// Ivan Carvalho
// Solution to https://www.urionlinejudge.com.br/judge/problems/view/1226
#include <bits/stdc++.h>
#define endl '\n'
using namespace std;
typedef unsigned long long llu;
const int MAXN = 21;
llu dp[MAXN][2][2];
bool vis[MAXN][2][2];
vector<int> digits;
llu solve(int pos,int flag,int ultimo){
	if(vis[pos][flag][ultimo]) return dp[pos][flag][ultimo];
	if(pos == digits.size() - 1){
		llu tot = 0;
		int limite = (flag) ? (digits[pos]) : 9;
		for(int i = 0;i<=limite;i++){
			if(i == 4 || (i == 3 && ultimo)) continue;
			tot += 1;
		}
		vis[pos][flag][ultimo] = true;
		return dp[pos][flag][ultimo] = tot;
	}
	else{
		llu tot = 0;
		int limite = (flag) ? (digits[pos]) : 9;
		for(int i = 0;i<=limite;i++){
			if(i == 4 || (i == 3 && ultimo)) continue;
			tot += solve(pos + 1, (flag) && (i == limite), (i == 1));
		}
		vis[pos][flag][ultimo] = true;
		return dp[pos][flag][ultimo] = tot;
	}
}
llu utilidade(llu val){
	digits.clear();
	memset(vis,false,sizeof(vis));
	while(val != 0){
		digits.push_back(val % 10);
		val /= 10;
	}
	reverse(digits.begin(),digits.end());
	return solve(0,1,0) - 1;
}
int main(){
	cin.tie(0);cout.tie(0);ios_base::sync_with_stdio(0);
	llu x;
	while(cin >> x){
		llu ini = 1, fim = 9330720600916705819LLU, meio,resp = 1;
		while(ini <= fim){
			meio = ini + (fim - ini)/2;
			if(utilidade(meio) >= x){
				resp = meio;
				fim = meio - 1;
			}
			else{
				ini = meio + 1;
			}
		}
		cout << resp << endl;
	}
	return 0;
}
