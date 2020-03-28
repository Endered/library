#include<bits/stdc++.h>
#define rep(i,a,...) for(int i = (a)*(strlen(#__VA_ARGS__)!=0);i<(int)(strlen(#__VA_ARGS__)?__VA_ARGS__:(a));++i)
#define per(i,a,...) for(int i = (strlen(#__VA_ARGS__)?__VA_ARGS__:(a))-1;i>=(int)(strlen(#__VA_ARGS__)?(a):0);--i)
#define foreach(i, n) for(auto &i:(n))
#define pii pair<int, int>
#define pll pair<long long, long long>
#define all(x) (x).begin(), (x).end()
#define bit(x) (1ll << (x))
using ll = long long;
//const ll MOD = (ll)1e9+7;
const ll MOD = 998244353;
const int INF = (ll)1e9+7;
const ll INFLL = (ll)1e18;
using namespace std;
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

ll modpow(ll x, ll b){
  ll res = 1;
  while(b){
    if(b&1)res = res * x % MOD;
    x = x * x % MOD;
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
ll in(){
  ll res;
  scanf("%lld", &res);
  return res;
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
void in(t&x){
  cin >> x;
}

template<class t>
void out(t x){
  cout << x;
}

int n;
vvector<pii> edges;
int x;

void setup(){
  n = in();
  x = in();
  edges.resize(n);
  rep(i,n-1){
    int a = in() - 1;
    int b = in() - 1;
    int c = in();
    edges[a].emplace_back(b,c);
    edges[b].emplace_back(a,c);
  }
}


ll solve(){
  ll ans = 0;
  map<int,ll> m;
  m[0]=1;
  function<void(int,int,int)> func =
    [&](int place,int last,int sum){
      foreach(i,edges[place]){
        if(i.first==last)continue;
        ans += m.count(sum^x^i.second)?m[sum^x^i.second]:0;
        ++m[sum^i.second];
        func(i.first,place,sum^i.second);
      }
    };
  func(0,-1,0);
  return ans;
}

int main(){
  setup();

  cout << solve() << endl;
  return 0;
}
