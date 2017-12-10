#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef pair<int, int> pi;

bool isJava(string s){
    if(s[0] < 'a' || s[0] > 'z') return 0;
    for(auto &i : s){
        if(i == '_') return 0;
    }
    return 1;
}

bool is_cpp(string s){
    for(auto &i : s){
        if(i <= 'Z' && i >= 'A') return 0;
    }
    return 1;
}

int main(){
    string s;
    cin >> s;
    if(!isJava(s) && !is_cpp(s)){
        puts("Error!");
        return 0;
    }
    if(isJava(s) && is_cpp(s)) cout << s;
    else if(isJava(s)){
        for(int i=0; i<s.size(); i++){
            if(s[i] <= 'Z' && s[i] >= 'A'){
                printf("_%c", s[i] - 'A' + 'a');
            }
            else putchar(s[i]);
        }
    }
    else{
        if(s[0] == '_'){
            puts("Error!");
            return 0;
        }
        for(int i=0; i<s.size(); i++){
            if(s[i] == '_'){
                if(i + 1 == s.size() || s[i+1] == '_'){
                    puts("Error!");
                    return 0;
                }
                s[i+1] += 'A' - 'a';
            }
        }
        for(int i=0; i<s.size(); i++){
            if(s[i] != '_') putchar(s[i]);
        }   
    }
}
