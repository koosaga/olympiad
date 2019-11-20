#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
typedef long long lint;
typedef pair<int, int> pi;

int n;
vector<pi> v;
int badboy[55][55];
pi wtf[1005][55];

int main(){
	scanf("%d",&n);
	for(int i=1; i<n; i++){
		int j = 0;
		while(true){
			int x; scanf("%d",&x);
			if(!x) break;
			wtf[x][i] = pi(i, ++j);
			v.emplace_back(x, i);
		}
	}
	sort(all(v));
	vector<int> skip(sz(v));
	while(true){
		memset(badboy, 0, sizeof(badboy));
		vector<int> idx(n);
		iota(all(idx), 0);
		bool iter = false;
		for(int i=0; i<sz(v); i++){
			if(skip[i]) continue;
			int y = v[i].second;
			int l = idx[y - 1], r = idx[y];
			swap(idx[y - 1], idx[y]);
			if(badboy[r][l]){
				skip[i] = skip[badboy[r][l] - 1] = 1;
				iter = true;
				break;
			}
			badboy[l][r] = i + 1;
		}
		if(!iter) break;
	}
	cout << count(all(skip), 0) << endl; 
	for(int i=0; i<sz(v); i++){
		if(!skip[i]){
			int x = v[i].first;
			int y = v[i].second;
			printf("%d %d\n", wtf[x][y].first, wtf[x][y].second); 
		}
	}
}
