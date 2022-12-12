//qwerasdfzxcl
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
vector<int> a[100100];

int main(){
    int n;
    scanf("%d", &n);
    int ans1 = 0, ans2 = 0;
    vector<int> V;

    for (int i=1;i<=n;i++){
        int m;
        scanf("%d", &m);
        a[i].resize(m+1);
        for (int j=1;j<=m;j++){
            scanf("%d", &a[i][j]);
            V.push_back(a[i][j]);
        }
    }

    sort(V.begin(), V.end());

    for (int i=1;i<=n;i++){
        for (int j=1;j<(int)a[i].size();j++) a[i][j] = lower_bound(V.begin(), V.end(), a[i][j]) - V.begin() + 1;

        for (int j=1;j<(int)a[i].size()-1;j++) if (a[i][j] + 1 != a[i][j+1]) ans1++;
    }

    ans2 = n - 1 + ans1;
    printf("%d %d\n", ans1, ans2);

    return 0;
}
