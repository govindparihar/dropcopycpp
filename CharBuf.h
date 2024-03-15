#ifndef CHARBUF_H
#define CHARBUF_H
#include <iostream>
#include <fstream>
#include <string>
#include <string.h>


#include "Constants.h"
class CharBuf
 {
   public :
     CharBuf(void);
     CharBuf(char *f_buffer,long int f_length);
     CharBuf& operator=(CharBuf& charbuf);
     void SetBuffer(char *f_buffer,long int f_length);
     void AppendBuffer(char *f_buffer,long int f_length);
     char *GetBuffer(void);
     void SetString(char *f_string);
     void AppendString(char *f_string);
     char *GetString(void);
     long int GetLength(void);
     ~CharBuf(void);
   private :
     char *m_Buffer;
     long int m_Length;
 };
#endif // CHARBUF_H
