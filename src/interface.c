#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../headers/interface.h"

void printNewRound(Board board)
{
	printf("###################################");
	printf("\nTour %d \n\n", board->round);
	printf("-----------------------------------------------\n");
	char *displayNbCard;

	if (board->round < 6)
	{
		displayNbCard = "Vous pouvez jouer uniquement 1 carte Personnel sur le plateau\n";
	}
	else if (board->round < 11)
	{
		displayNbCard = "Vous pouvez à présent jouer 2 cartes Personnel sur le plateau\n";
	}
	else
	{
		displayNbCard = "Vous pouvez à présent jouer 3 cartes Personnel sur le plateau\n";
	}
	printf("%s", displayNbCard);
}

void printNewPhase(int player)
{
	printf("-----------------------------------------------\n");

	printf("\nJoueur %d, c'est à votre tour de jouer !\n\n", player);
}

void flushStdin(){
    int c = 0;
    while (c != '\n' && c != EOF){
        c = getchar();
    }
}

int readUserType(char* str, int size){
    char* position = NULL;

    if (fgets(str, size, stdin) != NULL){
        position = strchr(str, '\n');
        if (position != NULL){
            *position = '\0';
        }else{
            flushStdin();
        }
        return 1;
    }else{
        flushStdin();
        return 0;
    }
}

int askTypeCard()
{
	char str[3];
	char *erreur;
	int chiffre;
	printf("Quel type de carte élève souhaitez-vous? \n -Tapez 0 pour FISE \n -Tappez 1 pour FISA\n");
	readUserType(str, 2);
	chiffre = strtol(str, &erreur, 10);

	while( (chiffre != 0 && chiffre != 1) || str == erreur){
		clear();
		printf("J'ai reçu %s, le chiffre doit être 0 ou 1\n", str);
		printf("Quel type de carte élève souhaitez-vous? \n -Tapez 0 pour FISE \n -Tappez 1 pour FISA\n");
		readUserType(str, 2);
		chiffre = strtol(str, &erreur, 10);
	}
		return chiffre;
}

void printWinner(int player)
{
	if (player == -1)
	{
		printf("Match nul!");
	}
	else
	{

		printf("Nous avons un gagnant! Félicitation au joueur %d\n", player);
	}
}

Card *askAction(Player player, int nbPE)
{
	Fifo head;
	Stack canPlayCards;
	head = player->hand;
	canPlayCards = createStack();
	int numberCard;
	char str[2];
	char *erreur;

	printf("Vous avez : %d PE\n", nbPE);
	while (head != NULL)
	{
		if (head->val.cost <= nbPE)
		{
			push(canPlayCards, head->val);
		}
		head = head->next;
	}
	if (empty(canPlayCards) == 1)
	{
		printf("Aucune carte ne peut être jouée\n");
		return NULL;
	}

	printf("Vous pouvez jouer les cartes suivantes ou passer le tour en entrant -1\n");
	print_stack(canPlayCards);
	printf("id:");
	readUserType(str, 3);
	numberCard = strtol(str, &erreur, 10);

	while(str == erreur ||  ((numberCard < 1 || numberCard > 31) && numberCard != -1) ){
		clear();
		printf("J'ai reçu %s, veuillez entrer l'id d'une carte de votre main ou -1 pour passer votre tour\n", str);
		printf("Vous avez : %d PE\n", nbPE);
		printf("Vous pouvez jouer les cartes suivantes ou passer le tour en entrant -1\n");
		print_stack(canPlayCards);
		printf("id ou -1 pour passer votre tour:");
		readUserType(str, 3);
		numberCard = strtol(str, &erreur, 10);
	}
	if (numberCard == -1)
	{
		return NULL;
	}
	else
	{
		//Ici tester si numberCard est bien dans la main ou sinon taper -1 pour ne pas choisir de carte
		while (canPlayCards->top != -1)
		{
			Card res = pop(canPlayCards);
			if (numberCard == res.id)
			{
				Card *c;
				c = (Card *)malloc(sizeof(Card));
				c->id = res.id;
				c->cost = res.cost;
				c->effect = res.effect;
				return c;
			}
		}
		clear();
		printf("L'id sélectionné n'est pas dans la main, recommencez.\n");
		return askAction(player, nbPE);
	}
}

//TODO
void printBoard(Board board)
{

	//printf("%d\n", board->idWinner);

	printf("\n");

	printf("Information sur les cartes du joueur 1 \n");
	printf("-Nombre de PE: %i\n", nbOfPE(board->p1, isOdd(board->round)));
	printf("-Nombre de DD: %i\n", nbOfDD(board->p1, isOdd(board->round)));
	printf("-Nombre de Durabilité: %i\n", nbOfDurability(board->p1, isOdd(board->round)));
	printf("-Nombre de cartes FISE: %i\n", board->p1->nbFISE);
	printf("-Nombre de cartes FISA: %i\n", board->p1->nbFISA);
	printf("-Nombre de carte restante dans la pioche: %d\n", board->p1->deck->size);
	printf("-Nombre de carte dans la main: %d\n", sizeFifo(board->p1->hand));
	printf("-Cartes en jeu:\n");
	printFifo(board->p1->inGameCards);

	printf("\n\nInformation sur les cartes du joueur 2 \n");
	printf("-Nombre de PE: %i\n", nbOfPE(board->p2, isOdd(board->round)));
	printf("-Nombre de DD: %i\n", nbOfDD(board->p2, isOdd(board->round)));
	printf("-Nombre de Durabilité: %i\n", nbOfDurability(board->p2, isOdd(board->round)));
	printf("-Nombre de cartes FISE: %i\n", board->p2->nbFISE);
	printf("-Nombre de cartes FISA: %i\n", board->p2->nbFISA);
	printf("-Nombre de carte restante dans la pioche: %d\n", board->p2->deck->size);
	printf("-Nombre de carte dans la main: %d\n", sizeFifo(board->p2->hand));
	printf("-Cartes en jeu:\n");
	printFifo(board->p2->inGameCards);
	printf("\n\n");
}

void printPoints(Board board)
{
	printf("\n\nFin du round! Calcul de DD pour chaque joueur:\n\n");
	printf("Nombre de DD du Joueur 1: %i\n", nbOfDD(board->p1, isOdd(board->round)));

	printf("Nombre de DD du Joueur 2: %i\n\n", nbOfDD(board->p2, isOdd(board->round)));
}

void printHand(Player p)
{
	printf("\n\nJoueur %d\n", p->id);
	printf("Voici votre main: \n");
	printFifo(p->hand);

	printf("\n");
}

void clear(void){
	system("clear");
}
