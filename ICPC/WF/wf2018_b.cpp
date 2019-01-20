#include <bits/stdc++.h>
using namespace std;
const int MAXN = 1000005;

int n, m, seq[MAXN];
char del[MAXN], buf[MAXN];
vector<int> gph[3 * MAXN];
string prnt[MAXN];
int vis[MAXN * 3];

void dfs(int x){
	if(vis[x]) return;
	vis[x] = 1;
	for(auto &i : gph[x]) dfs(i);
}

int main(){
	map<string, int> mp;
	while(~scanf("%s", buf)){
		string tmp = buf;
		if(tmp.back() == ','){
			del[++n] = tmp.back();
			tmp.pop_back();
		}
		else if(tmp.back() == '.'){
			del[++n] = tmp.back();
			tmp.pop_back();
		}
		else n++;
		if(mp.find(tmp) == mp.end()){
			mp[tmp] = ++m;
			prnt[m] = tmp;
		}
		seq[n] = mp[tmp];
	}
	vector<int> stp;
	for(int i=1; i<n; i++){
		if(del[i] == ','){
			stp.push_back(i);
		}
		if(del[i] == '.') continue;
		gph[i].push_back(n + seq[i + 1]);
		gph[i].push_back(n + m + seq[i]);
	}
	for(int i=1; i<=n; i++){
		if(del[i-1] != '.') gph[n + seq[i]].push_back(i - 1);
		if(del[i] != '.') gph[n + m + seq[i]].push_back(i);
	}
	for(auto &i : stp) dfs(i);
	for(int i=1; i<=n; i++){
		if(vis[i]) del[i] = ',';
		printf("%s", prnt[seq[i]].c_str());
		if(del[i]) putchar(del[i]);
		putchar(' ');
	}
}
