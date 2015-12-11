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
  
int trie[100005][26], piv;
int fail[100005], term[100005];
int nxt[100005][26];
bool vis[100005][26];
 
char str[100005], buf[100005];
 
int dfs(int i, int j){
    if(vis[i][j]) return nxt[i][j];
    if(trie[i][j]) return i;
    vis[i][j] = 1;
    return nxt[i][j] = dfs(fail[i], j);
}
 
int main(){
    scanf("%s",str);
    int qr;
    scanf("%d",&qr);
    while(qr--){
        scanf("%s",buf);
        int p = 0;
        for(int i=0; buf[i]; i++){
            if(!trie[p][buf[i] - 'a']){
                trie[p][buf[i] - 'a'] = ++piv;
            }
            p = trie[p][buf[i] - 'a'];
        }
        term[p] = strlen(buf);
    }
    queue<int> q;
    for(int i=0; i<26; i++){
        if(trie[0][i]){
            q.push(trie[0][i]);
        }
    }
    while(!q.empty()){
        int qf = q.front();
        q.pop();
        for(int i=0; i<26; i++){
            if(!trie[qf][i]) continue;
            int p = fail[qf];
            while(p && !trie[p][i]){
                p = fail[p];
            }
            p = trie[p][i];
            fail[trie[qf][i]] = p;
            term[trie[qf][i]] = max(term[trie[qf][i]], term[p]);
            q.push(trie[qf][i]);
        }
    }
    for(int i=1; i<=piv; i++){
        for(int j=0; j<26; j++){
            if(!vis[i][j]){
                nxt[i][j] = dfs(i, j);
            }
        }
    }
    vector<int> stk;
    string ret;
    stk.push_back(0);
    int p = 0;    
    for(int i=0; str[i]; i++){
        ret.push_back(str[i]);
        p = nxt[p][str[i] - 'a'];
        p = trie[p][str[i] - 'a'];
        stk.push_back(p);
        if(term[p]){
            for(int i=0; i<term[p]; i++){
                stk.pop_back();
                ret.pop_back();
            }
            p = stk.back();
        }
    }
    cout << ret;
}