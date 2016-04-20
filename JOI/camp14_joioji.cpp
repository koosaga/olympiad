#include <cstdio>
#include <map>
#include <utility>
using namespace std;
typedef pair<int,int> pi;

char str[200005];
int n;
int res = 0;

multimap<pi,int> mp;
multimap<pi,int> ::iterator it;

int main(){
    scanf("%d %s",&n,str);
    pi x = pi(0,0);
    mp.insert(make_pair(x,0));
    for (int i=0; i<n; i++) {
        if(str[i] == 'J'){
            x.first--;
            x.second--;
        }
        else if(str[i] == 'O') x.first++;
        else x.second++;
        mp.insert(make_pair(x,i+1));
    }
    it = mp.begin();
    while (it != mp.end()) {
        x = (*it).first;
        int t = (*it).second;
        while ((*it).first == x && it != mp.end()) it++;
        it--;
        res = max(res,(*it).second - t);
        it++;
    }
    printf("%d",res);
}