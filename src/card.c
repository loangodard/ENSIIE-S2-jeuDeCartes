#include "../headers/card.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define NB_CARDS_MAX 42
#define NB_EFFECT 12
#define NB_TOTAL_ACTION_CARDS 22
#define NB_TOTAL_PERSONAL_CARDS 20

//Tab of tab with name of each cards
char **nameCardsGlobal;

//Tab of tab with effects in int verson of each cards
int **effectsCardsGlobal;

int *copyIntTab(int *tab, int size)
{
    int *p;
    p = (int *)malloc(size * sizeof(int));
    for (int i = 0; i < size; i++)
    {
        p[i] = tab[i];
    }
    return p;
}

void printCard(Card c)
{
    int type = getTypeCard(c);
    //1 = Action et 0 = Personnel
    if (type == 1)
    {
        printf("[ID : %d, Type : Action,  Nom : %s, Cout : %d, Effet : %s]\n", getID(c), nameCardsGlobal[c.id - 1], getCost(c), getEffect(c));
    }
    else if (type == 0)
    {
        printf("[ID : %d, Type : Personnel, Nom : %s, Cout : %d, Effet : %s]\n", getID(c), nameCardsGlobal[c.id - 1], getCost(c), getEffect(c));
    }
    else
    {
        printf("Carte n'existe pas...\n");
    }
    fflush(stdout);
}

int getCost(Card c)
{
    return c.cost;
}

int getID(Card c)
{
    return c.id;
}

int getTypeCard(Card c)
{
    //Action Card
    if (c.id > 20 && c.id < 32)
    {
        return 1;
    }
    else
    {
        //Personnal Card
        if (c.id <= 20 && c.id > 0)
        {
            return 0;
        }
        else
        {
            return -1;
        }
    }
}

char *getEffect(Card c)
{
    return c.effect;
}

int *getBonusOfCard(Card c)
{
    return effectsCardsGlobal[c.id - 1];
}

int addActionCardsInDeck(Card *tab, int id, int cost, int quantity, char *effect, int index)
{
    Card tempCard;
    tempCard.id = id;
    tempCard.cost = cost;
    tempCard.effect = effect;
    for (int j = 0; j < quantity; j++)
    {
        tab[index + j] = tempCard;
        index++;
    }
    return index;
}

Card *getActionCards()
{
    Card *cardTab = (Card *)malloc(sizeof(Card) * NB_TOTAL_ACTION_CARDS);
    Card c1;
    c1.id = 21;
    c1.cost = 2;

    Card c2;
    c2.id = 21;
    c2.cost = 2;

    Card c3;
    c3.id = 21;
    c3.cost = 2;

    Card c4;
    c4.id = 22;
    c4.cost = 2;

    Card c5;
    c5.id = 22;
    c5.cost = 2;

    Card c6;
    c6.id = 22;
    c6.cost = 2;

    Card c7;
    c7.id = 23;
    c7.cost = 3;

    Card c8;
    c8.id = 23;
    c8.cost = 3;

    Card c9;
    c9.id = 24;
    c9.cost = 3;

    Card c10;
    c10.id = 24;
    c10.cost = 3;

    Card c11;
    c11.id = 25;
    c11.cost = 4;

    Card c12;
    c12.id = 25;
    c12.cost = 4;

    Card c13;
    c13.id = 26;
    c13.cost = 5;

    Card c14;
    c14.id = 26;
    c14.cost = 5;

    Card c15;
    c15.id = 27;
    c15.cost = 5;

    Card c16;
    c16.id = 27;
    c16.cost = 5;

    Card c17;
    c17.id = 27;
    c17.cost = 5;

    Card c18;
    c18.id = 27;
    c18.cost = 5;

    Card c19;
    c19.id = 28;
    c19.cost = 10;

    Card c20;
    c20.id = 29;
    c20.cost = 10;

    Card c21;
    c21.id = 30;
    c21.cost = 10;

    Card c22;
    c22.id = 31;
    c22.cost = 10;

    cardTab[0] = c1;
    cardTab[1] = c2;
    cardTab[2] = c3;
    cardTab[3] = c4;
    cardTab[4] = c5;
    cardTab[5] = c6;
    cardTab[6] = c7;
    cardTab[7] = c8;
    cardTab[8] = c9;
    cardTab[9] = c10;
    cardTab[10] = c11;
    cardTab[11] = c12;
    cardTab[12] = c13;
    cardTab[13] = c14;
    cardTab[14] = c15;
    cardTab[15] = c16;
    cardTab[16] = c17;
    cardTab[17] = c18;
    cardTab[18] = c19;
    cardTab[19] = c20;
    cardTab[20] = c21;
    cardTab[21] = c22;

    cardTab[0].effect = "Gagnez 1 DD";
    cardTab[1].effect = "Gagnez 1 DD";
    cardTab[2].effect = "Gagnez 1 DD";
    cardTab[3].effect = "Piochez une carte";
    cardTab[4].effect = "Piochez une carte";
    cardTab[5].effect = "Piochez une carte";
    cardTab[6].effect = "Mettez en jeu une carte FISE";
    cardTab[7].effect = "Mettez en jeu une carte FISE";
    cardTab[8].effect = "Mettez en jeu une carte FISA";
    cardTab[9].effect = "Mettez en jeu une carte FISA";
    cardTab[10].effect = "Gagnez 6 PE";
    cardTab[11].effect = "Gagnez 6 PE";
    cardTab[12].effect = "Retirez une carte FISE et une carte FISA du plateau de l’adversaire";
    cardTab[13].effect = "Retirez une carte FISE et une carte FISA du plateau de l’adversaire";
    cardTab[14].effect = "Mettez la première des cartes Personnel mise en jeu par l’adversaire dans sa défausse.";
    cardTab[15].effect = "Mettez la première des cartes Personnel mise en jeu par l’adversaire dans sa défausse.";
    cardTab[16].effect = "Mettez la première des cartes Personnel mise en jeu par l’adversaire dans sa défausse.";
    cardTab[17].effect = "Mettez la première des cartes Personnel mise en jeu par l’adversaire dans sa défausse.";
    cardTab[18].effect = "Mélangez votre défausse et cette carte avec votre pioche";
    cardTab[19].effect = "Vos cartes Élèves gagnent un point de Développement.Toute nouvelle carte Élève arrivant en jeu gagne 1 point de Développement";
    cardTab[20].effect = "Vos cartes Élèves gagnent un point de Durabilité. Toute nouvelle carte Élève arrivant en jeu gagne 1 point de Durabilité";
    cardTab[21].effect = "Retirez de tous les plateaux toutes les cartes FISE et FISA";

    return cardTab;
}

Card *shuffleCards(Card *cards, int size)
{
    srand(time(NULL));
    if (size > 1)
    {
        int nbshuffle = 50;
        for (int k = 0; k < nbshuffle; k++)
        {
            for (int i = 0; i < size - 1; i++)
            {
                int j = rand() % (size);
                Card t = cards[j];
                cards[j] = cards[i];
                cards[i] = t;
            }
        }
    }
    sleep(1);
    return cards;
}

Card *getCards()
{
    Card *personnalCards = getPersonnalCards();
    Card *actionCards = getActionCards();
    Card *allcards = concatCardTab(personnalCards, actionCards, NB_TOTAL_PERSONAL_CARDS, NB_TOTAL_ACTION_CARDS);
    return allcards;
}

Card *concatCardTab(Card *personnalCards, Card *actionCards, int sizeP, int sizeA)
{
    Card *finalTab = (Card *)malloc(sizeof(Card) * (sizeA + sizeP));
    int i = 0;
    for (i = 0; i < sizeP; i++)
    {
        finalTab[i] = personnalCards[i];
    }
    free(personnalCards);
    for (; i < (sizeP + sizeA); i++)
    {
        finalTab[i] = actionCards[i - sizeP];
    }
    free(actionCards);
    return finalTab;
}

Card *getPersonnalCards()
{
    if (nameCardsGlobal == NULL)
    {
        initializeTableCard();
    }
    Card *cardTab;

    cardTab = (Card *)malloc(sizeof(Card) * 20);

    Card c1;
    c1.id = 1;
    c1.cost = 3;

    Card c2;
    c2.id = 2;
    c2.cost = 3;

    Card c3;
    c3.id = 3;
    c3.cost = 3;

    Card c4;
    c4.id = 4;
    c4.cost = 3;

    Card c5;
    c5.id = 5;
    c5.cost = 3;

    Card c6;
    c6.id = 6;
    c6.cost = 3;

    Card c7;
    c7.id = 7;
    c7.cost = 3;

    Card c8;
    c8.id = 8;
    c8.cost = 3;

    Card c9;
    c9.id = 9;
    c9.cost = 5;

    Card c10;
    c10.id = 10;
    c10.cost = 5;

    Card c11;
    c11.id = 11;
    c11.cost = 5;

    Card c12;
    c12.id = 12;
    c12.cost = 5;

    Card c13;
    c13.id = 13;
    c13.cost = 7;

    Card c14;
    c14.id = 14;
    c14.cost = 8;

    Card c15;
    c15.id = 15;
    c15.cost = 8;

    Card c16;
    c16.id = 16;
    c16.cost = 10;

    Card c17;
    c17.id = 17;
    c17.cost = 10;

    Card c18;
    c18.id = 18;
    c18.cost = 15;

    Card c19;
    c19.id = 19;
    c19.cost = 15;

    Card c20;
    c20.id = 20;
    c20.cost = 20;

    cardTab[0] = c1;
    cardTab[1] = c2;
    cardTab[2] = c3;
    cardTab[3] = c4;
    cardTab[4] = c5;
    cardTab[5] = c6;
    cardTab[6] = c7;
    cardTab[7] = c8;
    cardTab[8] = c9;
    cardTab[9] = c10;
    cardTab[10] = c11;
    cardTab[11] = c12;
    cardTab[12] = c13;
    cardTab[13] = c14;
    cardTab[14] = c15;
    cardTab[15] = c16;
    cardTab[16] = c17;
    cardTab[17] = c18;
    cardTab[18] = c19;
    cardTab[19] = c20;

    cardTab[0].effect = "1 AE1";
    cardTab[1].effect = "1 AE2";
    cardTab[2].effect = "1 AA1";
    cardTab[3].effect = "1 AA2";
    cardTab[4].effect = "1 RE1";
    cardTab[5].effect = "1 RE2";
    cardTab[6].effect = "1 RA1";
    cardTab[7].effect = "1 RA2";
    cardTab[8].effect = "1 AE1 - 1 AA1";
    cardTab[9].effect = "1 AE2 - 1 AA2";
    cardTab[10].effect = "1 RE1 - 1 RA1";
    cardTab[11].effect = "1 RE2 - 1 RA2";
    cardTab[12].effect = "2 DR";
    cardTab[13].effect = "2 ADD - 1 DR - 1 E";
    cardTab[14].effect = "2 RDD - 1 DR - 1 E";
    cardTab[15].effect = "1 AE1 - 1 AE2 - 1 RE2 - 1 RDD";
    cardTab[16].effect = "1 AA1 - 1 AA2 - 1 RA2 - 1 RDD";
    cardTab[17].effect = "2 AE1 - 2 AE2 - 1 E";
    cardTab[18].effect = "2 AA1 - 2 AA2 - 1 E";
    cardTab[19].effect = "2 AE1 - 2 AE2 - 1 E - 2 AA1 - 2 AA2 - 1 ADD - 1 RDD - 1 DR - 2 E";

    return cardTab;
}

void initializeTableCard()
{
    nameCardsGlobal = (char **)malloc(NB_CARDS_MAX * sizeof(char *));
    effectsCardsGlobal = (int **)malloc(NB_TOTAL_PERSONAL_CARDS * sizeof(int *));
    char *tempCard;
    int tempEffect[NB_EFFECT] = {0};
    tempCard = "Thomas Lim";
    nameCardsGlobal[0] = tempCard;
    tempEffect[0] = 1;
    effectsCardsGlobal[0] = copyIntTab(tempEffect, NB_EFFECT);
    tempEffect[0] = 0;

    tempCard = "Marie Szafranski";
    nameCardsGlobal[1] = tempCard;
    tempEffect[1] = 1;
    effectsCardsGlobal[1] = copyIntTab(tempEffect, NB_EFFECT);
    tempEffect[0] = 0;

    tempCard = "Alain Faye";
    nameCardsGlobal[2] = tempCard;
    tempEffect[2] = 1;
    effectsCardsGlobal[2] = copyIntTab(tempEffect, NB_EFFECT);
    tempEffect[2] = 0;

    tempCard = "Christophe Mouilleron";
    nameCardsGlobal[3] = tempCard;
    tempEffect[3] = 1;
    effectsCardsGlobal[3] = copyIntTab(tempEffect, NB_EFFECT);
    tempEffect[3] = 0;

    tempCard = "Stefania Dumbrava";
    nameCardsGlobal[4] = tempCard;
    tempEffect[4] = 1;
    effectsCardsGlobal[4] = copyIntTab(tempEffect, NB_EFFECT);
    tempEffect[4] = 0;

    tempCard = "Julien Forest";
    nameCardsGlobal[5] = tempCard;
    tempEffect[5] = 1;
    effectsCardsGlobal[5] = copyIntTab(tempEffect, NB_EFFECT);
    tempEffect[5] = 0;

    tempCard = "Nicolas Brunel";
    nameCardsGlobal[6] = tempCard;
    tempEffect[6] = 1;
    effectsCardsGlobal[6] = copyIntTab(tempEffect, NB_EFFECT);
    tempEffect[6] = 0;

    tempCard = "Laurence Bourard";
    nameCardsGlobal[7] = tempCard;
    tempEffect[7] = 1;
    effectsCardsGlobal[7] = copyIntTab(tempEffect, NB_EFFECT);
    tempEffect[7] = 0;

    tempCard = "Dimitri Watel";
    nameCardsGlobal[8] = tempCard;
    tempEffect[0] = 1;
    tempEffect[2] = 1;
    effectsCardsGlobal[8] = copyIntTab(tempEffect, NB_EFFECT);
    tempEffect[0] = 0;
    tempEffect[2] = 0;

    tempCard = "Vitera Y";
    nameCardsGlobal[9] = tempCard;
    tempEffect[1] = 1;
    tempEffect[3] = 1;
    effectsCardsGlobal[9] = copyIntTab(tempEffect, NB_EFFECT);
    tempEffect[1] = 0;
    tempEffect[3] = 0;

    tempCard = "Kevin Goilard";
    nameCardsGlobal[10] = tempCard;
    tempEffect[4] = 1;
    tempEffect[6] = 1;
    effectsCardsGlobal[10] = copyIntTab(tempEffect, NB_EFFECT);
    tempEffect[4] = 0;
    tempEffect[6] = 0;

    tempCard = "Vincent Jeannas";
    nameCardsGlobal[11] = tempCard;
    tempEffect[1] = 1;
    tempEffect[5] = 1;
    tempEffect[7] = 1;
    effectsCardsGlobal[11] = copyIntTab(tempEffect, NB_EFFECT);
    tempEffect[1] = 0;
    tempEffect[5] = 0;
    tempEffect[7] = 0;

    tempCard = "Massinissa Merabet";
    nameCardsGlobal[12] = tempCard;
    tempEffect[10] = 2;
    effectsCardsGlobal[12] = copyIntTab(tempEffect, NB_EFFECT);
    tempEffect[10] = 0;

    tempCard = "Anne-Laure Ligozat";
    nameCardsGlobal[13] = tempCard;
    tempEffect[11] = 1;
    tempEffect[10] = 1;
    tempEffect[8] = 2;
    effectsCardsGlobal[13] = copyIntTab(tempEffect, NB_EFFECT);
    tempEffect[11] = 0;
    tempEffect[10] = 0;
    tempEffect[8] = 0;

    tempCard = "Catherine Dubois";
    nameCardsGlobal[14] = tempCard;
    tempEffect[11] = 1;
    tempEffect[10] = 1;
    tempEffect[9] = 2;
    effectsCardsGlobal[14] = copyIntTab(tempEffect, NB_EFFECT);
    tempEffect[11] = 1;
    tempEffect[10] = 1;
    tempEffect[9] = 2;

    tempCard = "Eric Lejeune";
    nameCardsGlobal[15] = tempCard;
    tempEffect[0] = 1;
    tempEffect[1] = 1;
    tempEffect[5] = 1;
    tempEffect[9] = 1;
    effectsCardsGlobal[15] = copyIntTab(tempEffect, NB_EFFECT);
    tempEffect[0] = 0;
    tempEffect[1] = 0;
    tempEffect[5] = 0;
    tempEffect[9] = 0;

    tempCard = "Christine Mathias";
    nameCardsGlobal[16] = tempCard;
    tempEffect[2] = 1;
    tempEffect[3] = 1;
    tempEffect[7] = 1;
    tempEffect[9] = 1;
    effectsCardsGlobal[16] = copyIntTab(tempEffect, NB_EFFECT);
    tempEffect[2] = 0;
    tempEffect[3] = 0;
    tempEffect[7] = 0;
    tempEffect[9] = 0;

    tempCard = "Katrin Salhab";
    nameCardsGlobal[17] = tempCard;
    tempEffect[0] = 2;
    tempEffect[1] = 2;
    tempEffect[11] = 1;
    effectsCardsGlobal[17] = copyIntTab(tempEffect, NB_EFFECT);
    tempEffect[0] = 0;
    tempEffect[1] = 0;
    tempEffect[11] = 0;

    tempCard = "Abass Sagna";
    nameCardsGlobal[18] = tempCard;
    tempEffect[2] = 2;
    tempEffect[3] = 2;
    tempEffect[11] = 1;
    effectsCardsGlobal[18] = copyIntTab(tempEffect, NB_EFFECT);
    tempEffect[2] = 0;
    tempEffect[3] = 0;
    tempEffect[11] = 0;

    tempCard = "Laurent Prével";
    nameCardsGlobal[19] = tempCard;
    tempEffect[0] = 2;
    tempEffect[1] = 2;
    tempEffect[2] = 2;
    tempEffect[3] = 2;
    tempEffect[8] = 1;
    tempEffect[9] = 1;
    tempEffect[10] = 1;
    tempEffect[11] = 2;
    effectsCardsGlobal[19] = copyIntTab(tempEffect, NB_EFFECT);

    tempCard = "Cours Développement Durable";
    nameCardsGlobal[20] = tempCard;

    tempCard = "Recrutement";
    nameCardsGlobal[21] = tempCard;

    tempCard = "Rentrée FISE";
    nameCardsGlobal[22] = tempCard;

    tempCard = "Rentrée FISA";
    nameCardsGlobal[23] = tempCard;

    tempCard = "Energie Verte";
    nameCardsGlobal[24] = tempCard;

    tempCard = "Diplomation";
    nameCardsGlobal[25] = tempCard;

    tempCard = "Décharge";
    nameCardsGlobal[26] = tempCard;

    tempCard = "Recyclage";
    nameCardsGlobal[27] = tempCard;

    tempCard = "Zéro papier";
    nameCardsGlobal[28] = tempCard;

    tempCard = "Repas végétarien";
    nameCardsGlobal[29] = tempCard;

    tempCard = "Fermeture annuelle";
    nameCardsGlobal[30] = tempCard;
}

int getSizeCardsTotal()
{
    return NB_TOTAL_PERSONAL_CARDS + NB_TOTAL_ACTION_CARDS;
}
