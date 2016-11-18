#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef pair<int, int> pi;

int n, k, a[2005][2005], b[15];
int chk[2005], chk2[2005];
int adj[13][13], indeg[13], val[2005];
int dp[2005], tra[2005], cmax[13], trk[13];
vector<int> ord;

vector<int> solve(int msk){
	memset(indeg, 0, sizeof(indeg));
	memset(cmax, -1, sizeof(cmax));
	memset(trk, -1, sizeof(trk));
	vector<int> ret, out;
	for(int i=0; i<k; i++){
		if(((~msk) >> i) & 1){
			ret.push_back(b[i]);
		}
		else{
			out.push_back(b[i]);
		}
	}
	queue<int> que;
	for(int i=0; i<out.size(); i++){
		for(int j=0; j<out.size(); j++){
			adj[i][j] = a[out[i]][out[j]];
			if(adj[i][j]) indeg[j]++;
		}
	}
	for(int i=0; i<out.size(); i++){
		if(!indeg[i]) que.push(i);
	}
	vector<int> lv, rv;
	while(!que.empty()){
		int x = que.front();
		que.pop();
		rv.push_back(out[x]);
		for(int i=0; i<out.size(); i++){
			if(adj[x][i]){
				indeg[i]--;
				if(indeg[i] == 0) que.push(i);
			}
		}
	}
	if(rv.size() != out.size()){
		vector<int> v = {-1};
		return v;
	}
	for(int i=0; i<ord.size(); i++){
		bool bad = 0;
		for(int j=1; j<rv.size(); j++){
			if(a[ord[i]][rv[j-1]] && a[ord[i]][rv[j]] == 0){
				bad = 1;
				break;
			}
		}
		if(!bad) lv.push_back(ord[i]);
		else ret.push_back(ord[i]);
	}
	for(int i=0; i<lv.size(); i++){
		val[i] = rv.size();
		for(int j=0; j<rv.size(); j++){
			if(a[rv[j]][lv[i]] == 0){
				val[i] = j;
				break;
			}
		}
	}
	int dap = 0;
	for(int i=0; i<lv.size(); i++){
		dp[i] = 1;
		tra[i] = -1;
		chk2[i] = 1;
		for(int j=0; j<=val[i]; j++){
			if(dp[i] < cmax[j] + 1){
				dp[i] = cmax[j] + 1;
				tra[i] = trk[j];
			}
		}
		if(cmax[val[i]] < dp[i]){
			cmax[val[i]] = dp[i];
			trk[val[i]] = i;
		}
		dap = max(dap, dp[i]);
	}
	for(int i=0; i<lv.size(); i++){
		if(dp[i] == dap){
			for(int j=i; j!=-1; j=tra[j]){
				chk2[j] = 0;
			}
			for(int i=0; i<lv.size(); i++){
				if(chk2[i]){
					ret.push_back(lv[i]);
				}
			}
			break;
		}
	}
	return ret;
}

int main(){
	scanf("%d",&n);
	for(int i=1; i<=n; i++){
		for(int j=1; j<=n; j++){
			scanf("%d",&a[i][j]);
		}
	}
	scanf("%d",&k);
	vector<int> ret;
	for(int i=0; i<k; i++){
		scanf("%d",&b[i]);
		ret.push_back(b[i]);
		chk[b[i]] = 1;
	}
	for(int i=1; i<=n; i++){
		if(!chk[i]) ord.push_back(i);
	}
	sort(ord.begin(), ord.end(), [&](const int &p, const int &q){
		return a[p][q];
	});
	for(int i=0; i<(1<<k); i++){
		vector<int> tmp = solve(i);
		if(!tmp.empty() && tmp[0] == -1) continue;
		if(ret.size() > tmp.size()) ret = tmp;
	}
	cout << ret.size() << endl;
	for(auto &i : ret) printf("%d ", i);
}
