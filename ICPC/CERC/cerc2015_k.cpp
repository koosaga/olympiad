#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef pair<int, int> pi;
typedef vector<int> vi;

int nxt[200005], n;
int indeg[200005], vis[200005];
int flag[200005];

vector<int> gph[200005];

void tsolve(int x){
	flag[x] = 1;
	for(auto &i : gph[x]){
		if(indeg[i]) continue;
		tsolve(i);
		if(flag[i] == 1) flag[x] = -1;
	}
}

void solve(int x){
	vector<int> lis;
	int stp = -1;
	for(int i=x; !vis[i]; i=nxt[i]){
		vis[i] = 1;
		if(gph[i].size() != 1){
			tsolve(i);
			if(flag[i] == -1){
				stp = i;
			}
			else{
				flag[i] = 0;
			}
		}		
		lis.push_back(i);
	}
	if(stp == -1){
		int dap = 1;
		for(auto &i : lis){
			flag[i] = dap;
			dap *= -1;
		}
		return;
	}
	rotate(lis.begin(), find(lis.begin(), lis.end(), stp), lis.end());
	int d = 0;
	for(auto &i : lis){
		if(flag[i] == -1){
			d = flag[i];
		}
		flag[i] = d;
		d *= -1;
	}
}
	
int main(){
	scanf("%d",&n);
	for(int i=1; i<=2*n; i++){
		scanf("%d",&nxt[i]);
		indeg[nxt[i]]++;
		gph[nxt[i]].push_back(i);
	}
	queue<int> q;
	for(int i=1; i<=2*n; i++){
		if(!indeg[i]) q.push(i);
	}
	while(!q.empty()){
		int x = q.front();
		q.pop();
		indeg[nxt[x]]--;
		if(indeg[nxt[x]] == 0){
			q.push(nxt[x]);
		}
	}
	for(int i=1; i<=2*n; i++){
		if(!vis[i] && indeg[i]) solve(i);
	}
	for(int i=1; i<=2*n; i++){
		if(flag[i] == 1) printf("%d ", i);
	}
}