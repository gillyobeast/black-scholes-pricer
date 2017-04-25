#include <iostream>         // console in/out library
#include <string>           // does the string stuff
#include <sstream>          // does the stringstream stuff
#include <fstream>          // file in/out library
#include <stdlib.h>         // adds 'exit()'
#include "Project.h"        // compulsory header file
#include "projectIO.h"      // header of i/o stuff used throughout
#include "calibration.h"    // header of model calibration functions
#include "payoff.h"         // header of payoff functions

using namespace std;

//vector<vector<double> > ifstreamToVector(ifstream _input){
//    string _line, _col0, _col1;
//    vector<vector<double> > _output(2);
//    while (getline(_input, _line)){
//
//        stringstream _lineStream(_line);
//
//        getline(_lineStream,_col0,',' );
//        _output[0].push_back(stod(_col0));
//
//        getline(_lineStream,_col1);
//        _output[1].push_back(stod(_col1));
//    }
//}

int main()
{
    vector<double> historicalVolatility;
    double sampleCovariance;
    vector<double> sampleVariance;
    double historicalCorrelation;
    cout.precision(10);                       // ensures cout outputs doubles to a reasonable accuracy
    /** 0. INTRODUCTION TO PROGRAM */
    cout << "Welcome to the two-dimensional Black-Scholes model option pricer!" << endl;
    cout << "It prices options!" << endl << endl;

    cout << "Before it can price options, the model must be calibrated using historical stock data." << endl;
    /** 1. MODEL CALIBRATION */
                                        // check if file is opened correctly.

    ifstream data("datacopy.csv");               // creates input stream object 'data'
    cout << "Opening historical stock data." << endl;
    if (data.fail()) {
        cout << "Error opening file. Closing program." << endl;
        exit(1);
    }
    cout << "Success opening file. Calibrating model." << endl << endl;
    cout << "Please specify a time interval." << endl;
    double t = getTime(0.25);
    vector<vector<double> > S(2);          // s[i][j] is gonna be S_{i,j}
    string line, s0i, s1i;
    while (getline(data, line)){             // stores each column in data in vectors s[0],s[1]
                                             // processes 'data' line by line - stores each line in 'line'
        stringstream lineStream(line);     // creates stringstream obj 'lineStream' with contents of 'line'

        getline(lineStream,s0i,',' );       // separates 'line' into 's0i' and 's1i'
        S[0].push_back(stod(s0i));           // converts to double and pushes onto end of s[0]

        getline(lineStream,s1i);             // same as above two lines
        S[1].push_back(stod(s1i));     /// THIS IS V MESSY AND I HATE IT but i can't get it to work outside of main
    }
    vector<vector <double> > R=logReturns(S);     // R stores log returns

    sampleVariance=sampleVar(R);
    sampleCovariance=sampleCovar(R);

    for(int i =0;i<2;i++)historicalVolatility.push_back(sqrt(sampleVariance[i]/t));
    historicalCorrelation = sampleCovariance / (t*historicalVolatility[0]*historicalVolatility[1]);
    cout << "Two-dimensional Black-Scholes model calibrated." << endl;
    cout << "Calibration values:" << endl;
    cout << "   Historical Volatility of S0:  "  << historicalVolatility[0] << endl
         << "                            S1:  "  << historicalVolatility[1] << endl;
    cout << "   Historical Correlation:       "  << historicalCorrelation   << endl << endl;

//    int menu=-1;
//    cout << "Please enter an option:" << endl;
//    cout << "1. Recalibrate model." << endl;
//    cout << "0. Exit program." << endl;
//        cin  >> menu;
//    switch(menu){
//        case 1:{
//            break;}
//        case 0:{
//            break;}
//        default:{
//            cout << "Please enter an option:" << endl;
//            cout << "1. Calibrate model." << endl;
//            cout << "0. Exit program." << endl;
//            cin >> menu;}
//    }








    /** 2. TWO-DIMENSIONAL BLACK-SCHOLES MODEL */
                                // note to self: remove these definitions and uncomment following
    double rate = getRate(0.05);
    vector<double> stockCurrent = getStock(100);



                //creates bs model with calibrated parameters and user entered data.
    BSModel2 model(stockCurrent, rate, historicalVolatility, historicalCorrelation);
    while (model.IsWellDefined()==0){                   // validation
        cout << "Please enter valid data." << endl;
        return 1;
    }
    double h = 1;//getTime();

                //creates corr bin model with calibrated bs model and user entered time step.
    CorrBinModel binModel(model,h);
    cout <<"qs:"<< binModel.Get_q() << endl;
    while(binModel.IsArbitrageFree()==0) {
        cout << "There is arbitrage. Closing program." << endl;
        exit(1);
    }




}
