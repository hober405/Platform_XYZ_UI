#ifndef SIMPLEENVELOPE_H
#define SIMPLEENVELOPE_H


//#include <QByteArray>
//#include <QString>
#include <string>
class Envelope
{
public:
    Envelope();

    Envelope(const Envelope &);
    Envelope setEnvelopeData(const char *buf, int bufLength, int checkSumStart=0);

    Envelope setEnvelopeDataAdjustFooterIndex(const char * buf, int bufLength, int checkSumStart=0);
    // header
    void enableHeader(std::string headervalue, int headerindex=0);

    // footer
    void enableFooter(std::string footervalue, int footerindex);

    // crc
    void enableCRC(int crcindex, int crclength);

    // xor
    void enableCheckXOR(int xorIndex);

    char * getEnvelopeArray();
    char * getHeader() const;

    char * getFooter() const;

    int getHeaderIndex() const;

    int getFooterIndex() const;

    bool checkXOR() const;

    char * getPayload() const;

    int length() const;

    int getPayloadLength() const;

    int getHeaderLength() const;

    int getFooterLength() const;

    Envelope &operator=(const Envelope &);

    bool getHasHeader() const;

    bool getHasFooter() const;

    ~Envelope();

private:
    char generateXor(char * input, int length);
    int appendData(char *toAppend, int startIndex, char *data, int dataLength);

    //header
    bool hasHeader = false;
    int headerIndex = 0;
    char * headerValue = NULL;
    int headerLength = 0;

    // Footer
    bool hasFooter;
    int footerIndex = 0;
    char * footerValue = NULL;
    int footerLength = 0;

    // check
    // CRC
    bool hasCRC = false;
    int checkCRCIndex = 0;
    int checkCRCLength = 0;

    // check xor
    bool hasCheckXOR = false;
    int checkXORIndex = 0;
    char Xor;

    char * payload;
    int payloadLength;
    int checkSumStart=0;

};

#endif // SIMPLEENVELOPE_H
