#ifndef PARSEARRAY_H
#define PARSEARRAY_H

#include <QByteArray>
#include <QString>

//typedef unsigned char byte;
class ParseArray
{
public:
    //header
    bool hasHeader = false;
    int headerIndex = 0;
    int headerLength = 0;
    QByteArray headerValue = { };
    QString headerValueTmp = "";
    // current header index
    int currentHeaderIndex;
    // Footer
    bool hasFooter;
    int footerIndex = 0;
    int footerLength = 0;
    QByteArray footerValue = { };
    QString footerValueTmp = "";
    // current footer index
    int currentFooterIndex;
    // check
    // CRC
    bool hasCRC = false;
    int checkCRCIndex = 0;
    int checkCRCLength = 0;
    // check xor
    bool hasCheckXOR = false;
    int checkXORIndex = 0;
    // length
    bool lengthFix;
    int length;

    // index
    int currentIndex;

    // array
    QByteArray bufferArray;
    int bufferLength;

    QByteArray dataArray;
    ParseArray();
private:
public:

    void setBufferValue(QByteArray buf, int lengthTmp, int checkSumStart);
    void setBufferValueAdjustFooterIndex(QByteArray buf, int buflength, int checkSumStart);
    void setBufferValue(QByteArray buf, int lengthTmp);
    // header
    void enableHeader(int headerindex, int headerlength, QString headervalue);
    // footer
    void enableFooter(int footerindex, int footerlength, QString footervalue);

    // crc
    void enableCRC(int crcindex, int crclength);

    // xor
    void enableCheckXOR(int xorIndex);

    // check Header
    bool testHeader(int hindex);

    // check Footer
    bool testFooter(int findex);

    // test XOR
    bool testXOR(int hindex);// set xindex as headerIndex
    // parsing
    bool parse(int curIndex);
};

#endif // PARSEARRAY_H
