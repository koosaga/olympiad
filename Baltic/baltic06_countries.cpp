#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = pair<int, int>;
#define sz(v) ((int)((v).size()))
const int MAXN = 1005;

int n, x[MAXN], y[MAXN], s[MAXN];
string ans[MAXN];
int par[MAXN];

bool cmp(pi a, pi b){
	return 1ll * a.first * b.second < 1ll * b.first * a.second;
}

int main(){
	cin >> n;
	for(int i=0; i<n; i++) cin >> x[i] >> y[i] >> s[i];
	for(int i=0; i<n; i++){
		pi rt(s[i], 1);
		int cnt = 0;
		int pos = -1;
		for(int j=0; j<n; j++){
			if(i == j) continue;
			int dist = (x[i] - x[j]) * (x[i] - x[j]) + (y[i] - y[j]) * (y[i] - y[j]);
			pi rat = pi(s[j], dist);
			if(cmp(rt, rat)){
				rt = rat;
				cnt = 0;
			}
			if(!cmp(rt, rat) && !cmp(rat, rt)){
				cnt++;
				pos = j;
			}
		}
		if(!cmp(pi(s[i], 1), rt)){
			ans[i] = "K";
		}
		else{
			if(cnt == 1){
				ans[i] = "?";
				par[i] = pos;
			}
			else{
				ans[i] = "D";
			}
		}
	}
	for(int i=0; i<n; i++){
		if(ans[i] != "?") cout << ans[i] << endl;
		else{
			int pos = i;
			while(ans[pos] == "?") pos = par[pos];
			cout << pos + 1 << endl;
		}
	}
}
