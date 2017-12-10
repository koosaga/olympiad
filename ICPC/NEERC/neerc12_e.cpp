#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef pair<lint, lint> pi;

int n;
lint x;
vector<pi> sk[22];
int ans[100005];

int main(){
    cin >> x >> n;
    for(int i=0; i<n; i++){
        int k;
        lint q;
        scanf("%d %lld",&k,&q);
        for(int j=0; j<k; j++) q *= 10;
        sk[k].push_back(pi(q, i));
    }
    vector<pi> cur_sack;
    lint fr = 0;
    lint curmod = 10;
    for(int i=0; i<=18 && x; i++){
        for(auto &j : sk[i]){
            cur_sack.push_back(j);
        }
        sort(cur_sack.begin(), cur_sack.end());
        lint resi = x;
        if(i < 18) resi %= curmod;
        while(fr < resi){
            if(cur_sack.empty()){
                puts("-1");
                return 0;
            }
            fr += cur_sack.back().first;
            ans[cur_sack.back().second] = 1;
            cur_sack.pop_back();
        }
        fr -= resi;
        x -= resi;
        curmod *= 10;
    }
    cout << count(ans, ans + n, 1) << endl;
    for(int i=0; i<n; i++) if(ans[i]) printf("%d ",i+1);
}
