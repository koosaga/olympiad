#include <cstdio>
#include <algorithm>
#include <queue>
#include <cstring>
using namespace std;

int n,m;
char s1[1000005], s2[105], mp[255];
int trie[1000005][4], fail[1000005], term[1000005], piv;

void make_trie(){
    int p = 0;
    for (int i=0; i<m; i++) {
        if(!trie[p][mp[s2[i]]]){
            trie[p][mp[s2[i]]] = ++piv;
        }
        p = trie[p][mp[s2[i]]];
    }
    term[p] = 1;
}

queue<int> q;
void solve(){
    scanf("%d %d",&n,&m);
    scanf("%s %s",s1,s2);
    for (int i=0; i<m; i++) {
        for (int j=i; j<m; j++) {
            reverse(s2+i,s2+j+1);
            make_trie();
            reverse(s2+i,s2+j+1);
        }
    }
    q.push(0);
    while (!q.empty()) {
        int qf = q.front();
        q.pop();
        for (int i=0; i<4; i++) {
            if(!trie[qf][i]) continue;
            if(qf != 0){
                int pos = fail[qf];
                while (pos && !trie[pos][i]) {
                    pos = fail[pos];
                }
                pos = trie[pos][i];
                fail[trie[qf][i]] = pos;
            }
            q.push(trie[qf][i]);
        }
    }
    int ret = 0, pos = 0;
    for (int i=0; i<n; i++) {
        while (pos && !trie[pos][mp[s1[i]]]) {
            pos = fail[pos];
        }
        pos = trie[pos][mp[s1[i]]];
        if(term[pos]) ret++;
    }
    printf("%d\n",ret);
}

int main(){
    int t;
    scanf("%d",&t);
    mp['A'] = 1, mp['C'] = 0, mp['G'] = 2, mp['T'] = 3;
    while (t--) {
        solve();
        memset(trie,0,sizeof(trie));
        memset(fail,0,sizeof(fail));
        memset(term,0,sizeof(term));
        piv = 0;
    }
}