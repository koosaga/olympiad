#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef pair<lint, lint> pi;
const int mod = 1e9 + 7;

int n;
int a[100005], b[100005];
vector<pi> v;

int main(){
	freopen("nocross.in", "r", stdin);
	freopen("nocross.out", "w", stdout);
	scanf("%d",&n);
	for(int i=0; i<n; i++){
		int x;
		scanf("%d",&x);
		a[x] = i;
	}
	for(int i=0; i<n; i++){
		int x;
		scanf("%d",&x);
		b[x] = i;
	}
	for(int i=1; i<=n; i++){
		for(int j=i-4; j<=i+4; j++){
			if(j > 0 && j <= n) v.push_back(pi(a[i], b[j]));
		}
	}
	sort(v.begin(), v.end(), [&](const pi &a, const pi &b){
		if(a.first != b.first) return a < b;
		return a.second > b.second;
	});
	vector<int> w;
	for(auto &i : v){
		auto it = lower_bound(w.begin(), w.end(), i.second);
		if(it == w.end()) w.push_back(i.second);
		else *it = i.second;
	}
	cout << w.size();
}
