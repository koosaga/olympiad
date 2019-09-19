#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = pair<int, int>;
#define sz(v) ((int)((v).size()))
const int MAXN = 200005;
 
int n;
vector<int> gph[MAXN];
 
bool QUERY(int v, vector<int> w){
	if(w.empty()){
		return 1;
	}
	printf("? %d %d ",sz(w), v);
	for(auto &i : w) printf("%d ", i);
	fflush(stdout);
	int x; scanf("%d",&x);
	return x;
}
 
int sz[MAXN], msz[MAXN], vis[MAXN];
 
void dfsc(int x, int p, vector<int> &dfn){
	sz[x] = 1;
	msz[x] = 0;
	dfn.push_back(x);
	for(auto &i : gph[x]){
		if(vis[i] || i == p) continue;
		dfsc(i, x, dfn);
		sz[x] += sz[i];
		msz[x] = max(msz[x], sz[i]);
	}
}
 
int get_center(int v){
	vector<int> dfn;
	dfsc(v, -1, dfn);
	pi ret(1e9, 1e9);
	for(auto &i : dfn){
		ret = min(ret, pi(max(sz(dfn) - sz[i], msz[i]), i));
	}
	return ret.second;
}
 
int main(){
	scanf("%d",&n);
	for(int i=0; i<n-1; i++){
		int s, e; scanf("%d %d",&s,&e);
		gph[s].push_back(e);
		gph[e].push_back(s);
	}
	queue<int> que;
	que.push(1);
	while(!que.empty()){
		int x = que.front();
		que.pop();
		x = get_center(x);
		vis[x] = 1;
		vector<int> cdfn;
		vector<pair<int, vector<int> > > v;
		for(auto &i : gph[x]){
			if(!vis[i]){
				vector<int> w;
				dfsc(i, x, w);
				v.emplace_back(i, w);
				for(auto &i : w) cdfn.push_back(i);
			}
		}
		if(QUERY(x, cdfn)){
			printf("! %d\n", x);
			fflush(stdout);
			return 0;
		}
		vector<int> chk(v.size());
		vector<int> idx(v.size());
		iota(idx.begin(), idx.end(), 0);
		sort(idx.begin(), idx.end(), [&](const int &x, const int &y){
			return v[x].second.size() > v[y].second.size();
		});
		while(count(chk.begin(), chk.end(), 0) > 1){
			int sum_size = 0;
			int max_size = 0;
			int max_pos = 0;
			for(int i=0; i<chk.size(); i++){
				if(!chk[i]){
					sum_size += v[i].second.size();
					if(!max_size){
						max_size = v[i].second.size();
						max_pos = i;
					}
				}
			}
			if((2 + sum_size) / 3 <= max_size){
				bool dap = QUERY(x, {v[max_pos].second[0]});
				if(!dap){
					fill(chk.begin(), chk.end(), 1);
					chk[max_pos] = 0;
				}
				else{
					chk[max_pos] = 1;
				}
			}
			else{
				int cur_sum = 0;
				pi minval(1e9, 1e9);
				for(int i=0; i<chk.size(); i++){
					if(!chk[i]) cur_sum += v[i].second.size();
					int tot_cost = max(cur_sum, sum_size - cur_sum);
					minval = min(minval, pi(tot_cost, i));
				}
				vector<int> ans;
				for(int i=0; i<=minval.second; i++){
					if(!chk[i]){
						ans.push_back(v[i].second[0]);
					}
				}
				bool dap = QUERY(x, ans);
				if(!dap){
					fill(chk.begin() + minval.second + 1, chk.end(), 1);
				}
				else{
					fill(chk.begin(), chk.begin() + minval.second + 1, 1);
				}
			}
		}
		for(int i=0; i<chk.size(); i++){
			if(chk[i] == 0){
				que.push(v[i].first);
			}
		}
	}
}
