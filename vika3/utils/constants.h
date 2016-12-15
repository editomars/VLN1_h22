#ifndef CONSTANTS_H
#define CONSTANTS_H


namespace constants
{
    const int CURRENT_YEAR = 2016;
    const int MAXIMUM_AGE = 150;
#ifdef __APPLE__
    const int DELETE_KEY_NUMBER = 16777219;
#else
    const int DELETE_KEY_NUMBER = 16777223;
#endif
    const int ESCAPE_KEY_NUMBER = 16777216;
    const int CONTROL_KEY_NUMBER = 16777250;
    const int ALT_KEY_NUMBER = 16777251;
    const int COMMAND_KEY_NUMBER = 16777249;

}

#endif // CONSTANTS_H
