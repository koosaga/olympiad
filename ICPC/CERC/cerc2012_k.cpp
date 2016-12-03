#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef long double llf;
typedef pair<int, int> pi;
typedef vector<int> vi;
int k, n, m;

int parse(string &s){
	int ret = 0;
	for(int i=2; i<s.size(); i++){
		ret = ret * 10 + (s[i] - '0');
	}
	return ret;
}

vector<vi> t1, t2;
vector<vi> path1, path2;
bool bad;

vi dfs(vector<vi> &tree, vector<vi> &path, int x, int p){
	if(x <= k){
		vi v = {x};
		return v;
	}
	vector<vi> paths;
	for(auto &i : tree[x]){
		if(i == p) continue;
		auto tmp = dfs(tree, path, i, x);
		if(tmp.empty()) continue;
		paths.push_back(tmp);
	}
	if(paths.size() == 1){
		auto v = paths[0];
		v.push_back(x);
		return v;
	}
	if(paths.size() == 2){
		reverse(paths[1].begin(), paths[1].end());
		auto ret = paths[0];
		ret.push_back(x);
		for(auto &i : paths[1]){
			ret.push_back(i);
		}
		path.push_back(ret);
		return vi();
	}
	bad = 1;
	return vi();
}

void print(int x){
	if(x < 0){
		if(abs(x) > k){
			printf(" BP%d",abs(x) - k);
		}
		else{
			printf(" BS%d",abs(x));
		}
	}
	else{
		if(x > k){
			printf(" AP%d",x - k);
		}
		else{
			printf(" AS%d",x);
		}
	}
}

int nxta[1005], nxtb[1005];
bool vis1[1005], vis2[1005];

void solve(){
	vi ret;
	int p = 1;
	while(1){
		int pos = -1;
		for(int j=0; j<path1.size(); j++){
			if(vis1[j]) continue;
			if(path1[j].back() == p){
				reverse(path1[j].begin(), path1[j].end());
			}
			if(path1[j].front() == p){
				pos = j;
				break;
			}
		}
		if(pos == -1) break;
		for(auto &i : path1[pos]){
			ret.push_back(i);
		}
		vis1[pos] = 1;
		p = nxta[path1[pos].back()];
		pos = -1;
		for(int j=0; j<path2.size(); j++){
			if(vis2[j]) continue;
			if(path2[j].back() == p){
				reverse(path2[j].begin(), path2[j].end());
			}
			if(path2[j].front() == p){
				pos = j;
				break;
			}
		}
		assert(pos != -1);
		for(auto &i : path2[pos]){
			ret.push_back(-i);
		}
		vis2[pos] = 1;
		p = nxtb[path2[pos].back()];
	}
	if(ret.size() != n + m + 2 * k){
		puts("NO");
		return;
	}
	printf("YES");
	for(auto &i : ret){
		print(i);
	}
	puts("");
}

int main(){
	int t;
	cin >> t;
	while(t--){
		memset(vis1, 0, sizeof(vis1));
		memset(vis2, 0, sizeof(vis2));
		t1.clear();
		t2.clear();
		path1.clear();
		path2.clear();
		bad = 0;
		cin >> k >> n >> m;
		t1.resize(n+k+1);
		t2.resize(m+k+1);
		for(int i=0; i<n+k-1; i++){
			string s1, s2;
			cin >> s1 >> s2;
			int p = parse(s1), q = parse(s2);
			if(s1[1] == 'P') p += k;
			if(s2[1] == 'P') q += k;
			t1[p].push_back(q);
			t1[q].push_back(p);
		}
		for(int i=0; i<m+k-1; i++){
			string s1, s2;
			cin >> s1 >> s2;
			int p = parse(s1), q = parse(s2);
			if(s1[1] == 'P') p += k;
			if(s2[1] == 'P') q += k;
			t2[p].push_back(q);
			t2[q].push_back(p);
		}
		for(int i=0; i<k; i++){
			string s1, s2;
			cin >> s1 >> s2;
			if(s1[0] == 'B') swap(s1, s2);
			int p = parse(s1), q = parse(s2);
			nxta[p] = q, nxtb[q] = p;
		}
		if(dfs(t1, path1, k+1, -1).size()) bad = 1;
		if(dfs(t2, path2, k+1, -1).size()) bad = 1;
		if(bad){
			puts("NO");
			continue;
		}
		solve();
	}
}
