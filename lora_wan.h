#ifndef lora_wan_h
#define lora_wan_h

class lora_wan
{
private:
    int PROG_PIN;
    int CTS_PIN;
    int TX_PIN;
    int RX_PIN;
    long BAUD;
    long t_BAUD;
    bool GATEWAY;
public:
    lora_wan(int CTS, int PROG, int TX = 1, int RX = 0, long baud = 115200, long t_baud);
    void progMode();
    void progModeDis();
    void setDestination(int destinationID);
    void setNetworkID(int networkID);
    void setGateway();
};




#endif