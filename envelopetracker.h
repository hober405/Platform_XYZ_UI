#ifndef ENVELOPETRACKER_H
#define ENVELOPETRACKER_H

#include <QByteArray>
#include <QList>
#include "envelope.h"
class EnvelopeTracker
{
public:
    EnvelopeTracker();

    // parsing
    void parse(char *buf, int bufLength);

    Envelope* getEnvelope(){
        Envelope* ret = NULL;
        if(envelopeListIndexFront != -1){
            ret = envelopeList[envelopeListIndexFront++];
            envelopeListIndexFront %= envelopeListLength;
            if(envelopeListIndexFront == envelopeListIndex) envelopeListIndexFront = -1;
        }
        return ret;
    }
    int bufferDataLength();
    
    void resetBuffer();

    void setEnvelope(const Envelope &value);

    void setBufferLength(int value);
    ~EnvelopeTracker();

private:
    // check Header
    bool testHeader();

    // check Footer
    bool testFooter();

    // test XOR
    bool testXOR();// set xindex as headerIndex


    // current header index
    int currentHeaderIndex;
    // current footer index
    int currentFooterIndex;
    int currentDataIndex;
    // index
    int currentIndex;
    // array
    char * bufferArray;
    int bufferLength;
    int bufferTailIndex;

    Envelope** envelopeList;
    int envelopeListLength;
    int envelopeListIndex;
    int envelopeListIndexFront;
    Envelope envelope;
    int envelopeLength;
    int envelopeDataLength;
    int headerLength;
};

#endif // ENVELOPETRACKER_H
