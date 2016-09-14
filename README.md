# dual-numbers
A small library of functions implemneting dual arithmetic. The dual numbers make it easy to compute derivatives of functions and do so accurately (up to machine precision). Derivatives are not approximated; they are computed exactly. The only limitation is the precision of the machine on which the code is being executed.

The supported functions are:
* arithmetic operations `Add`, `Sub`, `Mul`, `Div`
* `Sin`
* `Cos`
* `Exp`
* `Log`
* `Power`
* `Abs`

# Example
Say we wanted to compute the derivative of the function `(x + 1)*(x - 2)/(x + 3)` at `x = 3`. We convert this function into code by using the primitives listed above:

<pre>
DualNumber Func(double x) {
	DualNumber d = MakeVariable(x);
	return Div(Mul(Add(d, MakeConstant(1)), Sub(d, MakeConstant(2))),
		Add(d, MakeConstant(3)));
}
</pre>
  
The above function operates on dual numbers and returns a dual number. `DualNumber` has a `real` part and a `dual` part. The `real` part stores the value of the function at the given point and the `dual` part stores the first order derivative of the function at the given point. A call to `Func(3)` returns a dual number whose `real` part is equal ot `0.666667` and whose `dual` part is equal to `0.722222`.

We can compute the derivatives of complicated functions by using this technique. The functions are assumed to be differntiable at the input points.
