#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "Project.h"
#include "binomial.h"
#include "solver.h"
using namespace std;

/** this file implements member functions of classes
    `BSModel2` and `CorrBinModel` defined in project.h */


/**
    Constructor for BSModel2 class.
*/
BSModel2::BSModel2(vector<double> S0_, double r_, vector<double> sigma_, double rho_)
                    :S0(S0_),r(r_),sigma(sigma_),rho(rho_){}

/**
    Checks whether all data members of BSModel2 object are valid.
    @return 1 if all data are valid, 0 if not valid
*/
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
    cout << "Black-Scholes model validated." << endl << endl;
    return 1;
}



/**
    Constructor for CorrBinModel class.
*/
CorrBinModel::CorrBinModel (const BSModel2& model, double h_)
             :S0(model.Get_S0()),r(model.Get_r()),h(h_){
    vector<double> sigma = model.Get_sigma();
    double rho = model.Get_rho();
    double rooth = sqrt(h);

    double drift;
    for (int i=0;i<2;i++){
        drift =(r-0.5*sigma[i]*sigma[i])*h;
        alpha.push_back(drift);
    }

    beta.push_back(sigma[0]*rooth);
    beta.push_back(sigma[1]*rho*rooth);
    beta.push_back(sigma[1]*sqrt((1-rho*rho*h)));

    long double discount = exp(r*h);
    q.push_back((discount*S0[0]-S(1,0,0)[0])/(S(1,1,0)[0]-S(1,0,0)[0]));
    Func myFunction(q[0],S(1,0,0)[1],S(1,0,1)[1],S(1,1,0)[1],S(1,1,1)[1]);
    double target = discount*S0[1];
    q.push_back(SolveByBisect(&myFunction,target,0,1,EPSILON));
}


/**
    Computes stock prices at node (j0,j1), time step n.
    @param n time step
    @param j0 first coord of node
    @param j1 second coord of node
    @return stock prices at node (j0,j1) time step n
*/
vector<double> CorrBinModel::S (int n, int j0, int j1) const{
    vector<double> _S;
    _S.push_back(S0[0]*exp(alpha[0]*n+beta[0]*(2*j0-n)));
    _S.push_back(S0[1]*exp(alpha[1]*n+beta[1]*(2*j0-n)+beta[2]*(2*j1-n)));
    return _S;
}

/**
    Checks whether model is free of arbitrage.
    @return 1 if no arbitrage (if both values in q are true probabilites), else 0
*/

bool CorrBinModel::IsArbitrageFree() const{
    for(int i=0;i<2;i++){
        if (q[i]<=0||q[i]>=1) return 0;
    }
    return 1;
}

/**
    Computes risk-neutral probability of node (j0,j1), at time step n
    @param n time step
    @param j0 first coord of node
    @param j1 second coord of node
    @return risk-neutral probability of node (j0,j1) time step n
*/
double CorrBinModel::Prob(int n, int j0, int j1) const{
    return binomial(n,j0)
            *binomial(n,j1)
            *pow(q[0],j0)
            *pow(1-q[0],n-j0)
            *pow(q[1],j1)
            *pow(1-q[1],n-j1);
}



