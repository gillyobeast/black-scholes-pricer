#include <iostream>         // console in/out library
#include <string>           // does the string stuff
#include <sstream>          // does the stringstream stuff
#include <fstream>          // file in/out library
#include <stdlib.h>         // adds 'exit()'
#include "Project.h"        // compulsory header file
#include "projectIO.h"      // i/o stuff, used throughout
#include "calibration.h"    // model calibration functions
#include "payoff.h"         // payoff functions
#include "pricer.h"         // PriceEuropean()

using namespace std;


int main()
{
    cout.precision(10);
    /** INTRODUCTION TO PROGRAM */
    cout << "Welcome to the two-dimensional Black-Scholes model option pricer!" << endl;
    cout << "It prices options!" << endl << endl;

    /** MODEL CALIBRATION */
    cout << "Before it can price options, the model must be calibrated using historical stock data." << endl;
    ifstream data("data.csv");
    cout << "Opening historical stock data." << endl;
    if (data.fail()) {
        cout << "Error opening file. Closing program." << endl;
        exit(1);
    }
    cout << "Success opening file. Calibrating model." << endl;

    vector<vector<double> > S(2);       //stores historical stock data.
    string line, s0i, s1i;
    while (getline(data, line)){
        stringstream lineStream(line);
        getline(lineStream,s0i, ',');
        S[0].push_back(stod(s0i));
        getline(lineStream,s1i);
        S[1].push_back(stod(s1i));
    }
    data.close();

    cout << "Please specify the time interval for the historical data." << endl;
    double t = getTime();
    vector<vector<double> > R=logReturns(S);
    vector<double> sampleVariance = sampleVar(R);
    double sampleCovariance = sampleCovar(R);
    vector<double> historicalVolatility;
    for (int i = 0; i < 2; i++) historicalVolatility.push_back(sqrt(sampleVariance[i]/t));
    double historicalCorrelation = sampleCovariance / (t*historicalVolatility[0]*historicalVolatility[1]);

    cout << "Two-dimensional Black-Scholes model calibrated." << endl;
    cout << "Calibration values:" << endl;
    cout << "   Historical Volatility of S0:  "  << historicalVolatility[0] << endl
         << "                            S1:  "  << historicalVolatility[1] << endl;
    cout << "   Historical Correlation:       "  << historicalCorrelation   << endl << endl;

    /** 2-DIMENSIONAL BLACK-SCHOLES MODEL */
    cout << "Next, a Black-Scholes model needs to be set up with the calibrated data and your input:" << endl;

    double rate = getRate();

    vector<double> stockCurrent = getStock();

    BSModel2 model(stockCurrent, rate, historicalVolatility, historicalCorrelation);
    if (model.IsWellDefined()==0){
        cout << "Please enter valid data." << endl;
        exit(1);
    }

    /** OPTION PRICING */
    cout << "Now stock prices can be calculated." << endl;

    cout << "Please enter an expiry date for the option." << endl;
    int expiry = getTime();

    MinCall min_call;
    MaxCall max_call;
    SpreadCall spread_call;
    /* add more payoff funtion declarations here and expand options in the following 'while' loop and 'if-else' statements */
    Payoff* chosen_payoff;


    int payoff_choice=-1;
    while (payoff_choice < 1 || payoff_choice > 3){
        cout << "Please choose an option payoff function:" << endl;
        cout << "   1. Spread call." << endl;
        cout << "   2. Min call." << endl;
        cout << "   3. Max call." << endl;
        cin  >> payoff_choice;
    }
    if (payoff_choice == 1){
        chosen_payoff = &spread_call;
        cout << "Pricing with 'spread call' payoff function." << endl;
    } else if (payoff_choice == 2){
        chosen_payoff = &min_call;
        cout << "Pricing with 'min call' payoff function." << endl;
    } else if (payoff_choice == 3){
        chosen_payoff = &max_call;
        cout << "Pricing with 'max call' payoff function." << endl;
    }

    vector<double> strikes = getStrike();

    cout << "Calculating European option prices. Please wait." << endl;
    string euro_filename = "Eprices.csv";
    ofstream Eprices(euro_filename.c_str());
        if (Eprices.fail()) {
        cout << "Error opening file. Closing program." << endl;
        exit(1);
    }
    for (int j=1; j <= 5; j++){
        Eprices << ",N=" << 100*j;
    } Eprices << endl;
    for (double i = 0; i <= 10; i++){
        double strike = (i/10) * strikes[1] + (1-i/10) * strikes[0];
        min_call.set_K(strike);     // this is necessary because Payoff has no get_K() member.
        max_call.set_K(strike);     // could otherwise have used '&chosen_payoff->set_K(strike);'
        spread_call.set_K(strike);
        Eprices << "K=" << strike;
        for (double j = 1; j <= 5; j++){
            CorrBinModel binModel(model,expiry/(100*j));
            Eprices << "," << PriceEuropean(binModel, *chosen_payoff, 100*j);
            cout << ".";
        }
        Eprices << endl;
        cout << endl;
    }
    Eprices.close();
    cout << "Done. European option prices can be found in '" << euro_filename << "'" << endl << endl;


    cout << "Calculating American option prices. Please wait." << endl;
    string amer_filename = "Aprices.csv";
    ofstream Aprices(amer_filename.c_str());
        if (Aprices.fail()) {
        cout << "Error opening file. Closing program." << endl;
        exit(1);
    }
    for (int j=1; j <= 5; j++){
        Aprices << ",N=" << 100*j;
    } Aprices << endl;
    for (double i = 0; i <= 10; i++){
        double strike = (i/10) * strikes[1] + (1-i/10) * strikes[0];
        min_call.set_K(strike);
        max_call.set_K(strike);
        spread_call.set_K(strike);
        Aprices << "K=" << strike;
        for (double j = 1; j <= 5; j++){
            CorrBinModel binModel(model,expiry/(100*j));
            Aprices << "," << PriceAmerican(binModel, *chosen_payoff, 100*j);
            cout << ".";

        }
        Aprices << endl;
        cout << endl;
    }
    Aprices.close();
    cout << "Done. American option prices can be found in '" << amer_filename << "'" << endl << endl;

    cout << "Press a key and then return to close the program." << endl;
    char leave;
    cin  >> leave;



}
