#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../headers/structures.h"

Card errorCard()
{
    Card r;
    r.id = 0;
    r.cost = 0;
    r.effect = "ERROR";
    fflush(stdout);
    return r;
}

/*-----------------Stack-----------------*/

Stack createStack()
{
    Stack r = (struct stack *)malloc(sizeof(struct stack));
    r->c = (Card *)malloc(sizeof(Card));
    r->top = -1;
    r->size = 1;
    return r;
}

Stack initializeDeck()
{
    Stack s = createStack();
    Card *allCards;

    int length = getSizeCardsTotal();

    allCards = getCards();

    Card *tmp = shuffleCards(allCards, length);
    resizeStack(s, length);
    for (int i = 0; i < length; i++)
    {
        push(s, tmp[i]);
    }
    s->top = length - 1;
    return s;
}

/*@ requires p a valid adress
    assigns p
    ensures resize stack p */
void resizeStack(Stack p, int new_size)
{
    Card *tmp;
    int i;
    tmp = (Card *)malloc(new_size * sizeof(Card));
    for (i = 0; i <= p->top; i++)
    {
        tmp[i] = p->c[i];
    }
    free(p->c);
    p->c = tmp;
    p->size = new_size;
}

/*@ requires p valid adress
    assigns p
    ensures add c in the top of p*/
void push(Stack p, Card c)
{
    if (p->top >= p->size - 1)
    {
        resizeStack(p, 2 * (p->size));
    }
    p->top += 1;
    p->c[p->top] = c;
}

/*@ requires p valid adress
    assigns p
    ensures delete the element in the top of p and return it*/
Card pop(Stack p)
{
    if (p->top < 0)
    {
        return errorCard();
    }
    Card r;
    r = p->c[p->top];
    p->top -= 1;
    p->size--;
    return r;
}

/*@ requires nothing
    assigns nothing
    ensures print p */
void print_stack(Stack p)
{
    int i;
    if (p->top < 0)
    {
        printf("Stack vide\n");
        return;
    }
    for (i = 0; i <= p->top; i++)
    {
        printCard(p->c[i]);
    }
}

/*@ requires nothing
    assigns nothing
    ensures return 1 if the stack is empty, else return 0 */
int empty(Stack p)
{
    if (p->top == -1)
        return 1;
    return 0;
}

/*@requires nothing
   assigns nothing
   ensures return a copy of p */
Stack copy_stack(Stack p)
{
    Stack r = createStack();
    while (empty(p) != 1)
    {
        Card a = pop(p);
        push(r, a);
    }
    r->top = p->top;
    r->size = p->size;
    return r;
}

/*@requires nothing
   assigns p
   ensures make p empty */
void empty_stack(Stack p)
{
    while (!empty(p))
    {
        pop(p);
    }
}

/*@requires p valid adress
   assigns p
   ensures free p*/
void freeStack(Stack p)
{
    free(p->c);
}

Stack fusion(Stack p1, Stack p2)
{
    Stack r = createStack();
    while (!empty(p1))
    {
        push(r, pop(p1));
    }
    while (!empty(p2))
    {
        push(r, pop(p2));
    }
    return r;
}

/*-----------------Fifo-----------------*/

/*@requires nothing
   assigns noting
   ensures construct a new FIFO*/
Fifo consFifo(Card v, Fifo f)
{
    Fifo r = (Fifo)malloc(sizeof(struct fifoCell));
    r->val = v;
    r->next = f;
    return r;
}

/*@requires f valid adress
   assigns f
   ensures add v in the beginning of f */
void enqueue(Card v, Fifo *f)
{
    *f = consFifo(v, *f);
}

/*@requires f valid adress
   assigns f
   ensures return the element which has been add in first and delete it*/
Card dequeue(Fifo *f)
{
    if (*f == NULL)
        return errorCard();
    else
    {
        Fifo prev = *f;
        if ((*f)->next == NULL)
        {
            Card r = (*f)->val;
            *f = NULL;
            return r;
        }
        else
        {
            Fifo l = (*f)->next;
            while (l->next != NULL)
            {
                prev = l;
                l = l->next;
            }
            Card r = l->val;
            prev->next = NULL;
            return r;
        }
    }
}

/*@requires nothing
   assigns nothing
   ensures print f*/
void printFifo(Fifo f)
{
    if (f == NULL)
        printf("[]");
    else
    {
        while (f != NULL)
        {
            printCard(f->val);
            f = f->next;
        }
    }
}

/*@requires nothing
   assigns f
   ensures free f */
void freeFifo(Fifo f)
{
    Fifo tmp;
    while (f != NULL)
    {
        tmp = f->next;
        free(f);
        f = tmp;
    }
}

/*@requires nothing
   assigns nothing
   ensures return size of f*/
int sizeFifo(Fifo f)
{
    if (f == NULL)
    {
        return 0;
    }
    else
    {
        int c = 0;
        while (f != NULL)
        {
            c += 1;
            f = f->next;
        }
        return c;
    }
}

/*@requires f valid adress
   assigns f
   ensures return and delete the card which ID == id in f*/
Card deleteID(Fifo *f, int id)
{
    Fifo tmp = *f;
    Fifo after = (*f)->next;
    Card r;
    if (*f == NULL)
    {
        return errorCard();
    }
    if (tmp->val.id == id)
    {
        r = tmp->val;
        tmp = after;
        free(*f);
        *f = tmp;
        return r;
    }
    else
    {
        Fifo prev = *f;
        tmp = tmp->next;
        after = after->next;
        while (tmp->val.id != id)
        {
            tmp = tmp->next;
            after = after->next;
            prev = prev->next;
        }
        r = tmp->val;
        prev->next = after;
        return r;
    }
}

/*-----------------Test-----------------*/

// int main()
// {

//     Card A;
//     A.id = 1;
//     A.cost = 999;
//     A.effect = "shoot";

//     Card B;
//     B.id = 2;
//     B.cost = 111;
//     B.effect = "tir";

//     Card D;
//     D.id = 3;
//     D.cost = 123;
//     D.effect = "magie";

//     Stack pile1 = createStack();
//     Stack pile2 = createStack();
//     push(pile1, A);
//     push(pile1, B);
//     push(pile2, B);
//     push(pile2, A);
//     Stack r = fusion(pile1, pile2);
//     print_stack(r);

//     Fifo file = NULL;
//     printf("taille %d\n", sizeFifo(file));
//     enqueue(A, &file);
//     printf("taille %d\n", sizeFifo(file));
//     enqueue(B, &file);
//     printf("taille %d\n", sizeFifo(file));
//     printFifo(file);
//     enqueue(D, &file);
//     printFifo(file);
//     deleteID(&file, 3);
//     printFifo(file);
//     return 0;
// }