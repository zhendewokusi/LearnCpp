#include <iostream>
#include <ostream>

class Log {
   public:
    const int LevelError = 0;
    const int LevelWarning = 1;
    const int LevelInfo = 2;

   private:
    int m_level = LevelInfo;

   public:
    void SettLevel(int Settlevel) { m_level = Settlevel; }
    void Warn(const char* message) {
        if (m_level >= LevelWarning)
            std::cout << "[Warning]:" << message << std::endl;
    }
    void Error(const char* message) {
        if (m_level >= LevelError)
            std::cout << "[Error]:" << message << std::endl;
    }
    void Info(const char* message) {
        if (m_level >= LevelInfo)
            std::cout << "[Info]:" << message << std::endl;
    }
};

int main() {
    Log log;
    log.SettLevel(log.LevelError);
    log.Error("hello");
    log.Warn("hello");
    log.Info("hello");
}