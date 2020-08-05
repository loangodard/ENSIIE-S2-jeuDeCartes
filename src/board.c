#include "../headers/board.h"
#include <stdio.h>
#include <stdlib.h>

#define MAX_ROUND 30
#define NUMBER_DD_WIN 20
#define NB_MAX_EFFECT 12
#define AE1 0
#define AE2 1
#define AA1 2
#define AA2 3
#define RE1 4
#define RE2 5
#define RA1 6
#define RA2 7
#define ADD 8
#define RDD 9
#define DR 10
#define E 11
#define PE_FISA 2
#define PE_FISE 1

Bonus initializeBonus()
{
    Bonus b = (struct bonus *)malloc(sizeof(struct bonus));
    b->DDBonus = 0;
    b->valueDDFISE = 1;
    b->valueDurabilityFISE = 1;
    b->valueDDFISA = 1;
    b->valueDurabilityFISA = 1;

    return b;
}

Player newPlayer(int id)
{
    Player p = (struct player *)malloc(sizeof(struct player));
    p->bonus = initializeBonus();
    p->hand = NULL;
    p->id = id;
    p->nbFISA = 0;
    p->nbFISE = 0;
    p->inGameCards = NULL;
    p->discard = createStack();
    p->deck = initializeDeck();

    return p;
}

void freePlayer(Player p)
{
    freeFifo(p->hand);
    freeFifo(p->inGameCards);
    freeStack(p->discard);
    freeStack(p->deck);
    free(p);
}

Board initNewBoard()
{
    Board b = (struct board *)malloc(sizeof(struct board));
    b->idPlayerPlaying = 1;
    b->idWinner = -1;
    b->p1 = newPlayer(1);
    b->p2 = newPlayer(2);
    b->round = 1;

    return b;
}

void freeBoard(Board b)
{
    freePlayer(b->p1);
    freePlayer(b->p2);
    free(b);
}

void newRound(Board b)
{
    if (b->round == 6 || b->round == 11)
    {
        b->maxCardInGame++;
    }
}

int getSpecificBonusInGameCards(Player player, int indexBonus)
{
    int bonus = 0;
    Fifo head = player->inGameCards;
    int *bonuses;
    while (head != NULL)
    {
        bonuses = getBonusOfCard(head->val);
        bonus += bonuses[indexBonus];
        head = head->next;
    }
    return 1 + bonus;
}

int countDrawCard(Player p, int round)
{
    if (round == 1)
    {
        return 3;
    }
    else
    {
        return getSpecificBonusInGameCards(p, DR);
    }
}

void drawCard(Player p)
{
    Card draw = pop(p->deck);
    if (draw.id != 0)
    {
        printf("Vous avez pioché la carte suivante:\n");
        printCard(draw);
        enqueue(draw, &(p->hand));
    }
    else
    {
        printf("ERREUR: PLUS DE CARTE DANS LA PIOCHE");
    }
}

int countStudentCard(Player p)
{
    return getSpecificBonusInGameCards(p, E);
}

//typeStudent 1: FISA, 0 : FISE
void addCardStudent(Player p, int typeStudent)
{
    //FISE
    if (typeStudent == 0)
    {
        p->nbFISE++;
    }
    //FISA
    else
    {
        p->nbFISA++;
    }
}

int nbOfPE(Player p, int isOdd)
{
    int nbPE = PE_FISE * p->nbFISE;
    if (isOdd)
    {
        nbPE += PE_FISA * p->nbFISA;
    }
    return nbPE;
}

int nbOfDD(Player player, int isOdd)
{
    Bonus bonus = player->bonus;
    int nbDD = player->nbFISE * bonus->valueDDFISE;
    nbDD += bonus->DDBonus;
    if (isOdd)
    {
        nbDD += player->nbFISA * bonus->valueDDFISA;
    }
    int nbDurability = nbOfDurability(player, isOdd);
    if (nbDurability < 0)
    {
        nbDD += nbDurability;
    }
    else
    {
        nbDD -= nbDurability;
    }
    if (nbDD < 0)
        return 0;
    return nbDD;
}

int nbOfDurability(Player player, int isOdd)
{
    Bonus bonus = player->bonus;
    int nbDurability = player->nbFISE * bonus->valueDurabilityFISE;
    if (isOdd)
    {
        nbDurability += player->nbFISA * bonus->valueDurabilityFISA;
    }
    return nbDurability;
}

int scorePlayer(Board board, int idPlayer)
{
    Player actualPlayer = idPlayer == 1 ? board->p1 : board->p2;
    Player opponentPlayer = idPlayer == 1 ? board->p2 : board->p1;
    int odd = isOdd(board->round);
    int total = nbOfDD(actualPlayer, odd) - nbOfDurability(opponentPlayer, odd);
    if (total < 0)
        return 0;
    return total;
}

void doAE1(Player player, int nb)
{
    player->bonus->valueDDFISE += nb;
}

void doAE2(Player player, int nb)
{
    player->bonus->valueDurabilityFISE += nb;
}

void doAA1(Player player, int nb)
{
    player->bonus->valueDDFISA += nb;
}

void doAA2(Player player, int nb)
{
    player->bonus->valueDurabilityFISA += nb;
}

void doRE1(Player player, int nb)
{
    player->bonus->valueDDFISE -= nb;
}

void doRE2(Player player, int nb)
{
    player->bonus->valueDurabilityFISE -= nb;
}

void doRA1(Player player, int nb)
{
    player->bonus->valueDDFISA -= nb;
}

void doRA2(Player player, int nb)
{
    player->bonus->valueDurabilityFISA -= nb;
}

void doADD(Player player, int nb)
{
    player->bonus->DDBonus += nb;
}

void doRDD(Player player, int nb)
{
    player->bonus->DDBonus -= nb;
}

//isBonus = 1 : bonus, -1 : malus
int castEffectsPersonnal(Card card, Player actualPlayer, Player opponentPlayer, int isBonus)
{

    int *bonuses = getBonusOfCard(card);
    if (bonuses[AE1] != 0)
        doAE1(actualPlayer, isBonus * bonuses[AE1]);
    if (bonuses[AE2] != 0)
        doAE2(actualPlayer, isBonus * bonuses[AE2]);
    if (bonuses[AA1] != 0)
        doAA1(actualPlayer, isBonus * bonuses[AA1]);
    if (bonuses[AA2] != 0)
        doAA2(actualPlayer, isBonus * bonuses[AA2]);
    if (bonuses[RE1] != 0)
        doRE1(opponentPlayer, isBonus * bonuses[RE1]);
    if (bonuses[RE2] != 0)
        doRE2(opponentPlayer, isBonus * bonuses[RE2]);
    if (bonuses[RA1] != 0)
        doRA1(opponentPlayer, isBonus * bonuses[RA1]);
    if (bonuses[RA2] != 0)
        doRA2(opponentPlayer, isBonus * bonuses[RA2]);
    if (bonuses[ADD] != 0)
        doADD(actualPlayer, isBonus * bonuses[ADD]);
    if (bonuses[RDD] != 0)
        doRDD(opponentPlayer, isBonus * bonuses[RDD]);

    return card.cost;
}

void removeEffect(Player actualPlayer, Player opponentPlayer, Card card)
{
    castEffectsPersonnal(card, actualPlayer, opponentPlayer, -1);
}

//Return cost of the card after effect
int castActionEffect(Board board, Card c)
{
    Player actualPlayer = board->idPlayerPlaying == 1 ? board->p1 : board->p2;
    Player opponentPlayer = board->idPlayerPlaying == 1 ? board->p2 : board->p1;

    int cost = c.cost;
    Stack fusionCards;
    Card first;

    switch (c.id)
    {
    case 21:
        actualPlayer->bonus->DDBonus++;
        break;

    case 22:
        drawCard(actualPlayer);
        break;

    //ADD FISE CARD
    case 23:
        addCardStudent(actualPlayer, 0);
        break;

    //ADD FISA CARD
    case 24:
        addCardStudent(actualPlayer, 1);
        break;

    //Player gain 6 PE (Card cost 4 PE)
    case 25:
        cost = -2;
        break;

    case 26:
        if (opponentPlayer->nbFISA > 0)
            opponentPlayer->nbFISA--;
        if (opponentPlayer->nbFISE > 0)
            opponentPlayer->nbFISE--;
        break;

    case 27:
        first = dequeue(&(opponentPlayer->inGameCards));
        if (first.id != 0)
        {
            printf("J'ai enlevé la carte suivante:\n");
            push(opponentPlayer->discard, first);
            removeEffect(opponentPlayer, actualPlayer, first);
        }
        else
        {
            printf("ERREUR: L'OPPOSANT N'A PAS DE CARTE EN JEU\n");
        }
        break;

    case 28:

        fusionCards = fusion(actualPlayer->discard, actualPlayer->deck);
        Card *shuffle = shuffleCards(fusionCards->c, fusionCards->size);
        fusionCards->c = shuffle;

        empty_stack(actualPlayer->discard);
        actualPlayer->deck = fusionCards;
        break;

    case 29:
        actualPlayer->bonus->valueDDFISE++;
        actualPlayer->bonus->valueDDFISA++;
        break;

    case 30:
        actualPlayer->bonus->valueDurabilityFISE++;
        actualPlayer->bonus->valueDurabilityFISA++;
        break;

    case 31:
        opponentPlayer->nbFISA = 0;
        opponentPlayer->nbFISE = 0;
        actualPlayer->nbFISA = 0;
        actualPlayer->nbFISE = 0;
        break;
    }
    return cost;
}

int playCard(Board board, Card c)
{
    Player actualPlayer = board->idPlayerPlaying == 1 ? board->p1 : board->p2;
    Player opponentPlayer = board->idPlayerPlaying == 1 ? board->p2 : board->p1;
    int cost;

    //1 ACTION 0 PERSONAL -1 ERROR
    if (getTypeCard(c) == 1)
    {
        push(actualPlayer->discard, c);
        cost = castActionEffect(board, c);
    }
    //PERSONNAL
    else
    {
        //Remove first in game card
        if (sizeFifo(actualPlayer->inGameCards) > board->maxCardInGame)
        {
            Card first = dequeue(&(actualPlayer->inGameCards));
            if (first.id == 0)
            {
                push(actualPlayer->discard, first);
            }
        }

        enqueue(c, &(actualPlayer->inGameCards));
        cost = castEffectsPersonnal(c, actualPlayer, opponentPlayer, 1);
    }

    deleteID(&(actualPlayer->hand), c.id);
    return cost;
}

void endRound(Board b)
{
    b->round++;
}

int endGame(Board b)
{
    int nbDD1 = scorePlayer(b, 1);
    int nbDD2 = scorePlayer(b, 2);

    if (nbDD1 >= NUMBER_DD_WIN || nbDD2 >= NUMBER_DD_WIN)
    {
        if (nbDD1 > nbDD2)
            b->idWinner = 1;

        else if (nbDD1 < nbDD2)
            b->idWinner = 2;

        else
            b->idWinner = -1;

        return 1;
    }

    if (b->round == MAX_ROUND)
    {
        b->idWinner = -1;
        return 1;
    }
    return 0;
}

void updatePlayerPlaying(Board board, int phase)
{
    int *actualPlayer = &(board->idPlayerPlaying);
    if (phase == 0 && *actualPlayer == 2)
        *actualPlayer = 1;
    else if (phase == 0 && *actualPlayer == 1)
        *actualPlayer = 2;
}

int isOdd(int n)
{
    if (n % 2 == 0)
    {
        return 0;
    }
    return 1;
}
