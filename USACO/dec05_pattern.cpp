#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef long double llf;
typedef pair<lint, lint> pi;

int n, m;
int a[100005], b[25005];
int l[25005], r[25005], fail[25005];

bool match(int p, int *a){
	if(r[p] < 1e8 && *(a - r[p]) <= *a) return 0;
	if(l[p] < 1e8 && *(a - l[p]) > *a) return 0;
	return 1;
}

bool match2(int p, int *a){
	if(r[p] < 1e8 && *(a - r[p]) < *a) return 0;
	if(l[p] < 1e8 && *(a - l[p]) >= *a) return 0;
	return 1;
}

int chk[100005];

int main(){
	scanf("%d %d %*d",&n,&m);
	for(int i=0; i<n; i++) scanf("%d",&a[i]);
	for(int i=0; i<m; i++) scanf("%d",&b[i]);
	map<int, int> mp;
	for(int i=0; i<m; i++){
		auto it = mp.upper_bound(b[i]);
		if(it != mp.end()) r[i] = i - it->second;
		else r[i] = 1e9;
		if(it != mp.begin()) l[i] = i - (--it)->second;
		else l[i] = 1e9;
		mp[b[i]] = i;
	}
	int p = 0;
	for(int i=1; i<m; i++){
		while(p && !match(p, b+i)) p = fail[p];
		if(match(p, b+i)) p++;
		fail[i+1] = p;
	}
	p = 0;
	for(int i=0; i<n; i++){
		while(p && !match(p, a+i)) p = fail[p];
		if(match(p, a+i)) p++;
		if(p == m){
			chk[i+2-m] = 1;
			p = fail[p];
		}
	}
	p = 0;
	mp.clear();
	for(int i=0; i<m; i++){
		auto it = mp.lower_bound(b[i]);
		if(it != mp.end()) r[i] = i - it->second;
		else r[i] = 1e9;
		if(it != mp.begin()) l[i] = i - (--it)->second;
		else l[i] = 1e9;
		mp[b[i]] = i;
	}
	p = 0;
	for(int i=1; i<m; i++){
		while(p && !match2(p, b+i)) p = fail[p];
		if(match2(p, b+i)) p++;
		fail[i+1] = p;
	}
	p = 0;
	for(int i=0; i<n; i++){
		while(p && !match2(p, a+i)) p = fail[p];
		if(match2(p, a+i)) p++;
		if(p != m && i+2>=m) chk[i+2-m] = 0;
		if(p == m){
			p = fail[p];
		}
	}
	cout << count(chk, chk + 100005, 1) << endl;
	for(int i=0; i<100005; i++) if(chk[i]) printf("%d\n", i);
}
