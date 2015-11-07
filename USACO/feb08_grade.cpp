#include <cstdio>
#include <vector>
#include <algorithm>
#include <cstdlib>
using namespace std;

int n;
int a[2005];
int dp1[2005][2005], dp2[2005][2005];
vector<int> v;

int main(){
    scanf("%d",&n);
    for (int i=0; i<n; i++) {
        scanf("%d",&a[i]);
        v.push_back(a[i]);
    }
    sort(v.begin(),v.end());
    v.resize(unique(v.begin(),v.end()) - v.begin());
    for (int i=0; i<n; i++) {
        a[i] = (int)(lower_bound(v.begin(),v.end(),a[i]) - v.begin());
    }
    for (int j=0; j<v.size(); j++) {
        dp1[0][j] = abs(v[j] - v[a[0]]);
        if(j) dp1[0][j] = min(dp1[0][j],dp1[0][j-1]);
    }
    for (int j=(int)v.size()-1; j>=0; j--) {
        dp2[0][j] = abs(v[j] - v[a[0]]);
        if(j+1 != v.size()) dp2[0][j] = min(dp2[0][j],dp2[0][j+1]);
    }
    for (int i=1; i<n; i++) {
        for (int j=0; j<v.size(); j++) {
            dp1[i][j] = dp1[i-1][j] + abs(v[j] - v[a[i]]);
            if(j) dp1[i][j] = min(dp1[i][j],dp1[i][j-1]);
        }
        for (int j=(int)v.size()-1; j>=0; j--) {
            dp2[i][j] = dp2[i-1][j] + abs(v[j] - v[a[i]]);
            if(j+1 != v.size()) dp2[i][j] = min(dp2[i][j],dp2[i][j+1]);
        }
    }
    printf("%d",min(dp1[n-1][v.size()-1],dp2[n-1][0]));
}