#include<bits/stdc++.h>
using namespace std;

template<class t>
class Vector2{
	public:
		t x;
		t y;
		Vector2():x(0), y(0){}
		Vector2(t a, t b):x(a), y(b){}
		Vector2(const Vector2 &o):x(o.x), y(o.y){}

		Vector2& operator+=(Vector2 o){x+=o.x;y+=o.y;return *this;}
		Vector2& operator-=(Vector2 o){x-=o.x;y-=o.y;return *this; }
		Vector2& operator*=(t o){x*=o;y*=o;return *this;}
		Vector2& operator/=(t o){x/=o;y/=o;return *this;}

		Vector2 operator+(Vector2 o){return Vector2(*this)+=o;}
		Vector2 operator-(Vector2 o){return Vector2(*this)-=o;}
		Vector2 operator*(t o){return Vector2(*this)*=o;}
		Vector2 operator/(t o){return Vector2(*this)/=o;}
};

template<class t>
double abs(Vector2<t> x){
	return sqrt(x.x * x.x + x.y * x.y);
}

template<class t>
double dot(Vector2<t> x, Vector2<t> y){
	return x.x * y.x + x.y * y.y;
}

template<class t>
double cross(Vector2<t> x, Vector2<t> y){
	return x.x * y.y - x.y * y.x;
}

template<class t>
void output(Vector2<t> x){
	printf("%lf %lf\n", x.x, x.y);
}


int main(){
	Vector2<double> a(1, 1);
	output(a);
	a *= 3;
	output(a);
	a /= 2;
	output(a);

	return 0;
}

