#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;
typedef pair<int,int> pi;
typedef long long lint;

int n, m, q;
vector<int> coo;

int a[100005], b[100005], v[100005];
int x[100005], y[100005];
lint j[100005];

struct seq{int px, py, v;}arr[200005];

struct range_tree{
    lint query_res;
    int cnt_res;
    int seg_res;
    int lim;
    vector<int> tree[270000];
    vector<lint> psum[270000];
    void init(int n){
        for(lim = 1; lim <= n; lim <<= 1);
        for(int i=1; i<=2*lim; i++){
            sort(tree[i].begin(), tree[i].end());
            psum[i].resize(tree[i].size());
            for(int j=0; j<tree[i].size(); j++){
                psum[i][j] += tree[i][j];
                if(j) psum[i][j] += psum[i][j-1];
            }
        }
    }
    void add(int x, int v){
        x += lim;
        tree[x].push_back(v);
        while(x > 1){
            x >>= 1;
            tree[x].push_back(v);
        }
    }
    long long solve(int s, int e, int x){
        s += lim;
        e += lim;
        query_res = 0;
        cnt_res = 0;
        seg_res = 0;
        while(s < e){
            if(s%2 == 1){
                int pos = (int)(upper_bound(tree[s].begin(), tree[s].end(), x) - tree[s].begin());
                if(pos){
                    cnt_res += pos;
                    query_res += psum[s][pos-1];
                }
                seg_res += tree[s].size();
                s++;
            }
            if(e%2 == 0){
                int pos = (int)(upper_bound(tree[e].begin(), tree[e].end(), x) - tree[e].begin());
                if(pos){
                    cnt_res += pos;
                    query_res += psum[e][pos-1];
                }
                seg_res += tree[e].size();
                e--;
            }
            s >>= 1;
            e >>= 1;
        }
        if(s == e){
            int pos = (int)(upper_bound(tree[e].begin(), tree[e].end(), x) - tree[e].begin());
            if(pos){
                cnt_res += pos;
                query_res += psum[e][pos-1];
            }
            seg_res += tree[e].size();
        }
        return query_res + 1ll * (seg_res - cnt_res) * x;
    }
}rtree1, rtree2;

long long trial(int x, int y){
    return rtree1.solve(0,x,y) - rtree2.solve(0,x,y);
    //for(int i=0; i<2*m; i++){
    //  arr[2*i] = {v[i], a[i] - 1, -1};
    //  arr[2*i+1] = {v[i], b[i], 1};
    //  if(arr[i].px > x) break;
    //  ret += arr[i].v * min(arr[i].py, y);
    //}
}

int main(){
    scanf("%d %d %d",&n,&m,&q);
    for(int i=0; i<m; i++){
        scanf("%d %d %d",&a[i],&b[i],&v[i]);
        coo.push_back(v[i]);
    }
    sort(coo.begin(), coo.end());
    coo.resize(unique(coo.begin(), coo.end()) - coo.begin());
    for(int i=0; i<m; i++){
        v[i] = (int)(lower_bound(coo.begin(), coo.end(), v[i]) - coo.begin());
    }
    rtree1.init(m);
    rtree2.init(m);
    for(int i=0; i<m; i++){
        rtree1.add(v[i], b[i]);
        rtree2.add(v[i], a[i] - 1);
    }
    rtree1.init(m);
    rtree2.init(m);
    for(int i=0; i<q; i++){
        scanf("%d %d %lld",&x[i],&y[i],&j[i]);
        int s = 0, e = (int)coo.size() - 1;
        while(s != e){
            int m = (s+e)/2;
            if(trial(m, y[i]) - trial(m, x[i] - 1) < j[i]){
                s = m+1;
            }
            else e = m;
        }
        printf("%d\n",coo[s]);
    }
}
