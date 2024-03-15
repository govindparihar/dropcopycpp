#include <cstdint>

#pragma pack(push,2)

struct MessageHeader {
    int16_t TransactionCode;
    int32_t LogTime;
    char AlphaChar[2];
    int32_t TraderId;
    int16_t ErrorCode;
    int64_t TimeStamp;
    char TimeStamp1[8];
    char TimeStamp2[8];
    int16_t MessageLength;
};


struct SignOn {
    MessageHeader Header;
    int32_t UserId;                   // 4 bytes
    char Reserved[8];    // 8 bytes
    char Password[8];    // 8 bytes
    char Reserved1[8];   // 8 bytes
    char Reserved2[38];  // 38 bytes
    char BrokerId[5];    // 5 bytes
    char Reserved3[117]; // 117 bytes
    char Reserved4[16];  // 16 bytes
    char Reserved5[16];  // 16 bytes
    char Reserved6[16];  // 16 bytes
};

#pragma pack(pop)