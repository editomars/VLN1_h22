#ifndef CONSTANTS_H
#define CONSTANTS_H


namespace constants
{
    const int CURRENT_YEAR = 2016;
    const int MAXIMUM_AGE = 150;
#ifdef __APPLE__
    const int DELETE_KEY_NUMBER = 16777219;
    const int CONTROL_KEY_NUMBER = 16777249;
#else
    const int DELETE_KEY_NUMBER = 16777223;
    const int CONTROL_KEY_NUMBER = 16777250;
#endif
    const int ESCAPE_KEY_NUMBER = 16777216;
    const int L_KEY_NUMBER = 76;
    const int S_KEY_NUMBER = 83;
    const int R_KEY_NUMBER = 82;
    const int F5_KEY_NUMBER = 16777268;



}

#endif // CONSTANTS_H
