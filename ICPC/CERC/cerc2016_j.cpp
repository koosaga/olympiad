#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef pair<int, int> pi;
const lint inf = 1e18;

int n, d, a[300005];
lint c1[300005], c2[300005], c3[300005], c4[300005];
vector<int> seq[300005];

lint solve(int c){
	int stk = 0;
	lint ans = 0;
	if(c3[c] < c4[c]){
		stack<int> stk;
		for(auto &i : seq[c]){
			if(i == 1){
				stk.push(1);
			}
			else{
				if(!stk.empty() && stk.top() == 1){
					stk.pop();
					ans += c3[c];
				}
				else{
					stk.push(2);
				}
			}
		}
		int cc1 = 0, cc2 = 0;
		while(!stk.empty()){
			if(stk.top() == 1) cc1++;
			else cc2++;
			stk.pop();
		}
		ans += c4[c] * min(cc1, cc2);
		ans += c2[c] * (cc2 - min(cc1, cc2));
		ans += c1[c] * (cc1 - min(cc1, cc2));
	}
	else{
		stack<int> stk;
		for(auto &i : seq[c]){
			if(i == 2) stk.push(2);
			else{
				if(!stk.empty() && stk.top() == 2){
					stk.pop();
					ans += c4[c];
				}
				else{
					stk.push(1);
				}
			}
		}
		int cc1 = 0, cc2 = 0;
		while(!stk.empty()){
			if(stk.top() == 1) cc1++;
			else cc2++;
			stk.pop();
		}
		ans += c3[c] * min(cc1, cc2);
		ans += c2[c] * (cc2 - min(cc1, cc2));
		ans += c1[c] * (cc1 - min(cc1, cc2));
	}
	return ans;
}

vector<pi> v;
int main(){
	scanf("%d %d",&n,&d);
	for(int i=1; i<=d; i++) scanf("%d",&a[i]);
	for(int i=2; i<=d; i++){
		int s = a[i-1], e = a[i];
		if(s > e) swap(s, e);
		v.push_back(pi(s, e));
	}
	sort(v.begin(), v.end());
	v.resize(unique(v.begin(), v.end()) - v.begin());
	for(int i=2; i<=d; i++){
		int s = a[i-1], e = a[i];
		if(s > e) swap(s, e);
		auto l = lower_bound(v.begin(), v.end(), pi(s, e));
		if(*l == pi(a[i-1], a[i])) seq[l-v.begin()].push_back(1);
		else seq[l-v.begin()].push_back(2);
	}
	memset(c1, 0x3f, sizeof(c1));
	memset(c2, 0x3f, sizeof(c2));
	memset(c3, 0x3f, sizeof(c3));
	memset(c4, 0x3f, sizeof(c4));
	int q;
	scanf("%d",&q);
	while(q--){
		int s, d;
		char t[5];
		lint p;
		scanf("%d %d %s %lld",&s,&d,t,&p);
		pi w = pi(s, d);
		if(w.first > w.second) swap(w.first, w.second);
		auto l = lower_bound(v.begin(), v.end(), w);
		if(l == v.end() || *l != w) continue;
		int i = l - v.begin();
		if(w == pi(s, d)) c1[i] = min(c1[i], p);
		else c2[i] = min(c2[i], p);
		if(*t == 'R'){
			if(w == pi(s, d)) c3[i] = min(c3[i], p);
			else c4[i] = min(c4[i], p);
		}
	}
	lint ans = 0;
	for(int i=0; i<v.size(); i++){
		for(int j=0; j<3; j++){
			c3[i] = min(c3[i], c1[i] + c2[i]);
			c4[i] = min(c4[i], c1[i] + c2[i]);
			c1[i] = min(c1[i], c3[i]);
			c2[i] = min(c2[i], c4[i]);
		}

		ans += solve(i);
	}
	cout << ans;
}
