// #include "../headers/board.h"
// #include "../headers/interface.h"
// #include <stdio.h>

// int main(void)
// {
//     Board board = initNewBoard();
//     Player player;
//     while (!endGame(board))
//     {
//         newRound(board);
//         printNewRound(board);
//         for (int j = 0; j < 2; j++)
//         {
//             player = board->idPlayerPlaying == 1 ? board->p1 : board->p2;
//             printNewPhase(board->idPlayerPlaying);
//             printBoard(board);

//             int nbDrawCard = countDrawCard(player, board->round);
//             printf("Vous allez piocher %d carte(s) personnelle(s) / action(s) \n", nbDrawCard);

//             for (int i = 0; i < nbDrawCard; i++)
//             {
//                 drawCard(player);
//             }

//             printHand(player);

//             int nbStudentCard = countStudentCard(player);
//             printf("\nVous pouvez piocher %d carte(s) étudiante(s)\n", nbStudentCard);
//             int typeCard;
//             for (int i = 0; i < nbStudentCard; i++)
//             {
//                 typeCard = askTypeCard(); // 0 : FISE, 1: FISA
//                 addCardStudent(player, typeCard);
//             }
//             int nbPE = nbOfPE(player, isOdd(board->round));
//             Card *cardChoosed;

//             while ((cardChoosed = askAction(player, nbPE)) != NULL)
//             {
//                 nbPE = nbPE - playCard(board, *cardChoosed);
//             }

//             updatePlayerPlaying(board, j);
//         }
//         printPoints(board);
//         endRound(board);
//     }
//     printWinner(board->idWinner);
//     freeBoard(board);
// }

#include "../headers/board.h"
#include "../headers/interface.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


Card ChooseCardDeck(int id,Stack s){
    while(s->top != -1){
        Card c = pop(s);
        if (c.id == id){
            return c;
        }
    }
    return errorCard();
}

void print_success(int *i,int numTest,int clear){
    (*i)++;
    printf("Carte n %d : SUCCESS\n",numTest);
    sleep(1);
    if(clear){
        system("clear");
    }
}

void print_success_NC(int *i,int clear){
    (*i)++;
    printf("SUCCESS\n");
    sleep(1);
    if(clear){
        system("clear");
    }
}

void print_error(int *i,int numTest,int clear){
    (*i)++;
    printf("Carte n %d : ERROR\n",numTest);
    sleep(1);
    if(clear){
        system("clear");
    }
}

void print_error_NC(int *i,int clear){
    (*i)++;
    printf("ERROR\n");
    sleep(1);
    if(clear){
        system("clear");
    }
}


int main(){

    int isEndedRound;
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
            board->maxCardInGame=3;
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


        
        printf("--- Test numéro %d ---\n",nbTest);
        newRound(board);
        isEndedRound = 0;
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

                int beginningDD;

                int beginningValueDDFisa;
                int beginningValueDuraFisa;
                int beginningValueDuraFisep2;
                int beginningValueDuraFisap2;

                int beginningValueDDFise;
                int beginningValueDuraFise;

                int nbPickCard;

                int beginningStudentCard;
                int beginningDDBonus;
                int beginningDDBonusp2;

                int beginningFise;
                int beginningFisa;

                int beginningPE;

                switch(nbTest){
                    case 1: //On ne voudra pas que p2 joue 
                        beginningValueDDFise = player->bonus->valueDDFISE;
                        p2Play = 0;
                        break;
                    case 2: //On ne voudra pas que p2 joue 
                        beginningValueDuraFise = player->bonus->valueDurabilityFISE;
                        p2Play = 0;
                        break;
                    case 3: //On ne voudra pas que p2 joue 
                        beginningValueDDFisa = player->bonus->valueDDFISA;
                        p2Play = 0;
                        break;

                    case 4: //On ne voudra pas que p2 joue 
                        beginningValueDuraFisa = player->bonus->valueDurabilityFISA;
                        p2Play = 0;
                        break;

                    case 5:
                        beginningValueDDFise = board->p2->bonus->valueDDFISE;
                        p2Play = 0;
                        break;

                    case 6:
                        beginningValueDuraFise = board->p2->bonus->valueDurabilityFISE;
                        p2Play = 0;
                        break;

                    case 7:
                        beginningValueDDFisa = board->p2->bonus->valueDDFISA;
                        p2Play = 0;
                        break;
                    case 8:
                        beginningValueDuraFisa = board->p2->bonus->valueDurabilityFISA;
                        p2Play = 0;
                        break;

                    case 9:
                        beginningValueDDFise = player->bonus->valueDDFISE;
                        beginningValueDDFisa = player->bonus->valueDDFISA;
                        p2Play = 0;
                        break;
                    case 10:
                        beginningValueDuraFise = player->bonus->valueDurabilityFISE;
                        beginningValueDuraFisa = player->bonus->valueDurabilityFISA;
                        p2Play = 0;
                        break;

                    case 11:
                        beginningValueDDFise = board->p2->bonus->valueDDFISE;
                        beginningValueDDFisa = board->p2->bonus->valueDDFISA;
                        p2Play = 0;
                        break;

                    case 12:
                        beginningValueDuraFise = board->p2->bonus->valueDurabilityFISE;
                        beginningValueDuraFisa = board->p2->bonus->valueDurabilityFISA;
                        p2Play = 0;
                        break;

                    case 13:
                        p2Play = 0;
                        nbPickCard = countDrawCard(player, board->round);
                        break;
                    case 14:
                        p2Play=0;
                        beginningStudentCard = countStudentCard(player);
                        nbPickCard = countDrawCard(player, board->round);
                        beginningDDBonus = player->bonus->DDBonus;
                        break;

                    case 15:
                        p2Play=0;
                        beginningStudentCard = countStudentCard(player);
                        nbPickCard = countDrawCard(player, board->round);
                        beginningDDBonus = board->p2->bonus->DDBonus;
                        break;

                    case 16:
                        beginningValueDuraFisep2 = board->p2->bonus->valueDurabilityFISE;
                        beginningValueDuraFise = player->bonus->valueDurabilityFISE;
                        beginningValueDDFise = player->bonus->valueDDFISE;
                        beginningDDBonus = board->p2->bonus->DDBonus;
                        p2Play = 0;
                        break;

                    case 17: 
                        beginningValueDDFisa = player->bonus->valueDDFISA;
                        beginningValueDuraFisa = player->bonus->valueDurabilityFISA;
                        beginningValueDuraFisap2 = board->p2->bonus->valueDurabilityFISA;
                        beginningDDBonus = board->p2->bonus->DDBonus;
                        p2Play = 0;
                        break;

                    case 18:
                        beginningValueDDFise = player->bonus->valueDDFISE;
                        p2Play = 0;
                        beginningValueDuraFise = player->bonus->valueDurabilityFISE;
                        beginningStudentCard = countStudentCard(player);
                        break;
                    case 19:
                        p2Play = 0;
                        beginningValueDDFisa = player->bonus->valueDDFISA;
                        beginningValueDuraFisa = player->bonus->valueDurabilityFISA;
                        beginningStudentCard = countStudentCard(player);
                        break;
                    case 20:
                        beginningValueDDFise = player->bonus->valueDDFISE;
                        p2Play = 0;
                        beginningValueDuraFise = player->bonus->valueDurabilityFISE;
                        beginningValueDDFisa = player->bonus->valueDDFISA;
                        beginningValueDuraFisa = player->bonus->valueDurabilityFISA;
                        beginningStudentCard = countStudentCard(player);
                        beginningDDBonus = player->bonus->DDBonus;
                        beginningDDBonusp2 = board->p2->bonus->DDBonus;
                        nbPickCard = countDrawCard(player, board->round);
                        break;

                    case 21:
                        beginningDD = nbOfDD(player,isOdd(board->round));
                        p2Play = 0;
                        break;

                    case 22: 
                        p2Play = 0;
                        break;

                    case 23:
                        beginningFise = player->nbFISE;
                        p2Play = 0;
                        break;

                    case 24:
                        beginningFisa = player->nbFISA;
                        p2Play = 0;
                        break;

                    case 25:
                        beginningPE=nbOfPE(player, isOdd(board->round));
                        p2Play = 0;
                        break;

                    case 26:    
                        p2Play = 0;
                        beginningFise = board->p2->nbFISE;
                        beginningFisa = board->p2->nbFISA;
                        break;
                    case 27: break;
                    case 28: break;
                    case 29: break;
                    case 30: break;
                    case 31: 
                        p2Play = 0;
                        break;
                    default: printf("default");
                }
                

                enqueue(draw, &(player->hand));


                printHand(player);

                //int nbStudentCard = countStudentCard(player);
                // printf("\nVous pouvez piocher %d carte(s) étudiante(s)\n", nbStudentCard);
                //int typeCard;

                // for (int i = 0; i < nbStudentCard; i++)
                // {
                //     typeCard = askTypeCard(); // 0 : FISE, 1: FISA
                //     addCardStudent(player, typeCard);
                // }

                int nbPE = nbOfPE(player, isOdd(board->round));
                Card *cardChoosed = &draw;

                nbPE = nbPE - playCard(board, *cardChoosed);
                

                int endValueDuraFisep2;
                int endValueDuraFisap2;
                int endValueDDFisa;
                int endValueDuraFisa;
                int endValueDDFise;
                int endValueDuraFise;

                switch(nbTest){
                    case 1:
                        endValueDDFise = player->bonus->valueDDFISE;
                        if (endValueDDFise == beginningValueDDFise+1){
                            print_success(&success,nbTest,1);
                        }else{
                            print_error(&error,nbTest,1);
                        }
                        break;

                    case 2:
                        endValueDuraFise = player->bonus->valueDurabilityFISE;
                        if (endValueDuraFise == beginningValueDuraFise+1){
                            print_success(&success,nbTest,1);
                        }else{
                            print_error(&error,nbTest,1);
                        }break;

                    case 3:
                        endValueDDFisa = player->bonus->valueDDFISA;
                        if (endValueDDFisa == beginningValueDDFisa+1){
                            print_success(&success,nbTest,1);
                        }else{
                            print_error(&error,nbTest,1);
                        }
                        break;

                    case 4:
                        endValueDuraFisa = player->bonus->valueDurabilityFISA;
                        if (endValueDuraFisa == beginningValueDuraFisa+1){
                            print_success(&success,nbTest,1);
                        }else{
                            print_error(&error,nbTest,1);
                        }break;

                    case 5:
                        endValueDDFise = board->p2->bonus->valueDDFISE;
                        if (endValueDDFise == beginningValueDDFise-1){
                            print_success(&success,nbTest,1);
                        }else{
                            print_error(&error,nbTest,1);
                        }
                        break;
                        
                    case 6:
                        endValueDuraFise = board->p2->bonus->valueDurabilityFISE;
                        if (endValueDuraFise == beginningValueDuraFise-1){
                            print_success(&success,nbTest,1);
                        }else{
                            print_error(&error,nbTest,1);
                        }break;
                        
                    case 7:
                        endValueDDFisa = board->p2->bonus->valueDDFISA;
                        if (endValueDDFisa == beginningValueDDFisa-1){
                            print_success(&success,nbTest,1);
                        }else{
                            print_error(&error,nbTest,1);
                        }
                        break;
                        
                    case 8:
                        endValueDuraFisa = board->p2->bonus->valueDurabilityFISA;
                        if (endValueDuraFisa == beginningValueDuraFisa-1){
                            print_success(&success,nbTest,1);
                        }else{
                            print_error(&error,nbTest,1);
                        }
                        break;
                        
                    case 9:
                        endValueDDFise = player->bonus->valueDDFISE;
                        endValueDDFisa = player->bonus->valueDDFISA;
                        if(endValueDDFisa == beginningValueDDFisa+1 && endValueDDFise == beginningValueDDFise+1){
                            print_success(&success,nbTest,1);
                        }
                        else{
                            print_error(&error,nbTest,1);
                        }break;

                    case 10:
                        endValueDuraFise = player->bonus->valueDurabilityFISE;
                        endValueDuraFisa = player->bonus->valueDurabilityFISA;
                        if(endValueDuraFisa == beginningValueDuraFisa+1 && endValueDuraFise == beginningValueDuraFise+1){
                            print_success(&success,nbTest,1);
                        }
                        else{
                            print_error(&error,nbTest,1);
                        }break;

                    case 11://Error.
                        endValueDDFise = board->p2->bonus->valueDDFISE;
                        endValueDDFisa = board->p2->bonus->valueDDFISA;
                        if(endValueDDFisa == beginningValueDDFisa-1 && endValueDDFise == beginningValueDDFise-1){
                            print_success(&success,nbTest,1);
                        }
                        else{
                            print_error(&error,nbTest,1);
                        }break;

                    case 12:
                        endValueDuraFise = board->p2->bonus->valueDurabilityFISE;
                        endValueDuraFisa = board->p2->bonus->valueDurabilityFISA;
                        if(endValueDuraFisa == beginningValueDuraFisa-1 && endValueDuraFise == beginningValueDuraFise-1){
                            print_success(&success,nbTest,1);
                        }
                        else{
                            print_error(&error,nbTest,1);
                        }break;

                    case 13:
                        if(board->round == 1){
                            printf("---on attend le tour 2 pour tester l'effet DR de la carte---\n");
                            sleep(1);
                        }else{
                            if(nbPickCard + 2 == countDrawCard(player, board->round) ){
                                print_success(&success,nbTest,1);
                            }else{
                                print_error(&error,nbTest,1);
                            }
                        }
                        break;

                    case 14:

                        beginningDD = nbOfDD(player,isOdd(board->round)); // LES DD AVANT LA FIN DU ROUND POUR TESTER ADD

                        if(player->bonus->DDBonus != beginningDDBonus + 2){
                            printf("EFFET ADD : \n");
                            print_error(&error,nbTest,0);
                        }else{
                            printf("EFFET ADD : \n");
                            print_success(&success,nbTest,0);
                        }

                        if(board->round == 1){
                            printf("---on attend le tour 2 pour tester l'effet DR et E de la carte---\n");
                            sleep(1);
                        }else{
                            if(nbPickCard + 1 == countDrawCard(player, board->round) ){
                                printf("EFFET DR : \n");
                                print_success(&success,nbTest,0);
                            }else{
                                printf("EFFET DR : \n");
                                print_error(&error,nbTest,0);
                            }
                            if(countStudentCard(player) == beginningStudentCard + 1){//Il faut les deux cartes ajouté par l'effet de la carte 14 + la carte 14 qui est repioché automatiquement
                                printf("EFFET E : \n");
                                print_success(&success,nbTest,1);
                            }else{
                                printf("EFFET E : \n");
                                print_error(&error,nbTest,1);
                            }
                        }
        

                    break;

                    case 15:

                        beginningDD = nbOfDD(player,isOdd(board->round)); // LES DD AVANT LA FIN DU ROUND POUR TESTER ADD

                        if(board->p2->bonus->DDBonus != beginningDDBonus - 2){
                            printf("EFFET RDD : \n");
                            print_error(&error,nbTest,0);
                        }else{
                            printf("EFFET RDD : \n");
                            print_success(&success,nbTest,0);
                        }

                        if(board->round == 1){
                            printf("---on attend le tour 2 pour tester l'effet DR et E de la carte---\n");
                            sleep(1);
                        }else{
                            if(nbPickCard + 1 == countDrawCard(player, board->round) ){
                                printf("EFFET DR : \n");
                                print_success(&success,nbTest,0);
                            }else{
                                printf("EFFET DR : \n");
                                print_error(&error,nbTest,0);
                            }
                            if(countStudentCard(player) == beginningStudentCard + 1){//Il faut les deux cartes ajouté par l'effet de la carte 14 + la carte 14 qui est repioché automatiquement
                                printf("EFFET E : \n");
                                print_success(&success,nbTest,1);
                            }else{
                                printf("EFFET E : \n");
                                print_error(&error,nbTest,1);
                            }
                        }
                        break;

                    case 16:
                        endValueDDFise = player->bonus->valueDDFISE;
                        if (endValueDDFise == beginningValueDDFise+1){
                            printf("EFFET AE1 : \n");
                            print_success(&success,nbTest,0);
                        }else{
                            printf("EFFET AE1 : \n");
                            print_error(&error,nbTest,0);
                        }

                        endValueDuraFise = player->bonus->valueDurabilityFISE;
                        if (endValueDuraFise == beginningValueDuraFise+1){
                            printf("EFFET AE2 : \n");
                            print_success(&success,nbTest,0);
                        }else{
                            printf("EFFET AE2 : \n");
                            print_error(&error,nbTest,0);
                        }
                        endValueDuraFisep2 = board->p2->bonus->valueDurabilityFISE;
                        if (endValueDuraFisep2 == beginningValueDuraFisep2-1){
                            printf("EFFET RE2 : \n");
                            print_success(&success,nbTest,0);
                        }else{
                            printf("EFFET RE2 : \n");
                            print_error(&error,nbTest,0);
                        }

                        if(board->p2->bonus->DDBonus != beginningDDBonus - 1){
                            printf("EFFET RDD : \n");
                            print_error(&error,nbTest,1);
                        }else{
                            printf("EFFET RDD : \n");
                            print_success(&success,nbTest,1);
                        }
                        break;

                    case 17: 
                        endValueDDFisa = player->bonus->valueDDFISA;
                        if (endValueDDFisa == beginningValueDDFisa+1){
                            printf("EFFET AA1 : \n");
                            print_success(&success,nbTest,0);
                        }else{
                            printf("EFFET AA1 : \n");
                            print_error(&error,nbTest,0);
                        }

                        endValueDuraFisa = player->bonus->valueDurabilityFISA;
                        if (endValueDuraFisa == beginningValueDuraFisa+1){
                            printf("EFFET AA2 : \n");
                            print_success(&success,nbTest,0);
                        }else{
                            printf("EFFET AA2 : \n");
                            print_error(&error,nbTest,0);
                        }

                        endValueDuraFisap2 = board->p2->bonus->valueDurabilityFISA;
                        if (endValueDuraFisap2 == beginningValueDuraFisap2-1){
                            printf("EFFET RA2 : \n");
                            print_success(&success,nbTest,0);
                        }else{
                            printf("EFFET RA2 : \n");
                            print_error(&error,nbTest,0);
                        }

                        if(board->p2->bonus->DDBonus != beginningDDBonus - 1){
                            printf("EFFET RDD : \n");
                            print_error(&error,nbTest,1);
                        }else{
                            printf("EFFET RDD : \n");
                            print_success(&success,nbTest,1);
                        }
                        break;

                    case 18:
                        endValueDDFise = player->bonus->valueDDFISE;
                        if (endValueDDFise == beginningValueDDFise+2){
                            printf("EFFET AE1: \n");
                            print_success(&success,nbTest,0);
                        }else{
                            printf("EFFET AE1 : \n");
                            print_error(&error,nbTest,0);
                        }
                        endValueDuraFise = player->bonus->valueDurabilityFISE;
                        if (endValueDuraFise == beginningValueDuraFise+2){
                            printf("EFFET AE2 : \n");
                            print_success(&success,nbTest,0);
                        }else{
                            printf("EFFET AE2 : \n");
                            print_error(&error,nbTest,0);
                        }
                        if(countStudentCard(player) == beginningStudentCard + 1){//Il faut les deux cartes ajouté par l'effet de la carte 14 + la carte 14 qui est repioché automatiquement
                            printf("EFFET E : \n");
                            print_success(&success,nbTest,1);
                        }else{
                            printf("EFFET E : \n");
                            print_error(&error,nbTest,1);
                            }
                        break;

                    case 19:
                        endValueDDFisa = player->bonus->valueDDFISA;
                        if (endValueDDFisa == beginningValueDDFisa+2){
                            printf("EFFET AA1 : \n");
                            print_success(&success,nbTest,0);
                        }else{
                            printf("EFFET AA1 : \n");
                            print_error(&error,nbTest,0);
                        }
                        endValueDuraFisa = player->bonus->valueDurabilityFISA;
                        if (endValueDuraFisa == beginningValueDuraFisa+2){
                            printf("EFFET AA2 : \n");
                            print_success(&success,nbTest,0);
                        }else{
                            printf("EFFET AA2 : \n");
                            print_error(&error,nbTest,0);
                        }
                        if(countStudentCard(player) == beginningStudentCard + 1){//Il faut les deux cartes ajouté par l'effet de la carte 14 + la carte 14 qui est repioché automatiquement
                            printf("EFFET E : \n");
                            print_success(&success,nbTest,1);
                        }else{
                            printf("EFFET E : \n");
                            print_error(&error,nbTest,1);
                            }


                        break;
                    case 20:
                        endValueDDFise = player->bonus->valueDDFISE;
                        if (endValueDDFise == beginningValueDDFise+2){
                            printf("EFFET AE1: \n");
                            print_success(&success,nbTest,0);
                        }else{
                            printf("EFFET AE1 : \n");
                            print_error(&error,nbTest,0);
                        }
                        endValueDuraFise = player->bonus->valueDurabilityFISE;
                        if (endValueDuraFise == beginningValueDuraFise+2){
                            printf("EFFET AE2 : \n");
                            print_success(&success,nbTest,0);
                        }else{
                            printf("EFFET AE2 : \n");
                            print_error(&error,nbTest,0);
                        }
                        if(countStudentCard(player) == beginningStudentCard + 2){//Il faut les deux cartes ajouté par l'effet de la carte 14 + la carte 14 qui est repioché automatiquement
                            printf("EFFET E : \n");
                            print_success(&success,nbTest,0);
                        }else{
                            printf("EFFET E : \n");
                            print_error(&error,nbTest,0);
                        }
                        endValueDDFisa = player->bonus->valueDDFISA;
                        if (endValueDDFisa == beginningValueDDFisa+2){
                            printf("EFFET AA1 : \n");
                            print_success(&success,nbTest,0);
                        }else{
                            printf("EFFET AA1 : \n");
                            print_error(&error,nbTest,0);
                        }
                        endValueDuraFisa = player->bonus->valueDurabilityFISA;
                        if (endValueDuraFisa == beginningValueDuraFisa+2){
                            printf("EFFET AA2 : \n");
                            print_success(&success,nbTest,0);
                        }else{
                            printf("EFFET AA2 : \n");
                            print_error(&error,nbTest,0);
                        }

                        if(player->bonus->DDBonus != beginningDDBonus + 1){
                            printf("EFFET ADD : \n");
                            print_error(&error,nbTest,0);
                        }else{
                            printf("EFFET ADD : \n");
                            print_success(&success,nbTest,0);
                        }

                        if(board->round != 2){
                            printf("---on attend le tour 2 pour tester l'effet DR de la carte---\n");
                            sleep(1);
                        }else{
                        if(nbPickCard + 1 == countDrawCard(player, board->round) ){
                            printf("EFFET DR : \n");
                            print_success(&success,nbTest,0);
                        }else{
                            printf("EFFET DR : \n");
                            print_error(&error,nbTest,0);
                        }
                    }

                        if(board->p2->bonus->DDBonus != beginningDDBonusp2 - 1){
                            printf("EFFET RDD : \n");
                            print_error(&error,nbTest,1);
                        }else{
                            printf("EFFET RDD : \n");
                            print_success(&success,nbTest,1);
                        }
                        break;

                    case 21:
                        if(beginningDD+1 == nbOfDD(player,isOdd(board->round))){
                            print_success(&success,nbTest,1);
                        }else{
                            print_error(&error,nbTest,1);
                        }
                        break;

                    case 22:
                        if(sizeFifo(player->hand)==1){//On avait une carte de base, on la joue et on doit obtenir une carte -> il faut une carte donc
                            print_success(&success,nbTest,1);
                        }else{
                            print_error(&error,nbTest,1);
                        }
                        break;

                    case 23: 
                        if(beginningFise+1 == player->nbFISE){
                            print_success(&success,nbTest,1);
                        }else{
                            print_error(&error,nbTest,1);
                        }
                        break;

                    case 24:
                        if(beginningFisa+1 == player->nbFISA){
                            print_success(&success,nbTest,1);
                        }else{
                            print_error(&error,nbTest,1);
                        }
                        break;

                    case 25:
                        if(beginningPE + 2 == nbPE){// on doit avoir gagné 6-4 = 2 PE
                            print_success(&success,nbTest,1);
                        }else{
                            print_error(&error,nbTest,1);
                        }
                        break;

                    case 26:
                    if(beginningFise-1 == board->p2->nbFISE && beginningFisa-1 == board->p2->nbFISA){
                        print_success(&success,nbTest,1);
                    }else{
                        print_error(&error,nbTest,1);
                    }
                    break;

                    case 27: break;
                    case 28: break;
                    case 29: break;
                    case 30: break;
                    case 31:
                        if(board->p1->nbFISE == 0 && board->p2->nbFISE == 0 && board->p1->nbFISA == 0 && board->p2->nbFISA == 0){
                        print_success(&success,nbTest,1);
                        }else{
                            print_error(&error,nbTest,1);
                        }                          
                        break;

                    default: printf("default");
                }
            }
                updatePlayerPlaying(board, j);
            }
        // printf("--- Voulez vous continuer les test ? y/n ---\n");

        // char r[2];
        // scanf("%s", r);
        // testing = r[0];
            
        if(!isEndedRound){
            endRound(board);
        }

        printBoard(board);
        board->idPlayerPlaying=1;
        

    }

    printf("---Fin du test des cartes---\n");
    sleep(2);
    system("clear");
    printf("Test des structures : \n");

    Fifo testFifo = NULL;

    Card A;
    A.id = 1;
    A.cost = 999;
    A.effect = "shoot";

    Card B;
    B.id = 2;
    B.cost = 111;
    B.effect = "tir";

    Card C;
    C.id = 3;
    C.cost = 101;
    C.effect = "test";

    printf("Test de enqueue\n");
    sleep(2);
    enqueue(A,&testFifo);
    if(testFifo->val.id == 1 &&  testFifo->next == NULL){
        print_success_NC(&success,0);
    }else{
        print_error_NC(&error,0);
    }

    printf("Test de dequeue\n");
    sleep(2);
    Card D  = dequeue(&testFifo);
    if(D.id == A.id && D.cost == A.cost && D.effect == A.effect && testFifo == NULL){
        print_success_NC(&success,0);
    }else{
        print_error_NC(&error,0);
    }

    printf("Test de sizeFifo\n");
    enqueue(A,&testFifo);
    enqueue(B,&testFifo);
    enqueue(C,&testFifo);
    if(sizeFifo(testFifo) == 3){
        print_success_NC(&success,0);
    }else{
        print_error_NC(&error,0);
    }

    printf("Test de deleteID\n");
    sleep(2);

    printFifo(testFifo);
    printf("Deleting ID 2...\n");
    sleep(2);
    Card E = deleteID(&testFifo,2);
    printFifo(testFifo);
    if(sizeFifo(testFifo) == 2 && E.id == 2){
        print_success_NC(&success,0);
    }else{
        print_error_NC(&error,0);
    }

    printf("Test des Stacks\n");
    Stack testStack = createStack();

    printf("Test de push\n");
    sleep(2);
    push(testStack,A);
    if(testStack->top == 0 && testStack->c[testStack->top].id == A.id){
        print_success_NC(&success,0);
    }else{
        print_error_NC(&error,0);
    }

    printf("Test de pop\n");
    sleep(2);
    Card R = pop(testStack);
    if (R.id == A.id && testStack->top == -1){
        print_success_NC(&success,0);
    }else{
        print_error_NC(&error,0);
    }

    printf("Success : %d ; Error : %d\n",success,error);
    
    freeBoard(board);
}
