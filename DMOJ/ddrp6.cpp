// Ivan Carvalho
// Solution to https://dmoj.ca/problem/ddrp6
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef tuple<char,char,char,char> quadra;
typedef tuple<char,char,char> trinca;

const int MAXN = 64;
const ll MOD = 1e9 + 7;
char possiveis[4] = {'L','R','U','D'};

vector<trinca> todas;
map<trinca,int> conversao;
quadra proibida1,proibida2;

struct matrix{
	
	ll mat[MAXN][MAXN];
	
	matrix(int identidade = 0){
		for(int i = 0;i<MAXN;i++){
			for(int j = 0;j<MAXN;j++){
				mat[i][j] = ((i == j) && identidade);
			}
		}
	}

	matrix operator*(const matrix& other)const{
		matrix ans;
		for(int i = 0;i<MAXN;i++){
			for(int j = 0;j<MAXN;j++){
				for(int k = 0;k<MAXN;k++){
					ans.mat[i][j] = (ans.mat[i][j] + mat[i][k]*other.mat[k][j]) % MOD;
				}
			}
		}
		return ans;
	}

};

matrix expo(ll pot,matrix A){	
	matrix resposta(1);
	matrix copia = A;
	for(ll i = 0;(1LL << i) <= pot;i++){
		if(pot & (1LL << i)) resposta = resposta*copia;
		copia = copia*copia;
	}
	return resposta;
}

quadra rotaciona(quadra q){
	return make_tuple(get<3>(q),get<0>(q),get<1>(q),get<2>(q));
}

quadra adiciona(trinca t,char letra){
	return make_tuple(get<0>(t),get<1>(t),get<2>(t),letra);
}

trinca ultimas(quadra q){
	return make_tuple(get<1>(q),get<2>(q),get<3>(q));
}

int get_id(trinca t){
	if(!conversao.count(t)){
		int tam = conversao.size();
		conversao[t] = tam;
		todas.push_back(t);
	}
	return conversao[t];
}

int main(){
	
	ll  N;
	cin >> N;
	
	if(N < 3){
		if(N == 1) cout << 4 << endl;
		else cout << 16 << endl;
		return 0;
	}
	
	proibida1 = make_tuple('L','D','R','U');
	proibida2 = make_tuple('L','U','R','D');
	matrix base;

	for(int i = 0;i<4;i++){
		for(int j = 0;j<4;j++){
			for(int k = 0;k<4;k++){
				trinca davez = make_tuple(possiveis[i],possiveis[j],possiveis[k]);
				int numero = get_id(davez);
			}
		}
	}

	for(trinca davez : todas){
		for(int i = 0;i<4;i++){
			quadra nova = adiciona(davez,possiveis[i]);
			int flag = 0;
			quadra copia1 = proibida1,copia2 = proibida2;
			for(int j = 0;j<=4;j++){
				if(copia1 == nova || copia2 == nova) flag = 1;
				copia1 = rotaciona(copia1);
				copia2 = rotaciona(copia2);
			}
			if(flag) continue;
			trinca sobra = ultimas(nova);
			int id1 = get_id(davez);
			int id2 = get_id(sobra);
			base.mat[id2][id1] = 1;
		}
	}

	matrix resposta = expo(N - 3,base);
	ll tot = 0;
	for(int i = 0;i<MAXN;i++){
		for(int j = 0;j<MAXN;j++){
			tot = (tot + resposta.mat[i][j]) % MOD;
		}
	}

	cout << tot << endl;

	return 0;
}