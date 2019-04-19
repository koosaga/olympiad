#include <bits/stdc++.h>
using namespace std;
const int MAXN = 20005;
using lint = long long;
using pi = pair<int, int>;

struct event{
	int time, pos, who;
	bool operator<(const event &e)const{
		return time > e.time;
	}
};

priority_queue<event> evQueue;
int n, m, t[MAXN][3], boostUntil[MAXN];
int ahead[305], ans[MAXN], chk[305];

int main(){
	scanf("%d",&n);
	for(int i=1; i<=n; i++){
		for(int j=0; j<3; j++) scanf("%d",&t[i][j]);
		evQueue.push({0, 0, i});
	}
	scanf("%d",&m);
	for(int i=0; i<m; i++){
		int x; scanf("%d",&x);
		chk[x] = 1;
	}
	while(!evQueue.empty()){
		auto x = evQueue.top();
		evQueue.pop();
		vector<event> proc = {x};
		while(!evQueue.empty() && evQueue.top().time == x.time){
			proc.push_back(evQueue.top());
			evQueue.pop();
		}
		for(auto &i : proc){
			if(i.pos == 300){
				ans[i.who] = i.time;
				continue;
			}
			int nxtTime = i.time;
			bool good = 0;
			if(boostUntil[i.who] > i.pos){
				nxtTime++;
				good = 1;
			}
			else if(chk[i.pos]){
				boostUntil[i.who] = i.pos + (ahead[i.pos] % 20);
				if(boostUntil[i.who] > i.pos){
					nxtTime++;
					good = 1;
				}
			}
			if(!good){
				nxtTime += t[i.who][i.pos / 100];
			}
			evQueue.push({nxtTime, i.pos + 1, i.who});
		}
		for(auto &i : proc) ahead[i.pos]++;
	}
	for(int i=1; i<=n; i++) printf("%d\n", ans[i]);
}
