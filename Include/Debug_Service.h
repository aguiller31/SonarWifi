
#ifndef DEBUG_SERVICE
#define DEBUG_SERVICE

class DebugService{
  public:
    DebugService(int);
    void println(String);
    void print(String);
  private:
    int baud_rate;
};
#endif