#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
typedef long long lint;
typedef pair<int, int> pi;

int main(){
	int n, m; cin >> n >> m;
	vector<pi> a(m); // (top, bottom)
	queue<int> emp;
	vector<vector<int>> downs(n + 1);
	queue<int> downQueue;
	auto downsPb = [&](int p, int q){
		downs[p].push_back(q);
		if(sz(downs[p]) == 2) downQueue.push(p);
	};
	for(int i = 0; i < m; i++){
		cin >> a[i].second >> a[i].first;
		if(a[i] == pi(0, 0)) emp.push(i);
		if(a[i].first == 0 && a[i].second != 0){
			downsPb(a[i].second, i);
		}
	}
	vector<int> indeg(n + 1), outdeg(n + 1);
	vector<vector<pi>> gph(n + 1), rev(n + 1);
	int ecnt = 0;
	for(int i = 0; i < m; i++){
		if(a[i].first == a[i].second) continue;
		if(a[i].first && a[i].second){
			ecnt++;
			indeg[a[i].second]++;
			outdeg[a[i].first]++;
			gph[a[i].first].emplace_back(i, a[i].second);
			rev[a[i].second].emplace_back(i, a[i].first);
		}
	}
	vector<pi> ans;
	queue<int> que[3][3];
	auto upd = [&](int v){
		que[indeg[v]][outdeg[v]].push(v);
	};
	for(int i = 1; i <= n; i++) upd(i);
	while(true){
		while(sz(downQueue)){
			int i = downQueue.front();
			downQueue.pop();
			// Case 1. garbage collect
			ans.emplace_back(downs[i][0], downs[i][1]);
			a[downs[i][0]].second = 0;
			a[downs[i][1]].first = i;
			emp.push(downs[i][0]);
			downs[i].clear();
		}
		if(ecnt == 0) break;
		auto removeEdge = [&](int e){
			ecnt--;
			gph[a[e].first].erase(find(all(gph[a[e].first]), pi(e, a[e].second)));
			rev[a[e].second].erase(find(all(rev[a[e].second]), pi(e, a[e].first)));
			outdeg[a[e].first]--;
			indeg[a[e].second]--;
			upd(a[e].first);
			upd(a[e].second);
		};
		bool oped = 0;
		while(sz(que[0][1])){
			int i = que[0][1].front();
			que[0][1].pop();
			if(indeg[i] != 0 || outdeg[i] != 1) continue;
			int st = downs[i][0];
			int ed = gph[i][0].first;
			removeEdge(gph[i][0].first);
			ans.emplace_back(ed, st);
			a[st].first = a[ed].first;
			a[ed].first = 0;
			downs[i].clear();
			downsPb(a[ed].second, ed);
			oped = 1;
			break;
		}
		if(oped) continue;
		auto CaskOpen = [&](int pos){
			int emptySpace = emp.front();
			emp.pop();
			vector<int> toRem;
			for(int j = 0; j < sz(gph[pos]); j++){
				ans.emplace_back(gph[pos][j].first, emptySpace);
				if(a[emptySpace].second) a[emptySpace].first = pos;
				else a[emptySpace].second = pos;
				int foo = gph[pos][j].first;
				downsPb(a[foo].second, foo);
				toRem.push_back(foo);
			}
			if(a[emptySpace].first == 0) downsPb(a[emptySpace].second, emptySpace);
			for(auto &e : toRem) removeEdge(e);
			for(auto &e : toRem) a[e].first = 0;
		};
		while(sz(que[1][0])){
			int i = que[1][0].front();
			que[1][0].pop();
			if(indeg[i] != 1 || outdeg[i] != 0) continue;
			// case 3. cask open
			if(!sz(emp)){
				cout << "-1\n";
				return 0;
			}
			int pos = i;
			while(indeg[pos] == 1) pos = rev[pos][0].second;
			CaskOpen(pos);
			oped = 1;
			break;
		}
		if(oped) continue;
		while(sz(que[0][2])){
			int i = que[0][2].front();
			que[0][2].pop();
			if(indeg[i] != 0 || outdeg[i] != 2) continue;
			// case 4. force cask open
			if(!sz(emp)){
				cout << "-1\n";
				return 0;
			}
			CaskOpen(i);
			oped = 1;
			break;
		}
		if(oped) continue;
		while(sz(que[1][1])){
			int i = que[1][1].front();
			que[1][1].pop();
			if(indeg[i] != 1|| outdeg[i] != 1) continue;
			// case 5. open cycle
			if(!sz(emp)){
				cout << "-1\n";
				return 0;
			}
			CaskOpen(i);
			oped = 1;
			break;
		}
		assert(oped);
	}
	cout << sz(ans) << "\n";
	for(auto &[x, y] : ans){
		cout << x+1 << " " << y+1 << "\n";
	}
}
