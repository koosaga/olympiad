#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef long double llf;
const int mod = 1e9 + 7;
typedef pair<int, int> pi;

struct event{
	int x, y, t;
	lint st;
	bool operator<(const event &e)const{
		return st > e.st;
	}
};

char *str[1000005], buf[10];
set<int> sl[1000005], sr[1000005];
vector<event> ev[4];
int w, h, n;
lint *last[1000005];
int dx[4] = {1, 0, -1, 0}, dy[4] = {0, 1, 0, -1};

void cheum(){
	for(int i=0; i<w; i++) sl[i].clear();
	for(int i=0; i<h; i++) sr[i].clear();
	for(int i=0; i<w; i++){
		for(int j=0; j<h; j++){
			sl[i].insert(j);
			sr[j].insert(i);
		}
	}
}
void solve(){
	for(int i=0; i<4; i++) sort(ev[i].begin(), ev[i].end());
	cheum();
	for(auto &i : ev[0]){
		while(1){
			auto l = sr[i.y].upper_bound(i.x);
			if(l != sr[i.y].end() && *l <= i.x + i.t){
				last[*l][i.y] = max(last[*l][i.y], i.st + (*l - i.x));
				sr[i.y].erase(*l);
			}
			else break;
		}
	}
	cheum();
	for(auto &i : ev[2]){
		while(1){
			auto l = sr[i.y].lower_bound(i.x);
			if(l == sr[i.y].begin()) break;
			l--;
			if(*l >= i.x - i.t){
				last[*l][i.y] = max(last[*l][i.y], i.st + (i.x - *l));
				sr[i.y].erase(*l);
			}
			else break;
		}
	}
	cheum();
	for(auto &i : ev[1]){
		while(1){
			auto l = sl[i.x].upper_bound(i.y);
			if(l != sl[i.x].end() && *l <= i.y + i.t){
				last[i.x][*l] = max(last[i.x][*l], i.st + (*l - i.y));
				sl[i.x].erase(l);
			}
			else break;
		}
	}
	cheum();
	for(auto &i : ev[3]){
		while(1){
			auto l = sl[i.x].lower_bound(i.y);
			if(l == sl[i.x].begin()) break;
			l--;
			if(*l >= i.y - i.t){
				last[i.x][*l] = max(last[i.x][*l], i.st + (i.y - *l));
				sl[i.x].erase(l);
			}
			else break;
		}
	}
}

int main(){
	scanf("%d %d %d",&w,&h,&n);
	for(int i=0; i<w; i++){
		str[i] = (char*)calloc(h+1, sizeof(char));
		last[i] = (lint*)calloc(h+1, sizeof(lint));
		scanf("%s", str[i]);
	}
	ev[2].push_back({w, 0, 1, 0});
	int px = w-1, py = 0;
	lint t = 1;
	for(int i=0; i<n; i++){
		int k, d;
		scanf("%s %d", buf, &k);
		if(*buf == 'u') d = 2;
		if(*buf == 'd') d = 0;
		if(*buf == 'r') d = 1;
		if(*buf == 'l') d = 3;
		ev[d].push_back({px, py, k, t});
		px += k * dx[d];
		py += k * dy[d];
		t += k;
	}
	solve();
	lint s = 0, e = t;
	for(int i=0; i<w; i++){
		for(int j=0; j<h; j++){
			if(str[i][j] == '#'){
				if(!last[i][j]){
					puts("-1 -1");
					return 0;
				}
				s = max(s, last[i][j]);
			}
			else{
				if(last[i][j]) e = min(e, last[i][j] - 1);
			}
		}
	}
	if(s > e) puts("-1 -1");
	else printf("%lld %lld", s, e);
}
