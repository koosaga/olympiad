#include <cstdio>
#include <algorithm>
#include <queue>
using namespace std;
typedef long long lint;

struct sum{
    int tree[270000], lim;
    void init(int n){
        for(lim = 1; lim <= n; lim <<= 1);
        for(int i=1; i<=n; i++){
            tree[i+lim] = 2;
        }
        for(int i=lim; i; i--){
            tree[i] = tree[2*i] + tree[2*i+1];
        }
    }
    void add(int x, int v){
        x += lim;
        tree[x] += v;
        while(x > 1){
            x >>= 1;
            tree[x] = tree[2*x] + tree[2*x+1];
        }
    }
    int q(int s, int e){
        s += lim;
        e += lim;
        int ret = 0;
        while(s < e){
            if(s%2 == 1) ret += tree[s++];
            if(e%2 == 0) ret += tree[e--];
            s >>= 1; e >>= 1;
        }
        if(s == e) ret += tree[s];
        return ret;
    }
}sum;

int n, m, a, b;
int occu[100005][6];

void input(int &x, int &y){
    char str[10];
    scanf("%s",str);
    x = 0;
    for(int i=0; str[i]; i++){
        if(str[i] <= '9' && str[i] >= '0') x = 10 * x + str[i] - '0';
        else y = str[i] - 'A';
    }
}

priority_queue<int, vector<int>, greater<int> > pq;

lint member(int x){
    return 1ll * b * x * (x-1) / 2;
}

int main(){
    scanf("%d %d %d %d",&n,&m,&a,&b);
    sum.init(n);
    for(int i=1; i<=n; i++){
        fill(occu[i], occu[i] + 6, 1);
    }
    lint cost = 0;
    for(int i=0; i<m; i++){
        int p, q;
        input(p, q);
        occu[p][q] = 0;
        if(q == 2 || q == 3) sum.add(p, -1);
        if(q == 5 && occu[p][4]) cost += a;
        if(q == 0 && occu[p][1]) cost += a;
        cost += 1ll * a * sum.q(1, p);
        pq.push(sum.q(p+1, n) - sum.q(1, p-1));
    }
    lint mincost = cost + member(m) + member(0);
    for(int i=1; i<=m; i++){
        cost += 1ll * a * pq.top();
        pq.pop();
        mincost = min(mincost, cost + member(i) + member(m - i));
    }
    printf("%lld",mincost);
}