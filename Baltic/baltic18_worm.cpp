#include<bits/stdc++.h>
using namespace std;
using pi = pair<int, int>;
const int dx[6] = {1, -1, 0, 0, 0, 0};
const int dy[6] = {0, 0, 1, -1, 0, 0};
const int dz[6] = {0, 0, 0, 0, 1, -1};

int n, m, k, q;

int query(int x, int y, int z = 1){
	if(x <= 0 || x > n || y <= 0 || y > m || z <= 0 || z > k) return 0;
	printf("? %d %d %d\n", x, y, z);
	fflush(stdout);
	int v; scanf("%d",&v); return v;
}

void report(int x, int y, int z){
    printf("! %d %d %d\n", x, y, z);
    fflush(stdout);
	exit(0);
}

int global_max = 0;
pi  attain_max;

void solve(int sx, int ex, int sy, int ey){
	if(ex - sx <= 2 && ey - sy <= 2){
		for(int i=sx; i<=ex; i++){
			for(int j=sy; j<=ey; j++){
				if(max({query(i-1, j), query(i, j-1), query(i+1, j), query(i, j+1)}) <= query(i, j)){
					report(i, j, 1);
				}
			}
		}
		report(attain_max.first, attain_max.second, 1);
	}
	if(ex - sx <= ey - sy){
		int m = (sy + ey) / 2;
		int mx = -1, mxp = -1;
		for(int i=sx; i<=ex; i++){
			int v = query(i, m, 1);
			if(mx < v){
				mx = v;
				mxp = i;
			}
		}
		if(mx < global_max){
			assert(attain_max.second != m);
			if(attain_max.second < m) solve(sx, ex, sy, m - 1);
			else solve(sx, ex, m + 1, ey);
			return;
		}
		global_max = mx;
		attain_max = pi(mxp, m);
		// got something larger
		if(mx < query(mxp, m+1, 1)){
			global_max = query(mxp, m + 1, 1);
			attain_max = pi(mxp, m + 1); 
			solve(sx, ex, m + 1, ey);
		}
		else if(mx < query(mxp, m-1, 1)){
			global_max = query(mxp, m - 1, 1);
			attain_max = pi(mxp, m - 1);
			solve(sx, ex, sy, m - 1);
		}
		else report(mxp, m, 1);
	}
	else{
		int m = (sx + ex) / 2;
		int mx = -1, mxp = -1;
		for(int i=sy; i<=ey; i++){
			int v = query(m, i, 1);
			if(mx < v){
				mx = v;
				mxp = i;
			}
		}
		if(mx < global_max){
			assert(attain_max.first != m);
			if(attain_max.first < m) solve(sx, m-1, sy, ey);
			else solve(m+1, ex, sy, ey);
			return;
		}
		global_max = mx;
		attain_max = pi(m, mxp);
		// got something larger
		if(mx < query(m+1, mxp, 1)){
			global_max = query(m+1, mxp, 1);
			attain_max = pi(m+1, mxp);
			solve(m+1, ex, sy, ey);
		}
		else if(mx < query(m-1, mxp, 1)){
			global_max = query(m-1, mxp, 1);
			attain_max = pi(m-1, mxp);
			solve(sx, m-1, sy, ey);
		}
		else report(m, mxp, 1);
	}
}

int main(){
    cin >> n >> m >>  k >> q;
	auto ok = [&](int x, int y, int z){
		return 1 <= x && x <= n && 1 <= y && y <= m && 1 <= z && z <= k;
	};
	if(m == 1){
		map<int, int> qr;
		auto Do = [&](int x){
			if(x <= 0 || x > n) return 0;
			if(qr.find(x) != qr.end()) return qr[x];
			else return qr[x] = query(x, 1, 1);
		};
		double GR = (1 + sqrt(5)) / 2;
		int s = 1, e = n;
		int lcache = -1, rcache = -1;
		while(true){
			int m1 = round(s + (e - s) / (GR + 1));
			int m2 = round(s + (GR * (e - s)) / (GR + 1));
			if(~lcache) m1 = lcache;
			if(~rcache) m2 = rcache;
			if(m1 == m2) break;
			if(Do(m1) < Do(m2)){
				s = m1;
				lcache = m2;
				rcache = -1;
			}
			else{
				e = m2;
				lcache = -1;
				rcache = m1;
			}
		}
		for(int i=s; i<=e; i++){
			if(Do(i - 1) <= Do(i) && Do(i) >= Do(i+1)) report(i, 1, 1); 
		}
		assert(0);
	}
	if(k == 1){
		solve(1, n, 1, m);
	}
	int px = -1, py = -1, pz = -1, cur = 0;
	for(int i=0; i<q/2; i++){
		int vx = rand() % n + 1, vy = rand() % m + 1, vz = rand() % k + 1;
		int val = query(vx, vy, vz);
		if(val > cur){
			cur = val;
			tie(px, py, pz) = make_tuple(vx, vy, vz);
		}
	}
	q = q - q / 2;
	while(q >= 6){
		int dir = -1;
		for(int i=0; i<6; i++){
			if(ok(px + dx[i], py + dy[i], pz + dz[i])){
				q--;
				int nval = query(px + dx[i], py + dy[i], pz + dz[i]);
				if(nval > cur){
					cur = nval;
					dir = i;
				}
			}
		}
		if(dir == -1) report(px, py, pz);
		else{
			px += dx[dir];
			py += dy[dir];
			pz += dz[dir];
		}
	}
}
