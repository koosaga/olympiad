#include <cstdio>
#include <algorithm>
#include <vector>
#include <stack>
#include <deque>
using namespace std;

deque<long long> adj[105][105],key[105];
vector<int> res;

int indeg[105], outdeg[105],n;
int start;

int input(){
    long long t;
    scanf("%d",&n);
    for (int i=0; i<n; i++) {
        scanf("%lld",&t);
        indeg[t%100]++;
        outdeg[t/100000000LL]++;
        adj[t/100000000LL][t%100].push_back(t);
        key[t/100000000LL].push_back(t);
        if(i == 0) start = t / 100000000LL;
    }
    int s = -1, e = -1;
    for (int i=0; i<100; i++) {
        if(indeg[i] + 2 <= outdeg[i]){
            printf("impossible\n");
            return 1;
        }
        else if(indeg[i] + 1 == outdeg[i]){
            if(s == -1){
            	s = start = i;
           	}
            else{
                printf("impossible\n");
                return 1;
            }
        }
    }
    return 0;
}

void f(int pos){
    stack<int> s;
    s.push(pos);
    int upd = 0;
    while (!s.empty()) {
        upd = 0;
        pos = s.top();
        while (!key[pos].empty()) {
            long long r = key[pos].front()%100;
            key[pos].pop_front();
            s.push((int)r);
            upd = 1;
            break;
        }
        if(upd == 1) continue;
        s.pop();
        res.push_back(pos);
    }
}

int main(){
    if(input()) return 0;
    f(start);
    if((int)res.size() - 1 < n){
      puts("impossible");
      return 0;
    }
    reverse(res.begin(),res.end());
    for (int i=1; i<res.size(); i++) {
        printf("%010lld\n",adj[res[i-1]][res[i]].front());
        adj[res[i-1]][res[i]].pop_front();
    }
}
