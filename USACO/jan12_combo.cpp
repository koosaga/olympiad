#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;
 
int trie[301][26], fail[301], term[301], sz;
char str[20][16];
 
int n,k;
int dp[1005][301];
 
int f(int x, int p){
    if(x == 0) return term[p];
    if(~dp[x][p]) return dp[x][p];
    int ret = 0;
    for (int i=0; i<26; i++) {
        int q = p;
        while (q && !trie[q][i]) {
            q = fail[q];
        }
        q = trie[q][i];
        ret = max(ret,f(x-1,q));
    }
    return dp[x][p] = ret + term[p];
}
int main(){
    memset(dp,-1,sizeof(dp));
    scanf("%d %d",&n,&k);
    for (int i=0; i<n; i++) {
        char str[17];
        scanf("%s",str);
        int p = 0;
        for (int j=0; str[j]; j++) {
            if(!trie[p][str[j] - 'A']){
                trie[p][str[j] - 'A'] = ++sz;
            }
            p = trie[p][str[j] - 'A'];
        }
        term[p]++;
    }
    queue<int> q;
    q.push(0);
    while (!q.empty()) {
        int qf = q.front();
        q.pop();
        for (int i=0; i<26; i++) {
            if(trie[qf][i] == 0) continue;
            q.push(trie[qf][i]);
            if(qf == 0){
                fail[trie[qf][i]] = qf;
                continue;
            }
            int p = fail[qf];
            while (p && !trie[p][i]) {
                p = fail[p];
            }
            if(trie[p][i]) p = trie[p][i];
            fail[trie[qf][i]] = p;
            term[trie[qf][i]] += term[p];
        }
    }
    printf("%d",f(k,0));
}