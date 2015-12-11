#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>
using namespace std;
typedef long long lint;
 
struct rmq{
    int tree[132000], lim;
    void init(int n, int *a){
        for(lim = 1; lim <= n; lim <<= 1);
        memset(tree,0x3f,sizeof(tree));
        for(int i=1; i<=n; i++){
            tree[i+lim] = a[i];
        }
        for(int i=lim; i; i--){
            tree[i] = min(tree[2*i],tree[2*i+1]);
        }
    }
    int q(int s, int e){
        s += lim, e += lim;
        int ret = 1e9;
        while(s < e){
            if(s%2 == 1) ret = min(ret,tree[s++]);
            if(e%2 == 0) ret = min(ret,tree[e--]);
            s >>= 1, e >>= 1;
        }
        if(s == e) ret = min(ret,tree[s]);
        return ret;
    }
}rmq[10];
 
char buf[50005];
int a[10][50005];
int k, n;
 
struct comp{
    int arr[10];    
    int piv;
}p[50005];
 
bool cmp(comp a, comp b){
    for(int i=0; i<10; i++){
        if(a.arr[i] != b.arr[i]) return a.arr[i] < b.arr[i];
    }
    return a.piv < b.piv;
}
 
bool same(comp a, comp b){
    for(int i=0; i<10; i++){
        if(a.arr[i] != b.arr[i]) return 0;
    }
    return 1;
}
 
bool func(int s, int e){
    for(int i=0; i<k; i++){
        if(rmq[i].q(s,e) < a[i][s]) return 0;
    }
    return 1;
}
 
int main(){
    scanf("%d %d",&k,&n);
    for(int i=0; i<k; i++){
        scanf("%s",buf);
        for(int j=0; j<n; j++){
            if(buf[j] == '(') a[i][j+1] = a[i][j] + 1;
            else a[i][j+1] = a[i][j] - 1;
        }
        rmq[i].init(n, a[i]);
    }
    for(int i=1; i<=n; i++){
        for(int j=0; j<k; j++){
            p[i].arr[j] = a[j][i];
        }
        p[i].piv = i;
    }
    sort(p+1,p+n+1,cmp);
    lint ret = 0;
    for(int i=1; i<=n;){
        int e = i;
        vector<int> v;
        while(e <= n && same(p[i],p[e]) == 1){
            v.push_back(p[e].piv);
            e++;
        }
        for(int i=0; i<v.size();){
            int e = i;
            while(e < v.size() && func(v[i], v[e])){
                e++;
            }
            ret += (e - i) * (e - i - 1) / 2;
            i = e;
        }
        i = e;
    }
    printf("%lld",ret);
}