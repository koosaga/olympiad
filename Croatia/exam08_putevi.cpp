#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;
const int mod = 1e9 + 7;
typedef pair<int,int> pi;
typedef long long lint;
 
vector<pi> graph[100005];
int n;
 
lint ret;
 
lint f(int x, int pa){
    vector<lint> dsum;
    dsum.push_back(1);
    for(auto &i : graph[x]){
        if(i.second == pa) continue;
        dsum.push_back((1ll * i.first * f(i.second, x) % mod));
    }
    lint sum = 0;
    lint dx = 0;
    for(auto &i : dsum){
        sum += i;
        sum %= mod;
        dx -= i * i % mod;
    }
    dx += sum * sum % mod;
    dx %= mod;
    dx += mod;
    dx %= mod;
    dx *= (mod + 1) / 2;
    dx %= mod;
    ret += dx;
    ret %= mod;
    return sum;
}
 
int main(){
    scanf("%d",&n);
    for(int i=0; i<n-1; i++){
        int u, v, d;
        scanf("%d %d %d",&u,&v,&d);
        graph[u].push_back(pi(d,v));
        graph[v].push_back(pi(d,u));
    }
    f(1,0);
    printf("%lld",ret);
}