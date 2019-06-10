#include "envelopetracker.h"
//#include <QDebug>
EnvelopeTracker::EnvelopeTracker()
{
    currentIndex = 0;
    envelopeLength = 0;
    envelopeDataLength = 0;
    currentDataIndex = 0;
    bufferTailIndex = -1;
    envelopeListIndex = 0;
    envelopeListLength = 100;
    envelopeListIndexFront = -1;
    envelopeList = new Envelope*[envelopeListLength]{};
    bufferArray = NULL;
}

void EnvelopeTracker::parse(char * buf, int bufLength)
{
    int byteAmountToAddInBuffer = 0;
    int bufOffset = 0;/*
    int bufIndex;
    if(bufferTailIndex < 0){
        bufIndex = 0;
    }
    else if(bufferTailIndex<currentIndex){
        bufIndex = -(bufferTailIndex + bufferLength - currentIndex)-1;
    }
    else{
        bufIndex = -(bufferTailIndex - currentIndex)-1;
    }*/
    while(1){
        byteAmountToAddInBuffer = (bufLength<bufferLength/2)?bufLength:bufferLength/2;
        for(int i = 0; i < byteAmountToAddInBuffer; i++)
            bufferArray[(i+bufferTailIndex+1)%bufferLength] = buf[i+bufOffset];
        bufferTailIndex += byteAmountToAddInBuffer;
        bufferTailIndex %= bufferLength;

        int numToParse=(currentIndex>bufferTailIndex)?(bufferTailIndex + bufferLength - currentIndex):(bufferTailIndex - currentIndex);
//        qDebug()<<"num to parse: " << numToParse << bufferTailIndex << currentIndex << byteAmountToAddInBuffer << endl;
        for(;numToParse>=envelopeLength-1;numToParse--)
        {
            if(testHeader()&&testFooter()&&testXOR()){

                // pass all test
                currentHeaderIndex = currentIndex;
                currentDataIndex = currentIndex + headerLength;

                char * data = new char[envelopeDataLength];
                for(int i = 0; i < envelopeDataLength; i++){
                    data[i] = bufferArray[(i+currentDataIndex)%bufferLength];
//                    if(bufIndex>=-2) buf[i+bufIndex+1] = 'J';
                }
                Envelope* newEnvelope = new Envelope(envelope.setEnvelopeData(data, envelopeDataLength));
                if(envelopeListIndexFront == -1) envelopeListIndex = 0;
                envelopeList[envelopeListIndex++] = newEnvelope;
                envelopeListIndex %= envelopeListLength;
                if(envelopeListIndexFront == -1) envelopeListIndexFront = 0;
//                qDebug()<<"get 1 env, bufIndex: "<<bufIndex << endl;
            }
//            else if(testHeader()&&testFooter()&&!testXOR()) qDebug()<<"fail xor\n";
            ++currentIndex %= bufferLength;
//            bufIndex++;

        }
        if(byteAmountToAddInBuffer != bufLength){
            bufLength -= bufferLength/2;
            bufOffset += bufferLength/2;
        }
        else break;
    }
}

int EnvelopeTracker::bufferDataLength()
{
    if(bufferTailIndex < 0) return 0;
    else if(bufferTailIndex<currentIndex) return bufferTailIndex+bufferLength-currentIndex;
    else return bufferTailIndex-currentIndex;

}

void EnvelopeTracker::resetBuffer()
{
    currentIndex = 0;
    bufferTailIndex = -1;
}

void EnvelopeTracker::setEnvelope(const Envelope &value)
{
    envelope = value;
    envelopeLength = envelope.length();
    envelopeDataLength = envelope.getPayloadLength();
    headerLength = envelope.getHeaderLength();
    if(bufferLength<envelopeLength) bufferLength = 3*envelopeLength;
}

bool EnvelopeTracker::testHeader()
{
    if(!envelope.getHasHeader()) return true; // no header to test
    char * header = envelope.getHeader();
    for(int i = 0; i < envelope.getHeaderLength(); i++)
        if(header[i] != bufferArray[(i+currentIndex)%bufferLength]) return false;
    return true;
}

bool EnvelopeTracker::testFooter()
{
    if(!envelope.getHasFooter()) return true; // no footer to test
    char * footer = envelope.getFooter();
    int footerIndex = envelope.getFooterIndex();
    for(int i = 0; i < envelope.getFooterLength(); i++)
        if(footer[i] != bufferArray[(i+currentIndex+footerIndex)%bufferLength]){
//            qDebug()<<"footer fail";
            return false;
        }
    return true;
}

bool EnvelopeTracker::testXOR()
{
    if(!envelope.checkXOR()) return true; //no Xor to check
    char x_or = 0;
    for(int i = 0; i < envelopeLength; i++)
    {
        x_or ^= bufferArray[(i + currentIndex) % bufferLength];
    }
    return x_or == 0;
}

void EnvelopeTracker::setBufferLength(int value)
{
    int dataLength = bufferDataLength();
    if(value < dataLength || value < 2 * envelopeLength) return;
    if(bufferArray == NULL){
        bufferLength = value;
        bufferArray = new char [bufferLength];
        return;
    }
    char * tmp = new char [value];
    for(int i = 0, j = currentIndex; i < dataLength; i++, j++)
    {
        tmp[i] = bufferArray[j%bufferLength];
    }
    bufferLength = value;
    delete [] bufferArray;
    bufferArray = tmp;
    currentIndex = 0;
    bufferTailIndex = dataLength;
}

EnvelopeTracker::~EnvelopeTracker()
{
    delete [] bufferArray;
    for(int i = 0; i < envelopeListLength; i++) delete envelopeList[i];
    delete [] envelopeList;
}

