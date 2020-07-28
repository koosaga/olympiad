// Ivan Carvalho
// Solution to https://www.spoj.com/problems/RACETIME/
#include <iostream>
#include <cmath>
#include <set>
#include <unordered_map>
#define MAXN 150001
#define MAXS 400
#define endl '\n'
#define LSOne(S) (S & (-S))
using namespace std;
int vetor[MAXN],bit[MAXN][MAXS],contador,n,S,q,entrada2[MAXN],entrada3[MAXN],entrada4[MAXN];
char entrada1[MAXN];
set<int> conjunto;
unordered_map<int,int> compressao;
void update(int pos, int val, int id){
	while(pos <= n+q){
		bit[pos][id] += val;
		pos += LSOne(pos);
	}
}
int sum(int pos, int id){
	int answer = 0;
	while(pos > 0){
		answer += bit[pos][id];
		pos -= LSOne(pos);
	}
	return answer;
}
int main(){
	cin.tie(0);
	cout.tie(0);
	ios_base::sync_with_stdio(0);
	cin >> n >> q;
	S = sqrt(n);
	for(int i=0;i<n;i++){
		cin >> vetor[i];
		conjunto.insert(vetor[i]);
	}
	for(int i=0;i<q;i++){
		cin >> entrada1[i];
		if (entrada1[i] == 'C'){
			cin >> entrada2[i] >> entrada3[i] >> entrada4[i];
			entrada2[i]--;
			entrada3[i]--;
			conjunto.insert(entrada4[i]);
		}
		if (entrada1[i] == 'M'){
			cin >> entrada2[i] >> entrada3[i];
			entrada2[i]--;
			conjunto.insert(entrada3[i]);
		}
	}
	for(set<int>::iterator it = conjunto.begin();it != conjunto.end();it++){
		compressao[*it] = ++contador;
	}
	for(int i=0;i<n;i++){
		vetor[i] = compressao[vetor[i]];
		update(vetor[i],1,i/S);
	}
	for(int i=0;i<q;i++){
		if (entrada1[i] == 'M'){
			entrada3[i] = compressao[entrada3[i]];
			update(vetor[entrada2[i]],-1,entrada2[i]/S);
			vetor[entrada2[i]] = entrada3[i];
			update(vetor[entrada2[i]],1,entrada2[i]/S);
		}
		if (entrada1[i] == 'C'){
			int resposta = 0;
			int c_left = entrada2[i]/S, c_right = entrada3[i]/S , left = entrada2[i], right = entrada3[i], x = compressao[entrada4[i]];
			if (c_left == c_right){
				for(int j=left;j<=right;j++){
					resposta += (vetor[j] <= x);
				}
			}
			else{
				for (int j=left;j<=(c_left+1)*S-1;j++){
					resposta += (vetor[j] <= x);
				}
				for(int j = c_left+1;j<=c_right-1;j++) resposta += sum(x,j);
				for(int j = c_right*S;j<=right;j++){
					resposta += (vetor[j] <= x);
				}
			}
			cout << resposta << endl;
		}
	}
	return 0;
}