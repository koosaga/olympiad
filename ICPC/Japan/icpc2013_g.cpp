#include <cstdio>
#include <map>
#include <algorithm>
using namespace std;
 
int n;
 
struct tup{
    int x, y, z;
}a[300005];
 
map<int,int> mp[300005];
int dp[300005];
 
bool input(){
    int m, nn, A, B;
    scanf("%d %d %d %d",&m,&nn,&A,&B);
    if(m + nn + A + B == 0) return 0;
    n = m + nn;
    for(int i=1; i<=m; i++){
        scanf("%d %d %d",&a[i].x,&a[i].y,&a[i].z);
    }
    int a = A, b = B, C = ~(1<<31), M = (1<<16)-1;
    for(int i=m+1; i<=n; i++){
      a = 36969 * (a & M) + (a >> 16);
      b = 18000 * (b & M) + (b >> 16);
      ::a[i].x = (C & ((a << 16) + b)) % 1000000;
      a = 36969 * (a & M) + (a >> 16);
      b = 18000 * (b & M) + (b >> 16);
      ::a[i].y = (C & ((a << 16) + b)) % 1000000;
      a = 36969 * (a & M) + (a >> 16);
      b = 18000 * (b & M) + (b >> 16);
      ::a[i].z = (C & ((a << 16) + b)) % 1000000;
    }
    for(int i=0; i<=n; i++){
        mp[i].clear();
    }
    return 1;
}
 
bool trial(int m, int y, int z){
    auto it = mp[m].lower_bound(y);
    if(it == mp[m].begin()) return 0;
    it--;
    return (z > it->second);
}
 

void add(int x, int y, int z){
	auto it = mp[x].lower_bound(y);
	auto it2 = mp[x].upper_bound(y);
	if(it2 != mp[x].begin()){
		it2--;
		if(it2->second <= z) return;
	}
	while(it != mp[x].end() && it->second >= z){
		mp[x].erase(it);
		it = mp[x].lower_bound(y);
	}
	mp[x].insert(make_pair(y, z));
}

void solve(){
    sort(a + 1, a + n + 1, [&](const tup &a, const tup &b){
        return a.x < b.x;
    });
    mp[0].insert(make_pair(-1, -1));
    for(int i=1; i<=n;){
        int e = i;
        while(e <= n && a[e].x == a[i].x) e++;
        for(int j=i; j<e; j++){
            int s = 0, e = i;
            while(s != e){
                int m = (s+e+1) / 2;
                if(trial(m, a[j].y, a[j].z)) s = m;
                else e = m-1;
            }
            dp[j] = s + 1;
        }
        for(int j=i; j<e; j++){
            add(dp[j], a[j].y, a[j].z);
        }
        i = e;
    }
    printf("%d\n",*max_element(dp+1,dp+n+1));
}
 
int main(){
    while(input()){
        solve();
    }
}
