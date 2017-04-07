#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "Project.h"
#include "calibration.h"

using namespace std;




int main()
{
    cout.precision(10);                 // ensures cout outputs nicely

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
        s1.push_back(ds1i);
    }


    double t = .25; //getTime();
    vector<double> r0, r1;                  // r0[i-1] will store r0,i; log returns

    for (int i=0; i<s0.size()-1; i++){      // would it be more efficient than push_back to initialise to s0.size()-1 and assign directly?
        r0.push_back(log(s0[i+1]/s0[i]));
    }
    for (int i=0; i<s1.size()-1; i++){
        r1.push_back(log(s1[i+1]/s1[i]));
    }

    double sampleVar0=sampleVar(r0),sampleVar1=sampleVar(r1);
    double sampleCov=sampleCovar(r0,r1);                           //sample covariance


    double historicalVolatility0 = sqrt(sampleVar0/t);
    double historicalVolatility1 = sqrt(sampleVar1/t);
    double historicalCorrelation = sampleCov / (t*historicalVolatility0*historicalVolatility1);

                                            // cause cout for vectors is borked damnit
    cout << "Sample Variances: " << sampleVar0 << ", " << sampleVar1 << endl;
    cout << historicalVolatility0 << endl;
    cout << historicalVolatility1 << endl;
    cout << historicalCorrelation << endl;
}
