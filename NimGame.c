/**
 * @file NimGame.c
 * @author  Idan Refaeli <idan.refaeli@mail.huji.ac.il>
 * @version 1.0
 * @date 26 Jul 2014
 *
 * @brief A simple nim game.
 *
 * @section LICENSE
 * This program is a free software.
 *
 * @section DESCRIPTION
 * A simple nim game between 2 human players.
 * Input  : Number of balls for each box, and the number of balls to remove on each turn.
 * Process: First the number of balls on each box is set by the players. Then, each player choose
 * 			a box and how much balls he wants to remove. The player who takes the last ball on some
 * 			box loses.
 * Output : Status of boxes on each turn, requests for input from the players and the winner at
 * 			the end.
 */

// ------------------------------ includes ------------------------------
#include <stdio.h>

// -------------------------- const definitions -------------------------
/**
 * @def NUM_OF_PLAYERS 2
 * @brief Number of players in the game.
 */
#define NUM_OF_PLAYERS 2

/**
 * @def FIRST_PLAYER 1
 * @brief Index of the first player.
 */
#define FIRST_PLAYER 1

/**
 * @def NUM_OF_BOXES 2
 * @brief Number of boxes in the game.
 */
#define NUM_OF_BOXES 2

/**
 * @def HOW_MANY_BALLS "How many balls in box "
 * @brief Request for the user to number of balls in a box
 */
#define HOW_MANY_BALLS "How many balls in box"

/**
 * @def WRONG_NUM_OF_BALLS "Number of balls in box must be positive."
 * @brief Error when the number of balls entered for a box is not positive.
 */
#define WRONG_NUM_OF_BALLS "Number of balls in box must be positive."

/**
 * @def SEPARATE_LINE "---------------"
 * @brief Separate line for the game board.
 */
#define SEPERATE_LINE "---------------"

/**
 * @def BALL "o"
 * @brief A single ball.
 */
#define BALL "o"

/**
 * @def BOX "Box"
 * @brief 'Box' string.
 */
#define BOX "Box"

/**
 * @def PLAYER "Player"
 * @brief 'Player' string.
 */
#define PLAYER "Player"

/**
 * @def YOUR_TURN ", it's your turn."
 * @brief 'it's your turn' string.
 */
#define YOUR_TURN "it's your turn."

/**
 * @def CHOOSE_BOX ", choose a box (1 or 2):"
 * @brief 'choose a box' string.
 */
#define CHOOSE_BOX "choose a box (1 or 2):"

/**
 * @def MAX_NUM_OF_BALLS 3
 * @brief Maximum number possible to choose balls.
 */
#define MAX_NUM_OF_BALLS 3

/**
 * @def HOW_MANY_BALLS ", how many balls do you want to take from box "
 * @brief How many balls to take string.
 */
#define HOW_MANY_BALLS_TO_TAKE "how many balls do you want to take from box"

/**
 * @def WRONG_NUM_OF_BALLS_NOT_POSITIVE "Number of balls to take must be positive."
 * @brief Error when the number of balls entered to take is not positive.
 */
#define WRONG_NUM_OF_BALLS_NOT_POSITIVE "Number of balls to take must be positive."

/**
 * @def WRONG_NUM_OF_BALLS_BIGGER_THEN_MAX "Cannot take more than 3 balls at a time."
 * @brief Error when the number of balls entered to take is bigger then the max.
 */
#define WRONG_NUM_OF_BALLS_BIGGER_THAN_MAX "Cannot take more than 3 balls at a time."

/**
 * @def WRONG_NUM_OF_BALLS_BIGGER_THAN_BOX "Cannot take more balls then what's in the box.
 * @brief Error when the number of balls entered to take is bigger then what's in the box.
 */
#define WRONG_NUM_OF_BALLS_BIGGER_THAN_BOX "Cannot take more balls then what's in the box."

/**
 * @def WINNER "wins the game."
 * @brief message when some player wins.
 */
#define WINNER "wins the game."

// ------------------------------ functions -----------------------------

int gBoxes[NUM_OF_BOXES];	// Each cell contains the number of balls in the box whose number is
							// index + 1.
int gCurrentPlayer = FIRST_PLAYER;		// The current player.
int gEndGame = 0; 	// Has the game ended.


/**
 * @brief For each box, sets the number of balls given by the players for the box.
 * @return 0 if the input is wrong, means the number entered is not positive, 1 otherwise.
 */
int setBoxes();

/**
 * @brief Handles the turn of every player. In each turn the player is requested to choose a box
 * 		  and the amount of balls to take from that box.
 */
void turn();

/**
 * @brief Prints the board
 */
void printBoard();

/**
 * @brief Handles the box choosing operation of the current player.
 * @return The chosen box.
 */
int boxChoosing();

/**
 * @brief Handles the balls choosing operation from the chosen box of the curernt player.
 * @param box The chosen box.
 * @return Number of balls selected.
 */
int ballsChoosing(int box);

/**
 * @brief Change the current player playing when the turn ends.
 */
void changePlayer();

/**
 * @brief prints the final board and the winning player
 */
void printWinner();

/**
 * @brief Runs the game according its rules.
 * @return 0, to tell the system the execution ends.
 */
int main()
{
	// If setBoxes() returns 0, means the input for number of balls for each box is wrong, end
	// the execution.
	if(!setBoxes())
	{
		return 0;
	}

	// Run the game until gEndGame = 1, means the game has ended.
	while (!gEndGame)
	{
		turn();
		changePlayer();
	}

	// After the game ended, print the winner.
	printWinner();

	return 0;
}

int setBoxes()
{
	int i;

	// For every box, ask the players to choose number of balls and check if the number is legal.
	for(i = 0; i < NUM_OF_BOXES; i++)
	{
		printf("%s %d?\n", HOW_MANY_BALLS, i + 1);
		scanf("%d", &gBoxes[i]);

		if(gBoxes[i] <= 0)
		{
			printf("%s\n", WRONG_NUM_OF_BALLS);
			return 0;
		}
	}

	return 1;
}

void turn()
{
	// In each turn, print the board, ask the current player to choose a box and the amount of
	// balls to take. Finally check if the player took the last ball from the chosen box.

	printBoard();

	int chosenBox = boxChoosing();

	int chosenBalls = ballsChoosing(chosenBox);

	gBoxes[chosenBox - 1] -= chosenBalls;

	if (gBoxes[chosenBox - 1] == 0)
	{
		gEndGame = 1;
	}
}

void printBoard()
{
	printf("%s\n", SEPERATE_LINE);
	int i, j;
	for (i = 0; i < NUM_OF_BOXES; i++)
	{
		printf("%s %d: ", BOX, i + 1);
		for (j = 0; j < gBoxes[i]; j++)
		{
			printf("%s", BALL);
		}
		printf("\n");
	}
	printf("%s\n", SEPERATE_LINE);
}

int boxChoosing()
{
	// Ask the current player for box until he enter a legal box number (1 or 2)

	int chosenBox = 0;

	while(chosenBox <= 0 || chosenBox > NUM_OF_BOXES)
	{
		printf("%s %d, %s\n", PLAYER, gCurrentPlayer, YOUR_TURN);
		printf("%s %d, %s\n", PLAYER, gCurrentPlayer, CHOOSE_BOX);
		scanf("%d", &chosenBox);
	}

	return chosenBox;
}

int ballsChoosing(int box)
{

	// Ask the current player for number of balls until he enter a legal number (positive, between
	// 1-3 and not more than what's inside the box).

	int chosenBalls = 0;

	while (chosenBalls <= 0 || chosenBalls > MAX_NUM_OF_BALLS)
	{
		printf("%s %d, %s %d?\n", PLAYER, gCurrentPlayer, HOW_MANY_BALLS_TO_TAKE, box);
		scanf("%d", &chosenBalls);

		if(chosenBalls <= 0)
		{
			printf("%s\n", WRONG_NUM_OF_BALLS_NOT_POSITIVE);
		}
		else if(chosenBalls > MAX_NUM_OF_BALLS)
		{
			printf("%s\n", WRONG_NUM_OF_BALLS_BIGGER_THAN_MAX);
		}
		else if(chosenBalls > gBoxes[box - 1])
		{
			printf("%s\n", WRONG_NUM_OF_BALLS_BIGGER_THAN_BOX);
			chosenBalls = 0;
		}
	}

	return chosenBalls;
}

void changePlayer()
{
	if (gCurrentPlayer < NUM_OF_PLAYERS)
	{
		gCurrentPlayer++;
	}
	else
	{
		gCurrentPlayer = FIRST_PLAYER;
	}
}

void printWinner()
{
	printBoard();
	printf("%s %d %s\n", PLAYER, gCurrentPlayer, WINNER);
}
