#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef long double llf;
typedef pair<int, int> pi;
 
vector<int> gph[100005];
int n, m;
int cnt;

int trial(int x, int par, int l){
	vector<int> v;
	for(auto &i : gph[x]){
		if(i == par) continue;
		v.push_back(1 + trial(i, x, l));
	}
	sort(v.begin(), v.end());
	while(!v.empty() && v.back() > l){
		v.pop_back();
		cnt++;
	}
	while(v.size() >= 2 && v.back() + v[v.size()-2] > l){
		v.pop_back();
		cnt++;
	}
	return v.empty() ? 0 : v.back();
}

int main(){
	int l;
	cin >> n >> l;
	l *= 2;
	for(int i=0; i<n-1; i++){
		int s, e, x;
		scanf("%d %d %d",&s,&e,&x);
		gph[s].push_back(e);
		gph[e].push_back(s);
	}
	trial(1, -1, 2 * l);
	cout << cnt + 1 << endl;
}

