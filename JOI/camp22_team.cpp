#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
typedef long long lint;
typedef pair<lint, lint> pi;
const int MAXN = 150005;
const int mod = 1e9 + 7;

struct point{
	int a[3];
};

int mark[MAXN];

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n;
	cin >> n;
	vector<point> a(n);
	vector<int> v[3];
	for(int i = 0; i < n; i++){
		for(int j = 0; j < 3; j++){
			cin >> a[i].a[j];
			v[j].push_back(a[i].a[j]);
		}
	}
	vector<set<int>> idx[3];
	for(int i = 0; i < 3; i++){
		sort(all(v[i]));
		v[i].resize(unique(all(v[i])) - v[i].begin());
		idx[i].resize(sz(v[i]));
	}
	for(int i = 0; i < n; i++){
		for(int j = 0; j < 3; j++){
			int p = lower_bound(all(v[j]), a[i].a[j]) - v[j].begin();
			a[i].a[j] = p;
			idx[j][p].insert(i);
			if(p == sz(idx[j]) - 1) mark[i] |= (1 << j);
		}
	}
	for(int _ = 0; _ < n; _++){
		int toRemove = -1;
		int sum = 0;
		for(int i = 0; i < 3; i++){
			auto j = *idx[i].back().begin();
			if(mark[j] == (1 << i)){
				sum += v[i][a[j].a[i]];
			}
			else{
				toRemove = j;
				break;
			}
		}
		if(~toRemove){
			for(int j = 0; j < 3; j++){
				int pos = a[toRemove].a[j];
				idx[j][pos].erase(toRemove);
				if(sz(idx[j].back()) > 0) continue;
				while(sz(idx[j]) && sz(idx[j].back()) == 0){
					idx[j].pop_back();
				}
				if(sz(idx[j])){
					for(auto &p : idx[j].back()) mark[p] |= (1<<j);
				}
			}
		}
		else{
			cout << sum << "\n";
			return 0;
		}
	}
	cout << "-1\n";
}
