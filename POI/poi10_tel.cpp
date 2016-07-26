#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef long double llf;
typedef pair<lint, lint> pi;
 
int n, m;
vector<int> gph[40005];
vector<int> a, b, c;
 
int d1[40005], d2[40005];
 
void bfs(int s, int *d){
	d[s] = 0;
	queue<int> que;
	que.push(s);
	while(!que.empty()){
		int x = que.front();
		que.pop();
		for(auto &i : gph[x]){
			if(d[i] > d[x] + 1){
				d[i] = d[x] + 1;
				que.push(i);
			}
		}
	}
}
 
int s[1000005], e[1000005];
int col[40005];
 
lint nc2(int x){
	return 1ll * x * (x-1) / 2;
}
 
int main(){
	memset(d1, 0x3f, sizeof(d1));
	memset(d2, 0x3f, sizeof(d2));
	cin >> n >> m;
	for(int i=0; i<m; i++){
		scanf("%d %d",&s[i],&e[i]);
		gph[s[i]].push_back(e[i]);
		gph[e[i]].push_back(s[i]);
	}
	bfs(1, d1);
	bfs(2, d2);
	for(int i=3; i<=n; i++){
		if(d1[i] == 1) a.push_back(i);
		else if(d2[i] == 1) b.push_back(i);
		else c.push_back(i);
	}
	for(auto &i : a){
		col[i] = 1;
	}
	for(auto &i : b){
		col[i] = 2;
	}
	for(auto &i : c){
		col[i] = 3;
	}
	lint ret = 0;
	for(int i=0; i<m; i++){
		if(col[s[i]] == 1 && col[e[i]] == 1){
			ret--;
		}
		if(col[s[i]] == 2 && col[e[i]] == 2){
			ret--;
		}
		if(col[s[i]] == 3 && col[e[i]] == 3){
			ret--;
		}
	}
	ret += nc2(a.size()) + nc2(b.size()) + nc2(c.size());
	for(auto &i : c){
		int ca = 0, cb = 0;
		for(auto &j : gph[i]){
			if(d1[j] == 1) ca++;
			if(d2[j] == 1) cb++;
		}
		if(ca == 0 && cb == 0){
			ret += max(a.size(), b.size());
		}
		else if(ca == 0){
			ret += b.size() - cb;
		}
		else{
			ret += a.size() - ca;
		}
	}
	cout << ret;
}