#include "tcpsocket.hpp"
#include "structs.hpp"
#include "CharBuf.h"
#include <iostream>
#include <openssl/md5.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <cstdint>
#include <cstring>
#include <netinet/in.h>

using namespace std;

void calculateMD5(const SignOn& myStruct, unsigned char* digest) {
    MD5_CTX ctx;
    MD5_Init(&ctx);
    
    // Update the MD5 context with the bytes of the struct
    MD5_Update(&ctx, &myStruct, sizeof(myStruct));
    
    // Finalize the MD5 hash and store the result in digest
    MD5_Final(digest, &ctx);
}

union EndianTest {
    uint32_t intValue;
    uint8_t byteArray[4];
};

// Function to check endianness of the system
bool isBigEndian() {
    // Create an instance of the union and assign a known value
    EndianTest testValue;
    testValue.intValue = 0x12345678;

    // If the most significant byte (byteArray[0]) of the value is 0x12,
    // then the system is big endian; otherwise, it's little endian
    return (testValue.byteArray[0] == 0x12);
}
uint64_t swapEndian(uint64_t x) {
    return (((x & 0x00000000000000FF) << 56) |
            ((x & 0x000000000000FF00) << 40) |
            ((x & 0x0000000000FF0000) << 24) |
            ((x & 0x00000000FF000000) << 8)  |
            ((x & 0x000000FF00000000) >> 8)  |
            ((x & 0x0000FF0000000000) >> 24) |
            ((x & 0x00FF000000000000) >> 40) |
            ((x & 0xFF00000000000000) >> 56));
}

// Function to convert each field of MessageHeader to big endian format
void convertToBigEndian(MessageHeader& header) {
    header.TransactionCode = htons(header.TransactionCode);
    header.LogTime = htonl(header.LogTime);
    header.TraderId = htonl(header.TraderId);
    header.ErrorCode = htons(header.ErrorCode);
    header.TimeStamp = swapEndian(header.TimeStamp);
    header.MessageLength = htons(header.MessageLength);
    // No need to convert AlphaChar, TimeStamp1, and TimeStamp2 as they are char arrays
}

// Function to convert each field of SignOn to big endian format
void convertToBigEndian(SignOn& signOn) {
    convertToBigEndian(signOn.Header); // Convert MessageHeader fields
    signOn.UserId = htonl(signOn.UserId);
    // No need to convert Reserved, Password, Reserved1, Reserved2, BrokerId, Reserved3,
    // Reserved4, Reserved5, and Reserved6 as they are char arrays
}
void convertToBigEndian(char *data) {
    // Convert each 4-byte chunk to big endian
    for (int i = 0; i < 16; i += 4) {
        int32_t *chunk = reinterpret_cast<int32_t*>(data + i);
        *chunk = htonl(*chunk);
    }
}

int main()
{
    if (isBigEndian()) {
        std::cout << "System is big endian" << std::endl;
    } else {
        std::cout << "System is little endian" << std::endl;
    }

    // TcpClient();
    // return 0;

    // Initialize socket.
    TCPSocket<> tcpSocket([](int errorCode, std::string errorMessage){
        cout << "Socket creation error:" << errorCode << " : " << errorMessage << endl;
    });

    // Start receiving from the host.
    tcpSocket.onRawMessageReceived = [](const char* message, int length) {
        cout << "Message from the Server: " << message << "(" << length << ")" << endl;
    };

    // If you want to use std::string instead of const char*:
    //tcpSocket.onMessageReceived = [](string message) {
    //    cout << "Message from the Server: " << message << endl;
    //};
    
    // On socket closed:
    tcpSocket.onSocketClosed = [](int errorCode){
        cout << "Connection closed: " << errorCode << endl;
    };


    cout << "GSP0" << endl;
    // Send String:
    // tcpSocket.Send("Hello Server!");
    SignOn msg;
    msg.Header.TransactionCode = SIGN_ON_REQUEST_IN;
    msg.Header.LogTime = 0;
    msg.Header.TraderId = 12798;
    msg.Header.ErrorCode = 0;
    msg.Header.TimeStamp = 0;
    memset(msg.Header.AlphaChar, '\0', sizeof(msg.Header.AlphaChar));
    memset(msg.Header.TimeStamp1, '\0', sizeof(msg.Header.TimeStamp1));
    memset(msg.Header.TimeStamp2, '\0', sizeof(msg.Header.TimeStamp2));
    msg.UserId = 111;
    std::string strValue = std::to_string(1111);
    strncpy(msg.BrokerId, strValue.c_str(), sizeof(msg.BrokerId));
    strncpy(msg.Password, "xxx", sizeof(msg.Password));
    memset(msg.Reserved, '\0', sizeof(msg.Reserved));
    memset(msg.Reserved1, '\0', sizeof(msg.Reserved1));
    memset(msg.Reserved2, '\0', sizeof(msg.Reserved2));
    memset(msg.Reserved3, '\0', sizeof(msg.Reserved3));
    memset(msg.Reserved4, '\0', sizeof(msg.Reserved4));
    memset(msg.Reserved5, '\0', sizeof(msg.Reserved5));
    memset(msg.Reserved6, '\0', sizeof(msg.Reserved6));

    cout << "GSP1" << endl;

    unsigned char digest[MD5_DIGEST_LENGTH];
    calculateMD5(msg, digest);
    convertToBigEndian(reinterpret_cast<char*>(digest));


        cout << "GSP2" << endl;
    CharBuf SendPacketBuffer;

    //Packet length
    char LengthOfPacket[2];
    cout << "Size of SignOn struct : - " << sizeof(msg)<< endl;
    int16_t len = 22 + sizeof(msg);
    auto lenBigEndian = htons(len);

    
    memcpy(LengthOfPacket, &lenBigEndian, sizeof(lenBigEndian));


        cout << "GSP3" << endl;

    //sequence number
    char seqNum[4];
    int32_t seqNo = 1;
    int32_t SeqNobigEndianValue = htonl(seqNo);
    memcpy(seqNum, &SeqNobigEndianValue, sizeof(SeqNobigEndianValue));


        cout << "GSP4" << endl;

    //message Data 
    convertToBigEndian(msg);
    CharBuf l_objBuf;
    l_objBuf.SetBuffer((char *)&msg, sizeof(msg));

    SendPacketBuffer.AppendBuffer(LengthOfPacket, sizeof(LengthOfPacket));
    SendPacketBuffer.AppendBuffer(seqNum, sizeof(seqNum));
    SendPacketBuffer.AppendBuffer(reinterpret_cast<char*>(digest),sizeof(digest));
    SendPacketBuffer.AppendBuffer(l_objBuf.GetBuffer(),l_objBuf.GetLength());

    // Connect to the host (with a custom buffer size).
    tcpSocket.Connect("172.19.12.47", 10850, [&] {
        cout << "Connected to the server successfully." << endl;
        
         cout << "GSP5" << endl;
        
         // Send Packet:
        tcpSocket.Send(SendPacketBuffer.GetBuffer(),SendPacketBuffer.GetLength());


         cout << "GSP6" << endl;

    },
    [](int errorCode, std::string errorMessage){
        // CONNECTION FAILED
        cout << errorCode << " : " << errorMessage << endl;
    });

    // You should do an input loop, so the program won't terminate immediately
    string input;
    getline(cin, input);
    while (input != "exit")
    {
        tcpSocket.Send(input);
        getline(cin, input);
    }

    tcpSocket.Close();

    return 0;
}
