#include <bits/stdc++.h>
using namespace std;
const int MAXN = 3005;
using lint = long long;
using pi = pair<int, int>;
 
struct dap{
	int x, y, z;
	bool operator<(const dap &d)const{
		return z < d.z;
	}
};
 
int n, m;
string s, t;
int lcp[MAXN];
int sx[MAXN];
int sy[MAXN];

vector<int> getfail(string s){
	vector<int> fail(s.size() + 1);
	int p = 0;
	for(int i=1; i<s.size(); i++){
		while(p && s[p] != s[i]) p = fail[p];
		if(s[p] == s[i]) p++;
		fail[i + 1] = p;
	}
	return fail;
}

dap solve(){
	memset(lcp, 0, sizeof(lcp));
	memset(sx, 0x3f, sizeof(sx));
	memset(sy, 0x3f, sizeof(sy));
	dap ret = {-1, -1, -1};

	for(int i=n; i>=0; i--){
		if(i < n){
			for(int j=0; j<m; j++){
				if(s[i] == t[j]) lcp[j] = lcp[j + 1] + 1;
				else lcp[j]  = 0;
			}
		}

		string str;
		for(int j=i-1; j>=0; j--) str.push_back(s[j]);
		str.push_back('$');
		for(int j=m-1; j>=0; j--) str.push_back(t[j]);
		vector<int> f = getfail(str);

		memset(sy, 0x3f, sizeof(sy));
		for(int j=0; j<=m; j++){
			sy[lcp[j] + j] = min(sy[lcp[j] + j], j);
			sx[j] = min(sx[j], i - f.back());
			f.pop_back();
		}
		for(int j=m; j>=0; j--){
			sy[j] = min(sy[j], sy[j + 1]);
			int minsx = sx[j];
			int minsy = sy[j];
			ret = max(ret, (dap){minsx, minsy, i + j - minsx - minsy});
		}
	}
	return ret;
}
 
int main(){
	cin >> s >> t;
	n = s.size();
	m = t.size();
	auto ret = solve();
	reverse(t.begin(), t.end());
	auto y = solve();
	y.y = m - y.y - y.z;
	ret = max(ret, y);
	cout << ret.z << endl;
	cout << ret.x << " " << ret.y << endl;
}
