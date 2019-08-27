/**
 * Author:
 * Description: Counts 3 and 4 cycles
 */
#include <bits/stdc++.h>
using namespace std;

#define P 1000000007
#define N 110000

int n, m;
vector <int> go[N], lk[N];

int w[N];
int circle3(){ /// start-hash
	int ans=0;
	for (int i = 1; i <= n; i++)
		w[i]=0;

	for (int x = 1; x <= n; x++) {
		for(int y:lk[x])w[y]=1;

		for(int y:lk[x])for(int z:lk[y])if(w[z]){
			ans=(ans+go[x].size()+go[y].size()+go[z].size()-6)%P;
		}

		for(int y:lk[x])w[y]=0;
	}
	return ans;
} /// end-hash

int deg[N], pos[N], id[N];

int circle4(){ /// start-hash
	for (int i = 1; i <= n; i++)
		w[i]=0;
	int ans=0;
	for (int x = 1; x <= n; x++) {
		for(int y:go[x])for(int z:lk[y])if(pos[z]>pos[x]){
			ans=(ans+w[z])%P;
			w[z]++;
		}
		for(int y:go[x])for(int z:lk[y])w[z]=0;
	}
	return ans;
} /// end-hash

inline bool cmp(const int &x,const int &y){
	return deg[x]<deg[y];
}

void init() {
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++)
		deg[i] = 0, go[i].clear(), lk[i].clear();;
	while (m--) {
		int a,b;
		scanf("%d%d",&a,&b);
		deg[a]++;deg[b]++;
		go[a].push_back(b);go[b].push_back(a);
	}
	for (int i = 1; i <= n; i++)
		id[i] = i;
	sort(id+1,id+1+n,cmp);
	for (int i = 1; i <= n; i++) pos[id[i]]=i;
	for (int x = 1; x <= n; x++)
		for(int y:go[x])
			if(pos[y]>pos[x])lk[x].push_back(y);
}
