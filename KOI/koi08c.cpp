#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <limits.h>
#include <stack>
#include <queue>
#include <map>
#include <set>
#include <algorithm>
#include <string>
#include <functional>
#include <vector>
#include <numeric>
#include <deque>
#include <bitset>
#include <iostream>
using namespace std;
typedef long long lint;
typedef long double llf;
typedef pair<int, int> pi;
const lint mod = 1e13 + 37;
 
lint get_hash(vector<int> &v){
    lint ret = 0;
    for(int i=0; i<v.size(); i++){
        ret = (ret * 5009 + v[i]) % mod;
    }
    return ret;
}
 
int comp[5005];
int n, m;
vector<int> graph[5005];
lint hval[5005];
 
set<pi> st;
int main(){
    scanf("%d %d",&n,&m);
    for(int i=0; i<m; i++){
        int s, e;
        scanf("%d %d",&s,&e);
        graph[s].push_back(e);
        graph[e].push_back(s);
    }
    vector<lint> hs;
    for(int i=1; i<=n; i++){
        graph[i].push_back(i);
        sort(graph[i].begin(), graph[i].end());
        hs.push_back(hval[i] = get_hash(graph[i]));
    }
    sort(hs.begin(), hs.end());
    hs.resize(unique(hs.begin(), hs.end()) - hs.begin());
    for(int i=1; i<=n; i++){
        comp[i] = n + 1 + lower_bound(hs.begin(), hs.end(), hval[i]) - hs.begin();
        st.insert(pi(i, comp[i]));
    }
    for(int i=1; i<=n; i++){
        for(int j=0; j<graph[i].size(); j++){
            if(comp[i] < comp[graph[i][j]]){
                st.insert(pi(comp[i], comp[graph[i][j]]));
            }
        }
    }
    printf("%d\n",st.size());
    for(set<pi> ::iterator it = st.begin(); it != st.end(); it++){
        printf("%d %d\n",it->first, it->second);
    }
}