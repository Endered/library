#include<bits/stdc++.h>
#define rep(i,a,...) for(int i = (a)*(strlen(#__VA_ARGS__)!=0);i<(int)(strlen(#__VA_ARGS__)?__VA_ARGS__:(a));++i)
#define per(i,a,...) for(int i = (strlen(#__VA_ARGS__)?__VA_ARGS__:(a))-1;i>=(int)(strlen(#__VA_ARGS__)?(a):0);--i)
#define foreach(i, n) for(auto &i:(n))
#define all(x) (x).begin(), (x).end()
#define bit(x) (1ll << (x))
#define lambda(RES_TYPE, ...) (function<RES_TYPE(__VA_ARGS__)>)[&](__VA_ARGS__) -> RES_TYPE
#define method(FUNC_NAME, RES_TYPE, ...) function<RES_TYPE(__VA_ARGS__)> FUNC_NAME = lambda(RES_TYPE, __VA_ARGS__)
using namespace std;
using ll = long long;
using pii = pair<int,int>;
using pll = pair<ll,ll>;
//const ll MOD = (ll)1e9+7;
const ll MOD = 998244353;
const int INF = (ll)1e9+7;
const ll INFLL = (ll)1e18;
template<class t>
using vvector = vector<vector<t>>;
template<class t>
using vvvector = vector<vector<vector<t>>>;
template<class t>
using priority_queuer = priority_queue<t, vector<t>, greater<t>>;
template<class t, class u> bool chmax(t &a, u b){if(a<b){a=b;return true;}return false;}
template<class t, class u> bool chmin(t &a, u b){if(a>b){a=b;return true;}return false;}
#ifdef DEBUG
#define debug(x) cout<<"LINE "<<__LINE__<<": "<<#x<<" = "<<x<<endl;
#else
#define debug(x) (void)0
#endif

//https://onlinejudge.u-aizu.ac.jp/problems/2677
template<class cost = long long>
class lowest_common_ancestor{
public:
    using E = pair<int,cost>;
    int n;
    vector<vector<E>> edges;
    int log2;
    vector<vector<int>> ancests;
    vector<cost> dists;
    vector<int> heights;

    lowest_common_ancestor(int n):n(n),edges(n){
        log2 = 1;
        while((1<<log2)<=n)++log2;
    }

    void add_edge(int u,int v,cost c=1){
        edges[u].emplace_back(v,c);
        edges[v].emplace_back(u,c);
    }
    
    inline int height(int p){
        return heights[p];
    }

    void build(int root){
        ancests.assign(n,vector<int>(log2,-1));
        dists.assign(n,0);
        heights.assign(n,-1);
        stack<int> st;
        st.emplace(root);
        dists[root] = 0;
        heights[root] = 0;
        ancests[root][0] = root;
        while(st.size()){
            int p = st.top();st.pop();
            for(auto e:edges[p]){
                if(heights[e.first]>=0)continue;
                dists[e.first] = dists[p] + e.second;
                heights[e.first] = heights[p] + 1;
                ancests[e.first][0] = p;
                st.emplace(e.first);
            }
        }
    }

    int ancests_time(int p,int k){
        if(k==0){
            return ancests[p][0];
        }
        int &it = ancests[p][k];
        if(it >= 0)return it;
        return it = ancests_time(ancests_time(p,k-1),k-1);
    }

    inline cost dist(int p){
        return dists[p];
    }

    cost dist(int p,int q){
        cost res = dist(p) + dist(q);
        if(height(p) < height(q))swap(p,q);
        for(int i=log2-1;i>=0;--i){
            if(height(p)-height(q)<(1<<i))continue;
            p = ancests_time(p,i);
        }
        for(int i=log2-1;i>=0;--i){
            if(ancests_time(p,i)==ancests_time(q,i))continue;
            p = ancests_time(p,i);
            q = ancests_time(q,i);
        }
        if(p!=q)p=q=ancests_time(p,0);
        res -= dist(p) * 2;
        return res;
    }
};

namespace templates{
    ll modpow(ll x, ll b,ll mod=MOD){
        ll res = 1;
        while(b){
            if(b&1)res = res * x % mod;
            x = x * x % mod;
            b>>=1;
        }
        return res;
    }

    ll modinv(ll x){
        return modpow(x, MOD-2);
    }

    bool was_output = false;
    template<class t>
    void output(t a){
        if(was_output)cout << " ";
        cout << a;
        was_output = true;
    }
    void outendl(){
        was_output = false;
        cout << endl;
    }

    template<class t>
    istream& operator>>(istream&is, vector<t>&x){
        for(auto &i:x)is >> i;
        return is;
    }

    template<class t, class u>
    istream& operator>>(istream&is, pair<t, u>&x){
        is >> x.first >> x.second;
        return is;
    }

    template<class t>
    ostream& operator<<(ostream&os, vector<t> &v){
        os << "{";
        for(t &i:v){
            os << i << ", ";
        }
        os << "}";
        return os;
    }

    template<class t = long long>
    t in(){
        t res; cin >> res; return res;
    }

    template<class t>
    void out(t x){
        cout << x;
    }


    template<class t>
    vector<t> sorted(vector<t> line,function<bool(t,t)> comp=[](t a,t b){return a<b;}){
        sort(line.begin(),line.end(),comp);
        return line;
    }

    template<class t>
    vector<t> reversed(vector<t> line){
        reverse(line.begin(),line.end());
        return line;
    }
    string reversed(string str){
        reverse(str.begin(),str.end());
        return str;
    }

    long long gcd(long long a,long long b){
        while(b){
            a %= b;
            swap(a,b);
        }
        return a;
    }

    long long lcm(long long a,long long b){
        return a / gcd(a,b) * b;
    }
}

using namespace templates;


ll func(){
    int n = in();
    vvector<int> childs(n);
    lowest_common_ancestor<ll> lca(n);
    rep(i,n-1){
        int p = in()-1;
        childs[p].emplace_back(i+1);
        lca.add_edge(p,i+1,1);
    }
    vector<int> order;
    {
        vector<int> has;
        has.emplace_back(0);
        while(has.size()){
            order.insert(order.end(),all(has));
            vector<int> next;
            foreach(i,has){
                sort(all(childs[i]));
                next.insert(next.end(),all(childs[i]));
            }
            has = next;
        }
    }
    ll res = 0;
    lca.build(0);
    rep(i,order.size()-1){
        res += lca.dist(order[i],order[i+1]);
    }
    return res;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout << func() << endl;
    return 0;
}

