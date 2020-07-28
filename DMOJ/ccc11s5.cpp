// Ivan Carvalho
// Solution to https://dmoj.ca/problem/ccc11s5
#include <cstdio>
#include <queue>
#include <bitset>
#include <unordered_set>
#define MP make_pair
using namespace std;
typedef bitset<25> bt;
typedef pair<int,bt> ibt;
bitset< (1 << 25) + 1> cjt;
int n;
inline bt liga(int pos,bt davez){
	davez.set(pos);
	int ini = pos;
	int fim = pos;
	while(fim + 1 < n && davez.test(fim+1)){
		fim++;
	}
	while(ini - 1 >= 0 && davez.test(ini-1)){
		ini--;
	}
	if(fim - ini + 1 < 4) return davez;
	for(int i = ini;i<=fim;i++) davez.reset(i);
	return davez;
}
int main(){
	bt inicial;
	scanf("%d",&n);
	for(int i=0;i<n;i++){
		int davez;
		scanf("%d",&davez);
		if(davez) inicial.set(i);
	}
	queue<ibt> bfs;
	bfs.push(MP(0,inicial));
	cjt.set(inicial.to_ulong());
	while(!bfs.empty()){
		ibt agora = bfs.front();
		bfs.pop();
		int dist = agora.first;
		bt davez = agora.second;
		if(davez.count() == 0){
			printf("%d\n",dist);
			return 0;
		}
		for(int i=0;i<n;i++){
			if(davez.test(i)) continue;
			bt prox = liga(i,davez);
			if(!cjt.test(prox.to_ulong())){
				cjt.set(prox.to_ulong());
				bfs.push(MP(dist+1,prox));
			}
		}
	}
	return 0;
}