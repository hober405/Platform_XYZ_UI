#include "parsearray.h"
#include <QDebug>

ParseArray::ParseArray()
{
    hasCheckXOR = false;
    hasCRC = false;
    hasFooter = false;
    hasHeader = false;
}


void ParseArray::setBufferValue(QByteArray buf, int lengthTmp, int checkSumStart)
{
    if (hasCheckXOR)
    {
        bufferLength = checkXORIndex + 1;
    }
    else if (hasFooter)
    {
        bufferLength = footerIndex + footerLength + 1;
    }
    else if (hasHeader)
        bufferLength = headerIndex + headerLength + 1;
    else
        bufferLength = lengthTmp;



    // header values
    if (hasHeader)
    {
        for (int i = headerIndex, j = 0; i < headerLength; i++, j++)
            bufferArray[i] = headerValue[j];
        for (int i = headerIndex + headerLength, j = 0; j < lengthTmp; i++, j++)
            bufferArray[i] = buf[j];
    }
    else
    {
        for (int j = 0; j < lengthTmp; j++)
            bufferArray[j] = buf[j];
    }
    // footer values
    if (hasFooter)
    {
        for (int i = footerIndex, j = 0; j < footerLength; i++, j++)
            bufferArray[i] = footerValue[j];
    }
    // compute xor
    if (hasCheckXOR)
    {
        char XOR = 0;
        for (int i = checkSumStart; i < bufferLength - 1; i++)
        {
            XOR ^= bufferArray[i];
        }
        bufferArray[bufferLength - 1] = XOR;
    }
}

void ParseArray::setBufferValueAdjustFooterIndex(QByteArray buf, int buflength, int checkSumStart)
{
    bufferLength = (headerIndex + headerLength + buflength + footerLength + 1);
    int i = 0, j = 0;
    // header values
    for (i = headerIndex, j = 0; i < headerLength; i++, j++)
        bufferArray[i] = headerValue[j];
    for (i = headerIndex + headerLength, j = 0; j < buflength; i++, j++)
        bufferArray[i] = buf[j];

    // footer values
    for (i = headerIndex + headerLength + buflength, j = 0; j < footerLength; i++, j++)
        bufferArray[i] = footerValue[j];
    // compute xor
    char XOR = 0;
    for (i = checkSumStart; i < bufferLength - 1; i++)
    {
        XOR ^= bufferArray[i];
    }
    bufferArray[bufferLength - 1] = XOR;
}


void ParseArray::setBufferValue(QByteArray buf, int lengthTmp)
{
    if (hasCheckXOR)
    {
        bufferLength = checkXORIndex + 1;
    }
    else if (hasFooter)
    {
        bufferLength = footerIndex + footerLength + 1;
    }
    else if (hasHeader)
        bufferLength = headerIndex + headerLength + 1;
    else
        bufferLength = lengthTmp;



    // header values
    if (hasHeader)
    {
        for (int i = headerIndex, j = 0; i < headerLength; i++, j++)
            bufferArray[i] = headerValue[j];
        for (int i = headerIndex + headerLength, j = 0; j < lengthTmp; i++, j++)
            bufferArray[i] = buf[j];
    }
    else
    {
        for (int j = 0; j < lengthTmp; j++)
            bufferArray[j] = buf[j];
    }
    // footer values
    if (hasFooter)
    {
        for (int i = footerIndex, j = 0; j < footerLength; i++, j++)
            bufferArray[i] = footerValue[j];
    }
    // compute xor
    if (hasCheckXOR)
    {
        char XOR = 0;
        for (int i = 0; i < bufferLength - 1; i++)
        {
            XOR ^= bufferArray[i];
        }
        bufferArray[bufferLength - 1] = XOR;
    }
}

void ParseArray::enableHeader(int headerindex, int headerlength, QString headervalue)
{
    hasHeader = true;
    headerIndex = headerindex;
    headerLength = headerlength;
    headerValueTmp = headervalue;
    headerValue = headervalue.toLocal8Bit();
}

void ParseArray::enableFooter(int footerindex, int footerlength, QString footervalue)
{
    hasFooter = true;
    footerIndex = footerindex;
    footerLength = footerlength;
    footerValueTmp = footervalue;
    footerValue = footervalue.toLocal8Bit();
}

void ParseArray::enableCRC(int crcindex, int crclength)
{
    hasCRC = true;
    checkCRCIndex = crcindex;
    checkCRCLength = crclength;
}

void ParseArray::enableCheckXOR(int xorIndex)
{
    hasCheckXOR = true;
    checkXORIndex = xorIndex;
}

bool ParseArray::testHeader(int hindex)
{
    int i;
    for (i = 0; i < headerLength; i++)
    {
        if (bufferArray[(hindex + i) % bufferLength] != headerValue[i])
            return false;
    }
    return true;
}

bool ParseArray::testFooter(int findex)
{
    int i;
    for (i = 0; i < footerLength; i++)
    {
        if (bufferArray[(findex + i) % bufferLength] != footerValue[i])
            return false;
    }
    return true;
}

bool ParseArray::testXOR(int hindex)
{
    int i = 0;
    char x_or = 0;
    for (i = hindex; i < hindex+length; i++)
    {
        x_or ^= bufferArray[i % bufferLength];
    }
    if (x_or == 0)
        return true;
    else
        return false;
}

bool ParseArray::parse(int curIndex)
{
    // shift curIndex to end
    if (hasCheckXOR)
    {
        curIndex -= checkXORIndex;
        curIndex += bufferLength;
        curIndex %= bufferLength;
    }
    else if (hasFooter)
    {
        curIndex -= footerIndex;
        curIndex += bufferLength;
        curIndex %= bufferLength;
    }

    curIndex %= bufferLength;

    //
    if (hasHeader)
    {
        // test header
        if (testHeader(curIndex))
        {
            // pass header check
        }
        else{// fail header
//            qDebug()<<"header fail"<<endl;
            return false;
        }
    }
    // test footer
    if (hasFooter)
    {
        if (testFooter((curIndex + (footerIndex - headerIndex)) % bufferLength))
        {
            // pass footer check
        }
        else{// fail footer
            qDebug()<<"footer fail"<<endl;
            return false;
        }
    }
    // test xor
    if (hasCheckXOR)
    {
        if (!testXOR(curIndex)){// fail check
            qDebug()<<"XOR fail"<<endl;
            char x_or = 0;
            for (int i = curIndex; i < curIndex+length-1; i++)
            {
                x_or ^= bufferArray[i % bufferLength];
            }
            qDebug()<<"correct XOR: "<<x_or;
            return false;
        }
    }
    // pass all test
    currentHeaderIndex = curIndex;
    currentFooterIndex = (curIndex + (footerIndex - headerIndex));
    return true;
}
