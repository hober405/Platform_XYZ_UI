#ifndef MAGNETICSTRUCTDATA_H
#define MAGNETICSTRUCTDATA_H

class MagneticStructData
{
public:
    MagneticStructData(int n);
    bool input(double inputData[], int index);

    double *data() const;

private:
    MagneticStructData& operator=(MagneticStructData& mag){}
    int _numberOfSensor;
    double *_data;
    unsigned char *_updatedData;
};

#endif // MAGNETICSTRUCTDATA_H
