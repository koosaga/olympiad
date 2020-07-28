// Ivan Carvalho
// Solution to https://dmoj.ca/problem/coci08c5p5
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MAXN = 20;
const int LIMIT = 10;

ll dp[MAXN][2],A,B;
ll lo,hi,N,especial;
vector<ll> digitos;

ll solve(int pos,int flag){
	if(dp[pos][flag] != -1) return dp[pos][flag];
	if(pos == N) return dp[pos][flag] = 1;
	if(flag){
		ll tot = 0;
		if(lo <= pos && pos <= hi){
			if(especial <= digitos[pos]) tot += solve(pos+1, (especial == digitos[pos])); 
		}
		else{
			for(int i = 0;i<=digitos[pos];i++){
				if(pos == lo - 1 && i == especial) continue;
				if(pos == hi + 1 && i == especial) continue;
				tot += solve(pos+1, (i == digitos[pos]));
			}
		}
		return dp[pos][flag] = tot;
	} 
	else{
		ll tot = 0;
		if(lo <= pos && pos <= hi){
			tot += solve(pos+1,0);
		}
		else{
			for(int i = 0;i<LIMIT;i++){
				if(pos == lo - 1 && i == especial) continue;
				if(pos == hi + 1 && i == especial) continue;
				tot += solve(pos+1,0);
			}
		}
		return dp[pos][flag] = tot;
	}
}

ll conta(ll numero){
	if(numero == 0) return 0;
	digitos.clear();
	ll copia = numero;
	while(copia != 0){
		digitos.push_back(copia % 10);
		copia /= 10;
	}
	reverse(digitos.begin(),digitos.end());
	N = digitos.size();
	ll somatorio = 0;
	for(especial = 0;especial<LIMIT;especial++){
		for(lo = 0;lo<N;lo++){
			for(hi = lo;hi<N;hi++){
				memset(dp,-1,sizeof(dp));
				ll tam = (hi - lo + 1);
				somatorio += tam*tam*especial*solve(0,1);
			}
		}
	}
	return somatorio;
}

int main(){
	cin >> A >> B;
	cout << conta(B) - conta(A-1) << endl;
	return 0;
}