#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "Project.h"
#include "calibration.h"

using namespace std;



int main()
{
    /** 1. MODEL CALIBRATION */

    cout.precision(10);                       // ensures cout outputs doubles to a reasonable accuracy
    ifstream data("data.csv");               // creates input stream object 'data' [if i make it fstream, it clears it after reading]

    string line, s0i, s1i;
    vector<vector<double> > S(2);          // s[i][j] is gonna be S_{i,j}

    while (getline(data, line)){             // stores each column in data in vectors s[0],s[1]
                                             // processes 'data' line by line - stores each line in 'line'
        stringstream lineStream(line);     // creates stringstream obj 'lineStream' with contents of 'line'

        getline(lineStream,s0i,',' );       // separates 'line' into 's0i' and 's1i'
        S[0].push_back(stod(s0i));           // converts to double and pushes onto end of s[0]

        getline(lineStream,s1i);             // same as above two lines
        S[1].push_back(stod(s1i));       /// THIS IS V MESSY AND I HATE IT but i can't get it to work outside of main
    }

    double t = .25; //getTime();                    // commented out for testing reasons
    vector<vector <double> > R=logReturns(S);     // R stores log returns

    vector<double> sampleVariance=sampleVar(R);
    double sampleCovariance=sampleCovar(R);
    vector<double> historicalVolatility;
    for(int i =0;i<2;i++){
        historicalVolatility.push_back(sqrt(sampleVariance[i]/t));
    }
    double historicalCorrelation = sampleCovariance / (t*historicalVolatility[0]*historicalVolatility[1]);

    cout << "Historical Volatilities:   "  << historicalVolatility[0] << endl
         << "                           "  << historicalVolatility[1] << endl;
    cout << "Historical Correlation:    "  << historicalCorrelation << endl;




    /** 2. TWO-DIMENSIONAL BLACK-SCHOLES MODEL */
    double rate=0.05;  // note to self: remove these definitions and uncomment following
    vector<double> stockCurrent(2,100);

    /// make a 'getInput(stockCurrent,rate)' fn and make it do validation
//    cout << "Please provide values for initial stock prices and interest rate." << endl;
//    cout << "Current stock price of S0:" << endl;
//    cin  >> stockCurrent[0];
//    cout << "Current stock price of S1:" << endl;
//    cin  >> stockCurrent[1];
//    cout << "Interest Rate (as decimal value):" << endl;
//    cin  >> rate;


    BSModel2 model(stockCurrent, rate, historicalVolatility, historicalCorrelation);    //creates bs model with given params
    while (model.IsWellDefined()==0){                   // validation
        cout << "Please enter valid data." << endl;
        return 1;
    }
    double h = 1;//getTime();
    CorrBinModel binModel(model,h);                         //creates corr bin model with given params
    cout << binModel.Get_q() << endl;
    while(binModel.IsArbitrageFree()==0) {
        cout << "There is arbitrage. Closing program." << endl;
        return 1;
    }
    cout << binModel.Prob(10,10,11);


}
