#include<bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
using lint = long long;
using pi = pair<int, int>;
const int MAXN = 200005;

int n, a[MAXN], q[MAXN];

pi cross(int x, int y){
	pi ans(a[x] - a[y], x - y);
	if(ans.second < 0) ans.first *= -1, ans.second *= -1;
	if(ans.first < 0) return pi(1, 0);
	return ans;
}

bool cmp(pi a, pi b){
	return 1ll * a.first * b.second < 1ll * b.first * a.second;
}

vector<int> idx, rev;
pi ans[MAXN];
vector<int> pos[MAXN];

void solve1(){
	vector<int> stk;
	for(int i=0; i<n; i++){
		while(sz(stk) && stk.back() > idx[i]) stk.pop_back();
		while(sz(stk) >= 2 && cmp(cross(stk[sz(stk) - 2], stk.back()), cross(stk.back(), idx[i]))){
			stk.pop_back();
		}
		stk.push_back(idx[i]);
		for(auto &j : pos[i]){
			auto l = lower_bound(all(stk), q[j]) - stk.begin();
			if(l > 0){
				int s = 0, e = l - 1;
				while(s != e){
					int m = (s+e)/2;
					if(cmp(cross(stk[m], q[j]), cross(stk[m + 1], q[j]))) e = m;
					else s = m + 1;
				}
				ans[j] = cross(stk[s], q[j]);
			}
		}
	}
}

void solve2(){
	vector<int> stk;
	for(int i=n-1; i>=0; i--){
		while(sz(stk) && stk.back() < idx[i]) stk.pop_back();
		while(sz(stk) >= 2 && cmp(cross(stk[sz(stk) - 2], stk.back()), cross(stk.back(), idx[i]))){
			stk.pop_back();
		}
		stk.push_back(idx[i]);
		for(auto &j : pos[i]){
			auto l = lower_bound(all(stk), q[j], greater<int>()) - stk.begin();
			if(l > 0){
				int s = 0, e = l - 1;
				while(s != e){
					int m = (s+e)/2;
					if(cmp(cross(stk[m], q[j]), cross(stk[m + 1], q[j]))) e = m;
					else s = m + 1;
				}
				ans[j] = cross(stk[s], q[j]);
			}
		}
	}
}

int gcd(int x, int y){
	return y ? gcd(y, x%y) : x;
}

int main(){
	freopen("falling.in", "r", stdin);
	freopen("falling.out", "w", stdout);
	scanf("%d",&n);
	for(int i=1; i<=n; i++) scanf("%d",&a[i]);
	for(int i=1; i<=n; i++) scanf("%d",&q[i]);
	idx.resize(n); 
	rev.resize(n + 1);
	iota(all(idx), 1);
	sort(all(idx), [&](const int &p, const int &q){
		return a[p] < a[q];
	});
	for(int i=0; i<n; i++) rev[idx[i]] = i;
	fill(ans + 1, ans + n + 1, pi(1, 0));
	for(int i=1; i<=n; i++){
		if(rev[i] < rev[q[i]]){
			pos[rev[i]].push_back(i);
		}
	}
	solve1();
	for(int i=0; i<=n; i++) pos[i].clear();
	for(int i=1; i<=n; i++){
		if(rev[i] > rev[q[i]]){
			pos[rev[i]].push_back(i);
		}
	}
	solve2();
	for(int i=1; i<=n; i++){
		pi p = ans[i];
		if(p.second != 0){
			int g = gcd(p.first, p.second);
			printf("%d/%d\n", p.first / g, p.second / g);
		}
		else puts("-1");
	}
}

