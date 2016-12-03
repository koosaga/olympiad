#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef pair<int, int> pi;

vector<int> lines[100005];
vector<pi> gph[500005];
queue<int> que;
int d1[500005], d2[500005], vis[500005];

pi get_ans(int n, int m, int s, int e){
	for(int i=1; i<=2*n+m; i++){
		vis[i] = 0;
		d1[i] = 1e9;
		d2[i] = -1e9;
	}
	for(int i=0; i<n; i++){
		for(int j=0; j<lines[i].size(); j++){
			int pnt = lines[i][j];
			gph[pnt].push_back({-j, m+2*i+1});
			gph[m+2*i+1].push_back({j, pnt});
			gph[pnt].push_back({j, m+2*i+2});
			gph[m+2*i+2].push_back({-j, pnt});
		}
	}
	que.push(s);
	d1[s] = d2[s] = 0;
	vis[s] = 1;
	while(!que.empty()){
		int x = que.front();
		que.pop();
		for(auto &i : gph[x]){
			if(!vis[i.second]){
				vis[i.second] = 1;
				d1[i.second] = d1[x] + 1;
				d2[i.second] = d2[x] + i.first;
				que.push(i.second);
			}
			else if(d1[i.second] == d1[x] + 1){
				d2[i.second] = max(d2[i.second], d2[x] + i.first);
			}
		}
	}
	for(int i=1; i<=2*n+m; i++){
		gph[i].clear();
		gph[i].shrink_to_fit();
	}
	return pi(d1[e] / 2, d2[e]);
}

void my_assert(bool p){
	if(p) return;
	while(1){
		puts("aa");
	}
}

void solve(){
	int n = 0, m = 0;
	int st = -1, ed = -1;
	string sts, eds;
	map<string, int> stops;
	cin >> sts;
	while(1){
		string s;
		cin >> s;
		if(s.back() != ','){
			stops[s] = ++m;
			break;
		}
		else{
			s.pop_back();
			stops[s] = ++m;
		}
	}
	cin >> sts;
	while(1){
		string s;
		cin >> s;
		if(s.back() != ',') break;
	}
	int ppl = 0;
	while(ppl < 2){
		vector<string> spl;
		string s, t;
		cin >> s >> t;
		if(t == "route:"){
			while(1){
				cin >> t;
				if(t.back() != ','){
					spl.push_back(t);
					break;
				}
				t.pop_back();
				spl.push_back(t);
			}
			lines[n].clear();
			for(auto &i : spl){
				lines[n].push_back(stops[i]);
			}
			n++;
		}
		else if(t == "lives"){
			if(s == "Johny"){
				cin >> t >> sts;
			}
			else{
				cin >> t >> eds;
			}
			ppl++;
		}
	}
	st = stops[sts];
	ed = stops[eds];
	my_assert(st != 0 && ed != 0);
	printf("optimal travel from %s to %s: ", sts.c_str(), eds.c_str());
	pi ret = get_ans(n, m, st, ed);
	printf("%d line%s, %d minute%s\n",
		ret.first, (ret.first == 1 ? "" : "s"), 
		ret.second, (ret.second == 1 ? "" : "s"));
}

int main(){
	int t;
	scanf("%d",&t);
	while(t--) solve();
}