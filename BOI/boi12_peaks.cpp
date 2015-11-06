#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;
typedef pair<int,int> pi;
 
vector<pi> res;
 
int c_hi;
int n, m;
int val[100005], num[100005], piv, notpeak[100005], reps[100005], cnt[100005];
 
struct disj{
    int pa[100005], rep[100005];
    void init(int n){
        for (int i=0; i<=n; i++){
            pa[i] = i;
        }
    }
    void set(int p, int l){
        p = find(p);
        rep[p] = l;
        cnt[p]++;
    }
    int find(int x){
        return pa[x] = (pa[x] == x ? x : find(pa[x]));
    }
    void uni(int p, int q){
        p = find(p);
        q = find(q);
        if(p == q) return;
        if(rep[p] < rep[q]) swap(p,q);
        if(rep[p] > rep[q]){
            while(cnt[q]--) res.push_back(pi(rep[q],c_hi));
        }
        if(rep[p] == rep[q]){
            cnt[p] += cnt[q];
        }
        pa[q] = p;
        find(q);
    }
}disj;
 
struct edg{int s,e,x;};
bool cmp(edg a, edg b){return a.x > b.x;}
 
vector<int> graph[100005];
vector<edg> edgs;
 
void dfs(int x){
    num[x] = piv;
    for (int i=0; i<graph[x].size(); i++) {
        if(val[x] == val[graph[x][i]] && !num[graph[x][i]]){
            dfs(graph[x][i]);
        }
    }
}
 
int main(){
    scanf("%d %d",&n,&m);
    for (int i=1; i<=n*m; i++) {
        scanf("%d",&val[i]);
    }
    for (int i=1; i<=n; i++) {
        for (int j=1; j<=m; j++) {
            if(i != n && j != m){
                int st = (i-1) * m + j;
                int ed = i * m + j+1;
                graph[st].push_back(ed);
                graph[ed].push_back(st);
                edgs.push_back((edg){st,ed,min(val[st],val[ed])});
            }
            if(i != n && j != 1){
                int st = (i-1)*m + j;
                int ed = i*m + j - 1;
                graph[st].push_back(ed);
                graph[ed].push_back(st);
                edgs.push_back((edg){st,ed,min(val[st],val[ed])});
            }
            if(i != n){
                int st = (i-1) * m + j;
                int ed = i * m + j;
                graph[st].push_back(ed);
                graph[ed].push_back(st);
                edgs.push_back((edg){st,ed,min(val[st],val[ed])});
            }
            if(j != m){
                int st = (i-1) * m + j;
                int ed = (i-1) * m + j+1;
                graph[st].push_back(ed);
                graph[ed].push_back(st);
                edgs.push_back((edg){st,ed,min(val[st],val[ed])});
            }
        }
    }
    for (int i=1; i<=n*m; i++) {
        if(!num[i]){
            piv++;
            reps[piv] = i;
            dfs(i);
        }
    }
    for (int i=0; i<edgs.size(); i++) {
        if(val[edgs[i].s] != val[edgs[i].e]){
            if(val[edgs[i].s] > val[edgs[i].e]) swap(edgs[i].s,edgs[i].e);
            notpeak[num[edgs[i].s]] = 1;
        }
    }
    disj.init(n*m);
    for (int i=1; i<=piv; i++) {
        if(!notpeak[i]) disj.set(reps[i],val[reps[i]]);
    }
    sort(edgs.begin(),edgs.end(),cmp);
    for (int i=0; i<edgs.size();) {
        int e = i;
        while (e < edgs.size() && edgs[i].x == edgs[e].x) {
            e++;
        }
        c_hi = edgs[i].x;
        for (int j=i; j<e; j++) {
            disj.uni(edgs[j].s,edgs[j].e);
        }
        i = e;
    }
    int maxp = *max_element(val+1,val+n*m+1);
    for (int i=1; i<=piv; i++) {
        if(maxp == val[reps[i]]){
            res.push_back(pi(maxp,0));
        }
    }
    sort(res.begin(),res.end());
    reverse(res.begin(),res.end());
    printf("%d\n",(int)res.size());
    for (int i=0; i<res.size(); i++) {
        printf("%d %d\n",res[i].first,res[i].second);
    }
}