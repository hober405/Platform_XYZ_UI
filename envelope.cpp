#include "envelope.h"

Envelope::Envelope()
{
    hasCheckXOR = false;
    hasCRC = false;
    hasFooter = false;
    hasHeader = false;
    payload = NULL;
}

Envelope::Envelope(const Envelope &en)
{
    *this = en;
}

Envelope Envelope::setEnvelopeData(const char *buf, int bufLength, int checkSumStart)
{
    payload = new char [payloadLength];
    for(int i = 0; i < payloadLength; i++)
    {
        if(i < bufLength) payload[i] = buf[i];
        else payload[i] = 0;
    }
    this->checkSumStart=checkSumStart;
    return *this;
}

Envelope Envelope::setEnvelopeDataAdjustFooterIndex(const char *buf, int bufLength, int checkSumStart)
{
    payload=new char [bufLength];
    for(int i = 0; i < bufLength; i++) payload[i] = buf[i];
    this->checkSumStart=checkSumStart;
    return *this;
}

void Envelope::enableHeader(std::string headervalue, int headerindex)
{
    hasHeader = true;
    headerIndex = headerindex;
    headerLength = headervalue.length();
    headerValue = new char [headerLength];
    for(int i = 0; i < headerLength; i++) headerValue[i] = headervalue[i];
}

void Envelope::enableFooter(std::string footervalue, int footerindex)
{
    hasFooter = true;
    footerIndex = footerindex;
    footerLength = footervalue.length();
    footerValue = new char [footerLength];
    for(int i = 0; i < footerLength; i++) footerValue[i] = footervalue[i];
    payloadLength = footerindex - headerLength;
}

void Envelope::enableCheckXOR(int xorIndex)
{
    hasCheckXOR = true;
    checkXORIndex = xorIndex;
}

char * Envelope::getEnvelopeArray()
{
    int envelopeLength = length();
    char * ret = new char [envelopeLength];
    int index = 0;
    if(hasHeader) index = appendData(ret, index, headerValue, headerLength);
    index = appendData(ret, index, payload, payloadLength);
    if(hasFooter) index = appendData(ret, index, footerValue, footerLength);
    if(hasCheckXOR) ret[index] = generateXor(ret, envelopeLength-1);
    return ret;
}

char Envelope::generateXor(char *input, int length)
{
    Xor = 0;
    for(int i = checkSumStart; i < length; i++) Xor ^= input[i];
    return Xor;
}

int Envelope::appendData(char *toAppend, int startIndex, char *data, int dataLength)
{
    if(toAppend == NULL || data == NULL) return -1; // error
    for(int i = 0; i < dataLength; i++) toAppend[ i + startIndex ] = data[i];
    return startIndex + dataLength;
}

bool Envelope::getHasFooter() const
{
    return hasFooter;
}

Envelope::~Envelope()
{
    delete [] headerValue;
    delete [] footerValue;
    delete [] payload;
}

bool Envelope::getHasHeader() const
{
    return hasHeader;
}

int Envelope::getFooterLength() const
{
    return footerLength;
}

Envelope &Envelope::operator=(const Envelope & en)
{
    hasHeader = en.hasHeader;
    headerLength = en.headerLength;
    headerIndex = en.headerIndex;
    headerValue = new char[headerLength];
    appendData(headerValue, 0, en.headerValue, headerLength);

    hasFooter = en.hasFooter;
    footerLength = en.footerLength;
    footerIndex = en.footerIndex;
    footerValue = new char[footerLength];
    appendData(footerValue, 0, en.footerValue, footerLength);

    hasCheckXOR = en.hasCheckXOR;
    checkCRCIndex = en.checkXORIndex;
    Xor = en.Xor;

    payloadLength = en.payloadLength;
    payload = new char[payloadLength];
    appendData(payload, 0, en.payload, payloadLength);

    checkSumStart = en.checkSumStart;
}

int Envelope::getHeaderLength() const
{
    return headerLength;
}

int Envelope::getPayloadLength() const
{
    return payloadLength;
}

char * Envelope::getPayload() const
{
    return payload;
}

int Envelope::length() const
{
    int envelopeLength = payloadLength;
    if(hasHeader) envelopeLength += headerLength;
    if(hasFooter) envelopeLength += footerLength;
    if(hasCheckXOR) envelopeLength++;
    return envelopeLength;
}

bool Envelope::checkXOR() const
{
    return hasCheckXOR;
}

int Envelope::getFooterIndex() const
{
    return footerIndex;
}

int Envelope::getHeaderIndex() const
{
    return headerIndex;
}

char * Envelope::getFooter() const
{
    return footerValue;
}

char * Envelope::getHeader() const
{
    return headerValue;
}
