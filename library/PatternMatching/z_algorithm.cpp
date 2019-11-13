#include<bits/stdc++.h>
#define ll long long
#define rep(i, n) for(int i=0;i<(n);++i)
#define per(i, n) for(int i=(n)-1;i>=0;--i)
#define repa(i, n) for(int i=1;i<(n);++i)
#define foreach(i, n) for(auto &i:(n))
#define pii pair<int, int>
#define pll pair<long long, long long>
#define all(x) (x).begin(), (x).end()
#define bit(x) (1ll << (x))
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

class z_algorithm{
public:
	vector<int> prefix;
	vector<int> solve(string str){
		prefix.assign(str.size(), 0);
		int j = 0;
		repa(i, str.size()){
			if(i+prefix[i-j]<j+prefix[j]){
				prefix[i] = prefix[i-j];
			}else{
				int k = max(0, prefix[j]+j-i);
				while(i+k<str.size()&&str[k]==str[i+k])++k;
				prefix[i] = k;
				j = i;
			}
		}
		prefix[0]=str.size();
		return prefix;
	}
};

int main(){
	string target, search;
	cin >> target >> search;
	z_algorithm z;
	vector<int> ans = z.solve(search + target);
	for(int i=search.size();i<ans.size();++i){
		if(ans[i]>=search.size()){
			cout << i - search.size() << endl;
		}
	}

	return 0;
}
