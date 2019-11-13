#include <bits/stdc++.h>
using namespace std;
const int MAXN = 2005;
const int MAXT = 4100;
using lint = long long;
using pi = pair<int, int>;
#define sz(v) ((int)(v).size())

struct point{
	int x, y, k, t;
}a[12];

int dist(pi a, pi b){
	return abs(a.first - b.first) + abs(a.second - b.second);
}

lint solve(int n, int m, lint pos, lint neg){
	lint ret = 0;
	int rcnt[60] = {};
	int ccnt[60] = {};
	for(int i=0; i<60; i++){
		rcnt[i] = (n + 59 - i) / 60;
		ccnt[i] = (m + 59 - i) / 60;
	}
	for(int i=0; i<60; i++){
		for(int j=0; j<60; j++){
			int pl = (i + j) % 60;
			int ne = (i - j) % 60 + 60;
			ne %= 60;
			if((pos >> pl) % 2 && (neg >> ne) % 2) ret += 1ll * rcnt[i] * ccnt[j];
		}
	}
	return ret;
}

int main(){
	int t;
	scanf("%d",&t);
	while(t--){
		int n, m;
		cin >> n >> m;
		vector<int> vx = {0, m + 1};
		vector<int> vy = {0, m + 1};
		for(int i=0; i<n; i++){
			cin >> a[i].x >> a[i].y >> a[i].k >> a[i].t;
			vx.push_back(a[i].x);
			vy.push_back(a[i].y);
		}
		sort(vx.begin(), vx.end());
		sort(vy.begin(), vy.end());
		vx.resize(unique(vx.begin(), vx.end()) - vx.begin());
		vy.resize(unique(vy.begin(), vy.end()) - vy.begin());
		lint ret = 0;
		for(int i=0; i<sz(vx)-1; i++){
			for(int j=0; j<sz(vy)-1; j++){
				int sx = vx[i];
				int sy = vy[j];
				long long pos = (1ll << 60) - 1;
				long long neg = (1ll << 60) - 1;
				for(int k=0; k<n; k++){
					if(a[k].x <= sx && a[k].y <= sy){
						int v = dist(pi(sx, sy), pi(a[k].x, a[k].y));
						for(int l=0; l<60; l++){
							if((v + l) % a[k].k != a[k].t) pos &= ~(1ll << l); 
						}
					}
					if(a[k].x <= sx && a[k].y > sy){
						int v = dist(pi(sx, sy), pi(a[k].x, a[k].y));
						for(int l=0; l<60; l++){
							if((v + l) % a[k].k != a[k].t) neg &= ~(1ll << l); 
						}
					}
					if(a[k].x > sx && a[k].y <= sy){
						int v = dist(pi(sx, sy), pi(a[k].x, a[k].y));
						for(int l=0; l<60; l++){
							if((v + 60 - l) % a[k].k != a[k].t) neg &= ~(1ll << l); 
						}
					}
					if(a[k].x > sx && a[k].y > sy){
						int v = dist(pi(sx, sy), pi(a[k].x, a[k].y));
						for(int l=0; l<60; l++){
							if((v + 60 - l) % a[k].k != a[k].t) pos &= ~(1ll << l); 
						}
					}
				}
				ret += solve(vx[i + 1] - vx[i], vy[j + 1] - vy[j], pos, neg);
			}
		}
		cout << ret << endl;
	}
}
