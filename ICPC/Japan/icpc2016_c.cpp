#include<bits/stdc++.h>
using namespace std;
const int MAXN = 200005;

int n;
int l[MAXN], r[MAXN];
int p[MAXN];

int main(){
    scanf("%d",&n);
    int m;
    scanf("%d",&m);
    while(m--){
        int x, y;
        scanf("%d %d",&x,&y);
        p[x] = y;
    }
    for(int i=1; i<=n; i++){
        l[i] = r[i] = i;
    }
    for(int i=1; i<100000; i++){
        if(p[i]){
            int lv = min(l[p[i]], l[p[i] + 1]);
            int rv = max(r[p[i]], r[p[i] + 1]);
            l[p[i]] = l[p[i] + 1] = lv;
            r[p[i]] = r[p[i] + 1] = rv;
        }
    }
    for(int i=1; i<=n; i++) printf("%d ", r[i] - l[i] + 1);
}
