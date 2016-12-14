#ifndef ENUMS_H
#define ENUMS_H

enum folkValidation
{
    fSuccess = 1,
    nameEmpty = 2,
    noBirthYear = 3,
    deathBeforeBirth = 4,
    deathAfterCurrentYear = 5,
    genderNotValid = 6,
    ageTooHigh = 7,
    birthAfterCurrentYear = 8
};

enum velValidation
{
    vSuccess = 1,
    builtFieldMissing = 2,
    builtYearAfterCurrentYear = 3
};

#endif // ENUMS_H
