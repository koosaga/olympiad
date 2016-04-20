#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

struct disj{
    int pa[250005], sz[250005];
    void init(int n){
        for(int i=0; i<=n; i++) pa[i] = i, sz[i] = 1;
    }
    int find(int x){
        return pa[x] = (pa[x] == x ? x : find(pa[x]));
    }
    void uni(int p, int q){
        p = find(p);
        q = find(q);
        if(p == q) return;
        pa[q] = p;
        sz[p] += sz[q];
    }
}disj;

int a1[100005], a2[100005]; // a1[i] -> minimum cost to achieve so

int n,m,s,e,r;
int arr[505][505];

struct edg{int s,e,x;};
bool cmp(edg a, edg b){return a.x < b.x;}
vector<edg> v;

void solve(int *a){
    v.clear();
    scanf("%d %d %d %d",&m,&n,&e,&s);
    for (int i=0; i<n; i++) {
        for (int j=0; j<m; j++) {
            scanf("%d",&arr[i][j]);
        }
    }
    s--;
    e--;
    s = s * m + e;
    disj.init(n*m);
    for (int i=0; i<n; i++) {
        for (int j=0; j<m; j++) {
            if(j != m-1){
                v.push_back({i*m+j,i*m+j+1,max(arr[i][j],arr[i][j+1])});
            }
            if(i != n-1){
                v.push_back({i*m+j,i*m+j+m,max(arr[i][j],arr[i+1][j])});
            }
        }
    }
    sort(v.begin(),v.end(),cmp);
    a[1] = 1;
    int prev_pos = 2;
    for (int i=0; i<v.size(); ) {
        int e = i;
        while (e < v.size() && v[e].x == v[i].x) {
            e++;
        }
        for (int j=i; j<e; j++) {
            disj.uni(v[j].s,v[j].e);
        }
        int piv = disj.sz[disj.find(s)];
        for (int j=prev_pos; j<=piv && j <= r+1; j++) {
            a[j] = v[i].x;
        }
        prev_pos = piv+1;
        if(prev_pos > r) return;
        i = e;
    }
    for (int j=prev_pos; j<=r; j++) {
        a[j] = 1e9;
    }
}

int main(){
    scanf("%d",&r);
    solve(a1);
    solve(a2);
    int ret = 1e9;
    for (int i=0; i<=r; i++) {
        ret = min(ret,a1[i] + a2[r-i]);
    }
    printf("%d",ret);
}