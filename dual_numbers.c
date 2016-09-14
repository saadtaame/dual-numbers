
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>

typedef struct {
	double real;
	double dual;
} DualNumber;

DualNumber MakeDual(double r, double d) {
	DualNumber dual = {r, d};
	return dual;
}

DualNumber MakeConstant(double c) {
	return MakeDual(c, 0);
}

DualNumber MakeVariable(double v) {
	return MakeDual(v, 1);
}

DualNumber Add(DualNumber A, DualNumber B) {
	return MakeDual(A.real + B.real, A.dual + B.dual);
}

DualNumber Sub(DualNumber A, DualNumber B) {
	return MakeDual(A.real - B.real, A.dual - B.dual);
}

DualNumber Mul(DualNumber A, DualNumber B) {
	return MakeDual(A.real * B.real, A.real * B.dual + A.dual * B.real);
}

DualNumber Div(DualNumber A, DualNumber B) {
	assert(B.real != 0);
	return MakeDual(A.real / B.real, (A.dual - (A.real / B.real) * B.dual) / B.real);
}

DualNumber Sin(DualNumber A) {
	return MakeDual(sin(A.real), A.dual * cos(A.real));
}

DualNumber Cos(DualNumber A) {
	return MakeDual(cos(A.real), -A.dual * sin(A.real));
}

DualNumber Exp(DualNumber A) {
	return MakeDual(exp(A.real), A.dual * exp(A.real));
}

DualNumber Log(DualNumber A) {
	assert(A.real > 0);
	return MakeDual(log(A.real), A.dual / A.real);
}

DualNumber Abs(DualNumber A) {
	assert(A.real != 0);
	return MakeDual(abs(A.real), A.dual * ((A.real > 0) ? 1 : -1));
}

DualNumber Power(DualNumber A, double e) {
	return MakeDual(pow(A.real, e), A.dual * e * pow(A.real, e - 1));
}

DualNumber Func(double x) {
	DualNumber d = MakeVariable(x);
	return Div(Mul(Add(d, MakeConstant(1)), Sub(d, MakeConstant(2))),
		Add(d, MakeConstant(3)));
}

int main(void) {
	DualNumber d = Func(3);
	printf("%f %f\n", d.real, d.dual);
	return 0;
}
