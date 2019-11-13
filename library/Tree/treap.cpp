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


class treap{
public:
	class node{
	public:
		int key;
		int priority;
		node *right;
		node *left;
		node():right(NULL), left(NULL){}
		node(int k, int p):key(k), priority(p), right(NULL), left(NULL){}
	};


	node *root;

	treap():root(NULL){}

	node* insert(int key, int priority){
		return root = insert(root, key, priority);
	}

	node* insert(node* t, int key, int priority){
		if(t == NULL){
			return new node(key, priority);
		}
		if(key == t->key){
			return t;
		}
		if(key < t->key){
			t->left = insert(t->left, key, priority);
			if(t->priority < t->left->priority){
				t = right_rotate(t);
			}
		}else{
			t->right = insert(t->right, key, priority);
			if(t->priority < t->right->priority){
				t = left_rotate(t);
			}
		}
		return t;
	}

	node* right_rotate(node *t){
		node *s = t->left;
		t->left = s->right;
		s->right = t;
		return s;
	}

	node* left_rotate(node *t){
		node *s = t->right;
		t->right = s->left;
		s->left = t;
		return s;
	}

	node* erase(int key){
		root = erase(root, key);
	}

	node* erase(node *t, int key){
		if(t == NULL){
			return NULL;
		}
		if(key < t->key){
			t->left = erase(t->left, key);
		}else if(key > t->key){
			t->right = erase(t->right, key);
		}else{
			return _erase(t, key);
		}
		return t;
	}

	node* _erase(node* t, int key){
		if(t->left == NULL && t->right == NULL){
			delete t;
			return NULL;
		}else if(t->left == NULL){
			t = left_rotate(t);
		}else if(t->right == NULL){
			t = right_rotate(t);
		}else{
			if(t->left->priority > t->right->priority){
				t = right_rotate(t);
			}else{
				t = left_rotate(t);
			}
		}
		return erase(t, key);
	}

	bool find(int key){
		return find(root, key);
	}

	bool find(node *t, int key){
		if(t==NULL){
			return false;
		}
		if(t->key==key){
			return true;
		}
		if(key < t->key){
			return find(t->left, key);
		}else{
			return find(t->right, key);
		}
		return false;
	}

	void print_inorder(){
		print_inorder(root);
	}

	void print_inorder(node *t){
		if(t==NULL){
			return;
		}
		print_inorder(t->left);
		cout << " " << t->key;
		print_inorder(t->right);
	}

	void print_preorder(){
		print_preorder(root);
	}

	void print_preorder(node *t){
		if(t==NULL){
			return;
		}
		cout << " " << t->key;
		print_preorder(t->left);
		print_preorder(t->right);
	}

};


int main(){
	int time;
	cin >> time;
	treap tr;
	rep(i, time){
		string op;
		cin >> op;
		if(op=="insert"){
			int key, priority;
			cin >> key >> priority;
			tr.insert(key, priority);
		}else if(op=="print"){
			tr.print_inorder();
			cout << endl;
			tr.print_preorder();
			cout << endl;
		}else if(op=="delete"){
			int key;
			cin >> key;
			tr.erase(key);
		}else{
			int key;
			cin >> key;
			bool flag = tr.find(key);
			cout << (flag?"yes":"no") << endl;
		}
	}

	return 0;
}


