#include <cstdio>
#include <algorithm>
#include <vector>
#include <utility>
#include <set>
using namespace std;
typedef pair<int,int> pi;

struct disj{
    int pa[200005], l[200005], r[200005];
    void init(int n, int m){
        for(int i=0; i<=n+m; i++) pa[i] = i;
        for(int i=0; i<=n; i++) l[i] = 1e9, r[i] = -1e9;
        for(int i=n+1; i<=n+m; i++) l[i] = r[i] = i;
    }
    int find(int x){
        if(x == pa[x]) return x;
        return pa[x] = find(pa[x]);
    }
    void uni(int p, int q){
        p = find(p);
        q = find(q);
        pa[q] = p;
        l[p] = min(l[p],l[q]);
        r[p] = max(r[p],r[q]);
    }
}disj1, disj2;

struct seg{int s,e,x;};
struct edg{int s,e,x;};

vector<seg> seg;
vector<pi> tree1, tree2;

int n,m1,m2,q;
int y1[200005], y2[200005];
int between1[200005], between2[200005];

bool cmp1(pi a, pi b){
    return max(y1[a.first],y1[a.second]) < max(y1[b.first],y1[b.second]);
}

bool cmp2(pi a, pi b){
    return max(y2[a.first],y2[a.second]) < max(y2[b.first],y2[b.second]);
}

bool cmp3(pi a, pi b){
    return a.first != b.first ? (a.first < b.first) : (a.second > b.second);
}

bool cmp4(int a, int b){
    return between1[a] < between1[b];
}

multiset<int> s;
vector<pi> sweep;
vector<pi> ret;

void segmentize1(){
    disj1.init(m1,n);
    for (int i=0; i<tree1.size(); i++) {
        disj1.uni(tree1[i].first,tree1[i].second);
        int t = disj1.find(tree1[i].first);
        int p = max(y1[tree1[i].first],y1[tree1[i].second]);
        if(disj1.l[t] < disj1.r[t]){
            seg.push_back({disj1.l[t]-m1,disj1.r[t]-m1,p});
        }
    }
    for (int i=0; i<seg.size(); i++) {
        sweep.push_back(pi(seg[i].s,seg[i].x));
        sweep.push_back(pi(seg[i].e,-seg[i].x));
    }
    sort(sweep.begin(),sweep.end(),cmp3);
    int p = 0;
    for (int i=1; i<n; i++) {
        while (p < sweep.size() && sweep[p].first == i) {
            if(sweep[p].second > 0) s.insert(sweep[p].second);
            else s.erase(s.find(-sweep[p].second));
            p++;
        }
        between1[i] = *s.begin();
    }
}

void segmentize2(){
    s.clear();
    sweep.clear();
    seg.clear();
    disj2.init(m2,n);
    for (int i=0; i<tree2.size(); i++) {
        disj2.uni(tree2[i].first,tree2[i].second);
        int t = disj2.find(tree2[i].first);
        int p = max(y2[tree2[i].first],y2[tree2[i].second]);
        if(disj2.l[t] < disj2.r[t]){
            seg.push_back({disj2.l[t]-m2,disj2.r[t]-m2,p});
        }
    }
    for (int i=0; i<seg.size(); i++) {
        sweep.push_back(pi(seg[i].s,seg[i].x));
        sweep.push_back(pi(seg[i].e,-seg[i].x));
    }
    sort(sweep.begin(),sweep.end(),cmp3);
    int p = 0;
    for (int i=1; i<n; i++) {
        while (p < sweep.size() && sweep[p].first == i) {
            if(sweep[p].second > 0) s.insert(sweep[p].second);
            else s.erase(s.find(-sweep[p].second));
            p++;
        }
        between2[i] = *s.begin();
    }
}

void input(){
    int t;
    scanf("%d %d %d %d",&n,&m1,&m2,&q);
    for (int i=1; i<=m1; i++) {
        scanf("%d %d",&t,&y1[i]);
    }
    for (int i=0; i<n+m1-1; i++) {
        int p,q,r;
        scanf("%d %d %d",&p,&q,&r);
        if(p == 1){
            tree1.push_back(pi(q+m1,r));
        }
        else{
            tree1.push_back(pi(q,r));
        }
    }
    for (int i=1; i<=m2; i++) {
        scanf("%d %d",&t,&y2[i]);
        y2[i] = -y2[i];
    }
    for (int i=0; i<n+m2-1; i++) {
        int p,q,r;
        scanf("%d %d %d",&p,&q,&r);
        if(p == 1){
            tree2.push_back(pi(q+m2,r));
        }
        else{
            tree2.push_back(pi(q,r));
        }
    }
    sort(tree1.begin(),tree1.end(),cmp1);
    sort(tree2.begin(),tree2.end(),cmp2);
}

int idx[100005];

void solve(){
    sweep.clear();
    for (int i=1; i<n; i++){
        idx[i] = i;
    }
    sort(idx+1,idx+n,cmp4);
    for (int i=n-2; i; i--) {
        between2[idx[i]] = max(between2[idx[i]],between2[idx[i+1]]);
    }
}

void query(){
    while (q--) {
        int t;
        scanf("%d",&t);
        int s = 1, e = n;
        while (s != e) {
            int m = (s+e)/2;
            if(t < between1[idx[m]]) e = m;
            else s = m+1;
        }
        printf("%d\n",-between2[idx[s]]);
    }
}

int main(){
    input();
    segmentize1();
    segmentize2();
    solve();
    query();
}