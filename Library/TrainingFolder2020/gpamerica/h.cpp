#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
typedef long long lint;
typedef pair<int, int> pi;
const int MAXN = 5005;

int fail[MAXN];

int minRot(string s, string t){
	int n = sz(s);
	int p = 0;
	for(int i=1; i<n; i++){
		while(p && s[i] != s[p]) p = fail[p];
		if(s[i] == s[p]) p++;
		fail[i + 1] = p;
	}
	t = t + t;
	p = 0;
	int idx = 0;
	int ret = 1e9;
	for(auto &i : t){
		idx++;
		while(p && i != s[p]) p = fail[p];
		if(i == s[p]) p++;
		if(p == n){
			ret = min({ret, idx - n, 2 * n - idx});
			p = fail[p];
		}
	}
	return ret;
}

string s[3];

int Do(){
	int n = sz(s[0]);
	int ret = 1e9;
	for(int i=0; i<n; i++){
		int dist = min(i, n - i);
		string t;
		for(int j=0; j<n; j++){
			if(s[0][j] == s[1][j]) continue;
			t.push_back('A' ^ 'B' ^ 'C' ^ s[0][j] ^ s[1][j]);
		}
		if(sz(t) == n) ret = min(ret, dist +minRot(s[2], t));
		rotate(s[1].begin(), s[1].begin() + 1, s[1].end());
	}
	return ret;
}

int main(){
	cin >> s[0] >> s[1] >> s[2];
	int ret = 1e9;
	for(int i=0; i<3; i++){
		swap(s[0], s[i]);
		ret = min(ret, Do());
		swap(s[0], s[i]);
	}
	if(ret > 1e8) ret = -1;
	cout << ret << endl;
}
