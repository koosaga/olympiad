#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef pair<lint, lint> pi;
const int MAXN = 100005;

int n, m, s, da[MAXN], db[MAXN];
int chk[MAXN];
set<int> gph[MAXN];
vector<int> rgph[MAXN];
queue<int> que;

void REMOVE(int x){
	for(auto &i : rgph[x]){
		auto k = gph[i].find(x);
		if(k != gph[i].end()) gph[i].erase(k);
	}
	que.push(x);
}

void solve(){
	db[s] = 0;
	REMOVE(s);
	while(!que.empty()){
		int x = que.front();
		que.pop();
		for(auto &i : rgph[x]) chk[i] = 1;
		for(auto &i : rgph[x]){
			auto it = gph[i].begin();
			while(it != gph[i].end()){
				if(chk[*it]){
					it++;
					continue;
				}
				int nxt = *it;
				db[nxt] = db[x] + 1;
				it = gph[i].erase(it);
				REMOVE(nxt);
			}
		}
		for(auto &i : rgph[x]) chk[i] = 0;
	}
}

int main(){
	int a, b;
	scanf("%d %d %d %d %d",&n,&m,&s,&a,&b);
	for(int i=0; i<m; i++){
		int s, e;
		scanf("%d %d",&s,&e);
		rgph[s].push_back(e);
		rgph[e].push_back(s);
		gph[s].insert(e);
		gph[e].insert(s);
	}
	memset(da, 0x3f, sizeof(da));
	memset(db, 0x3f, sizeof(db));
	queue<int> que;
	da[s] = 0; que.push(s);
	while(!que.empty()){
		int x = que.front();
		que.pop();
		for(auto &i : rgph[x]){
			if(da[i] > da[x] + 1){
				que.push(i);
				da[i] = da[x] + 1;
			}
		}
	}
	solve();
	for(int i=1; i<=n; i++){
		int w = min(2 * a, b);
		if(da[i] % 2 == 0){
			printf("%lld\n", 1ll * w * (da[i] / 2));
		}
		else{
			printf("%lld\n", min(1ll * w * (da[i] / 2) + a, 1ll * db[i] * b));
		}
	}
}
