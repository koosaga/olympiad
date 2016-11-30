#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef pair<int, int> pi;

struct tup{
	int x, y, v;
	bool operator<(const tup &t)const{
		return v < t.v;
	}
};

int n, m, c[1005][1005];

struct bit{
	lint cmax;
	lint tree[1005][1005];
	void init(){
		cmax = -1e18;
	}
	void add(int x, int y, lint v){
		cmax = max(cmax, v);
	}
	lint query(int x, int y){
		return cmax;
	}	
}seg1, seg2, seg3, seg4;

vector<tup> v;

int main(){
	cin >> n >> m;
	for(int i=1; i<=n; i++){
		for(int j=1; j<=m; j++){
			int t; 
			scanf("%d",&t);
			if(t != 0){
				v.push_back((tup){i, j, t});
			}
		}
	}
	for(int i=1; i<=n; i++){
		for(int j=1; j<=m; j++){
			scanf("%d",&c[i][j]);
		}
	}
	seg1.init();
	seg2.init();
	seg3.init();
	seg4.init();
	lint ret = 0;
	sort(v.begin(), v.end());
	for(int i=0; i<v.size(); ){
		int e = i;
		while(e < v.size() && v[e].v == v[i].v) e++;
		vector<lint> aux;
		for(int j=i; j<e; j++){
			lint tmp = 0;
			tmp = max(tmp, seg1.query(v[j].x, v[j].y) + v[j].x + v[j].y);
			tmp = max(tmp, seg2.query(n + 1 - v[j].x, m + 1 - v[j].y) - v[j].x - v[j].y);
			tmp = max(tmp, seg3.query(n + 1 - v[j].x, v[j].y) - v[j].x + v[j].y);
			tmp = max(tmp, seg4.query(v[j].x, m + 1 - v[j].y) + v[j].x - v[j].y);
			tmp += c[v[j].x][v[j].y];
			aux.push_back(tmp);
			ret = max(ret, tmp);
		}
		for(int j=i; j<e; j++){
			seg1.add(v[j].x, v[j].y, aux[j-i] - v[j].x - v[j].y);
			seg2.add(n + 1 - v[j].x, m + 1 - v[j].y, aux[j-i] + v[j].x + v[j].y);
			seg3.add(n + 1 - v[j].x, v[j].y, aux[j-i] + v[j].x - v[j].y);
			seg4.add(v[j].x, m + 1 - v[j].y, aux[j-i] - v[j].x + v[j].y);
		}
		i = e;
	}
	cout << ret;
}