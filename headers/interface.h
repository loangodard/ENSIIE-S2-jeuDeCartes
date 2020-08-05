#ifndef _INTERFACE_H
#define _INTERFACE_H

#include "card.h"
#include "board.h"

/*Print message in console for the new round and inform 
new space for Personnal card is available*/
void printNewRound(Board board);

//Print message for the new phase with team associated
void printNewPhase(int player);

//Print the board
void printBoard(Board board);

//Ask the player to choose him Student card (FISE or FISA)
int askTypeCard();

//Ask the player to choose a card or to finish the phase
Card *askAction(Player player, int nbPE);

//Print the last sentence when the game is finished
void printWinner(int player);

void printHand(Player p);

void printPoints(Board board);

void clear(void);

void flushStdin();

int readUserType(char* str, int size);

#endif