#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef long double llf;
typedef pair<int, int> pi;

vector<int> lis[55];
vector<pi> v;
int n;

pi mx[1000005][2], mn[1000005][2];

void build(int i){
	int p = 0;
	for(int j=0; j<lis[i].size(); j++){
		if(j){
			mx[j][0] = mx[j-1][0];
			mx[j][1] = mx[j-1][1];
		}
		else{
			mx[j][0] = pi(0, 0);
			mx[j][1] = pi(0, 0);
		}
		while(p < v.size() && v[p].second <= lis[i][j]){
			if(v[p].first != i){
				if(mx[j][0].first == v[p].first){
					mx[j][0] = v[p];
				}
				else{
					mx[j][1] = mx[j][0];
					mx[j][0] = v[p];
				}
			}
			p++;
		}
	}
	p = v.size()-1;
	for(int j=lis[i].size()-1; j>=0; j--){
		if(j + 1 == lis[i].size()){
			mn[j][0] = mn[j][1] = pi(0, 0);
		}
		else{
			mn[j][0] = mn[j+1][0];
			mn[j][1] = mn[j+1][1];
		}
		while(p >= 0 && v[p].second > lis[i][j]){
			if(v[p].first != i){
				if(mn[j][0].first == v[p].first){
					mn[j][0] = v[p];
				}
				else{
					mn[j][1] = mn[j][0];
					mn[j][0] = v[p];
				}
			}
			p--;
		}
	}
}

void upload(pi a, pi b, pi c){
	if(a.second + b.second > c.second){
		printf("%d %d %d %d %d %d\n", a.first, a.second, b.first, b.second, c.first, c.second);
		exit(0);
	}
}
int main(){
	scanf("%d",&n);
	for(int i=1; i<=n; i++){
		int x;
		scanf("%d",&x);
		lis[i].resize(x);
		for(int j=0; j<x; j++){
			scanf("%d",&lis[i][j]);
		}
		sort(lis[i].begin(), lis[i].end());
		lis[i].resize(unique(lis[i].begin(), lis[i].end()) - lis[i].begin());
		for(auto &j : lis[i]){
			v.push_back(pi(i, j));
		}
	}
	sort(v.begin(), v.end(), [&](const pi &a, const pi &b){
		return a.second < b.second;
	});
	int low[55] = {};
	for(int i=0; i<v.size(); ){
		int e = i;
		while(e < v.size() && v[e].second == v[i].second) e++;
		if(e - i >= 3){
			upload(v[i], v[i+1], v[i+2]);
		}
		if(e - i >= 2){
			int chk[55] = {};
			for(int j=i; j<e; j++){
				chk[v[j].first] = 1;
			}
			for(int j=1; j<=n; j++){
				if(e - i - chk[j] >= 2 && low[j]){
					printf("%d %d ", j, low[j]);
					int cnt = 2;
					for(int k=1; k<=n; k++){
						if(chk[k] && cnt && k != j){
							cnt--;
							printf("%d %d ",k, v[i].second);
						}
					}
					return 0;
				}
			}
		}
		for(int j=i; j<e; j++){
			low[v[j].first] = v[j].second;
		}
		i = e;
	}
	for(int i=1; i<=n; i++){
		build(i);
		for(int j=0; j<lis[i].size(); j++){
			for(int k=0; k<2; k++){
				for(int l=0; l<2; l++){
					if(mx[j][k].first && mn[j][l].first && mx[j][k].first != mn[j][l].first){
						upload(mx[j][k], pi(i, lis[i][j]), mn[j][l]);
					}
				}
			}
		}
	}
	puts("NIE");
}