// Ivan Carvalho
// Solution to https://dmoj.ca/problem/cco18p5
#include <bits/stdc++.h>
using namespace std;

typedef pair<int,int> ii;

const int MAXN = 1e6 + 10;
const int BUCKET = 1000;

#define gc getchar_unlocked
void getint(int &x){
    int c = gc();
    x = 0;
    for(;(c<48 || c>57);c = gc());
    for(;c>47 && c<58;c = gc()) {x = (x<<1) + (x<<3) + c - 48;}
}

inline void print(int n){
	if (n == 0){
		putchar_unlocked('0');
		putchar_unlocked('\n');
	}
	else{
		char buf[11];
		buf[10] = '\n';
		int i = 9;
		while (n){
			buf[i--] = n % 10 + '0';
			n /= 10;
		}
		while (buf[i] != '\n') putchar_unlocked(buf[++i]);
	}
}

vector<int> especiais;
int vetor[MAXN],marcado[MAXN],maximo[MAXN],melhor,N,K,Q;
int exibe[MAXN],y[MAXN],x[MAXN];
ii janela[MAXN];

int main(){

	scanf("%d %d %d",&N,&K,&Q);
	for(int i = 1;i<=N;i++){
		getint(vetor[i]);
	}

	y[0] = 1;x[0] = vetor[1];
	for(int i = 1;i<=Q;i++){
		getint(y[i]);getint(x[i]);
	}
	Q++;

	for(int lo = 0;lo < Q;lo += BUCKET){
		
		melhor = 0;
		int hi = lo + BUCKET - 1;
		hi = min(hi,Q-1);
		for(int i : especiais){
			maximo[i] = 0;
			marcado[i] = 0;
		}
		especiais.clear();

		for(int i = lo;i<=hi;i++){
			if(!marcado[y[i]]){
				marcado[y[i]] = 1;
				especiais.push_back(y[i]);
			}
		}
		sort(especiais.begin(),especiais.end());

		int ini = 1,fim = 0;
		for(int i = 1;i<=N;i++){
			if(ini <= fim && janela[ini].second <= i - K) ini++;
			if(marcado[i]){
				if(ini <= fim) maximo[i] = max(maximo[i], janela[ini].first );
				continue;
			}
			if(ini <= fim) melhor = max(melhor, vetor[i] + janela[ini].first );
			ii par = ii(vetor[i],i);
			while(ini <= fim && janela[fim].first <= par.first) fim--;
			janela[++fim] = par;
		}
		ini = 1,fim = 0;
		for(int i = N;i>=1;i--){
			if(ini <= fim && janela[ini].second >= i + K) ini++;
			if(marcado[i]){
				if(ini <= fim) maximo[i] = max(maximo[i], janela[ini].first );
				continue;
			}
			if(ini <= fim) melhor = max(melhor, vetor[i] + janela[ini].first );
			ii par = ii(vetor[i],i);
			while(ini <= fim && janela[fim].first <= par.first) fim--;
			janela[++fim] = par;
		}
		ini = 1,fim = 0;

		for(int vez = lo;vez<=hi;vez++){
			vetor[y[vez]] = x[vez];
			int best = melhor;
			ini = 1,fim = 0;
			for(int i : especiais){
				while(ini <= fim && janela[ini].second <= i - K) ini++;
				if(ini <= fim) best = max(best, vetor[i] + janela[ini].first );
				best = max(best, maximo[i] + vetor[i] );
				ii par = ii(vetor[i],i);
				while(ini <= fim && janela[fim].first <= par.first) fim--;
				janela[++fim] = par;
			}
			exibe[vez] = best;
		}

	}

	for(int i = 0;i<Q;i++) print(exibe[i]);

	return 0;
}int i = 0;i<Q;i++) print(exibe[i]);

	return 0;
}