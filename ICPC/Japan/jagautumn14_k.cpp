#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
using real_t = long double;
using pi = pair<int, int>;
const int MAXN = 105;
const int dx[7] = {-1, -1, 0, 0, 0, 1, 1};
const int dy[7] = {-1, 0, -1, 0, 1, 0, 1};

vector<pi> pos;
int grid[5][5];

int main(){
	for(int i=0; i<3; i++) pos.emplace_back(0, i);
	for(int i=0; i<4; i++) pos.emplace_back(1, i);
	for(int i=0; i<5; i++) pos.emplace_back(2, i);
	for(int i=1; i<5; i++) pos.emplace_back(3, i);
	for(int i=2; i<5; i++) pos.emplace_back(4, i);
	while(true){
		string s;
		cin >> s;
		if(s == "#") break;
		int WRONG = 0;
		for(int i=0; i<(1<<19); i++){
			for(int j=0; j<19; j++){
				int msk = (i >> j) & 1;
				grid[pos[j].first][pos[j].second] = msk;
			}
			int last_filter = 0;
			for(int t=0; t<7; t++){
				pi v(2 + dx[t], 2 + dy[t]);
				int msk = 0;
				for(int j=0; j<7; j++){
					int px = v.first + dx[j], py = v.second + dy[j];
					msk |= (grid[px][py] << j);
				}
				int val = s[msk] & 1;
				last_filter |= (val << t);
			}
			if(s[last_filter] % 2 != (last_filter >> 3) % 2) WRONG++;
		}
		puts(WRONG ? "no" : "yes");
	}
}
