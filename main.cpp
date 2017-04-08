#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "Project.h"
#include "calibration.h"

using namespace std;



int main()
{
    /* 1. MODEL CALIBRATION */

    cout.precision(10);                 // ensures cout outputs doubles to a reasonable accuracy

    ifstream data("data.csv");          // creates input stream object 'data' [if i make it fstream, it clears it after reading]
    string line, s0i, s1i;
    vector<double> s0, s1;

    while (getline(data, line)){        // stores each column in data in vectors s0,s1
                                        // processes 'data' line by line - stores each line in 'line'
        stringstream lineStream(line);  // creates stringstream obj 'lineStream' with contents of 'line'

        getline(lineStream,s0i,',' );   // separates 'line' into 's0i' and 's1i'
        double ds0i = stod(s0i);        // converts to double
        s0.push_back(ds0i);             // pushes onto end of s0

        getline(lineStream,s1i);        // same as above three lines
        double ds1i = stod(s1i);
        s1.push_back(ds1i);             // THIS IS V MESSY AND I HATE IT but i can't get it to work outside of main
    }

    double t = .25; //getTime();
    vector<double> r0=logReturns(s0), r1=logReturns(s1);
    double sampleVar0=sampleVar(r0),sampleVar1=sampleVar(r1);
    double sampleCov=sampleCovar(r0,r1);
    double historicalVolatility0 = sqrt(sampleVar0/t);
    double historicalVolatility1 = sqrt(sampleVar1/t);
    vector<double> historicalVolatility;
    historicalVolatility.push_back(historicalVolatility0);
    historicalVolatility.push_back(historicalVolatility1);
    double historicalCorrelation = sampleCov / (t*historicalVolatility0*historicalVolatility1);


    cout << "Sample Variances:          " << sampleVar0 << endl
         << "                           " << sampleVar1 << endl;
    cout << "Historical Volatilities:   " << historicalVolatility0 << endl
         << "                           " << historicalVolatility1 << endl;
    cout << "Historical Correlation:    " << historicalCorrelation << endl;




    /* 2. TWO-DIMENSIONAL BLACK-SCHOLES MODEL */
    double stock0, stock1, rate;
    vector<double> stockCurrent;
    cout << "Please provide values for initial stock prices and interest rate." << endl;
    cout << "Current stock price of S0:" << endl;
    cin  >> stock0;
    cout << "Current stock price of S1:" << endl;
    cin  >> stock1;
    cout << "Interest Rate (as decimal value):" << endl;
    cin  >> rate;
    stockCurrent.push_back(stock0); stockCurrent.push_back(stock1);
    //BSModel2 Model(stockCurrent, rate, historicalVolatility, historicalCorrelation);

}
