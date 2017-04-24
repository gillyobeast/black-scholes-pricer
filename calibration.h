#ifndef CALIBRATION_H_INCLUDED
#define CALIBRATION_H_INCLUDED



inline vector<vector<double> > logReturns(vector<vector <double> > _vec){    // creates a vector containing log returns of a given vector
    int _m = _vec[0].size();        //sets m to the length of the dataset
    vector<vector<double> > _out(2);
    for (int j=0; j<2;j++){
        for (int i=0; i<_m-1; i++){
            _out[j].push_back(log(_vec[j][i+1]/_vec[j][i]));
        }
    }
    return _out;
}

inline vector<double> vecMean(vector<vector<double> > _vec){                //calculates mean of a vector of doubles
    vector<double> _mean(2,0);
    int _m=_vec[0].size();
    for (int j=0; j<2;j++){
        for (int i=0;i<_m;i++){
            _mean[j] += _vec[j][i];
        }
        _mean[j]=_mean[j]/_m;
    }
    return _mean;
}

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

inline double sampleCovar(vector<vector<double> > _vec){
    int _m=_vec[0].size();
    double _sum = 0;
    for (int i = 0;i<_m;i++){
       _sum+= _vec[0][i]*_vec[1][i];
    }
    return _sum/(_m-1) - (_m*vecMean(_vec)[0]*vecMean(_vec)[1])/(_m-1);
}
#endif // CALIBRATION_H_INCLUDED
