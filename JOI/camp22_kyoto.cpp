#include <bits/stdc++.h>
using namespace std;
using pi = pair<int, int>;
using lint = long long;
const int MAXN = 500005;

// oops, just atcoder
// https://atcoder.jp/contests/jag2015summer-day3/tasks/icpc2015summer_day3_i

lint ccw(pi a, pi b, pi c){
	int dx1 = b.first - a.first;
	int dy1 = b.second - a.second;
	int dx2 = c.first - a.first;
	int dy2 = c.second - a.second;
	return 1ll * dx1 * dy2 - 1ll * dy1 * dx2;
}
 
int n, m;
vector<pi> ah, bh;
 
int main(){
	scanf("%d %d",&n,&m);
	for(int i=0; i<n; i++){
		int z; scanf("%d",&z);
		while(ah.size() >= 2 && ccw(ah[ah.size() - 2], ah.back(), pi(i, z)) <= 0){
			ah.pop_back();
		}
		ah.emplace_back(i, z);
	}
	for(int i=0; i<m; i++){
		int z; scanf("%d",&z);
		while(bh.size() >= 2 && ccw(bh[bh.size() - 2], bh.back(), pi(i, z)) <= 0){
			bh.pop_back();
		}
		bh.emplace_back(i, z);
	}
	int px = 0, py = 0;
	lint ret = 0;
	while(px + 1 < ah.size() || py + 1 < bh.size()){
		bool goDown = 0;
		if(px + 1 == ah.size()) goDown = 1;
		else if(px + 1 < ah.size() && py + 1 < bh.size()){
			pi p1 = pi(bh[py + 1].first - bh[py].first, bh[py + 1].second - bh[py].second);
			pi p2 = pi(ah[px + 1].first - ah[px].first, ah[px + 1].second - ah[px].second);
			if(ccw(pi(0, 0), p1, p2) >= 0) goDown = 1;
		}
		if(goDown) ret += 1ll * (bh[py + 1].first - bh[py].first) * ah[px].second, py++;
		else ret += 1ll * (ah[px + 1].first - ah[px].first) * bh[py].second, px++;
	}
	cout << ret << endl;
}

