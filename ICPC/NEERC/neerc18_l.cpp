#include <bits/stdc++.h>
const int MAXN = 100005;
using namespace std;

int n, k, a[MAXN], b[MAXN];
vector<int> v[MAXN];

int main(){
	cin >> n >> k;
	for(int i=0; i<n; i++) scanf("%d",&a[i]);
	for(int i=0; i<n; i++) scanf("%d",&b[i]);
	for(int i=0; i<n; i++) v[a[i]].push_back(b[i]);
	vector<int> w;
	int cnt = 0;
	for(int i=1; i<=k; i++){
		sort(v[i].begin(), v[i].end());
		if(v[i].empty()){
			cnt++;
			continue;
		}
		for(int j=0; j<v[i].size()-1; j++){
			w.push_back(v[i][j]);
		}
	}
	sort(w.begin(), w.end());
	cout << accumulate(w.begin(), w.begin() + cnt, 0ll) << endl;
}
