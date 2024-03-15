#ifndef CONSTANT_H
#define CONSTANT_H


const int HEARTBEAT = 23506;
const int SIGN_ON_REQUEST_IN = 2300;
const int SIGN_ON_REQUEST_OUT = 2301;
const int DC_DOWNLOAD_REQUEST = 8000;



#define NULL 0

#define FAILURE1 -1

#define FAILURE2 -2

#define FAILURE3 -3

#define FAILURE4 -4

#define SUCCESS1 0

#define TRUE  1

#define FALSE 0

//For Expiry Date //required when epoch timestamp is since 1980 1st Jan
#define TEN_YEAR_SECONDS            315513000

#define FIVE_AND_HALF_HOUR_SECONDS  19800

//Default values
#define DEFAULT_NEST_USER "ADMINB2B"

#define DEFAULT_NEST_USER_PASS "abc123"

#define DEFAULT_OMNESYS_ID (1)

#define DATA_START_STRING "<PKT>\r\n"

#define DATA_END_STRING "</PKT>\r\n"

#define MAX_DATA_LENGTH_SIZE 7

#endif // CONSTANT_H
