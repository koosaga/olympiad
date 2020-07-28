// Ivan Carvalho
// Solution to https://dmoj.ca/problem/ccc12s4
#include <bits/stdc++.h>
using namespace std;
typedef vector<long long> vi;
map<long long,long long> mapa;
long long n;
inline long long get_most(long long bitmask){
	for(long long i = 1;i<=n;i++){
		if(bitmask & (1 << i)){
			return i;
		}
	}
	return 0;
}
inline long long meuhash(vi davez){
	long long ans = 0,pot = 1,prime = 99989,mod = 1e9 + 9;
	for(long long i : davez){
		ans = (ans + i*pot) % mod;
		pot = (pot * prime) % mod;
	}
	return ans;
}
int main(){
	while(cin >> n){
		if(n == 0) break;
		vi ini,alvo;
		mapa.clear();
		for(long long i=0;i<n;i++){
			alvo.push_back((1 << (i+1)));
			long long x;
			cin >> x;
			ini.push_back((1 << x));
		}
		queue<vi> bfs;
		bfs.push(ini);
		mapa[meuhash(ini)] = 0;
		long long possivel = 0;
		while(!bfs.empty()){
			vi davez = bfs.front();
			long long dist = mapa[meuhash(davez)];
			bfs.pop();
			if(davez == alvo){
				cout << dist << endl;
				possivel = 1;
				break;
			}
			vi copia;
			for(long long i=0;i<n;i++) copia.push_back(get_most(davez[i]));
			for(long long i=0;i<n;i++){
				if(copia[i] == 0) continue;
				if((i >= 1 && copia[i] < copia[i-1]) || (i >= 1 && copia[i-1] == 0)){
					//cout << "esquerda " << i << endl;
					long long bitmask = (1 << copia[i]);
					davez[i-1] |= bitmask;
					davez[i] ^= bitmask;
					if(!mapa.count(meuhash(davez))){
						mapa[meuhash(davez)] = dist + 1;
						bfs.push(davez);
					}
					davez[i-1] ^= bitmask;
					davez[i] |= bitmask;
				}
				if((i + 1 < n && copia[i] < copia[i+1]) || (i + 1 < n && copia[i+1] == 0)){
					//cout << "direita " << i << endl;
					long long bitmask = (1 << copia[i]);
					davez[i+1] |= bitmask;
					davez[i] ^= bitmask;
					if(!mapa.count(meuhash(davez))){
						mapa[meuhash(davez)] = dist + 1;
						bfs.push(davez);
					}
					davez[i+1] ^= bitmask;
					davez[i] |= bitmask;
				}
			}
		}
		if(!possivel) cout << "IMPOSSIBLE" << endl;
	}
	return 0;
}
	return 0;
}