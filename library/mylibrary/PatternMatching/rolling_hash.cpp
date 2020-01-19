#include<bits/stdc++.h>
#define rep(i, n) for(int i=0;i<(n);++i)
#define per(i, n) for(int i=(n)-1;i>=0;--i)
#define repa(i, n) for(int i=1;i<(n);++i)
#define foreach(i, n) for(auto &i:(n))
#define pii pair<int, int>
#define pll pair<long long, long long>
#define all(x) (x).begin(), (x).end()
#define bit(x) (1ll << (x))
using ll = long long;
const ll MOD = (ll)1e9+7;
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

template<ll B, ll MOD>
class rolling_hash{
public:
	vector<int> prefix;

	vvector<ll> to_hash(const vector<string> &x){
		int h = x.size();
		int w = x.front().size();
		vvector<ll> res(h, vector<ll>(w));
		for(int i=0;i<h;++i){
			for(int j=0;j<w;++j){
				res[i][j] = x[i][j];
			}
		}
		return res;
	}

	vector<pii> solve(const vector<string> &x, const vector<string> &y){
		vvector<ll> x_, y_;
		x_ = to_hash(x);
		y_ = to_hash(y);
		return solve(x_, y_, B);
	}

	vector<pii> solve(const vvector<ll> &x, const vvector<ll> &y, ll b){
		int x_h = x.size();
		int x_w = x.front().size();
		int y_h = y.size();
		int y_w = y.front().size();
		if(x_h<y_h||x_w<y_w)return vector<pii>(0);
		ll pow_b_y_h = 1;
		ll pow_b_y_h_1 = 1;
		for(int i=0;i<y_h;++i){
			pow_b_y_h = pow_b_y_h * b % MOD;
		}
		for(int i=0;i<y_h-1;++i){
			pow_b_y_h_1 = pow_b_y_h_1 * b % MOD;
		}
		vvector<ll> hash_table(x_h-y_h+1, vector<ll>(x_w));
		vector<ll> y_hash(y_w);
		for(int i=0;i<x_w;++i){
			ll now_hash = 0;
			for(int j=0;j<y_h-1;++j){
				now_hash = now_hash * b + x[j][i];
				now_hash %= MOD;
			}
			for(int j=0;j<x_h-y_h+1;++j){
				now_hash = now_hash * b + x[j+y_h-1][i];
				now_hash %= MOD;
				hash_table[j][i] = now_hash;
				if(j+y_h<x_h){
					now_hash = now_hash - x[j][i] * pow_b_y_h_1;
					now_hash = (now_hash % MOD + MOD) % MOD;
				}
			}
			
		}
		for(int i=0;i<y_w;++i){
			ll now_hash = 0;
			for(int j=0;j<y_h;++j){
				now_hash = now_hash * b + y[j][i];
				now_hash %= MOD;
			}
			y_hash[i] = now_hash;
		}
		vector<pii> res;
		for(int i=0;i<x_h-y_h+1;++i){
			vector<int> now_res = solve(hash_table[i], y_hash, pow_b_y_h);
			for(auto j:now_res){
				res.emplace_back(i, j);
			}
		}
		return res;
	} 

	vector<int> solve(const string &x, const string &y){
		vector<ll> x_, y_;
		for(auto i:x){
			x_.push_back(i);
		}
		for(auto i:y){
			y_.push_back(i);
		}
		return solve(x_, y_, B);
	}

	vector<int> solve(const vector<ll> &x, const vector<ll> &y, ll b){
		ll x_len = x.size();
		ll y_len = y.size();
		ll pow_b_y = 1;
		if(x_len<y_len)return vector<int>(0);

		ll x_hash = 0;
		ll y_hash = 0;
		rep(i, y_len){
			y_hash = y_hash * b + y[i];
			x_hash = x_hash * b + x[i];
			pow_b_y = pow_b_y * b;
			y_hash %= MOD;
			x_hash %= MOD;
			pow_b_y %= MOD;
		}
		prefix.clear();
		for(int i=y_len;i<=x_len;++i){
			if(x_hash==y_hash){
				prefix.emplace_back(i-y_len);
			}
			if(i<x_len){
				x_hash = x_hash * b - x[i-y_len] * pow_b_y + x[i];
				x_hash = (x_hash % MOD + MOD) % MOD;
				x_hash %= MOD;
			}
		}
		return prefix;
	}

};


int main(){
	rolling_hash<17777, (ll)1e9+7> r;
	int h, w;
	cin >> h >> w;
	vector<string> target(h);
	foreach(i, target){
		cin >> i;
	}
	cin >> h >> w;
	vector<string> search(h);
	foreach(i, search){
		cin >> i;
	}
	vector<pii> ans = r.solve(target, search);
	foreach(i, ans){
		cout << i.first << " " << i.second << endl;
	}

	return 0;
}

