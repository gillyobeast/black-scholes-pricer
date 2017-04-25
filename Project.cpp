#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "Project.h"
#include "binomial.h"
#include "solver.h"
using namespace std;




BSModel2::BSModel2(vector<double> S0_, double r_, vector<double> sigma_, double rho_)
                    :S0(S0_),r(r_),sigma(sigma_),rho(rho_){}    ///using initializer list

bool BSModel2::IsWellDefined() const{
    cout << "Validating Black-Scholes model data." << endl;
    if (S0[0] <= 0||S0[1]<=0) {
        cout << "Invalid current stock prices. Closing program." << endl;
        return 0;
    }
    if (r < 0) {
        cout << "Invalid interest rate. Closing program." << endl;
    return 0;
    }
    if (sigma[0] <= 0||sigma[1] < 0) {
        cout << "Error with calibration data: Historical Volatility. Closing program." << endl;
    return 0;
    }
    if (rho<-1 || rho>1) {
        cout << "Error with calibration data: Historical Correlation. Closing program." << endl;
    return 0;
    }
    cout << "Black-Scholes model validated." << endl;
    return 1;
}



///Constructor. Computes qs, alphas and betas, but does not include any error checking.
CorrBinModel::CorrBinModel (const BSModel2& model, double h_):S0(model.Get_S0()),r(model.Get_r()),h(h_){

    vector<double> sigma = model.Get_sigma();
    double rho = model.Get_rho();                   /// so we only have to fetch rho and sigma once
    double rooth = sqrt(h);                         /// and calculate sqrt(h) once

    for(int i=0;i<2;i++){
        double drift=(r-0.5*sigma[i]*sigma[i])*h;
        alpha.push_back(drift);
    }

    beta.push_back(sigma[0]*rooth);
    beta.push_back(sigma[1]*rho*rooth);
    beta.push_back(sigma[1]*sqrt((1-rho*rho*h)));

    long double discount = exp(r*h);

    q.resize(2);

    /// used the rearranged form from hint

    q[0] = (discount*S0[0]-S(1,0,0)[0])/(S(1,1,0)[0]-S(1,0,0)[0]);
    //doesn't seem to depend on h...

    //this is the messiest thing ever but its the only way i can think to do it
    Func myFunction(q[0],S(1,0,0)[1],S(1,0,1)[1],S(1,1,0)[1],S(1,1,1)[1]);
    q[1] = SolveByBisect(&myFunction,discount*S0[1],0,1,EPSILON);


}
//  function to solve:    return (1-q0)*(1-x)*S(1,0,0)[1]+q0*(1-x)*S(1,1,0)[1]
//                              +(1-q0)*x*S(1,0,1)[1]+q0*x*S(1,1,1)[1];



        ///Computes stock price at node (j0,j1) time step n
vector<double> CorrBinModel::S (int n, int j0, int j1) const{
    vector<double> _S;
    _S.push_back(S0[0]*exp(alpha[0]*n+beta[0]*(2*j0-n)));
    _S.push_back(S0[1]*exp(alpha[1]*n+beta[1]*(2*j0-n)+beta[2]*(2*j1-n)));
    return _S;
}

        ///returns 1 if 0<q[k]<1 for k=0,1
bool CorrBinModel::IsArbitrageFree() const{
    for(int i=0;i<2;i++){
        if (q[i]<=0||q[i]>=1) return 0;
    }
    return 1;
}

        ///Probability of node (j0,j1) at time step n -- aka Q(n;j0,j1)
double CorrBinModel::Prob(int n, int j0, int j1) const{

    return binomial(n,j0)*binomial(n,j1)*pow(q[0],j0)*pow(1-q[0],n-j0)*pow(q[1],j1)*pow(1-q[1],n-j1);

}
