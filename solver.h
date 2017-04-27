#ifndef SOLVER_H_INCLUDED
#define SOLVER_H_INCLUDED

/** this file contains a nonlinear solver by bisection, and
    a class with very specific data members required to solve
    the specific equation i need to solve in Project.cpp   */


template<typename F> double SolveByBisect(F* Function, double target, double leftEnd,
                                        double rightEnd, double Acc){
    double left = leftEnd, right = rightEnd, mid = (left + right)/2;
    double y_left = Function->Value(left) - target, y_mid = Function->Value(mid) - target;
    while (mid-left > Acc){
        if ((y_left > 0 && y_mid > 0) || (y_left < 0&& y_mid < 0)){
            left = mid; y_left = y_mid;
        }
        else right = mid;
        mid = (left  +right)/2;
        y_mid = Function->Value(mid) - target;
    }
    return mid;
}

class Func
{
public:
    Func(double _q0, double _S100, double _S101, double _S110,double _S111)
    :q0(_q0),S100(_S100),S101(_S101),S110(_S110),S111(_S111){};
    double Value(double x);
private:
    double q0;
    double S100;
    double S101;
    double S110;
    double S111;
};

double Func::Value(double x){
    return (1 - q0) * (1 - x) * S100 + q0 * (1 - x) * S110
                     + (1 - q0) * x * S101 + q0 * x * S111;
}

#endif // SOLVER_H_INCLUDED
