#include <cstdio>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;
typedef pair<int,int> pi;
 
vector<int> graph[300005];
int n, k, ord[300005], piv, dfn[300005];
 
pi up[300005];
int low[300005];
int pmax[300005];
pi v[300005];
 
int main(){
    scanf("%d %d",&n,&k);
    for (int i=0; i<n-1; i++) {
        int u,v;
        scanf("%d %d",&u,&v);
        graph[u].push_back(v);
        graph[v].push_back(u);
    }
    queue<int> q,d;
    q.push(1);
    d.push(0);
    while (!q.empty()) {
        int qf = q.front(), df = d.front();
        q.pop(), d.pop();
        ord[++piv] = qf;
        dfn[qf] = piv;
        for (int i=0; i<graph[qf].size(); i++) {
            if(graph[qf][i] == df) continue;
            q.push(graph[qf][i]);
            d.push(qf);
        }
    }
    for (int i=n; i>=1; i--) {
        int pos = ord[i];
        int sum = 0;
        pi ret(0,0);
        for (int j=0; j<graph[pos].size(); j++) {
            if(dfn[graph[pos][j]] < i) continue;
            sum += low[graph[pos][j]];
            pi tmp = up[graph[pos][j]];
            if(tmp.second == k){
                tmp.second = 0;
                tmp.first++;
            }
            tmp.second++;
            tmp.first -= low[graph[pos][j]];
            ret = min(ret,tmp);
        }
        ret.first += sum;
        up[pos] = ret;
        low[pos] = sum + 1;
         
        for (int j=0; j<graph[pos].size(); j++) {
            if(dfn[graph[pos][j]] < i){
                v[j] = pi(-1,0);
                continue;
            }
            int p2 = graph[pos][j];
            v[j] = pi(up[p2].second,low[p2] - up[p2].first);
        }
        sort(v,v+graph[pos].size());
        pmax[0] = v[0].second;
        for (int i=1; i<graph[pos].size(); i++) {
            pmax[i] = max(pmax[i-1],v[i].second);
        }
        int w1 = (int)graph[pos].size(), w2 = (int)graph[pos].size();
        for (int j=1; j<graph[pos].size(); j++) {
            low[pos] = min(low[pos],sum - v[j].second - pmax[j-1] + 3);
            while (w1 > 0 && v[w1-1].first >= 2 * k - v[j].first) {
                w1--;
            }
            if(w1 != 0){
                low[pos] = min(low[pos],sum - v[j].second - pmax[min(w1-1,j-1)] + 2);
            }
            while (w2 > 0 && v[w2-1].first >= k - 1 - v[j].first ) {
                w2--;
            }
            if(w2 != 0){
                low[pos] = min(low[pos],sum - v[j].second - pmax[min(w2-1,j-1)] + 1);
            }
        }
    }
    printf("%d",min(up[1].first + 1, low[1]));
}