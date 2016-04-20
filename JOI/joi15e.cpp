#include <cstdio>
#include <cstring>
#include <algorithm>
#include <utility>
#include <vector>
using namespace std;
typedef pair<int,int> pi;
 
int p[4005][4005];
int n,m,l;
 
int low[4005][4005], high[4005][4005];
 
void make_table(){
    int t;
    scanf("%d %d %d %d",&n,&m,&l,&t);
    while (t--) {
        int x,y;
        scanf("%d %d",&x,&y);
        p[x][y] = 1;
    }
    for (int i=1; i<=n; i++) {
        int q = 0;
        for (int j=m; j; j--) {
            if(p[i][j] == 1) q = 0;
            else q++;
            low[i][j] = q;
        }
    }
    for (int i=1; i<=m; i++) {
        int q = 0;
        for (int j=n; j; j--) {
            if(p[j][i] == 1) q = 0;
            else q++;
            low[j][i] = min(low[j][i],q);
        }
    }
    for (int i=1; i<=n; i++) {
        int q = 0;
        for (int j=1; j<=m; j++) {
            if(p[i][j] == 1) q = 0;
            else q++;
            high[i][j] = q;
        }
    }
    for (int i=1; i<=m; i++){
        int q = 0;
        for (int j=1; j<=n; j++){
            if(p[j][i] == 1) q = 0;
            else q++;
            high[j][i] = min(high[j][i],q);
        }
    }
}
 
struct bit{
    int tree[4096], lim;
    void init(int n){
        for(lim = 1; lim <= n+4; lim <<= 1);
        memset(tree,0,sizeof(tree));
    }
    void add(int x, int v){
        x+=3;
        while(x <= lim){
            tree[x] += v;
            x += x & -x;
        }
    }
    int sum(int x){
        x+=3;
        int r = 0;
        while(x){
            r += tree[x];
            x -= x & -x;
        }
        return r;
    }
}bit;
 
int solve(int *a, int *b, int size){
    vector<pi> v;
    for (int i=0; i<size; i++) {
        v.push_back(pi(a[i],i));
    }
    sort(v.begin(),v.end());
    bit.init(size);
    int ret = 0;
    for (int i=0; i<size; i++) {
        while (!v.empty() && v.back().first >= 1 - i) {
            bit.add(v.back().second,1);
            v.pop_back();
        }
        if(min(size,i+b[i]) - 1 >= i + l - 2)
            ret += bit.sum(min(size,i+b[i]) - 1) - bit.sum(i+l-2);
    }
    return ret;
}
 
int main(){
    make_table();
    long long ret = 0;
    for (int i=1; i<=n; i++) {
        int a[4005] = {}, b[4005] = {}, size = 0;
        for (int j=0; i+j <= n && j+1 <= m; j++) {
            a[j] = high[i+j][j+1] - j;
            b[j] = low[i+j][j+1];
            size++;
        }
        ret += solve(a,b,size);
    }
    for (int i=2; i<=m; i++) {
        int a[4005] = {}, b[4005] = {}, size = 0;
        for (int j=0; j+1 <= n && i+j <= m; j++) {
            a[j] = high[j+1][i+j] - j;
            b[j] = low[j+1][i+j];
            size++;
        }
        ret += solve(a,b,size);
    }
    printf("%lld",ret);
}