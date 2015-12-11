#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;
typedef pair<int,int> pi;
 
struct disj{
    int pa[250005];
    int procsize[250005];
    int size[250005];
    void init(int n){
        for(int i=0; i<=n; i++) pa[i] = i, size[i] = 1;
    }
    int find(int x){
        return pa[x] = (pa[x] == x ? x : find(pa[x]));
    }
    bool uni(int p, int q){
        p = find(p), q = find(q);
        if(p == q) return 0;
        procsize[p] += procsize[q];
        size[p] += size[q];
        pa[q] = p;
        find(q);
        return 1;
    }
}disj;
 
struct edg{int s, e, x;};
vector<edg> v;
 
int n, m, a[505][505], p;
 
int pos(int x, int y){
    return (x-1) * m + y;
}
 
int main(){
    scanf("%d %d %d",&n,&m,&p);
    for(int i=1; i<=n; i++){
        for(int j=1; j<=m; j++){
            scanf("%d",&a[i][j]);
            if(j != 1){
                v.push_back({pos(i,j), pos(i,j-1), abs(a[i][j] - a[i][j-1])});
            }
            if(i != 1){
                v.push_back({pos(i,j), pos(i-1,j), abs(a[i][j] - a[i-1][j])});
            }
        }
    }
    disj.init(n * m);
    sort(v.begin(), v.end(), [&](const edg &a, const edg &b){return a.x < b.x;});
    for(int i=1; i<=n; i++){
        for(int j=1; j<=m; j++){
            int t;
            scanf("%d",&t);
            if(t == 1){
                disj.procsize[pos(i,j)]++;
            }
        }
    }
    long long ret = 0;
    for(auto &i : v){
        if(disj.uni(i.s, i.e)){
            int fnd = disj.find(i.s);
            if(disj.size[fnd] >= p){
                ret += 1ll * i.x * disj.procsize[fnd];
                disj.procsize[fnd] = 0;
            }
        }
    }
    printf("%lld",ret);
}