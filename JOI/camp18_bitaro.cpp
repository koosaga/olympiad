#include <cmath>
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <set>
#include <map>
#include <list>
#include <time.h>
#include <math.h>
#include <random>
#include <deque>
#include <queue>
#include <cassert>
#include <unordered_map>
#include <iomanip>
#include <bitset>
using namespace std;
typedef long long lint;
typedef pair<int, int> pi;
const int MAXN = 100005;

int n, m, q;
vector<int> gph[MAXN];
vector<int> rev[MAXN];
int dp[MAXN];
vector<pi> low[MAXN];
int chk[MAXN];

int main(){
	scanf("%d %d %d",&n,&m,&q);
	for(int i=0; i<m; i++){
		int s, e;
		scanf("%d %d",&s,&e);
		gph[s].push_back(e);
		rev[e].push_back(s);
	}
	for(int i=1; i<=n; i++){
		low[i].push_back(pi(0, i));
		for(auto &j : rev[i]){
			vector<pi> nxt = low[j];
			vector<pi> prv = low[i];
			low[i].clear();
			int ptr = 0;
			for(auto &k : nxt){
				k.first++;
				while(ptr < prv.size() && prv[ptr].first >= k.first){
					if(chk[prv[ptr].second]){
						ptr++;
						continue;
					}
					chk[prv[ptr].second] = 1;
					low[i].push_back(prv[ptr++]);
				}
				if(chk[k.second]) continue;
				chk[k.second] = 1;
				low[i].push_back(k);
			}
			while(ptr < prv.size()){
				if(chk[prv[ptr].second]){
					ptr++;
					continue;
				}
				chk[prv[ptr].second] = 1;
				low[i].push_back(prv[ptr++]);
			}
			for(auto &i : nxt) chk[i.second] = 0;
			for(auto &i : prv) chk[i.second] = 0;
			while(low[i].size() > 200) low[i].pop_back();
		}
	}
	for(int i=0; i<q; i++){
		int pos, k;
		scanf("%d %d",&pos,&k);
		vector<int> v(k);
		for(auto &i : v) scanf("%d",&i);
		for(auto &i : v) chk[i] = 1;
		int ans = -1;
		if(k >= 200){
			fill(dp, dp + n + 1, -1e9);
			dp[pos] = 0;
			for(int j=pos; j; j--){
				for(auto &k : gph[j]){
					dp[j] = max(dp[j], dp[k] + 1);
				}
				if(chk[j] == 0) ans = max(ans, dp[j]);
			}
		}
		else{
			for(auto &i : low[pos]){
				if(!chk[i.second]){
					ans = i.first;
					break;
				}
			}
		}
		printf("%d\n", ans);
		for(auto &i : v) chk[i] = 0;
	}
}
