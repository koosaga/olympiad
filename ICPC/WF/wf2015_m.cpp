#include <bits/stdc++.h>
const int MAXN = 100005;
using namespace std;
using lint = long long;
using pi = pair<lint, lint>;

struct rect{
	int sx, ex, sy, ey;
	bool operator==(const rect &r)const{
		return make_tuple(sx, ex, sy, ey) == make_tuple(r.sx, r.ex, r.sy, r.ey);
	}
};

vector<rect> v;

int find_window(int x, int y){
	for(int ii=0; ii<v.size(); ii++){
		auto i = v[ii];
		if(i.sx <= x && i.ex > x && i.sy <= y && i.ey > y){
			return ii;
		}
	}
	return -1;
}

int cnt;

void Move(int pos, int d){
	vector<int> ord(v.size());
	vector<int> dp(v.size());
	iota(ord.begin(), ord.end(), 0);
	sort(ord.begin(), ord.end(), [&](const int &a, const int &b){
		return v[a].ex < v[b].ex;
	});
	int delta = 0;
	for(int i=0; i<ord.size(); i++){
		for(int j=0; j<i; j++){
			if(max(v[ord[j]].sy, v[ord[i]].sy) < min(v[ord[j]].ey, v[ord[i]].ey)){
				dp[i] = max(dp[i], dp[j]);
			}
		}
		dp[i] += v[ord[i]].ex - v[ord[i]].sx;
		if(ord[i] == pos){
			delta = v[ord[i]].ex - dp[i];
		}
	}
	delta = min(delta, d);
	if(delta < d){
		printf("Command %d: MOVE - moved %d instead of %d\n", cnt, delta, d);
	}
	fill(dp.begin(), dp.end(), 0);
	for(int i=0; i<ord.size(); i++){
		if(ord[i] == pos) dp[i] = delta;
	}
	for(int i=(int)ord.size()-1; i>=0; i--){
		for(int j=i+1; j<ord.size(); j++){
			if(max(v[ord[j]].sy, v[ord[i]].sy) < min(v[ord[j]].ey, v[ord[i]].ey)){
				dp[i] = max(dp[i], dp[j] - (v[ord[j]].sx - v[ord[i]].ex));
			}
		}
	}
	for(int i=0; i<ord.size(); i++){
		v[ord[i]].sx -= dp[i];
		v[ord[i]].ex -= dp[i];
	}
}

int main(){
	int xmax, ymax;
	char buf[50];
	cin >> xmax >> ymax;
	auto ERROR = [&](int i, char *s, string t){
		printf("Command %d: %s - %s\n", i, s, t.c_str());
	};
	while(~scanf("%s", buf)){
		cnt++;
		if(*buf == 'O'){
			int sx, ex, sy, ey;
			cin >> sx >> sy >> ex >> ey;
			ex += sx, ey += sy;
			bool err = false;
			if(ex > xmax || ey > ymax){
				err = true;
			}
			for(auto &i : v){
				if(max(i.sx, sx) < min(i.ex, ex) && max(i.sy, sy) < min(i.ey, ey)){
					err = true;
				}
			}
			if(err){
				ERROR(cnt, buf, "window does not fit");
			}
			else{
				v.push_back({sx, ex, sy, ey});
			}
		}
		if(*buf == 'C'){
			int x, y;
			cin >> x >> y;
			int num = find_window(x, y);
			if(num == -1){
				ERROR(cnt, buf, "no window at given position");
			}
			else{
				v.erase(v.begin() + num);
			}
		}
		if(*buf == 'M'){
			int sx, sy, dx, dy;
			cin >> sx >> sy >> dx >> dy;
			int num = find_window(sx, sy);
			if(num == -1){
				ERROR(cnt, buf, "no window at given position");
			}
			else{
				bool swp1 = 0, swp2 = 0;
				if(dy != 0){
					for(auto &i : v){
						swap(i.sx, i.sy);
						swap(i.ex, i.ey);
					}
					dx = dy;
					swap(xmax, ymax);
					swp1 = true;
				}
				if(dx > 0){
					swp2 = true;
					for(auto &i : v){
						tie(i.sx, i.ex) = pi(xmax - i.ex, xmax - i.sx);
					}
					dx = -dx;
				}
				Move(num, abs(dx));
				if(swp2){
					for(auto &i : v){
						tie(i.sx, i.ex) = pi(xmax - i.ex, xmax - i.sx);
					}
					dx = -dx;
				}
				if(swp1){
					for(auto &i : v){
						swap(i.sx, i.sy);
						swap(i.ex, i.ey);
					}
					swap(xmax, ymax);
				}
			}
		}
		if(*buf == 'R'){
			int sx, ex, sy, ey;
			cin >> sx >> sy >> ex >> ey;
			int num = find_window(sx, sy);
			if(num == -1){
				ERROR(cnt, buf, "no window at given position");
				continue;
			}
			sx = v[num].sx, sy = v[num].sy;
			ex += sx, ey += sy;
			bool err = false;
			if(ex > xmax || ey > ymax){
				err = true;
			}
			for(auto &i : v){
				if(i == v[num]) continue;
				if(max(i.sx, sx) < min(i.ex, ex) && max(i.sy, sy) < min(i.ey, ey)){
					err = true;
				}
			}
			if(err){
				ERROR(cnt, buf, "window does not fit");
			}
			else{
				v[num] = {sx, ex, sy, ey};
			}
		}
	}
	printf("%d window(s):\n", v.size());
	for(auto &i : v){
		printf("%d %d %d %d\n", i.sx, i.sy, i.ex-i.sx, i.ey-i.sy);
	}
}
