#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
using lint = long long;
using pi = pair<lint, lint>;
const int mod = 1e9 + 7;
const int MAXN = 10005;

vector<vector<int>> fucks = {
	{1, 4, 7},
	{2, 5, 8, 11},
	{3, 6, 9},
	{1, 2, 3},
	{4, 5, 6},
	{7, 8, 9},
	{1, 5, 9},
	{3, 5, 7}
};

int main(){
	int tc; cin >> tc;
	while(tc--){
		string s; cin >> s;
		s.resize(unique(all(s)) - s.begin());
		int chk[12][12] = {};
		set<vector<int>> voov;
		int hasTwoFive = 0;
		int hasEightZero = 0;
		int hasIt = 0;
		for(int i=0; i<sz(s)-1; i++){
			int x = s[i] - '0';
			int y = s[i+1] - '0';
			if(x == 0) x = 11;
			if(y == 0) y = 11;
			if(x > y) swap(x, y);
			if(x == 2 && y == 5) hasTwoFive++;
			if(x == 8 && y == 11) hasEightZero++;
			bool found = 0;
			for(auto &i : fucks){
				auto it1 = find(all(i), x);
				auto it2 = find(all(i), y);
				if(it1 != i.end() && it2 != i.end()){
					if(sz(i) == 4) hasIt++;
					found = 1;
					voov.insert(i);
				}
			}
			if(!found){
				vector<int> v = {x, y};
				voov.insert(v);
			}
		}
		int ret = sz(voov);
		if(hasTwoFive + hasEightZero == hasIt && hasTwoFive && hasEightZero) ret++;
		if(ret <= 3) puts("EXCELLENT");
		if(ret == 4) puts("GOOD");
		if(ret >= 5) puts("BAD");
	}
}
