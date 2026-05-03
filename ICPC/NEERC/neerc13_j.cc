#include<bits/stdc++.h>
using namespace std;
const int MAXN = 50505;
int DP[MAXN];
int From[MAXN];
char buf[280]; 
int N;
map<string, pair<int, int> > M; //DPVAL, FROM
vector<string> tokenizer(string s)
{
    s += " ";
    vector<string> a;
    string buf="";
    for(auto x: s)
    {
        if(x== ' ')
        {
            if(buf!="") a.push_back(buf);
            buf = "";
        }
        else
        {
            buf += x;
        }
    }
    return a;
}
int main()
{
    scanf("%d\n", &N);
    for(int i=1; i<=N; ++i)
    {
        scanf("%[^\n]\n", buf);
       
        vector<string> s = tokenizer(string(buf));
        string handle = s[0]; handle.pop_back();
        //cout << handle << endl;
        int mydp = 0, myfrom = 0;
        for(auto x: s)
        {
            if(M.find(x) == M.end()) continue;
            if(x==handle) continue;
            //cout << "/"<<x<<"/"<<handle<<"/"<<endl;
            if(x[0] != '@') continue;
            int dpval, from; tie(dpval, from) = M[x];
            if(mydp<dpval)
            {
                mydp = dpval;
                myfrom = from;
            }
        }
        ++mydp;
        if(M.find(handle) != M.end())
        {
            int tdp, tv; tie(tdp, tv) = M[handle];
            if(tdp<mydp)
                M[handle] = make_pair(mydp, i);
        }
        else
        {
            M[handle] = make_pair(mydp, i);
        }
        DP[i] = mydp;
        From[i] = myfrom;
    }
    int v = max_element(DP+1, DP+1+N) - DP;
    vector<int> ans;
    while(v)
    {
        ans.push_back(v);
        v = From[v];
    }
    reverse(ans.begin(), ans.end());
    printf("%d\n", (int)ans.size());
    for(auto x: ans)
        printf("%d ", x);
    puts("");
}
