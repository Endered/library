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

pii nil = pii(INF,INF);
vector<pii> dirs = {{1,0},{0,1},{-1,0},{0,-1}};
map<pii,vector<pii>> m;

int char2dir(char d){
  if(d=='R')return 0;
  if(d=='U')return 1;
  if(d=='L')return 2;
  if(d=='D')return 3;
  return -1;
}

pii operator+(pii a,pii b){
  return {a.first+b.first,a.second+b.second};
}


pii move(pii pos,int dir){
  if(m[pos].empty())m[pos].assign(dirs.size(),nil);
  pii &res = m[pos][dir];
  if(res==nil){
    res = pos + dirs[dir];
  }
  return res;
}

void apply(pii pos){
  int n = dirs.size();
  rep(front,n/2){
    int back = front+n/2;
    pii front_p = move(pos,front);
    pii back_p = move(pos,back);
    vector<pii>& front_it = m[front_p];
    vector<pii>& back_it = m[back_p];
    if(front_it.empty())front_it.assign(n,nil);
    if(back_it.empty())back_it.assign(n,nil);
    front_it[back] = back_p;
    back_it[front] = front_p;
  }
}

pii func(pii pos,int dir){
  pii res = move(pos,dir);
  apply(res);
  return res;
}


int main(){
  pii cp = {0,0};
  int k = in();
  string str;
  in(str);
  apply(cp);
  foreach(i,str){
    cp = func(cp,char2dir(i));
  }
  cout << cp.first << " " << cp.second << endl;
  return 0;
}
