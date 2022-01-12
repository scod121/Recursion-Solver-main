// Recursion Solver

#include <bits/stdc++.h>
using namespace std;

class splnum{ 
    public:  
    int a;
    int b;
    int c;
    int d;
    splnum addspl(splnum u, splnum v);
    splnum subspl(splnum u, splnum v);
    splnum mulspl(splnum u, splnum v);
    splnum divspl(splnum u, splnum v);
    splnum invspl(splnum u);
    splnum simplify(splnum u);
    void prnspl(splnum u);  
};

int absolute(int x){
	if(x < 0) x *= -1;
	return(x); 
}

int gcd(int a, int b){
    if (a == 0) return b;
    if (b == 0) return a;
    if (a == b) return a;
    if (a > b) return gcd(a-b, b);
    return gcd(a, b-a);
}

int Sqrt(int x){
    if (x == 0 || x == 1) return x;  
    int start = 1, end = x, ans;    
    while (start <= end){         
        int mid = (start + end) / 2; 
        if (mid*mid == x) return mid;  
        if (mid*mid < x){ 
            start = mid + 1; 
            ans = mid; 
        }  
        else end = mid-1;         
    } 
    return ans; 
} 

splnum splnum::addspl(splnum u, splnum v){
	splnum sum;
	if(u.c == v.c){
		sum.a = u.a + v.a;
		sum.b = u.b + v.b;
		sum.c = u.c;
		if(u.d != 0) sum.d = u.d;
		else sum.d = v.d;
	}
	else{
		sum.a = u.a*v.c + u.c*v.a;
		sum.b = u.b*v.c + u.c*v.b;
		sum.c = u.c*v.c;
				if(u.d != 0) sum.d = u.d;
		else sum.d = v.d;
	}
	int x = sum.c;
	if(sum.a%x == 0 && sum.b%x == 0 && sum.c != 1){
		sum.a = sum.a/x;
		sum.b = sum.b/x;
		sum.c = 1;
	}
	return(sum);
}

splnum splnum::subspl(splnum u, splnum v){
	splnum diff;
	if(u.c == v.c){
		diff.a = u.a - v.a;
		diff.b = u.b - v.b;
		diff.c = u.c;
		if(u.d != 0) diff.d = u.d;
		else diff.d = v.d;
	}
	else{
		diff.a = u.a*v.c - u.c*v.a;
		diff.b = u.b*v.c - u.c*v.b;
		diff.c = u.c*v.c;
		if(u.d != 0) diff.d = u.d;
		else diff.d = v.d;
	}
	int x = diff.c;
	if(diff.a%x == 0 && diff.b%x == 0 && diff.c != 1){
		diff.a = diff.a/x;
		diff.b = diff.b/x;
		diff.c = 1;
	}
	return(diff);
}

splnum splnum::mulspl(splnum u, splnum v){
	splnum mult;
	mult.a = u.a*v.a + u.b*v.b*u.d;
	mult.b = u.a*v.b + u.b*v.a;
	mult.c = u.c*v.c;
	if(u.d != 0) mult.d = u.d;
	else mult.d = v.d;
	int x = mult.c;
	if(mult.a%x == 0 && mult.b%x == 0 && mult.c != 1){
		mult.a = mult.a/x;
		mult.b = mult.b/x;
		mult.c = 1;
	}
	return(mult);
}

splnum splnum::invspl(splnum u){
	splnum inverse;
	inverse.a = u.a*u.c;
	inverse.b = -1*u.b*u.c;
	inverse.c = u.a*u.a - u.b*u.b*u.d;   
	inverse.d = u.d;
	if(inverse.c < 0){
		inverse.a *= -1;
		inverse.b *= -1;
		inverse.c = absolute(inverse.c);
	}
	int x = inverse.c;
	int d = gcd(absolute(inverse.a), absolute(inverse.b));
	if(inverse.a%x == 0 && inverse.b%x == 0 && inverse.c != 1){
		inverse.a = inverse.a/x;
		inverse.b = inverse.b/x;
		inverse.c = 1;
	}
	else if(d != 0 && inverse.c%d == 0){
		inverse.a = inverse.a/d;
		inverse.b = inverse.b/d;
		inverse.c /= d;
	}
	return(inverse);
}

splnum splnum::divspl(splnum u, splnum v){
	splnum temp, div;
	temp = temp.invspl(v);
	div = div.mulspl(u, temp);
	return(div);
}

bool is_equal(splnum u, splnum v){
	if(u.a == v.a && u.b*u.b*u.d == v.b*v.b*v.d && u.c == v.c) return true;
	else return false;
}

splnum splnum::simplify(splnum u){
	int a = gcd(absolute(u.a), u.c);
	int b = gcd(absolute(u.b), u.c);
	int d = gcd(a, b);
	if(a != 0 && b!= 0){
		u.a /= d;
		u.b /= d;
		u.c /= d;
	} 
	if(a == 0) u.b /= d, u.c /= d;
	if(b == 0) u.a /= d, u.c /= d;
	return(u);
}

void findroots(int r, int s, splnum roots[2]){
	int discriminant;
	discriminant = r*r + 4*s;
	int x, y, z;
	if (discriminant%4 == 0){
		x = r / 2;
		y = discriminant / 4;
		discriminant = discriminant / 4;
		z = 1;
	}
	else {
		x = r;
		y = discriminant;
		z = 2;
	}
	splnum A, B;
	A.a = x, A.b = 1, A.c = z, A.d = y;
	B.a = x, B.b = -1, B.c = z, B.d = y; 
	roots[0] = A;
	roots[1] = B;
	int temp = Sqrt(discriminant);
	if(temp*temp == discriminant){
		roots[0].a += temp;
		roots[0].b = roots[0].d = 0;
		roots[1].a -= temp;
		roots[1].b = roots[1].d = 0;
	}
	if(roots[0].a%2 == 0 && roots[0].b%2==0 && roots[0].c == 2){
		roots[0].a /= 2;
		roots[0].b /= 2;
		roots[0].c = 1;
	}
	if(roots[1].a%2 == 0 && roots[1].b%2==0 && roots[1].c == 2){
		roots[1].a /= 2;
		roots[1].b /= 2;
		roots[1].c = 1;
	}
}

void splnum::prnspl(splnum u){
	if(u.b != 0 && u.d != 0){
		char c;
		if(u.b > 0) c = '+';
		else c = '-';
		if(absolute(u.b) != 1){
			if(u.c != 1){
				if(u.a != 0) cout<<"("<<u.a<<" "<<c<<" "<<absolute(u.b)<<"sqrt("<<u.d<<")) / "<<u.c;
				else cout<<u.b<<"sqrt("<<u.d<<")) / "<<u.c;
			}
			else{
				if(u.a != 0) cout<<u.a<<" "<<c<<" "<<absolute(u.b)<<"sqrt("<<u.d<<")";
				else cout<<u.b<<"sqrt("<<u.d<<")";
			}
		}
		else{
			if(u.c != 1){
				if(u.a != 0) cout<<"("<<u.a<<" "<<c<<" "<<"sqrt("<<u.d<<")) / "<<u.c;
				else if(c == '-') cout<<c<<" sqrt("<<u.d<<")) / "<<u.c; 
				else cout<<"sqrt("<<u.d<<")) / "<<u.c; 
			}
			else{
				if(u.a != 0) cout<<u.a<<" "<<c<<" "<<"sqrt("<<u.d<<")";
				else if(c == '-') cout<<c<<" sqrt("<<u.d<<")";
				else cout<<"sqrt("<<u.d<<")";
			}
		}
	}
	else{
		if(u.c == 1) cout<<u.a;
		else cout<<u.a<<" / "<<u.c;
	}
}

void solvehomogeneous(int r, int s, int a0, int a1){
	splnum roots[2];
	cout<<"+++ Solving the homogeneous recurrence"<<endl;
	cout<<"Characteristic equation: x^2 + ("<<-r<<")x + ("<<-s<<") = 0"<<endl;
	findroots(r, s, roots);
	cout<<"Root 1 = ";
	roots[0].prnspl(roots[0]);
	cout<<endl;
	cout<<"Root 2 = ";
	roots[1].prnspl(roots[1]);
	cout<<endl;
	cout<<"Homogeneous solution :"<<endl;
	if(r*r + 4*s == 0){
		splnum U, V;
		V.a = a0;
		V.c = 1;
		V.b = V.d = 0;
		splnum temp;
		temp.a = a1;
		temp.c = 1;
		temp.b = temp.d = 0;
		U = U.mulspl(V, roots[0]);
		U = U.subspl(temp, U);
		U = U.divspl(U, roots[0]);
		U = U.simplify(U);
		V = V.simplify(V);
		cout<<" [(";
		U.prnspl(U);
		cout<<")n + (";
		V.prnspl(V);
		cout<<")] ";
		roots[0].prnspl(roots[0]);
		cout<<"^n"<<endl;
	}
	else{
		splnum U, V;
		splnum x, y;
		x.a = a1;
		x.c = 1;
		x.b = x.d = 0;
		y.a = a0;
		y.c = 1;
		y.b = y.d = 0;
		splnum numerator, denominator;
		numerator = numerator.mulspl(y, roots[1]);
		numerator = numerator.subspl(x, numerator);
		denominator = denominator.subspl(roots[0], roots[1]);
		U = U.divspl(numerator, denominator);
		V = V.subspl(y, U);
		U = U.simplify(U);
		V = V.simplify(V);
		cout<<"[";
		U.prnspl(U);
		cout<<"] [";
		roots[0].prnspl(roots[0]);
		cout<<"]^n + [";
		V.prnspl(V);
		cout<<"] [";
		roots[1].prnspl(roots[1]);
		cout<<"]^n"<<endl;
	}
}

void solvenonhomogeneous(int r, int s, int t, int a0, int a1){
	splnum roots[2];
	cout<<"+++ Solving the non homogeneous recurrence"<<endl;
	cout<<"Characteristic equation: x^2 + ("<<-r<<")x + ("<<-s<<") = 0"<<endl;
	findroots(r, s, roots);
	cout<<"Root 1 = ";
	roots[0].prnspl(roots[0]);
	cout<<endl;
	cout<<"Root 2 = ";
	roots[1].prnspl(roots[1]);
	cout<<endl;
	cout<<"Particular solution : ";
	int count = 0;
	splnum X, x, y;
	x.a = a1, x.c = 1, x.b = x.d = 0;
	y.a = a0, y.c = 1, y.b = y.d = 0;
	X.a = 1, X.b = X.d = 0, X.c = 1;
	if(is_equal(roots[0], X)) count++;
	if(is_equal(roots[1], X)) count++;
	if(count == 0){
		X.a = t;
		X.c = 1 - r - s;
		if(X.c < 0){
			X.a *= -1;
			X.c *= -1;
		}
		int d = gcd(absolute(X.a), X.c);
		if(d > 0) X.a /= d; X.c /= d;
		X.prnspl(X);
		cout<<endl;
		y = y.subspl(y, X);
		x = x.subspl(x, X);
	}
	if(count == 1){
		X.a = t;
		X.c = r + 2*s;
		if(X.c < 0){
			X.a *= -1;
			X.c *= -1;
		}
		int d = gcd(absolute(X.a), X.c);
		if(d > 0) X.a /= d; X.c /= d;
		cout<<"[";
		X.prnspl(X);
		cout<<"]"<<" n"<<endl;
		x = x.subspl(x, X);
	}
	if(count == 2){
		X.a = -1*t;
		X.c = r + 4*s;
		if(X.c < 0){
			X.a *= -1;
			X.c *= -1;
		}
		int d = gcd(absolute(X.a), X.c);
		if(d > 0) X.a /= d; X.c /= d;
		cout<<"[";
		X.prnspl(X);
		cout<<"]"<<" n^2"<<endl;
		x = x.subspl(x, X);
	}
	cout<<"Homogeneous Solution : "<<endl;
	if(r*r + 4*s == 0){
		splnum U, V;
		V = y;
		U = U.mulspl(V, roots[0]);
		U = U.subspl(x, U);
		U = U.divspl(U, roots[0]);
		U = U.simplify(U);
		V = V.simplify(V);
		cout<<" [(";
		U.prnspl(U);
		cout<<")n + (";
		V.prnspl(V);
		cout<<")] ";
		roots[0].prnspl(roots[0]);
		cout<<"^n"<<endl;
	}
	else{
		splnum U, V;
		splnum numerator, denominator;
		numerator = numerator.mulspl(y, roots[1]);
		numerator = numerator.subspl(x, numerator);
		denominator = denominator.subspl(roots[0], roots[1]);
		U = U.divspl(numerator, denominator);
		V = V.subspl(y, U);
		U = U.simplify(U);
		V = V.simplify(V);
		cout<<"[";
		U.prnspl(U);
		cout<<"] [";
		roots[0].prnspl(roots[0]);
		cout<<"]^n + [";
		V.prnspl(V);
		cout<<"] [";
		roots[1].prnspl(roots[1]);
		cout<<"]^n"<<endl;
	}
}

signed main(){
	ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    int r, s, t, a0, a1;
    cout<<"r = "; cin>>r;
    cout<<"s = "; cin>>s;
    cout<<"t = "; cin>>t;
    cout<<"a0 = "; cin>>a0;
    cout<<"a1 = "; cin>>a1;
    cout<<endl;
    solvehomogeneous(r, s, a0, a1);
    cout<<endl;
    solvenonhomogeneous(r, s, t, a0, a1);
    return 0;
}