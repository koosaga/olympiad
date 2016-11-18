#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef pair<int, int> pi;

struct seg{
	int x, s, e, idx;
	bool operator<(const seg &a)const{
		return pi(x, s) < pi(a.x, a.s);
	}
};

bool ret[25005];

void solve(vector<seg> &v){
	for(int i=0; i<v.size(); ){
		int e = i;
		while(e < v.size() && v[e].x == v[i].x) e++;
		for(int j=i; j<e; j++){
			int k = j;
			while(k < e && v[k].s <= v[j].e) k++;
			if(k > j+1){
				for(int l=j; l<k; l++){
					ret[v[l].idx] = 1;
				}
			}
		}
		i = e;
	}
}

int main(){
	int n;
	vector<seg> xs, ys;
	cin >> n;
	for(int i=0; i<n; i++){
		int sx, ex, sy, ey;
		scanf("%d %d %d %d",&sx,&sy,&ex,&ey);
		xs.push_back({sx, sy, ey, i});
		xs.push_back({ex, sy, ey, i});
		ys.push_back({sy, sx, ex, i});
		ys.push_back({ey, sx, ex, i});
	}
	sort(xs.begin(), xs.end());
	solve(xs);
	sort(ys.begin(), ys.end());
	solve(ys);
	cout << count(ret, ret + n, 0);
}
