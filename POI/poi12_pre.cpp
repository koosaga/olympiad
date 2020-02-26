#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;

vector<int> get_fail(string str){
	int n = str.size();
	int p = 0;
	vector<int> fail(n + 1);
	for(int i=1; i<n; i++){
		while(p && str[p] != str[i]) p = fail[p];
		if(str[p] == str[i]) p++;
		fail[i + 1] = p;
	}
	return fail;
}

int n;
string s;

int solve(int l, int r){
	auto fail = get_fail(s.substr(l, r - l));
	for(int i=r-l; ; i=fail[i]) if(i + i <= r - l) return i; 
}

int main(){
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> s;
	vector<int> fail = get_fail(s);
	vector<int> v;
	for(int i=fail[n]; i; i=fail[i]){
		if(i <= n / 2) v.push_back(i);
	}
	int ret = 0;
	for(int i=0; i<sz(v); i++){
		if(0 < i && i < sz(v)-1 && v[i-1] + v[i+1] == 2 * v[i]) continue;
		ret = max(ret, v[i] + solve(v[i], n - v[i]));
	}
	cout << ret << endl;
}

