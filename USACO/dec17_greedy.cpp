#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = pair<int, int>;
const int MAXN = 100005;
const int mod = 1e9 + 7;

int n, a[MAXN];

bool trial(int m){
	vector<int> v;
	for(int i=0; i<m-1; i++){
		v.push_back(max(0, a[i] - (n - m)));
	}
	sort(v.begin(), v.end());
	for(int i=0; i<v.size(); i++){
		if(v[i] > i) return 0;
	}
	return 1;
}

int main(){
	cin >> n;
	for(int i=0; i<n; i++){
		scanf("%d",&a[i]);
	}
	int s = 0, e = n;
	while(s != e){
		int m = (s+e+1)/2;
		if(trial(m)) s = m;
		else e = m-1;
	}
	cout << n - s << endl;
}
