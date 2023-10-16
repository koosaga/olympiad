#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
using namespace std;
const int MAXN = 250005;
using lint = long long;

int n, a[MAXN], b[MAXN];

lint f(int x){
	vector<int> l, r;
	for(int i=0; i<n; i++){
		if(a[i] <= x) l.push_back(i);
		if(b[i] > n-x) r.push_back(i);
	}
	lint ret = 0;
	for(int i=0; i<sz(l); i++) ret += abs(l[i] - r[i]);
	return ret;
}

int main(){
	scanf("%d",&n);
	for(int i=0; i<n; i++) scanf("%d",&a[i]);
	for(int i=0; i<n; i++) scanf("%d",&b[i]);
	cout << min(f(n/2), f((n+1)/2)) << endl;
}
