#include <cstdio>
#include <set>
using namespace std;

multiset<int> st;

void solve(){
    int q;
    st.clear();
    scanf("%d",&q);
    while (q--) {
        char str[10];
        int t;
        scanf("%s %d",str,&t);
        if(str[0] == 'I') st.insert(t);
        else{
            if(st.empty()) continue;
            if(t == 1) st.erase(--st.end());
            else st.erase(st.begin());
        }
    }
    if(st.empty()) puts("EMPTY");
    else printf("%d %d\n",*--st.end(),*st.begin());
}

int main(){
    int t;
    scanf("%d",&t);
    while (t--) {
        solve();
    }
}