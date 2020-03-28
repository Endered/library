#include<bits/stdc++.h>
#define rep(i, n) for(int i=0;i<(n);++i)
#define per(i, n) for(int i=(n)-1;i>=0;--i)
#define repa(i, n) for(int i=1;i<(n);++i)
#define foreach(i, n) for(auto &i:(n))
#define pii pair<int, int>
#define pll pair<long long, long long>
#define all(x) (x).begin(), (x).end()
#define bit(x) (1ll << (x))
using namespace std;
using ll = long long;
const ll MOD = (ll)1e9+7;
//const ll MOD = 998244353;
//const ll MOD = 924844033;
const int INF = (ll)1e9+7;
const ll INFLL = (ll)1e18;
const double EPS = 1e-5;
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
#define OUTPUT(x) (output(x), outendl())
#else
#define OUTPUT(x) (void)0
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

//below here


class Vector2{
public:
  double x;
  double y;
  Vector2():x(0), y(0){}
  Vector2(double a, double b):x(a), y(b){}
  Vector2(const Vector2 &o):x(o.x), y(o.y){}

  Vector2& operator+=(Vector2 o){x+=o.x;y+=o.y;return *this;}
  Vector2& operator-=(Vector2 o){x-=o.x;y-=o.y;return *this; }
  Vector2& operator*=(double o){x*=o;y*=o;return *this;}
  Vector2& operator/=(double o){x/=o;y/=o;return *this;}

  Vector2 operator+(Vector2 o){return Vector2(*this)+=o;}
  Vector2 operator-(Vector2 o){return Vector2(*this)-=o;}
  Vector2 operator-(){return Vector2(-x,-y);}
  Vector2 operator*(double o){return Vector2(*this)*=o;}
  Vector2 operator/(double o){return Vector2(*this)/=o;}

  double abs(){
    return sqrt(mag());
  }

  double mag(){
    return x*x+y*y;
  }

  Vector2 normal(){
    return (*this) / abs();
  }

  Vector2 rotate_90(){
    return Vector2(-y,x);
  }

  static double dot(Vector2 a,Vector2 b){
    return a.x * b.x + a.y * b.y;
  }

  static double cross(Vector2 a,Vector2 b){
    return a.x * b.y - a.y * b.x;
  }
};


double dot(Vector2 x, Vector2 y){
  return Vector2::dot(x,y);
}

double cross(Vector2 x, Vector2 y){
  return Vector2::cross(x,y);
}

void output(Vector2 x){
  cout << x.x << " " << x.y << endl;
}


class Line{
public:
  Vector2 f;
  Vector2 s;
  Line(){
    f = Vector2(0,0);
    s = Vector2(1,0);
  }
  Line(Vector2 a,Vector2 b):f(a),s(b){}

  Vector2 projection(Vector2 pos){
    pos -= f;
    Vector2 n = (s-f).normal();
    Vector2 res;
    res = n * dot(pos,n) + f;
    return res;
  }

  Vector2 reflection(Vector2 pos){
    Vector2 n;
    Vector2 res;
    pos -= f;
    double x = f.y-s.y;
    double y = s.x-f.x;
    n = Vector2(x,y).normal();
    res = pos + f - n * dot(pos,n) * 2;
    return res;
  }

  static bool is_cross(Line a,Line b){
    Vector2 ap = a.s - a.f;
    Vector2 bp = b.s - b.f;
    if(abs(Vector2::dot(ap,bp))<EPS){
      return true;
    }
    return false;
  }

  static bool is_cross_segment(Line a,Line b){
    if(Line::is_parallel(a,b)){
      return a.is_online(b.f) || a.is_online(b.s) || b.is_online(a.f) || b.is_online(a.s);
    }
	  if(Vector2::cross(a.s-a.f,b.f-a.f)*Vector2::cross(a.s-a.f,b.s-a.f)>EPS)return false;
	  if(Vector2::cross(b.s-b.f,a.f-b.f)*Vector2::cross(b.s-b.f,a.s-b.f)>EPS)return false;
return true;
  }

  static bool is_parallel(Line a,Line b){
    Vector2 ap = a.s - a.f;
    Vector2 bp = b.s - b.f;
    if(abs(Vector2::cross(ap,bp))<EPS){
      return true;
    }
    return false;
  }

  static Vector2 cul_cross(Line a,Line b){
    if(a.is_online(b.f)){
      return b.f;
    }
    if(a.is_online(b.s)){
      return b.s;
    }
    if(b.is_online(a.f)){
      return a.f;
    }
    if(b.is_online(a.s)){
      return a.s;
    }
    Vector2 an = (a.s-a.f).rotate_90();
    if(Vector2::dot(b.f-a.f,an)<0){
      an = -an;
    }
    double dis_1 = Vector2::dot(b.f-a.f,an);
    double dis_2 = Vector2::dot(b.s-a.f,an);
    return b.f + (b.s - b.f) * dis_1 / (dis_1 - dis_2);
  }

  double cul_distance(Vector2 pos){
    Vector2 v = s-f;
    Vector2 n = v.normal();
    double k = v.abs();
    pos -= f;
    double dis = Vector2::dot(pos,n);
    if(dis>0){
      if(dis>k)dis=k;
      pos -= n * dis;
    }
    return pos.abs();
  }

  static double cul_distance(Line a,Line b){
    if(Line::is_cross_segment(a,b))return 0;
    return min({a.cul_distance(b.f),a.cul_distance(b.s),
          b.cul_distance(a.f),b.cul_distance(a.s)});
  }

  bool is_online(Vector2 pos){
    return cul_distance(pos) < EPS;
  }
};

Vector2 input_vector2(){
	double x,y;
	cin >> x >> y;
	return Vector2(x,y);
}

double func(){
	Line a,b;
	a.f = input_vector2();
	a.s = input_vector2();
	b.f = input_vector2();
	b.s = input_vector2();
  return Line::cul_distance(a,b);
}

int main(){
	int q;
	cin >> q;
	rep(i,q){
    printf("%.10lf\n",func());
	}
}
