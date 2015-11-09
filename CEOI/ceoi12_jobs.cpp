#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <utility>
using namespace std;
typedef pair<int,int> pi;

vector<pi> p;
int n,d,m;
int a[1000005];
int v[100005];
vector<int> h[100005];

int f(int x){
    memset(v,0,sizeof(v));
    int head = 0;
    for (int i=0; i<m; i++) {
        head = max(head,p[i].first);
        while(v[head] >= x) head++;
        if(head > p[i].first + d) return 0;
        v[head]++;
    }
    return 1;
}

int main(){
    scanf("%d %d %d",&n,&d,&m);
    for (int i=0; i<m; i++) {
        scanf("%d",&a[i]);
        p.push_back(pi(a[i],i+1));
    }
    sort(p.begin(),p.end());
    int s = 0, e = m;
    while (s != e) {
        int m = (s+e)/2;
        if(f(m)) e = m;
        else s = m+1;
    }
    printf("%d\n",s);
    int head = 0;
    for (int i=0; i<m; i++) {
        head = max(head,p[i].first);
        while(h[head].size()>= s) head++;
        if(head > p[i].first + d) return 0;
        h[head].push_back(p[i].second);
    }
    for (int i=1; i<=n; i++) {
        for (int j=0; j<h[i].size(); j++) {
            printf("%d ",h[i][j]);
        }
        puts("0");
    }
}