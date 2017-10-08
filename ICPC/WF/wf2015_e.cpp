#include <cstdio>
#include <vector>
#include <string>
#include <cstring>
using namespace std;

int n;
string s[4005];
char buf[4005], st[4005];

vector<string> v[4005];

vector<int> l, r, m;

bool match(int x, int y){
    if(x == -1) return 1;
    int pt = 0;
    for(int i=0; i<s[x].size(); i++){
        while(pt < s[y].size() && s[y][pt] != s[x][i]){
            pt++;
        }
        if(pt == s[y].size()) return 0;
        pt++;
    }
    return 1;
}

int main(){
    if(scanf("%d %s",&n,st) == -1) return 0;
    for(int i=0; i<n; i++){
        scanf("%s",buf);
        v[strlen(buf)].push_back(buf);
    }
    int pt = 0;
    for(int i=0; i<=4000; i++){
        if(v[i].size() > 2){
            puts("impossible");
            return 0;
        }
        for(auto &j : v[i]){
            s[pt++] = j;
        }
    }
    for(int i=0; i<n; i++){
        int lmatch = match(l.empty() ? -1 : l.back(), i);
        int mmatch = match(m.empty() ? -1 : m.back(), i);
        int rmatch = match(r.empty() ? -1 : r.back(), i);
        if(!lmatch && !rmatch){
            puts("impossible");
            return 0;
        }
        else if(lmatch && rmatch && mmatch){
            m.push_back(i);
        }
        else if(lmatch && rmatch){
            for(auto &j : m){
                l.push_back(j);
            }
            r.push_back(i);
            m.clear();
        }
        else if(lmatch){
            l.push_back(i);
            for(auto &j : m){
                r.push_back(j);
            }
            m.clear();
        }
        else if(rmatch){
            r.push_back(i);
            for(auto &j : m){
                l.push_back(j);
            }
            m.clear();
        }
    }
    s[n] = st;
    int lmatch = match(l.empty() ? -1 : l.back(), n);
    int mmatch = match(m.empty() ? -1 : m.back(), n);
    int rmatch = match(r.empty() ? -1 : r.back(), n);
    if(!lmatch || !rmatch || !mmatch){
        puts("impossible");
        return 0;
    }
    for(auto &j : m){
        l.push_back(j);
    }
    printf("%d %d\n",(int)l.size(),(int)r.size());
    for(auto &j : l){
        puts(s[j].c_str());
    }
    for(auto &j : r){
        puts(s[j].c_str());
    }
}