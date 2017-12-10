#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef long double llf;
typedef pair<int, int> pi;
const int mod = 1e9 + 7;

string str;

bool valid(string str){
    if(str.size() <= 1) return 0;
    for(int i=1; i<str.size(); i++){
        if(islower(str[i]) == 0) return 0;
    }
    return isupper(str[0]);
}

void digest(string str){
    for(int i=0; i+1<str.size(); i++){
        if(str[i] == ' ' && str[i+1] == ' '){
            string l = str.substr(0, i);
            string r = str.substr(i + 2, str.size() - i - 2);
            digest(l);
            putchar(' ');
            putchar(' ');
            digest(r);
            return;
        }
    }
    if(!str.empty() && str[0] == ' '){
        putchar(' ');
        str = str.substr(1, str.size() - 1);
        digest(str);
        return;
    }
    if(!str.empty() && str.back() == ' '){
        str.pop_back();
        digest(str);
        putchar(' ');
        return;
    }
    // word, ' ', word, ' ', word, ' ', word
    vector<string> v;
    string aux;
    for(int i=0; i<str.size(); i++){
        if(isalpha(str[i])) aux.push_back(str[i]);
        else{
            v.push_back(aux);
            aux.clear();
        }
    }
    v.push_back(aux);
    for(int i=0; i<v.size();){
        if(!valid(v[i]) || i + 1 == v.size() || !valid(v[i+1])){
            printf("%s", v[i].c_str());
            if(i + 1 < v.size()) putchar(' ');
            i++;
            continue;
        }
        int e = i;
        while(e < v.size() && valid(v[e])) e++;
        for(int j=i; j<e; j++){
            putchar(v[j][0]);
        }
        printf(" (");
        for(int j=i; j<e; j++){
            printf("%s", v[j].c_str());
            if(j + 1 < e) putchar(' ');
            else putchar(')');
        }
        if(e < v.size()) putchar(' ');
        i = e;
    }
}

void feed(char c){
    str.push_back(c);
}

int main(){
    freopen("abbreviation.in", "r", stdin);
    freopen("abbreviation.out", "w", stdout);
    while(true){
        char c = getchar();
        if(c == -1){
            digest(str);
            break;
        }
        if(c == '.' || c == ',' || c == '\n'){
            digest(str);            
            str.clear();
            putchar(c);
        }
        else{
            feed(c);
        }
    }
}
