#include "CharBuf.h"

CharBuf::CharBuf(void)
{
    m_Buffer = NULL;
    m_Length = 0;
    SetBuffer((char*)"",0);
}

CharBuf::CharBuf(char *f_buffer,long int f_length)
{
    m_Buffer = NULL;
    m_Length = 0;
    SetBuffer(f_buffer,f_length);
}

CharBuf& CharBuf::operator=(CharBuf& charbuf)
{
    char *l_buffer;
    long int l_length;
    if (&charbuf == this)
        {
            return(*(this));
        }
    l_buffer = charbuf.GetBuffer();
    l_length = charbuf.GetLength();
    SetBuffer(l_buffer,l_length);
    return(*(this));
}

void CharBuf::SetBuffer(char *f_buffer,long int f_length)
{
    char *buffer_ptr;
    buffer_ptr = m_Buffer;
    m_Buffer = new char[f_length + 1];
    memcpy(m_Buffer,f_buffer,f_length);
    m_Buffer[f_length] = '\0';
    m_Length = f_length;
    if (buffer_ptr != NULL )
        {
        delete [] buffer_ptr;
        buffer_ptr = NULL;
        }
}

void CharBuf::AppendBuffer(char *buffer,long int length)
{
    char *buffer_ptr;
    buffer_ptr = m_Buffer;
    m_Buffer = new char[ m_Length + length + 1];
    memcpy(m_Buffer,buffer_ptr,m_Length);
    memcpy(&(m_Buffer[m_Length]),buffer,length);
    m_Buffer[m_Length + length] = '\0';
    m_Length = m_Length + length;
    delete [] buffer_ptr;
}

char* CharBuf::GetBuffer(void)
{
    return(m_Buffer);
}

void CharBuf::SetString(char *string)
{
    long int length;
    char *buffer_ptr;
    buffer_ptr = m_Buffer;
    length = strlen(string);
    m_Buffer = new char[length + 1];
    strcpy(m_Buffer,string);
    m_Length = length;
    if (buffer_ptr != NULL )
    {
            delete [] buffer_ptr;
    }
}

void CharBuf::AppendString(char *string)
{
    char *buffer_ptr;
    long int length;
    buffer_ptr = m_Buffer;
    length = strlen(string);
    m_Buffer = new char[m_Length + length + 1];
    memcpy(m_Buffer,buffer_ptr,m_Length);
    strcpy((m_Buffer + m_Length),string);
    m_Length = m_Length + length;
    delete [] buffer_ptr;
}

char* CharBuf::GetString(void)
{
    return(m_Buffer);
}

long int CharBuf::GetLength(void)
{
    return(m_Length);
}

CharBuf::~CharBuf(void)
{
    if (m_Buffer != NULL)
    {
        delete [] m_Buffer;
        m_Buffer = NULL;
    }
}

