#include <cstdio>
#include <cstring>
#include <algorithm>
#include <map>
#include <utility>
#include <vector>
using namespace std;
typedef pair<int,int> pi;
 
char str[600005];
int n;
int dp[600005];
 
void manacher(){
    int max_val = 0, pos = 0;
    for (int i=1; i<=n; i++) {
        int ret = i;
        if(max_val >= i){
            ret = min(max_val,i + dp[2 * pos - i]);
        }
        while (ret+1<=n && 2*i-ret-1> 0 && str[ret+1] == str[2*i-ret-1]){
            ret++;
        }
        dp[i] = ret - i;
        if(ret > max_val){
            pos = i, max_val = ret;
        }
    }
    for (int i=1; i<=n; i++) {
        if(i%2 == 0) dp[i]++;
        dp[i] /= 2;
    }
}
 
const int prime = 811;
const long long mod = 1e15 + 811;
long long hs[300005], pw[300005];
 
long long gob(long long b1, long long b2){
    long long r = 0;
    while (b1) {
        r += b2 * (b1 & 4095);
        b2 <<= 12;
        b1 >>= 12;
        b2 %= mod;
        r %= mod;
    }
    return r;
}
 
long long get_hash(int s, int e){
    if(s > e) return 0;
    return ((hs[e] - gob(hs[s-1],pw[e - s + 1])) % mod + mod) % mod;
}
 
map<long long,int> num;
int piv;
 
int tpar[300005], tcnt[300005], tlen[300005];
vector<int> graph[300005];
int subsize[300005];
long long ret;
 
void shrink(int s, int e, long long pa){
    if(s > e) return;
    long long par = 0;
    num[0] = 0;
    int st = 1;
    while (s <= e) {
        long long hsh = get_hash(s,e);
        int npar = num[par], nhsh = 0;
        if(num.find(hsh) != num.end()){
            nhsh = num[hsh];
            if(par){
                graph[npar].push_back(nhsh);
                graph[nhsh].push_back(npar);
            }
            if(st){
                tcnt[nhsh]++;
            }
            break;
        }
        nhsh = num[hsh] = ++piv;
        if(par){
            graph[npar].push_back(nhsh);
            graph[nhsh].push_back(npar);
        }
        if(st){
            tcnt[nhsh]++;
            st = 0;
        }
        tlen[nhsh] = e - s + 1;
        par = hsh;
        s++;
        e--;
    }
    if(s > e){
        graph[0].push_back(num[par]);
        graph[num[par]].push_back(0);
    }
}
 
int dfs(int x, int pa){
    int r = tcnt[x];
    for (int i=0; i<graph[x].size(); i++) {
        if(graph[x][i] == pa) continue;
        r += dfs(graph[x][i],x);
    }
    ret = max(ret,1ll * r * tlen[x]);
    return r;
}
 
int main(){
    num[0] = 0;
    scanf("%s",str);
    n = (int)strlen(str);
    for (int i=n-1; i>=0; i--) {
        str[2*i+1] = str[i];
        str[2*i] = ' ';
    }
    n = 2 * n - 1;
    str[0] = 0;
    manacher();
    pw[0] = 1;
    for (int i=1; i<=(n+1)/2; i++) {
        hs[i] = (hs[i-1] * prime + str[2*i-1]) % mod;
        pw[i] = pw[i-1] * prime % mod;
    }
    for (int i=1; i<=n; i++) {
        if(i % 2 == 1){
            shrink((i+1)/2 - dp[i],(i+1)/2 + dp[i],0);
        }
        else{
            shrink(i/2 + 1 - dp[i], i/2 + dp[i],0);
        }
    }
    dfs(0,-1);
    printf("%lld",ret);
}