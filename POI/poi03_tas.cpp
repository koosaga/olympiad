#include <bits/stdc++.h>
using namespace std;
typedef pair<int,int> pi;
const int MAXN = 1000005;

int n, k, a[MAXN], b[MAXN], vis[MAXN];
vector<int> v[MAXN];

void proc_one(int x){
	vector<int> cyc;
	while(!vis[x]){
		cyc.push_back(x);
		vis[x] = 1;
		x = a[x];
	}
	for(int i=1; i<cyc.size(); i++){
		if(1ll * i * k % cyc.size() == 1){
			for(int j=0; j<cyc.size(); j++){
				b[cyc[j]] = cyc[(j + i) % cyc.size()];
			}
			return;
		}
	}
	assert(0);
}

void proc_all(vector<int> v, int l){
	int g = v.size();
	int T = l * g;
	vector<int> ans(T);
	for(int i=0; i<g; i++){
		for(int j=0; j<l; j++){
			ans[j * g + i] = v[i];
			v[i] = a[v[i]];
		}
	}
	for(int i=1; i<T; i++){
		if(1ll * k * i % T == g){
			for(int j=0; j<ans.size(); j++){
				b[ans[j]] = ans[(j + 1ll * i) % T];
			}
			return;
		}
	}
	exit(0);
}

int main(){
	scanf("%d %d",&n,&k);
	for(int i=1; i<=n; i++){
		scanf("%d",&a[i]);
	}
	for(int i=1; i<=n; i++){
		if(!vis[i]){
			int cnt = 0;
			for(int j=i; !vis[j]; j=a[j]){
				vis[j] = 1;
				cnt++;
			}
			v[cnt].push_back(i);
		}
	}
	memset(vis, 0, sizeof(vis));
	for(auto &i : v[1]) b[i] = i;
	for(int i=2; i<=n; i++){
		if(v[i].empty()) continue;
		if(gcd(i, k) == 1){
			for(auto &j : v[i]) proc_one(j);
		}
		else{
			int grp = -1;
			for(int j=1; j<=v[i].size(); j++){
				if(v[i].size() % j) continue;
				int T = j * i;
				if(T / gcd(T, k) == i){
					grp = j;
					break;
				}
			}
			assert(grp != -1);
			for(int j=0; j<v[i].size(); j+=grp){
				vector<int> tmp;
				for(int k=0; k<grp; k++) tmp.push_back(v[i][j+k]);
				proc_all(tmp, i);
			}
		}
	}
	for(int i=1; i<=n; i++) printf("%d\n", b[i]);
}

