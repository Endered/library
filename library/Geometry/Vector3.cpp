#include<bits/stdc++.h>
using namespace std;

template<class t>
class Vector3{
	public:
		t x;
		t y;
		t z;
		Vector3():x(0), y(0), z(0){}
		Vector3(t a, t b, t c):x(a), y(b), z(c){}
		Vector3(const Vector3 &o):x(o.x), y(o.y), z(o.z){}

		Vector3& operator+=(Vector3 o){x+=o.x;y+=o.y;z+=o.z;return *this;}
		Vector3& operator-=(Vector3 o){x-=o.x;y-=o.y;z-=o.z;return *this;}
		Vector3& operator*=(t o){x*=o;y*=o;z*=o;return *this;}
		Vector3& operator/=(t o){x/=o;y/=o;z/=o;return *this;}

		Vector3 operator+(Vector3 o){return Vector3(*this)+=o;}
		Vector3 operator-(Vector3 o){return Vector3(*this)-=o;}
		Vector3 operator*(t o){return Vector3(*this)*=o;}
		Vector3 operator/(t o){return Vector3(*this)/=o;}
};

template<class t>
double abs(Vector3<t> x){
	return sqrt(x.x * x.x + x.y * x.y + x.z * x.z);
}

template<class t>
double dot(Vector3<t> x, Vector3<t> y){
	return x.x * y.x + x.y * y.y + x.z * y.z;
}

template<class t>
Vector3<t> cross(Vector3<t> x, Vector3<t> y){
	t rx = x.y * y.z - x.z * y.y;
	t ry = x.z * y.x - x.x * y.z;
	t rz = x.x * y.y - x.y * y.x;
	return Vector3<t>(rx, ry, rz); 
}

template<class t>
void output(Vector3<t> x){
	printf("%lf %lf %lf\n", x.x, x.y, x.z);
}

int main(){
	Vector3<double> a(1, 2, 2);
	Vector3<double> b(2, 2, 1);
	cout << dot(a, b) << endl;
	output(cross(a, b));

	return 0;
}


