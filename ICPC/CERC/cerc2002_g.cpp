#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <limits.h>
#include <stack>
#include <queue>
#include <map>
#include <set>
#include <algorithm>
#include <string>
#include <functional>
#include <vector>
#include <numeric>
#include <deque>
#include <utility>
#include <bitset>
#include <iostream>
using namespace std;
typedef long long lint;
typedef long double llf;
typedef pair<int, int> pi;

int n, ridx[2000005], sidx[2000005];
struct edg{
	int s, e, ts, te;
};

vector<edg> edgs;
vector<int> tlis[100005], idx[100005];
vector<int> gph[2000005];
int dp[2000005];

int f(int x){
	if(ridx[x] == n) return tlis[n][sidx[x]];
	if(~dp[x]) return dp[x];
	int ret = 1e9;
	for(auto &i : gph[x]){
		ret = min(ret, f(i));
	}
	return dp[x] = ret;
}

int gett(char *t){
	for(int i=0; i<5; i++){
		t[i] -= '0';
	}
	return (t[0] * 10 + t[1]) * 60 + (t[3] * 10 + t[4]);
}

string print(int x){
	string s;
	int h = x/60, m = x%60;
	s.push_back(h/10 + '0');
	s.push_back(h%10 + '0');
	s.push_back(':');
	s.push_back(m/10 + '0');
	s.push_back(m%10 + '0');
	return s;
}

int main(){
	memset(dp, -1, sizeof(dp));
	scanf("%d",&n);
	for(int i=1; i<=n; i++){
		int t;
		scanf("%d",&t);
		char s[10], e[10];
		int x;
		for(int j=0; j<t; j++){
			scanf("%s %s %d",s,e,&x);
			int ts = gett(s), te = gett(e);
			tlis[i].push_back(ts);
			tlis[x].push_back(te);
			edgs.push_back({i, x, ts, te});
		}
	}
	int cnt = 0;
	for(int i=1; i<=n; i++){
		sort(tlis[i].begin(), tlis[i].end());
		tlis[i].resize(unique(tlis[i].begin(), tlis[i].end()) - tlis[i].begin());
		int p = 0;
		for(auto &j : tlis[i]){
			ridx[cnt] = i;
			sidx[cnt] = p;
			idx[i].push_back(cnt);
			if(p) gph[cnt-1].push_back(cnt);
			cnt++;
			p++;
		}
	}
	for(auto &i : edgs){
		int p = lower_bound(tlis[i.s].begin(), tlis[i.s].end(), i.ts) - tlis[i.s].begin();
		int q = lower_bound(tlis[i.e].begin(), tlis[i.e].end(), i.te) - tlis[i.e].begin();
		gph[idx[i.s][p]].push_back(idx[i.e][q]);
	}
	vector<pi> ret;
	for(int i=0; i+1<tlis[1].size(); i++){
		if(f(i) != f(i+1) && f(i) < 1440){
			ret.emplace_back(tlis[1][i], f(i));
		}
	}
	if(f(tlis[1].size()-1) < 1440){
		ret.emplace_back(tlis[1].back(), f(tlis[1].size()-1));
	}
	cout << ret.size() << endl;
	for(auto &i : ret){
		cout << print(i.first) << " " << print(i.second) << endl;
	}
}