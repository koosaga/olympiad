#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef long double llf;
typedef pair<lint, lint> pi;
const int mod = 1e9 + 7;

map<int, int> gph[100005];
map<int, int> useless;

int n, q, occ[100005], cost[100005];
int s[500005], e[500005], x[500005];

int main(){
	scanf("%d %d",&n,&q);
	for(int i=0; i<q; i++){
		scanf("%d %d %d",&s[i],&e[i],&x[i]);
		occ[s[i]]++;
		occ[e[i]]++;
	}
	int root = min_element(occ + 1, occ + n + 1) - occ;
	int bad = 0;
	for(int i=0; i<q; i++){
		if(s[i] == e[i]){
			if(useless.find(s[i]) != useless.end()){
				if(useless[s[i]] != 0) bad--;
			}
			if(x[i] != 0) bad++;
			useless[s[i]] = x[i];
		}
		else if(s[i] == root || e[i] == root){
			if(e[i] == root) swap(s[i], e[i]), x[i] *= -1;
			for(int j=1; j<=n; j++){
				if(j == e[i] || j == s[i]) continue;
				if(gph[e[i]].find(j) != gph[e[i]].end()){
					if(cost[j] - cost[e[i]] != gph[e[i]][j]) bad--;
				}
				else{
					if(cost[j] - cost[e[i]] != 0) bad--;
				}
			}
			cost[e[i]] = x[i];
			for(int j=1; j<=n; j++){
				if(j == e[i] || j == s[i]) continue;
				if(gph[e[i]].find(j) != gph[e[i]].end()){
					if(cost[j] - cost[e[i]] != gph[e[i]][j]) bad++;
				}
				else{
					if(cost[j] - cost[e[i]] != 0) bad++;
				}
			}
		}
		else{
			int w = gph[s[i]][e[i]];
			if(cost[e[i]] - cost[s[i]] != w){
				bad--;
			}
			if(cost[e[i]] - cost[s[i]] != x[i]){
				bad++;
			}
			gph[s[i]][e[i]] = x[i];
			gph[e[i]][s[i]] = -x[i];
		}
		if(bad > 0) puts("YES");
		else puts("NO");
	}
}
