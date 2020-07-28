// Ivan Carvalho
// Solution to https://dmoj.ca/problem/banknotes
#include <bits/stdc++.h>
using namespace std;
typedef pair<int,int> ii;
const int MAXN = 201;
const int MAXK = 20001;
int N,K,b[MAXN],c[MAXN],resposta[MAXN],dp[MAXN][MAXK];
int main(){
	cin >> N;
	for(int i = 1;i<=N;i++) cin >> b[i];
	for(int i = 1;i<=N;i++) cin >> c[i];
	cin >> K;
	for(int i = 0;i<=K;i++) dp[0][i] = MAXK;
	dp[0][0] = 0;
	for(int i = 1;i<=N;i++){
		for(int j = 0;j<=K;j++){
			dp[i][j] = dp[i-1][j];
		}
		for(int resto = 0;resto < b[i];resto++){
			int ultimo = (K/b[i])*b[i];
			int sobra = K % b[i];
			if(resto <= sobra){
				ultimo += resto;
			}
			else{
				ultimo += (sobra - resto);
			}
			deque<ii> janela;
			for(int j = 1;j<c[i] && ultimo - j*b[i] >= 0;j++){
				ii novo = ii(dp[i-1][ultimo - j*b[i]] + j,ultimo - j*b[i]);
				while(!janela.empty() && janela.back().first >= novo.first) janela.pop_back();
				janela.push_back(novo); 
			}
			for(int j = 0,val = ultimo;val > 0;j++,val -= b[i]){
				while(!janela.empty() && janela.front().second >= val) janela.pop_front();
				if(val - c[i]*b[i] >= 0){
					ii novo = ii(dp[i-1][val - c[i]*b[i]] + j + c[i],val - c[i]*b[i]);
					while(!janela.empty() && janela.back().first >= novo.first) janela.pop_back();
					janela.push_back(novo); 
				}
				if(!janela.empty()) dp[i][val] = min(dp[i][val],janela.front().first - j);
				//printf("I %d Resto %d Val %d Dp %d %d\n",i,resto,val,dp[i][val],dp[i-1][val]);
			}
		}
	}
	cout << dp[N][K] << endl; 
	return 0;
}
