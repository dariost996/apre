#if defined _APRE_H_
#ifndef _APRE_BASE_H_
#define _APRE_BASE_H_

/*! \file apre_base.h
*/

/*! \fn void apreSetErrorCallback(void (*c)(int,const char*))
    \brief Set the default error callback for APRE
    \param c The callback<br>
    The callback must accept 2 parameters:
    an integer (int) and a string (const char*)<br>
    The integer has the following meanings:<br>
    0 - Information message (the program shouldn't close)<br>
    1 - Warning message (the program shouldn't close)<br>
    2 - Error message (the program should close)<br>
    The string contains the error
*/

void apreSetErrorCallback(void (*c)(int,const char*))
{
    if(c!=nullptr)
    {
        apreErrFunc=c;
    }
    else
    {
        apreErrFunc=apreDefaultErrFunc;
    }
    return;
}

#endif
#endif
