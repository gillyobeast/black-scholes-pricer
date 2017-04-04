#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "Project.h"
using namespace std;

double stod(string s) {                 // std:stod doesn't work!!

    double d;
    stringstream ss(s); //turn the string into a stream
    ss >> d;            //convert
    return d;
}


int main()
{
    cout.precision(10);

    ifstream data("data.csv");          // creates input stream object 'data' [if i make it fstream, it clears it after reading]
    string line, s0i, s1i;
    vector<double> s0, s1;              // look at pushing the below out to a discrete function
                                        // taking args 'ifstream data, vector<double> s0, vector<double> s1'

    while (getline(data, line)){        // stores each column in data in vectors s0,s1
                                        // processes 'data' line by line - stores each line in 'line'
        stringstream lineStream(line);  // creates stringstream obj 'lineStream' with contents of 'line'

        getline(lineStream,s0i,',' );   // separates 'line' into 's0i' and 's1i'
        double ds0i = stod(s0i);        // converts to double
        s0.push_back(ds0i);             // pushes onto end of s0

        getline(lineStream,s1i);        //same as above three lines
        double ds1i = stod(s1i);
        s1.push_back(ds1i);
    }


    {   double t=0;                        // gets time step t
        while (t <= 0) {                // ensures t is strictly positive
            cout << "Enter (positive) time step, in years: " << endl;
            cin >> t;
        }
    }

    // here we will estimate volatilities sigma0, sigma1 and correlation rho

    vector<double> r0, r1;






    // cause cout for vectors is borked damnit
    cout <<"(  s0     ,   s1   )" << endl;
    for (int i=0;i<s0.size();i++) cout << "(" << s0[i] << "," << s1[i] << ")" << endl;
}
