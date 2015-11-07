#include <cstdio>
#include <algorithm>
#include <queue>
using namespace std;

int n;
char str[5005];
int ret[5005];

int solve(int x){
    int cnt = 0, ret = 0;
    queue<int> q;
    for (int i=0; i<n; i++) {
        if((cnt&1) ^ (str[i] == 'B')) {
            cnt++;
            ret++;
            q.push(i + x - 1);
        }
        if(!q.empty() && q.front() == i) q.pop(), cnt--;
    }
    if(!q.empty()) return 1e9;
    return ret;
}

int main(){
    scanf("%d\n",&n);
    for (int i=0; i<n; i++) {
        scanf("%c\n",&str[i]);
    }
    for (int i=1; i<=n; i++) {
        ret[i] = solve(i);
    }
    int* p = min_element(ret+1,ret+n+1);
    printf("%d %d",(int)(p - ret),*p);
}