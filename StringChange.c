/**
 * @file StringChange.c
 * @author  Idan Refaeli <idan.refaeli@mail.huji.ac.il>
 * @version 1.0
 * @date 26 Jul 2014
 *
 * @brief Program that gets a String and change it.
 *
 * @section LICENSE
 * This program is a free software.
 *
 * @section DESCRIPTION
 * Program that gets a String and change it according to some rules.
 * Input  : A string.
 * Process: Checks every letter and change it according to given rules.
 * Output : The changed string.
 */

// ------------------------------ includes ------------------------------
#include <stdio.h>

// -------------------------- const definitions -------------------------
/**
 * @def MAX_STRING_LENGTH 50
 * @brief Maximum length for the given string.
 */
#define MAX_STRING_LENGTH 50

/**
 * @def ARROW ->
 * @brief The arrow symbol.
 */
#define ARROW "->"

/**
 * @def FIRST_LOWER_LETTER 97
 * @brief ASCII code of 'a' (first lower letter)
 */
#define FIRST_LOWER_LETTER 97

/**
 * @def LAST_LOWER_LETTER 122
 * @brief ASCII code of 'z' (last lower letter)
 */
#define LAST_LOWER_LETTER 122

/**
 * @def FIRST_UPPER_LETTER 65
 * @brief ASCII code of 'A' (first upper letter)
 */
#define FIRST_UPPER_LETTER 65

/**
 * @def LAST_UPPER_LETTER 90
 * @brief ASCII code of 'Z' (last upper letter)
 */
#define LAST_UPPER_LETTER 90

/**
 * @def TO_UPPER(x) x - 32
 * @brief Change ASCII code of lower letter to its upper letter.
 */
#define TO_UPPER(x) x - 32

/**
 * @def TO_LOWER(x) x + 32
 * @brief Change ASCII code of upper letter to its lower letter.
 */
#define TO_LOWER(x) x + 32

/**
 * @def FIRST_DIGIT 48
 * @brief ASCII code of '0' (first digit)
 */
#define FIRST_DIGIT 48

/**
 * @def LAST_DIGIT 57
 * @brief ASCII code of '9' (last digit)
 */
#define LAST_DIGIT 57

/**
 * @def FIVE_ASCII 53
 * @brief ASCII code of '5' (middle digit)
 */
#define FIVE_ASCII 53

/**
 * @def EIGHT_ASCII 56
 * @brief ASCII code of '8' (middle digit)
 */
#define EIGHT_ASCII 56

// ------------------------------ functions -----------------------------

/**
 * @brief Change the given character according to the following rules:
 * 		  1. If the character is between a-z, change it to its uppercase letter.
 * 		  2. If the character is between A-Z, change it to its lowercase letter.
 * 		  3. If the character is a digit bigger then 0 and smaller then 5, change it to 0.
 * 		  4. If the character is a digit bigger than or equal to 5 and smaller then or equal to 9,
 * 		  	 change it to 8.
 * 		  5. Everything else stays the same.
 * @param The character to change.
 * @return The changed character.
 */
char changeChar(char charToChange);

/**
 * @brief Gets a string from the user and change it according to given rules. Prints the result.
 * @return 0, to tell the system the execution ends without errors.
 */
int main()
{
	char stringToChange[MAX_STRING_LENGTH + 1] = "";
	int i = 0;

	scanf("%[^\n]s", &stringToChange);

	printf("\"%s\" %s ", stringToChange, ARROW);

	// The loop stops on the last character of the string given by the user (and not at the end
	// of the array).
	while (stringToChange[i] != '\0')
	{
		stringToChange[i] = changeChar(stringToChange[i]);
		i++;
	}

	printf("\"%s\"\n", stringToChange);

	return 0;
}

char changeChar(char charToChange)
{
	if (charToChange >= FIRST_LOWER_LETTER && charToChange <= LAST_LOWER_LETTER)
	{
		charToChange = TO_UPPER(charToChange);
	}
	else if(charToChange >= FIRST_UPPER_LETTER && charToChange <= LAST_UPPER_LETTER)
	{
		charToChange = TO_LOWER(charToChange);
	}
	else if(charToChange >= FIVE_ASCII && charToChange <= LAST_DIGIT)
	{
		charToChange = EIGHT_ASCII;
	}
	else if(charToChange > FIRST_DIGIT && charToChange < FIVE_ASCII)
	{
		charToChange = FIRST_DIGIT;
	}

	return charToChange;
}
