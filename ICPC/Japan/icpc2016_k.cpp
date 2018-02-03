#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef pair<lint, int> pi;
typedef long long lint;
const int MAXN = 42;

lint a[MAXN];
int b[MAXN];
vector<pi> v1, v2;

void bktk(int s, int e, int c, lint sum, vector<pi> &v){
	if(s == e){
		v.push_back(pi(sum, c));
		return;
	}
	bktk(s+1, e, c + b[s], sum + a[s], v);
	bktk(s+1, e, c, sum, v);
}

int main(){
	int n;
	cin >> n;
	for(int i=0; i<n; i++){
		string s;
		cin >> s;
		lint cf = (1ll << MAXN);
		bool flg = 0;
		for(int j=0; j<s.size(); j++){
			if(j && s[j-1] != s[j]) flg = 1;
			if(flg) cf >>= 1;
			a[i] += (s[j] == 'B' ? cf : -cf);
		}
		b[i] = s.size();
	}
	bktk(0, n/2, 0, 0, v1);
	bktk(n/2, n, 0, 0, v2);
	sort(v1.begin(), v1.end());
	sort(v2.rbegin(), v2.rend());
	int ptr = 0, ans = 0;
	for(auto &i : v1){
		while(ptr < v2.size() && v2[ptr].first + i.first > 0) ptr++;
		if(ptr < v2.size() && i.first + v2[ptr].first == 0){
			ans = max(ans, v2[ptr].second + i.second);
		}
	}
	cout << ans << endl;
}
