#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <limits.h>
#include <stack>
#include <queue>
#include <map>
#include <set>
#include <algorithm>
#include <string>
#include <functional>
#include <vector>
#include <numeric>
#include <deque>
#include <bitset>
#include <iostream>
using namespace std;
typedef long long lint;
typedef long double llf;
typedef pair<lint, lint> pi;
const int m1 = 1e9 + 409;
const int m2 = 1e9 + 433;
const int p = 1e8 + 7;
 
struct area{
    int minx, miny;
    lint hash1, hash2;
};
 
lint pow1[1000005], pow2[1000005];
int n, m, a[1005][1005];
 
struct disj{
    area p[1000005];
    int par[1000005];
    bool vis[1005][1005];
    void init(){
        for(int i=0; i<n; i++){
            for(int j=0; j<m; j++){
                par[i*m+j] = i*m+j;
            }
        }
    }
    int find(int x){
        return par[x] = (par[x] == x ? x : find(par[x]));
    }
    lint curr;
    map<pi, int> mp;
    void insert_hash(area x){
        int offset = n * m - 1 - x.minx * m - x.miny;
        pi t = pi(x.hash1 * pow1[offset] % m1, x.hash2 * pow2[offset] % m2);
        curr += mp[t];
        mp[t]++;
    }
    void erase_hash(area x){
        int offset = n * m - 1 - x.minx * m - x.miny;
        pi t = pi(x.hash1 * pow1[offset] % m1, x.hash2 * pow2[offset] % m2);
        curr -= mp[t]-1;
        mp[t]--;
    }
    void uni(int x, int y){
        x = find(x), y = find(y);
        if(x == y) return;
        par[y] = x;
        erase_hash(p[x]);
        erase_hash(p[y]);
        p[x].minx = min(p[x].minx, p[y].minx);
        p[x].miny = min(p[x].miny, p[y].miny);
        p[x].hash1 += p[y].hash1;
        p[x].hash2 += p[y].hash2;
        p[x].hash1 %= m1;
        p[x].hash2 %= m2;
        insert_hash(p[x]);
    }
    void activate(int i, int j){
        p[i*m+j].minx = i;
        p[i*m+j].miny = j;
        p[i*m+j].hash1 = pow1[i*m+j];
        p[i*m+j].hash2 = pow2[i*m+j];
        insert_hash(p[i*m+j]);
        vis[i][j] = 1;
        if(i && vis[i-1][j]) uni((i-1) * m + j, i*m + j);
        if(j && vis[i][j-1]) uni(i * m + j-1, i*m + j);
        if(i+1<n && vis[i+1][j]) uni((i+1) * m + j, i*m + j);
        if(j+1<m && vis[i][j+1]) uni(i*m +j+1, i*m+j);
    }
    lint query(){
        return curr;
    }
}disj;
 
int q, ls[100005];
lint ret[100005];
 
struct elem{
    int x, y, v;
    bool operator<(const elem &a)const{
        return v > a.v;
    }
}tmp[1000005];
 
int main(){
    scanf("%d %d",&n,&m);
    pow1[0] = pow2[0] = 1;
    for(int i=1; i<=n*m; i++){
        pow1[i] = pow1[i-1] * p % m1;
        pow2[i] = pow2[i-1] * p % m2;
    }
    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++){
            scanf("%d",&a[i][j]);
            tmp[i*m+j] = {i, j, a[i][j]};
        }
    }
    sort(tmp, tmp + n*m);
    disj.init();
    int p = 0;
    scanf("%d",&q);
    for(int i=0; i<q; i++){
        scanf("%d",&ls[i]);
    }
    for(int i=q-1; i>=0; i--){
        while(p < n*m && tmp[p].v > ls[i]){
            disj.activate(tmp[p].x, tmp[p].y);
            p++;
        }
        ret[i] = disj.query();
    }
    for(int i=0; i<q; i++){
        printf("%lld\n",ret[i]);
    }
}