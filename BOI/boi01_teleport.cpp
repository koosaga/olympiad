#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;
 
int n, m, a[50005], b[50005];
int nxt[100005], vis[100005], deg[100005];
 
queue<int> q, d;
 
char s1[50005], s2[50005];
 
void set(int x, char t){
    if(x > n) s2[x-n-1] = t;
    else s1[x-1] = t;
}
 
int main(){
    scanf("%d %d",&n,&m);
    for (int i=1; i<=n; i++) {
        scanf("%d",&a[i]);
        nxt[i] = a[i] + n;
        deg[a[i]+n]++;
    }
    for (int i=1; i<=m; i++) {
        scanf("%d",&b[i]);
        nxt[i+n] = b[i];
        deg[b[i]]++;
    }
    for (int i=1; i<=n+m; i++){
        if(deg[i] == 0){
            q.push(i);
            d.push(1);
            vis[i] = 1;
        }
    }
    fill(s1,s1+n,'1');
    fill(s2,s2+m,'0');
    while (!q.empty()) {
        int qf = q.front();
        q.pop();
        int df = d.front();
        d.pop();
        set(qf,df + '0');
        deg[nxt[qf]]--;
        if(df == 1 && !vis[nxt[qf]]){
            vis[nxt[qf]] = 1;
            q.push(nxt[qf]);
            d.push(0);
        }
        if(deg[nxt[qf]] == 0 && !vis[nxt[qf]]){
            vis[nxt[qf]] = 1;
            q.push(nxt[qf]);
            d.push(1);
        }
    }
    puts(s1);
    puts(s2);
}