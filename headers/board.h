#ifndef _BOARD_H
#define _BOARD_H
#include "card.h"
#include "structures.h"

struct bonus
{
    int DDBonus;
    int valueDDFISE;
    int valueDurabilityFISE;
    int valueDDFISA;
    int valueDurabilityFISA;
};
typedef struct bonus *Bonus;

/* structure of a player */
struct player
{
    int id;
    int nbFISE; /* number of fise cards played */
    int nbFISA; /* number of fisa cards played */
    Stack discard;
    Fifo hand;
    Stack deck;
    Fifo inGameCards;
    Bonus bonus;
};
typedef struct player *Player;

/* structure of a board */
struct board
{
    int idPlayerPlaying; // 1 : player one, 2 : player two
    int idWinner;        // -1 : equality, 1 : player one win, 2 player two win
    Player p1, p2;
    int round;
    int maxCardInGame;
};

typedef struct board *Board;

Bonus initializeBonus();
/*Initialize struct Player*/
Player newPlayer(int id);

/*Free memory of board*/
void freePlayer(Player p);

/* Init a new board*/
Board initNewBoard();

/*Free memory of board b*/
void freeBoard(Board b);

/*indicate a new round to the board*/
void newRound(Board b);

int getSpecificBonusInGameCards(Player player, int indexBonus);

/*return the number of card the player must draw at the begining of a phase*/
int countDrawCard(Player p, int round);

/*use this fonction when a player must draw a card*/
void drawCard(Player p);

/* return the number of student card to draw on the begining of the turn */
int countStudentCard(Player p);

/* use this function to add a student card (fise or fisa) on the board */
void addCardStudent(Player p, int typeStudent);

/* return the number of PE avaible for an ENSIIE after playing the student card */
int nbOfPE(Player p, int isOdd);

int nbOfDD(Player player, int isOdd);

int nbOfDurability(Player player, int isOdd);

int scorePlayer(Board board, int idPlayer);

void doAE1(Player player, int nb);

void doAE2(Player player, int nb);

void doAA1(Player player, int nb);

void doAA2(Player player, int nb);

void doRE1(Player player, int nb);

void doRE2(Player player, int nb);

void doRA1(Player player, int nb);

void doRA2(Player player, int nb);

void doADD(Player player, int nb);

void doRDD(Player player, int nb);

int castEffectsPersonnal(Card card, Player actualPlayer, Player opponentPlayer, int isBonus);

void removeEffect(Player actualPlayer, Player opponentPlayer, Card card);

int castActionEffect(Board board, Card c);

/* use this function to play a card from your hand */
int playCard(Board b, Card c);

/* use this function to specify that the turn is finish */
void endRound(Board b);

/* use this function to check if one player win the game */
int endGame(Board b);

/* use this function to update the player playing */
void updatePlayerPlaying(Board board, int phase);

/* use this fonction to check if the argument is odd or even*/
int isOdd(int n);

#endif