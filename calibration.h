#ifndef CALIBRATION_H_INCLUDED
#define CALIBRATION_H_INCLUDED

/** this file is for model calibration funtions */

/// calculates log returns of dataset, returns as vector of vectors
inline vector<vector<double> > logReturns(vector<vector <double> > _vec){
    vector<vector<double> > _out(2);  // initialises _out with two empty vectors
    int _m = _vec[0].size();        // sets _m to the length of the dataset
    for (int j=0; j<2;j++){
        for (int i=0; i<_m-1; i++){
            _out[j].push_back(log(_vec[j][i+1]/_vec[j][i]));
        }
    }
    return _out;
}

/// calculates means of dataset, returns as vector
inline vector<double> vecMean(vector<vector<double> > _vec){
    vector<double> _mean(2,0);     // initialises _mean with two values of 0
    int _m = _vec[0].size();        // sets _m to the length of the dataset
    for (int j=0; j<2;j++){
        for (int i=0;i<_m;i++){
            _mean[j] += _vec[j][i];
        }
        _mean[j]=_mean[j]/_m;
    }
    return _mean;
}

/// calculates sample variance of dataset, returns as vector
inline vector<double> sampleVar(vector<vector<double> > _vec){
    vector<double> _var(2,0);
    vector<double> _mean = vecMean(_vec);
    int _m=_vec[0].size();
    for(int j=0;j<2;j++){
        for (int i=0;i<_m;i++){
            _var[j] += _vec[j][i]*_vec[j][i];
        }
        _var[j] = _var[j]/(_m-1)+(_m*_mean[j]*_mean[j])/(_m-1);
    }
    return _var;
}

/// calculates sample covariance of dataset, returns as double
inline double sampleCovar(vector<vector<double> > _vec){
    int _m=_vec[0].size();
    double _sum = 0;
    for (int i = 0;i<_m;i++){
       _sum+= _vec[0][i]*_vec[1][i];
    }
    return _sum/(_m-1) - (_m*vecMean(_vec)[0]*vecMean(_vec)[1])/(_m-1);
}


#endif // CALIBRATION_H_INCLUDED
