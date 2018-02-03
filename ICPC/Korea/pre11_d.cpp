#include <cstdio>
#include <queue>
#include <cstring>
using namespace std;

int par[10005];
char ops[10005];
bool vis[10005];

queue<int> q;

int D(int x){ return 2 * x % 10000; }
int S(int x){ return (x + 9999) % 10000; }
int L(int x){ return (x % 1000) * 10 + x / 1000; }
int R(int x){ return x / 10 + 1000 * (x % 10); }

void solve(){
    int s, e;
    scanf("%d %d",&s,&e);
    memset(vis,0,sizeof(vis));
    q.push(s);
    while(!q.empty()){
        int qf = q.front();
        if(qf == e) break;
        q.pop();
        if(!vis[D(qf)]){
            int x = D(qf);
            vis[x] = 1;
            par[x] = qf;
            ops[x] = 'D';
            q.push(x);
        }
        if(!vis[S(qf)]){
            int x = S(qf);
            vis[x] = 1;
            par[x] = qf;
            ops[x] = 'S';
            q.push(x);
        }
        if(!vis[L(qf)]){
            int x = L(qf);
            vis[x] = 1;
            par[x] = qf;
            ops[x] = 'L';
            q.push(x);
        }
        if(!vis[R(qf)]){
            int x = R(qf);
            vis[x] = 1;
            par[x] = qf;
            ops[x] = 'R';
            q.push(x);
        }
    }
    int sz = 0;
    char stk[10005] = {};
    while(e != s){
        stk[sz++] = ops[e];
        e = par[e];
    }
    while(sz){
        putchar(stk[--sz]);
    }
    puts("");
}

int main(){
    int t;
    scanf("%d",&t);
    while(t--){
        solve();
        while(!q.empty()) q.pop();
    }
}