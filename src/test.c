#include "../headers/board.h"
#include "../headers/interface.h"
#include <stdio.h>
#include <stdlib.h>


Card ChooseCardDeck(int id,Stack s){
    while(s->top != -1){
        Card c = pop(s);
        if (c.id == id){
            return c;
        }
    }
    return errorCard();
}

void print_success(int *i,int numTest){
    (*i)++;
    printf("Carte n %d : SUCCESS\n",numTest);
    sleep(2);
    system("clear");
}

void print_error(int *i,int numTest){
    (*i)++;
    printf("Carte n %d : ERROR\n",numTest);
    sleep(2);
    system("clear");
}



/*
int main(void)
{
    Board board = initNewBoard();
    Player player;
    while (!endGame(board))
    {
        newRound(board);
        printNewRound(board);
        for (int j = 0; j < 2; j++)
        {
            player = board->idPlayerPlaying == 1 ? board->p1 : board->p2;
            printNewPhase(board->idPlayerPlaying);
            printBoard(board);

            int nbDrawCard = countDrawCard(player, board->round);
            printf("Vous allez piocher %d carte(s) personnelle(s) / action(s) \n", nbDrawCard);

            for (int i = 0; i < nbDrawCard; i++)
            {
                drawCard(player);
            }

            printHand(player);

            int nbStudentCard = countStudentCard(player);
            printf("\nVous pouvez piocher %d carte(s) étudiante(s)\n", nbStudentCard);
            int typeCard;
            for (int i = 0; i < nbStudentCard; i++)
            {
                typeCard = askTypeCard(); // 0 : FISE, 1: FISA
                addCardStudent(player, typeCard);
            }
            int nbPE = nbOfPE(player, isOdd(board->round));
            Card *cardChoosed;

            while ((cardChoosed = askAction(player, nbPE)) != NULL)
            {
                nbPE = nbPE - playCard(board, *cardChoosed);
            }

            updatePlayerPlaying(board, j);
        }
        endRound(board);
    }
    printWinner(board->idWinner);
    freeBoard(board); 

    for(int i=0;i<20;i++){
        addCardStudent(board->p1,0);
        addCardStudent(board->p1,0);
    }
}*/



int main(){

    int nbTest;

    int success = 0;
    int error = 0;

    char r[2];
    char *erreur;
    printf("---Voulez vous tester toutes les cartes ? y/n---\n");
    scanf("%s", r);
    if(r[0] == 'n'){
        char str[2];
        printf("---Quelle carte voulez vous tester ? entrez un nombre dans [1;31]---\n");
        scanf("%s", str);
        nbTest = strtol(str, &erreur, 10)+1;
    }else{
        nbTest = 32;
    }

    system("clear");

    char testing ='y';
    Board board = initNewBoard();
    int p2Play = 1;
    Player player;

    while (testing == 'y' && nbTest > 1)
    {
        if(board->round == 3){
            freeBoard(board);
            system("clear");
            board->round = 1;
        }
        if (board->round == 1){
            p2Play = 1;
            nbTest--;
            printf("---TEST---\n");
            printf("---Test de la carte %d---\n",nbTest);
            board = initNewBoard();
            for(int i=0;i<15;i++){
                addCardStudent(board->p1,0);
                addCardStudent(board->p2,0);
                addCardStudent(board->p1,1);
                addCardStudent(board->p2,1);
                board->p1->bonus->valueDDFISE=2;
                board->p2->bonus->valueDDFISE=2;
            }
        }
        if (board->round == 2){
            for(int i=0;i<15;i++){
                addCardStudent(board->p1,0);
                addCardStudent(board->p2,0);
                addCardStudent(board->p1,1);
                addCardStudent(board->p2,1);
                board->p1->bonus->valueDDFISE=2;
                board->p2->bonus->valueDDFISE=2;
            }
        }


        
        printf("--- Test numéro %d ---",nbTest);
        newRound(board);
        printNewRound(board);

        //On initialise le nombre de PE pour pouvoir tester.


        for (int j = 0; j < 2; j++)
        {
            if(j == 1 && p2Play == 0){
                printf("P2 NE JOUE PAS\n");
            }
            else{
                player = board->idPlayerPlaying == 1 ? board->p1 : board->p2;
                printNewPhase(board->idPlayerPlaying);
                printBoard(board);

                Card draw = ChooseCardDeck(nbTest,player->deck);
                player->deck = initializeDeck();

                //Tests des cartes personnels

                //Carte 1:Thomas LIM -> ajout de 1 point de Développement à chaque carte FISE ENSIIE
                //Card draw = ChooseCardDeck(1,player->deck);

                //Carte 2:Marie Szafranski -> ajout de 1 point de Durabilité à chaque carte FISE ENSIIE
                //Card draw = ChooseCardDeck(2,player->deck);
     
                //Carte 3:Alain Faye -> ajout de 1 point de Développement à chaque carte FISA ENSIIE
                //Card draw = ChooseCardDeck(3,player->deck);
     
                //Carte 4:Christophe Mouilleron -> ajout de 1 point de Durabilité à chaque carte FISA ENSIIE
                //Card draw = ChooseCardDeck(4,player->deck);

                //Carte 5:Stefania DUmbrava -> retire 1 point de Developpement à chaque carte FISE adversaire
                //Card draw = ChooseCardDeck(5,player->deck);

                //Carte 6:Julien Forest -> retrait de 1 point de Durabilité à chaque carte FISE adversaire
                //Card draw = ChooseCardDeck(6,player->deck);

                //Carte 7:Nicolas Brunel -> retrait de 1 point de Developpement à chaque carte FISA adversaire
                //Card draw = ChooseCardDeck(7,player->deck);

                //Carte 8:Laurence Bourard-> retrait de 1 point de Durabilité à chaque carte FISA adversaire
                //Card draw = ChooseCardDeck(8,player->deck);

                //Carte 9:Dimitri Watel -> ajout 1 Dev à fisa + fise
                //Card draw = ChooseCardDeck(9,player->deck);

                //Carte 10:Vitera Y-> ajout 1 Durabilité fisa + fise
                //Card draw = ChooseCardDeck(10,player->deck);

                //Carte 11:Kevin Goilard-> retrait 1 dev fise + fisa adverse
                //Card draw = ChooseCardDeck(11,player->deck);

                //Carte 12:Vincent Jeannas-> retirait 1 durabilité fise + fisa adverse
                //Card draw = ChooseCardDeck(12,player->deck);

                //Carte 13:Massinissa Merabet -> piocher 2 cartes de plus
                //Card draw = ChooseCardDeck(13,player->deck);

                //Carte 14:Anne-Laure Ligozat -> 2DD de plus + 1 carte piochée supplémentaire + 1 carte élève en plus
                //Card draw = ChooseCardDeck(14,player->deck);

                //Carte 15:Catherine Dubois-> retranche 2 DD gagné à la fin du tour + 1 carte de plus pioché + 1 carte élève supplémentaire
                //Card draw = ChooseCardDeck(15,player->deck);

                //Carte 16:Eric Lejeune->  1 dev + 1 dur au fise + 1 dur retrait fise adverse +1 dd retrancher à l'adversaire
                //Card draw = ChooseCardDeck(16,player->deck); 

                //Carte 17:Christine Mathias-> 1 dur + 1 dev fisa +1 dur retrait fisa adverse + 1 dd retiré à l'adversaire
                //Card draw = ChooseCardDeck(17,player->deck);

                //Carte 18:Katrine Salhab -> 2 dur et 2 dev à fise  + 1 carte élève en plus
                //Card draw = ChooseCardDeck(18,player->deck);

                //Carte 19:Abass Sagna-> 2dev + 2dur à chaque FISA + 1 carte elève supplémentaire
                //Card draw = ChooseCardDeck(19,player->deck);

                //Carte 20:Laurent Prevel
                //Card draw = ChooseCardDeck(20,player->deck);


                // Tests des cartes Actions

                //Carte 21: ajout d'un DD: OK
                //Card draw = ChooseCardDeck(21,board->p1->deck);

                //Carte 22: pioche d'une Carte: OK
                //Card draw = ChooseCardDeck(22,board->p1->deck);
                
                //Carte 23: Mettre en Jeu une carte FISE: OK
                //Card draw = ChooseCardDeck(23,board->p1->deck);

                //Carte 24: Mettez en Jeu une carte FISA: OK
                //Card draw = ChooseCardDeck(24,board->p1->deck);

                //Carte 25: Gagner 6 PE (on ajoute une autre carte pour vérifier qu'on a bien les PE disponible au tour même)
                //Card perso = ChooseCardDeck(8,player->deck);
                //enqueue(perso, &(player->hand));
                //Card draw = ChooseCardDeck(25,player->deck);

                //Carte 26: On enlève une Carte Fise ou Fisa à l'adversaire
                //Card draw = ChooseCardDeck(26,player->deck);

                //Carte 27: pioche d'une Carte: OK
                //Card perso = ChooseCardDeck(8,player->deck);
                //enqueue(perso, &(player->hand));
                //Card draw = ChooseCardDeck(27,player->deck);

                //Carte 28: Mélange de la défausse et de cette carte avec la pioche
                //Card draw = ChooseCardDeck(28,player->deck);

                //Carte 29:Vos cartes Élèves gagnent un point de Développement.Toute nouvelle carte Élève arrivant en jeu gagne 1 point de Développement"
                //Card draw = ChooseCardDeck(29,player->deck);
     
                //Carte 30:"Vos cartes Élèves gagnent un point de Durabilité. Toute nouvelle carte Élève arrivant en jeu gagne 1 point de Durabilité"
                //Card draw = ChooseCardDeck(30,player->deck);

                //Carte 31:"Vos cartes Élèves gagnent un point de Durabilité. Toute nouvelle carte Élève arrivant en jeu gagne 1 point de Durabilité"
                //Card draw = ChooseCardDeck(31,player->deck);

                int beginningDD;
                int beginningDurability;
                int beginningDDp2;
                int beginningDurabilityp2;
                int beginningValueDDFisa;

                switch(nbTest){
                    case 1: //On ne voudra pas que p2 joue 
                        beginningDD = nbOfDD(player,isOdd(board->round));
                        p2Play = 0;
                        break;
                    case 2: //On ne voudra pas que p2 joue 
                        beginningDurability = nbOfDurability(player, isOdd(board->round));
                        p2Play = 0;
                        break;
                    case 3: //On ne voudra pas que p2 joue 
                        beginningValueDDFisa = player->bonus->valueDDFISA;
                        p2Play = 0;
                        break;
                    case 4: //On ne voudra pas que p2 joue 
                        beginningDurability = nbOfDurability(player, isOdd(board->round));
                        p2Play = 0;
                        break;
                    case 5: //On ne voudra pas que p2 joue 
                        beginningDDp2 = nbOfDD(board->p2, isOdd(board->round));
                        beginningDD = nbOfDD(board->p1, isOdd(board->round));
                        p2Play = 0;
                        break;
                    case 6:
                        beginningDurabilityp2 = nbOfDurability(board->p2, isOdd(board->round));
                        beginningDurability = nbOfDurability(board->p1, isOdd(board->round));
                        p2Play = 0;
                        break;
                    case 7:
                        beginningDDp2 = nbOfDD(board->p2, isOdd(board->round));
                        beginningDD = nbOfDD(board->p1, isOdd(board->round));
                        p2Play = 0;
                        break;
                    case 8:
                        beginningDurabilityp2 = nbOfDurability(board->p2, isOdd(board->round));
                        beginningDurability = nbOfDurability(board->p1, isOdd(board->round));
                        p2Play = 0;
                        break;
                    case 9:
                        beginningDD = nbOfDD(player,isOdd(board->round));
                        beginningDurability = nbOfDurability(board->p1, isOdd(board->round));
                        p2Play = 0;
                        break;
                    case 10: break;
                    case 11: break;
                    case 12: break;
                    case 13: break;
                    case 14: break;
                    case 15: break;
                    case 16: break;
                    case 17: break;
                    case 18: break;
                    case 19: break;
                    case 20: break;
                    case 21: break;
                    case 22: break;
                    case 23: break;
                    case 24: break;
                    case 25: break;
                    case 26: break;
                    case 27: break;
                    case 28: break;
                    case 29: break;
                    case 30: break;
                    case 31: break;
                    default: printf("default");
                }
                

                enqueue(draw, &(player->hand));


                printHand(player);

                int nbStudentCard = countStudentCard(player);
                // printf("\nVous pouvez piocher %d carte(s) étudiante(s)\n", nbStudentCard);
                int typeCard;

                // for (int i = 0; i < nbStudentCard; i++)
                // {
                //     typeCard = askTypeCard(); // 0 : FISE, 1: FISA
                //     addCardStudent(player, typeCard);
                // }

                int nbPE = nbOfPE(player, isOdd(board->round));
                Card *cardChoosed;

                while ((cardChoosed = askAction(player, nbPE)) != NULL)
                {
                    nbPE = nbPE - playCard(board, *cardChoosed);
                }


                int endDD;
                int endDDp2;
                int endDurability;
                int endDurabilityp2;
                int endValueDDFisa;


                switch(nbTest){
                    case 1:
                        endDD = nbOfDD(player,isOdd(board->round));
                        if(endDD-beginningDD == player->nbFISE){
                            print_success(&success,nbTest);
                        }else{
                            print_error(&error,nbTest);
                        }
                        break;

                    case 2:
                        endDurability = nbOfDurability(player, isOdd(board->round));
                        if(endDurability-beginningDurability == player->nbFISE){
                            print_success(&success,nbTest);
                        }else{
                            print_error(&error,nbTest);
                        }
                        break;

                    case 3:
                        endValueDDFisa = player->bonus->valueDDFISA;
                        if (endValueDDFisa == beginningValueDDFisa+1){
                            print_success(&success,nbTest);
                        }
                        break;

                    case 4:
                        endDurability = nbOfDurability(player, isOdd(board->round));
                        if(endDurability-beginningDurability == player->nbFISA){
                            print_success(&success,nbTest);
                        }else{
                            print_error(&error,nbTest);
                        }
                        break;

                    case 5: //Error -> enleve des DD des DEUX JOUEURS
                        endDDp2 = nbOfDD(board->p2, isOdd(board->round));
                        endDD = nbOfDD(board->p1, isOdd(board->round));
                        if(beginningDDp2 - endDDp2 == board->p2->nbFISE && beginningDD == endDD){
                            print_success(&success,nbTest);
                        }else{
                            print_error(&error,nbTest);
                        }
                        break;

                    case 6: 
                        endDurabilityp2 = nbOfDurability(board->p2, isOdd(board->round));
                        endDurability = nbOfDurability(board->p1, isOdd(board->round));
                        if(beginningDurabilityp2 - endDurabilityp2 == board->p2->nbFISE && beginningDurability == endDurability){
                            print_success(&success,nbTest);
                        }else{
                            printBoard(board);
                            print_error(&error,nbTest);
                        }
                        break;

                    case 7: //Error -> enleve des DD aux deux joueurs
                        endDDp2 = nbOfDD(board->p2, isOdd(board->round));
                        endDD = nbOfDD(board->p1, isOdd(board->round));
                        if(beginningDDp2 - endDDp2 == board->p2->nbFISA && beginningDD == endDD){
                            print_success(&success,nbTest);
                        }else{
                            printBoard(board);
                            print_error(&error,nbTest);
                        }
                        break;
                    case 8: // Error -> même erreur que 6
                        endDurabilityp2 = nbOfDD(board->p2, isOdd(board->round));
                        endDurability = nbOfDD(board->p1, isOdd(board->round));
                        if(beginningDurabilityp2 - endDurabilityp2 == board->p2->nbFISA && beginningDurability == endDurability){
                            print_success(&success,nbTest);
                        }else{
                            printBoard(board);
                            print_error(&error,nbTest);
                        }
                        break;

                    case 9:
                        endDD = nbOfDD(player,isOdd(board->round));
                        endDurability = nbOfDurability(player,isOdd(board->round));
                        if(endDD-beginningDD == player->nbFISE && endDurability-beginningDurability == player->nbFISA){
                            print_success(&success,nbTest);
                        }else{
                            printBoard(board);
                            print_error(&error,nbTest);
                        }
                        break;
                    case 10: break;
                    case 11: break;
                    case 12: break;
                    case 13: break;
                    case 14: break;
                    case 15: break;
                    case 16: break;
                    case 17: break;
                    case 18: break;
                    case 19: break;
                    case 20: break;
                    case 21: break;
                    case 22: break;
                    case 23: break;
                    case 24: break;
                    case 25: break;
                    case 26: break;
                    case 27: break;
                    case 28: break;
                    case 29: break;
                    case 30: break;
                    case 31: break;
                    default: printf("default");
                }
            }
                updatePlayerPlaying(board, j);
            }
        // printf("--- Voulez vous continuer les test ? y/n ---\n");

        // char r[2];
        // scanf("%s", r);
        // testing = r[0];
        endRound(board);
        printBoard(board);
        board->idPlayerPlaying=1;
        

    }
    printf("---Fin du test---\n");
    printf("Success : %d ; Error : %d\n",success,error);
    
    freeBoard(board);
}

int main(){
    printf("testeeeee\n");
    return 0;
}