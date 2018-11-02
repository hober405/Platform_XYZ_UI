#include "magneticstructdata.h"

MagneticStructData::MagneticStructData(int n)
{
    _numberOfSensor = n;
    _data = new double [3*_numberOfSensor];
    _updatedData = new unsigned char [8*(_numberOfSensor/8+1)];
}

bool MagneticStructData::input(double inputData[], int index)
{
    for(int i = 0; i < 3; i++) _data[3*index+i] = inputData[i];
    _updatedData[index/8] |= 1<<(index%8);
    for(int i = 0; i < _numberOfSensor/8; i++)
    {
        if(_updatedData[i] != 0xff)
            return false;
    }
    return true;
}

double *MagneticStructData::data() const
{
    return _data;
}
