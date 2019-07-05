#include <bits/stdc++.h>
using namespace std;
using pi = pair<int, int>;
const int MAXN = 400005;

int ptr = 1;
vector<int> path_info = {1};
pi par[MAXN], dep[MAXN];
int anc[19][MAXN];

void init(){}

pi get_idx_and_depth(int pos){
	auto itr = --upper_bound(path_info.begin(), path_info.end(), pos);
	int fst = (itr - path_info.begin());
	int snd = dep[fst].first + (pos - *itr);
	return pi(fst, snd);
}

void path(int a, int s){
	path_info.push_back(ptr + 1);
	ptr += s;
	auto pos = get_idx_and_depth(a);
	par[path_info.size() - 1] = pi(a, pos.first);
	dep[path_info.size() - 1] = pi(pos.second + 1, dep[pos.first].second + 1);
	anc[0][path_info.size() - 1] = pos.first;
	for(int i=1; i<19; i++){
		anc[i][path_info.size() - 1] = anc[i-1][anc[i-1][path_info.size() - 1]];
	}
}

pi getLCA(pi x, pi y){
	if(dep[y.first].second < dep[x.first].second) swap(x, y);
	int dx = dep[y.first].second - dep[x.first].second;
	if(dx > 0){
		int w = y.first;
		dx--;
		for(int i=0; i<19; i++){
			if((dx >> i) & 1) w = anc[i][w];
		}
		y = pi(par[w].second, dep[w].first - 1);
	}
	if(x.first != y.first){
		int wx = x.first, wy = y.first;
		for(int i=18; i>=0; i--){
			if(anc[i][wx] != anc[i][wy]){
				wx = anc[i][wx];
				wy = anc[i][wy];
			}
		}
		x = pi(par[wx].second, dep[wx].first - 1);
		y = pi(par[wy].second, dep[wy].first - 1);
	}
	return min(x, y);
}

int getAnc(int x, int cnt){
	auto y = get_idx_and_depth(x);
	int curUp = x - path_info[y.first];
	if(cnt <= curUp) return x - cnt;
	cnt = y.second - cnt;
	int curNd = y.first;
	for(int i=18; i>=0; i--){
		if(dep[anc[i][curNd]].first > cnt) curNd = anc[i][curNd];
	}
	y = pi(par[curNd].first, dep[curNd].first - 1);
	cnt = (y.second - cnt);
	return y.first - cnt;
}

int dig(int a, int b){
	auto v1 = get_idx_and_depth(a);
	auto v2 = get_idx_and_depth(b);
	auto l = getLCA(v1, v2);
	if(v1.second >= v2.second){
		int howUp = v1.second + v2.second - 2 * l.second;
		return getAnc(a, howUp / 2);
	}
	else{
		int howUp = v1.second + v2.second - 2 * l.second;
		return getAnc(b, (1 + howUp) / 2);
	}
}
