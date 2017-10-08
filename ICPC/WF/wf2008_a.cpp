#include <bits/stdc++.h>
typedef long long lint;
using namespace std;

int dx[6] = {1, -1, 0, 0, 0, 0};
int dy[6] = {0, 0, 1, -1, 0, 0};
int dz[6] = {0, 0, 0, 0, 1, -1};
int nx, ny, nz;
int sx, sy, sz, sd;
int ex, ey, ez, ed;

bool chk[22][22][22];
int ans;

bool ok(int x, int y, int z){
	return 1 <= x && x <= nx && 1 <= y && y <= ny && 1 <= z && z <= nz && !chk[x][y][z];
}

void back(int x, int y, int z, int d, int dep){
	if(make_tuple(x, y, z, d) == make_tuple(ex, ey, ez, ed)){
		ans = min(ans, dep);
		return;
	}
	if(!ok(x, y, z) || dep >= 6) return;
	vector<int> v;
	for(int i=0; i<6; i++) if(d / 2 != i / 2) v.push_back(i);
	for(int i=2; i<=3; i++){
		for(int j=0; j<4; j++){
			// examine validity
			int cx = x, cy = y, cz = z;
			bool bad = 0;
			vector<tuple<int, int, int>> tra;
			tra.emplace_back(cx, cy, cz);
			for(int k=0; k<i-1; k++){
				cx += dx[d];
				cy += dy[d];
				cz += dz[d];
				if(ok(cx, cy, cz) == 0) bad = 1;
				tra.emplace_back(cx, cy, cz);
			}
			for(int k=0; k<4-i; k++){
				cx += dx[v[j]];
				cy += dy[v[j]];
				cz += dz[v[j]];
				if(ok(cx, cy, cz) == 0) bad = 1;
				tra.emplace_back(cx, cy, cz);
			}
			if(!bad){
				for(auto &k : tra){
					chk[get<0>(k)][get<1>(k)][get<2>(k)] = 1;
				}
				back(cx + dx[v[j]], cy + dy[v[j]], cz + dz[v[j]], v[j], dep + 1);
				for(auto &k : tra){
					chk[get<0>(k)][get<1>(k)][get<2>(k)] = 0;
				}
			}
		}
	}
}

int main(){
	int tc = 0;
	auto getdir = [&](const string s){
		if(s == "+x") return 0;
		if(s == "-x") return 1;
		if(s == "+y") return 2;
		if(s == "-y") return 3;
		if(s == "+z") return 4;
		if(s == "-z") return 5;
	};
	while(1){
		cin >> nx;
		if(nx == 0) break;
		printf("Case %d: ", ++tc);
		string buf;
		cin >> ny >> nz;
		cin >> sx >> sy >> sz >> buf;
		sd = getdir(buf);
		cin >> ex >> ey >> ez >> buf;
		ed = getdir(buf);
		ex += dx[ed];
		ey += dy[ed];
		ez += dz[ed];
		ans = 1e9;
		back(sx, sy, sz, sd, 0);
		if(ans <= 6) printf("%d\n", ans);
		else puts("Impossible");
	}
}

