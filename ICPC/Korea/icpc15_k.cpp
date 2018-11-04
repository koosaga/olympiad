#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef long double llf;
typedef pair<int, int> pi;

int p1, p2, l1, l2;
char s1[5000], s2[5000];
int m1[5000], m2[5000];

char r1[1005], r2[1005];
int sz1[1005], sz2[1005];
vector<pi> e1, e2;
vector<int> g1[1005], g2[1005];

int parse(char *s, int *m, int st, int ed, int &idx, int *sz, char *r, vector<pi> &e){
    idx++;
    r[idx] = s[st];
    sz[idx] =1 ;
    int ret = idx;
    st++;
    while(st <= ed){
        int nxt = parse(s, m, st+1, m[st] - 1, idx, sz, r, e);
        sz[ret] += sz[nxt];
        e.push_back(pi(ret, nxt));
        st = m[st] + 1;
    }
    return ret;
}

int dp2[1005][1005];

int f(int l, int r){
    if(~dp2[l][r]) return dp2[l][r];
    vector<int> v1 = g1[l];
    vector<int> v2 = g2[r];
    vector<vector<int> > dp(v1.size() + 1);
    for(int i=0; i<=v1.size(); i++){
        dp[i].resize(v2.size() + 1);
        for(int j=0; j<=v2.size(); j++){
            if(!i && !j) continue;
            dp[i][j] = 1e9;
            if(i > 0) dp[i][j] = min(dp[i][j], dp[i-1][j] + sz1[v1[i-1]]);
            if(j > 0) dp[i][j] = min(dp[i][j], dp[i][j-1] + sz2[v2[j-1]]);
            if(i > 0 && j > 0) dp[i][j] = min(dp[i][j], dp[i-1][j-1] + f(v1[i-1], v2[j-1]));
        }
    }
    return dp2[l][r] = dp[v1.size()][v2.size()] + (r1[l] != r2[r]);
}

int main(){
    int tc;
    scanf("%d",&tc);
    while(tc--){
        memset(dp2, -1, sizeof(dp2));
        e1.clear();
        e2.clear();
        for(int i=0; i<=1000; i++) g1[i].clear(), g2[i].clear();
        p1 = p2 = 0;
        scanf("%s %s",s1, s2);
        l1 = strlen(s1), l2 = strlen(s2);
        stack<int> stk;
        for(int i=0; i<l1; i++){
            if(s1[i] == ')'){
                m1[stk.top()] = i;
                stk.pop();
            }
            if(s1[i] == '('){
                stk.push(i);
            }
        }
        for(int i=0; i<l2; i++){
            if(s2[i] == ')'){
                m2[stk.top()] = i;
                stk.pop();
            }
            if(s2[i] == '('){
                stk.push(i);
            }
        }
        parse(s1, m1, 1, l1-2, p1, sz1, r1, e1);
        parse(s2, m2, 1, l2-2, p2, sz2, r2, e2);
        for(auto &i : e1){
            g1[i.first].push_back(i.second);
        }
        for(auto &i : e2){
            g2[i.first].push_back(i.second);
        }
        cout << f(1, 1) << endl;
    }
}
