#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef long double llf;
typedef pair<int, int> pi;

int n, m, l[20005], r[20005];
char str[20005];
int vis[20005];
vector<int> gph[20005];
bitset<10005> s0, s1, dod[10005];

void dfs(int x){
	if(vis[x]) return;
	vis[x] = 1;
	if(x > n){
		dfs(l[x]);
		dfs(r[x]);
	}
}

int input(){
	string s;
	cin >> s;
	int num = 0;
	for(int i=1; i<s.size(); i++){
		num = num * 10 + s[i] - '0';
	}
	if(s[0] == 'x'){
		return num;
	}
	return num + n;
}

bool p0[10005], p1[10005];

int main(){
	scanf("%d %d",&n,&m);
	scanf("%s", str + 1);
	for(int i=n+1; i<=n+m; i++){
		l[i] = input();
		r[i] = input();
		gph[l[i]].push_back(i);
		gph[r[i]].push_back(i);
	}
	for(int i=n+m; i>n; i--){
		if(!vis[i] && str[i-n] == '0'){
			dfs(i);
		}
	}
	for(int i=1; i<=n; i++){
		if(vis[i]) s0.set(i);
		else s1.set(i);
	}
	for(int i=1; i<=m; i++){
		memset(vis, 0, sizeof(vis));
		dfs(i + n);
		for(int j=1; j<=n; j++){
			if(vis[j]) dod[i].set(j);
		}
	}
	for(int i=1; i<=m; i++){
		if(str[i] == '0'){
			p0[i] = 1;
			continue;
		}
		if(str[i] == '1'){
			p1[i] = 1;
			continue;
		}
		if((dod[i] & s1).any()) p1[i] = 1;
		else p0[i] = 1, str[i] = '0';
	}
	for(int i=1; i<=m; i++){
		if(str[i] == '?' && p0[i] == 0){
			p0[i] = 1;
			queue<int> que;
			bool vis[20005] = {};
			for(int j=1; j<=n; j++){
				if(s1.test(j) && !dod[i].test(j)){
					que.push(j);
				}
			}
			while(!que.empty()){
				auto x = que.front();
				que.pop();
				for(auto &y : gph[x]){
					if(!vis[y]){
						vis[y] = 1;
						que.push(y);
					}
				}
			}
			for(int j=1; j<=m; j++){
				if(str[j] == '1' && !vis[j + n]){
					p0[i] = 0;
					break;
				}
			}
		}
		if(p0[i] && p1[i]) putchar('?');
		else if(p0[i]) putchar('0');
		else putchar('1');
	}
}

