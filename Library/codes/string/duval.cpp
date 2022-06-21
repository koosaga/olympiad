vector<int> duval(vector<int> &s){
    int n = sz(s);
    vector<int> v;
    for(int i = 0; i < n; ){
        int j = i + 1, k = i;
        while(j < n && s[k] <= s[j]){
            if(s[k] == s[j]) j++, k++;
            else if(s[k] < s[j]) j++, k = i;
        }
        while(i <= k){
            i += j - k;
            v.push_back(i);
        }
    }
    return v;
}
