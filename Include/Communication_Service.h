#ifndef COMMUNICATION_SERVICE
#define COMMUNICATION_SERVICE

class CommunicationService{
  public:
    CommunicationService();
    void startWiFI();
  private:
    WifiService wifi;
};
#endif