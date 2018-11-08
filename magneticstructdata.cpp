#include "magneticstructdata.h"

#define NUMBER_OF_HISTORY 100
MagneticStructData::MagneticStructData(int n)
{
    _numberOfSensor = n;
    _data = new double [3*_numberOfSensor];
    for(int i = 0; i < 3*_numberOfSensor; i++) _data[i] = 0;
    _calibrateData = new double [3*_numberOfSensor];
    for(int i = 0; i < 3*_numberOfSensor; i++) _calibrateData[i] = 0;
    _outputData = new double [3*_numberOfSensor];
    for(int i = 0; i < 3*_numberOfSensor; i++) _outputData[i] = 0;
    _updatedData = new unsigned char [8*(_numberOfSensor/8+1)];
    _history = new double* [NUMBER_OF_HISTORY];
    for(int i = 0; i < NUMBER_OF_HISTORY; i++)
    {
        _history[i] = new double [3*_numberOfSensor];
        for(int j = 0; j < 3*_numberOfSensor; j++) _history[i][j] = 0;
    }
    _historyIndex = 0;
}

bool MagneticStructData::input(double inputData[], int index)
{
    for(int i = 0; i < 3; i++)
    {
        _data[3*index+i] = inputData[i];
    }
    _updatedData[index/8] |= 1<<(index%8);
    for(int i = 0; i < _numberOfSensor/8; i++)
    {
        if(_updatedData[i] != 0xff)
            return false;
    }
    for(int i = 0; i < _numberOfSensor*3; i++)
    {
        double historyMean = 0;
        for(int j = 0; j < NUMBER_OF_HISTORY; j++)
        {
            historyMean += _history[j][i];
        }
        historyMean /= double(NUMBER_OF_HISTORY);
        _outputData[i] = _data[i] - historyMean;
//        _calibrateData[i] = _data[i];
        _historyIndex++;
        _history[_historyIndex%=NUMBER_OF_HISTORY][i] = _data[i];
    }
    return true;
}

double *MagneticStructData::data() const
{
    for(int i = 0; i < _numberOfSensor/8; i++)
    {
        _updatedData[i] = 0;
    }
    return _outputData;
}
