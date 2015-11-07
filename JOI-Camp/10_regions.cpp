#include <stdio.h>#include <vector>
#include <algorithm>
#include <utility>
using namespace std;
typedef pair<int,int> pi;

vector<pi> graph[30005];
int n,m;

int cnt, lim;

int dp(int x, int pa){
    vector<int> cand;
    for (auto &i : graph[x]){
        if(i.first != pa) cand.push_back(dp(i.first,x) + i.second);
    }
    if(cand.empty()) return 0;
    cand.push_back(0);
    sort(cand.begin(),cand.end());
    while(cand.size() >= 2){
        if(cand.back() + cand[cand.size()-2] > lim){
            cand.pop_back();
            cnt++;
        }
        else break;
    }
    return cand.back();
}

bool trial(int x){
    cnt = 0;
    lim = x;
    dp(1,0);
    return cnt < m;
}

int main(){
    scanf("%d %d",&n,&m);
    for (int i=0; i<n-1; i++) {
        int x,y,c;
        scanf("%d %d %d",&x,&y,&c);
        graph[x].push_back(pi(y,c));
        graph[y].push_back(pi(x,c));
    }
    int s = 0, e = 3e6;
    while (s != e) {
        int m = (s+e)/2;
        if(trial(m)) e = m;
        else s = m+1;
    }
    printf("%d\n",s);
}