
template<class t>
ll mergesort(vector<t> &line){
    ll res = 0;
    function<void(int,int,int)> merge = [&](int l,int m,int r) -> void{
        int L = m - l;
        int R = r - m;
        vector<t> A(L);
        vector<t> B(R);
        for(int i=l;i<m;++i)A[i-l] = line[i];
        for(int i=m;i<r;++i)B[i-m] = line[i];
        int lp = 0;
        int rp = 0;
        for(int i=0;i<r-l;++i){
            if(rp==R or (lp < L and A[lp] <= B[rp])){
                line[i+l] = A[lp++];
            }else{
                line[i+l] = B[rp++];
                res += L - lp;
            }
        }
    };
    function<void(int,int)> rec = [&](int l,int r) -> void{
        if(l+1==r)return;
        int m = (l + r) / 2;
        rec(l,m);
        rec(m,r);
        merge(l,m,r);
    };
    rec(0,line.size());
    return res;
}
