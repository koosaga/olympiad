#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = pair<int, int>;
const int MAXN = 500005;

struct bit{
	int tree[MAXN];
	void add(int x, int v = 1){
		while(x < MAXN){
			tree[x] += v;
			x += x & -x;
		}
	}
	int query(int x){
		int ret = 0;
		while(x){
			ret += tree[x];
			x -= x & -x;
		}
		return ret;
	}
}bit;

int n, m;
char buf[MAXN];
vector<int> gph[MAXN], rev[MAXN];
bool vis0[MAXN], vis1[MAXN];
int goodin[MAXN];

void dfs0(int x){
	if(vis0[x]) return;
	vis0[x] = 1;
	for(auto &i : gph[x]) dfs0(i);
}

void dfs1(int x){
	if(vis1[x]) return;
	vis1[x] = 1;
	for(auto &i : rev[x]) dfs1(i);
}

int d1[MAXN], d2[MAXN], piv;
void dfs(int x, int *ans){
	vis0[x]= 1;
	for(auto &i : gph[x]){
		if(!vis0[i]) dfs(i, ans);
	}
	ans[x] = ++piv;
}

int get(int x, int y){
	return x * m + y;
}

int getdir(int x, int y){
	pi p1 = pi(x / m, x % m);
	pi p2 = pi(y / m, y % m);
	if(p1.first == p2.first){
		if(p1.second < p2.second) return 0;
		return 2;
	}
	if(p1 < p2) return 1;
	return 3;
}

int main(){
	scanf("%d %d",&n,&m);
	assert(getchar() == 10);
	for(int i=0; i<2*n-1; i++){
		int ptr = 0;
		while(!feof(stdin)){
			buf[ptr++] = getchar();
			if(isspace(buf[ptr-1])){
				assert(buf[ptr-1] == '\n');
				buf[--ptr] = 0;
				break;
			}
		}
		for(int j=0; j<ptr; j++){
			if(i % 2 == 1){
				int l = get(i / 2, j);
				int r = get(i / 2 + 1, j);
				if(buf[j] == 'v') gph[l].push_back(r);
				else if(buf[j] == '^') gph[r].push_back(l);
			}
			else{
				int l = get(i / 2, j);
				int r = get(i / 2, j + 1);
				if(buf[j] == '>') gph[l].push_back(r);
				else if(buf[j] == '<') gph[r].push_back(l);
			}
		}
	}
	for(int i=0; i<n*m; i++){
		for(auto &j : gph[i]) rev[j].push_back(i);
	}
	dfs0(0);
	if(!vis0[n*m-1]){
		puts("0");
		return 0;
	}
	dfs1(n*m-1);
	for(int i=0; i<n*m; i++) gph[i].clear();
	vector<int> good;
	for(int i=0; i<n*m; i++){
		if(vis0[i] && vis1[i]){
			good.push_back(i);
			for(auto &j : rev[i]){
				if(vis0[j] && vis1[j]){
					gph[j].push_back(i);
					goodin[i] = j;
				}
			}
		}
	}
	lint ret = 0;
	for(auto &i : good){
		if(i == 0){
			sort(gph[i].begin(), gph[i].end());
		}
		else{
			int d = getdir(i, goodin[i]);
			sort(gph[i].begin(), gph[i].end(), [&](const int &a, const int &b){
				int v1 = getdir(i, a) + 8 - d;
				int v2 = getdir(i, b) + 8 - d;
				v1 %= 4;
				v2 %= 4;
				return v1 < v2;
			});
		}
	}
	memset(vis0, 0, sizeof(vis0));
	dfs(0, d1);
	piv = 0;
	memset(vis0, 0, sizeof(vis0));
	for(auto &i : good) reverse(gph[i].begin(), gph[i].end());
	dfs(0, d2);
	sort(good.begin(), good.end(), [&](const int &a, const int &b){
		return d1[a] < d1[b];
	});
	for(auto &i : good){
		bit.add(d2[i]);
		ret += bit.query(d2[i]);
	}
	cout << ret << endl;
}
