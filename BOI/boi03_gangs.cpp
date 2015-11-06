#include <cstdio>
 
struct disj{
    int pa[2005], r[2005];
    void init(int n){
        for(int i=0; i<=n; i++){
            pa[i] = i;
        }
    }
    int find(int x){
        if(pa[x] == x) return x;
        else return pa[x] = find(pa[x]);
    }
    void uni(int p, int q){
        p = find(p);
        q = find(q);
        if(p == q) return;
        if(r[p] < r[q]) pa[q] = p;
        else pa[p] = q;
        if(r[p] == r[q]) r[p]++;
    }
}disj;
 
int n,m;
int v[2005];
 
int main(){
    scanf("%d %d",&n,&m);
    disj.init(2*n);
    for (int i=0; i<m; i++) {
        char str[10];
        int x,y;
        scanf("%s %d %d\n",str,&x,&y);
        if(str[0] == 'F'){
            disj.uni(x,y);
        }
        else{
            disj.uni(x,y+n);
            disj.uni(x+n,y);
        }
    }
    int cnt = 0;
    for (int i=1; i<=n; i++) {
        int j = disj.find(i);
        if(v[j] == 0){
            v[j] = 1;
            cnt++;
        }
    }
    printf("%d",cnt);
}