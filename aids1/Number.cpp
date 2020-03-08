#include "Number.h"

Number::Number() {
    numberOfDigits = 0;
    isPositive = true;
    firstDigit = NULL;
    lastDigit = NULL;
    buffer = ' ';
    isInitiated = false;
}

Number::~Number() {
}

void Number::WriteNumber() {
	PrintSymbol();
	PrintDigits();
}

void Number::PrintSymbol() {
    if(IsNegative() && firstDigit->digit != 0) {
        printf("-");
	}
}

void Number::PrintDigits() {
    DigitsList* current = firstDigit;

    do {
        printf("%i", current->digit);
        current = current->nextDigit;
    } while (current != NULL);

    printf("\n");
}

void Number::CreateNumber() {
    ReadNextCharToBuffer();
    while (IsNotEOL()) {
        CreateNextDigit();
	}
}
bool Number::IsNotEOL()
{
    return buffer != '\n';
}

void Number::CreateNextDigit()
{
    if (!isInitiated) {
        InitiateNumber();
    }
    else {
        AddNewDigit();
    }
	
    ReadNextCharToBuffer();
}

void Number::ReadNextCharToBuffer()
{
    buffer = _getchar_nolock();
}

void Number::InitiateNumber()
{
    DetermineSymbol();
    if (isPositive) {
        AddNewDigit();
    }
    isInitiated = true;
}

void Number::DetermineSymbol()
{
	if(buffer == '-') {
        isPositive = false;
	}
    else {
        isPositive = true;
    }
}

void Number::AddNewDigit() {
    CreateNewListElement();
    AppendNewDigitFromBufferToList();
}

void Number::CreateNewListElement()
{
	if(IsEmpty()) {
        InitiateList();
	}
    else {
        DigitsList* temp = lastDigit;
        lastDigit->nextDigit = new DigitsList;
        lastDigit = lastDigit->nextDigit;
        lastDigit->previousDigit = temp;
    }
}

bool Number::IsEmpty()
{
    return  numberOfDigits == 0;
}


void Number::InitiateList()
{
    firstDigit = new DigitsList;
    firstDigit->nextDigit = NULL;
    firstDigit->previousDigit = NULL;
    lastDigit = firstDigit;
}

void Number::AppendNewDigitFromBufferToList()
{
    lastDigit->digit = (uint_fast8_t)buffer - '0';
    lastDigit->nextDigit = NULL;
    numberOfDigits++;
}


void Number::DeleteNumber() {
    DigitsList* current = firstDigit;
	
    while (current != NULL) {
        DeleteDigit(current);
    }
}

void Number::DeleteDigit(DigitsList* &digit) {
    DigitsList* temp = digit->nextDigit;
    delete digit;
    digit = temp;
	firstDigit = digit;
}

bool Number::IsPositive() {
    return isPositive;
}

bool Number::IsNegative() {
    return !isPositive;
}

size_t Number::Length() {
    return numberOfDigits;
}

char Number::GetDigit(int index) {
    DigitsList* searched_digit = firstDigit;
    for(int i=0;i<index;i++) {
        searched_digit = searched_digit->nextDigit;
    }

    return (char)searched_digit->digit;
}

void Number::PushDigitToStart(uint_fast8_t digit) {
    DigitsList* newElement = new DigitsList;
    
    newElement->nextDigit = firstDigit;
    newElement->digit = digit;
    newElement->previousDigit = NULL;
	if(firstDigit != NULL)
	{
        firstDigit->previousDigit = newElement;
	}

    firstDigit = newElement;
    if(IsEmpty()) {
        lastDigit = newElement;
    }

    numberOfDigits++;
}

void Number::InitiateCursor() {
    cursor = lastDigit;
}

uint_fast8_t Number::GetNextDigit() {
    uint_fast8_t temp;

    if (cursor == NULL) {
        return 0;
    }
	
    temp = cursor->digit;
    cursor = cursor->previousDigit;
	
    return temp;
}


void Number::InverseSymbol() {
    isPositive = !isPositive;
}

void Number::CleanZerosInfront() {
    DigitsList* current = firstDigit;

    while ((current->digit == 0) && !(current->nextDigit == NULL)) {
        DeleteDigit(current);
    }
}
