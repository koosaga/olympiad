#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef pair<int, int> pi;

struct edg{int s, e, x;};
vector<edg> v;
vector<pi> gph[1005];

int n, k, dist[1005];

bool trial(int x){
	for(auto &i : gph[0]) i.first = x;
	memset(dist, 0x3f, sizeof(dist));
	dist[0] = 0;
	for(int i=0; i<=n+1; i++){
		bool upd = 0;
		for(int j=0; j<=n; j++){
			for(auto &k : gph[j]){
				if(dist[k.second] > dist[j] + k.first){
					dist[k.second] = dist[j] + k.first;
					upd = 1;
				}
			}
		}
		if(!upd) break;
		if(i == n+1) return 0;
	}
	return 1;
}

int main(){
	cin >> n >> k;
	for(int i=0; i<k; i++){
		int t, a, b, c;
		scanf("%d %d %d %d",&t,&a,&b,&c);
		if(t == 1 || t == 3){
			gph[b].push_back(pi(-c, a));
		}
		if(t == 2 || t == 3){
			gph[a].push_back(pi(c, b));
		}
	}
	for(int i=1; i<=n; i++){
		gph[i].push_back(pi(0, 0));
		gph[0].push_back(pi(0, i));
	}
	int s = 0, e = 101;
	while(s != e){
		int m = (s+e)/2;
		if(trial(m)) e = m;
		else s = m+1;
	}
	if(e == 101) puts("-1");
	else printf("%d", e);
}

