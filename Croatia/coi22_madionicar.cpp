#include <iostream>
#include <algorithm>
#include <set>
#include <map>
#include <vector>
#include <functional>
using namespace std;
using lint = long long;
using pi = pair<int, int>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
const int mod = 1e9 + 7;
const int MAXN = 3005;
const int dx[4] = {1, 0, -1, 0};
const int dy[4] = {0, 1, 0, -1};

int main(){	
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int n; cin >> n;
    map<pi, int> mp;
	auto query = [&](int x, int y){
		if(x % 2 == 1) x++, y--;
		if(x > y) return 1;
		if(x == y) return 1;
        if(mp.count(pi(x, y))) return mp[pi(x, y)];
		cout << "? " << x/2+1 << " " << y/2+1 << endl;
		int z; cin >> z; return mp[pi(x, y)] = z;
	};
	vector<int> dp(2*n-1);
	int ptr = 0, ans = 0;
	for(int i = 0; i < 2 * n - 1; i+=2){
		while(i - ptr - 1 >= 0 && i + ptr + 1 < 2 * n - 1 && query(i - ptr - 1, i + ptr + 1)) ptr++;
		ans = max(ans, 1 + (ptr / 2) * 2);
	}
	ptr = 0;
	for(int i = 1; i < 2 * n - 1; i+=2){
		while(i - ptr - 1 >= 0 && i + ptr + 1 < 2 * n - 1 && query(i - ptr - 1, i + ptr + 1)) ptr++;
		ans = max(ans, ((ptr + 1) / 2) * 2);
	}
	cout << "! " << ans << endl;
}

