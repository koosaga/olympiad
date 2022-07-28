#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
typedef long long lint;
typedef pair<lint, lint> pi;
#include "onetwothree.h"

int startLeq[3][15005];
int endLeq[3][15005];

void maximize (std::vector<int> A) {
	vector<int> pos[3];
	int n = sz(A);
	vector<int> low(n + 1);
	for(int i = 0; i < n; i++){
		A[i]--;
		pos[A[i]].push_back(i);
		low[i + 1] = low[i];
		if(A[i] == 1) low[i + 1]++;
	}
	auto ok = [&](int l, int r, int track){
		if(l + r > sz(pos[0]) || l + r > sz(pos[2]) || l + r > sz(pos[1])) return false;
		if(track){
			vector<pi> v;
			for(int i = 0; i < l; i++){
				v.emplace_back(pos[0][i], pos[2][sz(pos[2]) - l + i]);
			}
			for(int i = 0; i < r; i++){
				v.emplace_back(pos[2][i], pos[0][sz(pos[0]) - r + i]);
			}
			sort(all(v));
			reverse(all(v));
			set<int> s;
			int p = sz(pos[1]);
			for(auto &[x, y] : v){
				while(p > 0 && pos[1][p - 1] >= x){
					s.insert(pos[1][--p]);
				}
				auto it = s.upper_bound(y);
				if(it != s.begin()){
					it--;
					if(track) answer(x, *it, y);
					s.erase(it);
				}
				else return false;
			}
			return true;
		}
		else{
			memset(startLeq, 0, sizeof(startLeq));
			memset(endLeq, 0, sizeof(endLeq));
			for(int i = 0; i < l; i++){
				int x = pos[0][i];
				int y = pos[2][sz(pos[2]) - l + i];
				x = low[x + 1] + 1;
				y = low[y + 1];
				if(x > y) return false;
				startLeq[0][x]++;
				startLeq[2][x]++;
				endLeq[0][y]++;
				endLeq[2][y]++;
			}
			for(int i = 0; i < r; i++){
				int x = pos[2][i];
				int y = pos[0][sz(pos[0]) - r + i];
				x = low[x + 1] + 1;
				y = low[y + 1];
				if(x > y) return false;
				startLeq[1][x]++;
				startLeq[2][x]++;
				endLeq[1][y]++;
				endLeq[2][y]++;
			}
			for(int i = 0; i < 3; i++){
				int curmin = 1e9;
				for(int j = 1; j <= sz(pos[1]); j++){
					endLeq[i][j] += endLeq[i][j - 1];
					startLeq[i][j] += startLeq[i][j - 1];
					curmin = min(curmin, startLeq[i][j - 1] - (j - 1));
					if(curmin < endLeq[i][j] - j) return false;
				}
			}
			return true;
		}
	};
	int r = 0;
	while(ok(0, r + 1, 0)) r++;
	pi ans(0, 0);
	for(int i = 0; i <= n / 3; i++){
		ans = max(ans, pi(i + r, i));
		while(r >= 0 && ok(i + 1, r, 0) == 0) r--;
		if(r < 0) break;
	}
	ok(ans.second, ans.first - ans.second, 1);
}
