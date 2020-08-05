#ifndef _CARD_H
#define _CARD_H

struct card
{
    int id;
    int cost;
    char *effect;
};

typedef struct card Card;

//Duplicate an int tab
int *copyIntTab(int *tab, int size);

//Print id, cost and effects of the card c
void printCard(Card c);

//Return the card cost
int getCost(Card c);

//Return the card ID
int getID(Card c);

//Action = 1 - Personnal = 0 - Error = -1
int getTypeCard(Card c);

//Return card effects
char *getEffect(Card c);

//Return Bonus tab for the Card c
int *getBonusOfCard(Card c);

//Initialize all the associate tabs with name and effect
void initializeTableCard();

//Return card tab with all cards
Card *getCards();

//Return personnal cards
Card *getPersonnalCards();

//Return action cards
Card *getActionCards();

//Add multiple action cards in tabs
int addActionCardsInDeck(Card *tab, int id, int cost, int quantity, char *effect, int index);


//Concatenate two tab of Card
Card *concatCardTab(Card *personnalCards, Card *actionCards, int sizeP, int sizeA);

//Get size of all Cards
int getSizeCardsTotal();

//Shuffle a cards tab
Card *shuffleCards(Card *cards, int size);

#endif
