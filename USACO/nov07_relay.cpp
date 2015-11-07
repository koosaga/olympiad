#include <cstdio>
#include <set>
#include <vector>
#include <algorithm>
using namespace std;

int n,m;
vector<int> qr[1005];
int sun[1005];

int main(){
    scanf("%d %d",&n,&m);
    int cnt = 0;
    for (int i=0; i<n; i++) {
        int t,u;
        scanf("%d %d",&t,&u);
        qr[t].push_back(u);
    }
    for (int i=0; i<m; i++) {
        int t,u;
        scanf("%d %d",&t,&u);
        sun[t] += u;
    }
    multiset<int> s;
    for (int i=1; i<=1000; i++) {
        for (int j=0; j<qr[i].size(); j++) {
            s.insert(qr[i][j]);
        }
        for (int j=0; j<sun[i]; j++) {
            if(!s.empty()){
                cnt++;
                s.erase(s.begin());
            }
        }
        while(!s.empty() && *s.begin() == i) s.erase(s.begin());
    }
    printf("%d",cnt);
}