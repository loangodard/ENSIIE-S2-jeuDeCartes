#ifndef _STRUCTURES_H
#define _STRUCTURES_H

#include "card.h"

/*return an error card*/
Card errorCard();

/*-----------------Stack-----------------*/

struct stack
{
   Card *c;
   int top;
   int size;
};

/*Deck,hand,discard*/
typedef struct stack *Stack;

Stack createStack();

Stack initializeDeck();

/*@ requires p a valid adress
    assigns p
    ensures resize stack p */
void resizeStack(Stack p, int new_size);

/*@ requires p valid adress
    assigns p
    ensures add c in the top of p*/
void push(Stack p, Card c);

/*@ requires p valid adress
    assigns p
    ensures delete the element in the top of p and return it*/
Card pop(Stack p);

/*@ requires nothing
    assigns nothing
    ensures print p */
void print_stack(Stack p);

/*@ requires nothing
    assigns nothing
    ensures return 1 if the stack is empty, else return 0 */
int empty(Stack p);

/*@requires nothing
   assigns nothing
   ensures return a copy of p */
Stack copy_stack(Stack p);

/*@requires nothing
   assigns p
   ensures make p empty */
void empty_stack(Stack p);

/*@requires p valid adress
   assigns p
   ensures free p*/
void freeStack(Stack p);

/*@requires p valid adress
   assigns p1, p2
   ensures return the of merge p1 & p2 and make p1 and p2 empty*/
Stack fusion(Stack p1, Stack p2);

Stack initializeDeck();

/*-----------------Fifo-----------------*/

struct fifoCell
{
   Card val;
   struct fifoCell *next;
};

/*Employees cards on the board*/
typedef struct fifoCell *Fifo;

/*@requires nothing
   assigns noting
   ensures construct a new FIFO*/
Fifo consFifo(Card v, Fifo f);

/*@requires f valid adress
   assigns f
   ensures add v in the beginning of f */
void enqueue(Card v, Fifo *f);

/*@requires f valid adress
   assigns f
   ensures return the element which has been add in first and delete it*/
Card dequeue(Fifo *f);

/*@requires nothing
   assigns nothing
   ensures print f*/
void printFifo(Fifo f);

/*@requires nothing
   assigns f
   ensures free f */
void freeFifo(Fifo f);

/*@requires nothing
   assigns nothing
   ensures return size of f*/
int sizeFifo(Fifo f);

/*@requires f valid adress
   assigns f
   ensures return and delete the card which ID == id in f*/
Card deleteID(Fifo *f, int id);

#endif