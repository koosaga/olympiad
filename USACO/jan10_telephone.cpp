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
#include <utility>
#include <bitset>
#include <iostream>
using namespace std;
typedef long long lint;
typedef long double llf;
typedef pair<int, int> pi;
 
int n, k, r;
vector<int> graph[100005];
 
int f(int x, int p){
    if(graph[x].size() == 1) return 1;
    int ret = 0;
    for(auto &i : graph[x]){
        if(i != p) ret += f(i, x);
    }
    if(ret >= 2 * k){
        r += k;
        return 0;
    }
    r += ret / 2;
    return ret % 2;
}
 
int main(){
    scanf("%d %d",&n,&k);
    for(int i=0; i<n-1; i++){
        int s, e;
        scanf("%d %d",&s,&e);
        graph[s].push_back(e);
        graph[e].push_back(s);
    }
    for(int i=1; i<=n; i++){
        if(graph[i].size() != 1){
            f(i, 0);
            cout << r;
            return 0;
        }
    }
    cout << n-1;
}#include <stdio.h>
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
#include <utility>
#include <bitset>
#include <iostream>
using namespace std;
typedef long long lint;
typedef long double llf;
typedef pair<int, int> pi;
 
int n, k, r;
vector<int> graph[100005];
 
int f(int x, int p){
    if(graph[x].size() == 1) return 1;
    int ret = 0;
    for(auto &i : graph[x]){
        if(i != p) ret += f(i, x);
    }
    if(ret >= 2 * k){
        r += k;
        return 0;
    }
    r += ret / 2;
    return ret % 2;
}
 
int main(){
    scanf("%d %d",&n,&k);
    for(int i=0; i<n-1; i++){
        int s, e;
        scanf("%d %d",&s,&e);
        graph[s].push_back(e);
        graph[e].push_back(s);
    }
    for(int i=1; i<=n; i++){
        if(graph[i].size() != 1){
            f(i, 0);
            cout << r;
            return 0;
        }
    }
    cout << n-1;
}