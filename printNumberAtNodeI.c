#include <stdio.h>
#include <stdlib.h>


typedef struct node {
    float number;
    struct node *next;
} Node;


void addNumber(Node *head, float number){
    Node *current = head;

    
    Node *newNode = (Node *) malloc(sizeof(Node));
    newNode->next = NULL;
    newNode->number = number;

   
    while(current->next != NULL){
        current = current->next;
    }

   
    current->next = newNode;
}


void printNumberAtNodeI(Node *head, int i){
    if(i == 0){
        printf("Not valid input!Must be over 1!\n");
        return;
    }

    Node *current = head;

    int currPos = 1;

 

    while((currPos < i) && (current->next != NULL)){
        current = current->next;
        currPos++;
    }


    if(currPos < i) {
        printf("Index i = %d exceeds the number of nodes in the list %d: Reached the last node of the list before hitting node #%d.", i, currPos, i);
        return;
    }

    printf("Number at Node #%d: number = %0.3f\n", currPos, current->number);
}


void deleteNumberAtNodeI(Node **headPos, int i){
    if(i == 0){
        printf("Not valid input!Must be over 1.\n");
        return;
    }

    if(i == 1){
        printf("Deleting number at Node #1 : number = %0.2f\n", (*headPos)->number);

        if(*headPos == NULL){
            return;
        }

        Node *nextNode = NULL;
        nextNode = (*headPos)->next;

        free(*headPos);

        *headPos = nextNode;
        return;
    }

    Node *current = *headPos;

    int currPos = 1;

    

    while((currPos < (i - 1)) && (current->next != NULL)){
        current = current->next;
        currPos++;
    }


     if(currPos == i-1 && current->next != NULL){
        printf("Deleting number at Node #%d : number = %0.3f\n", i , current->next->number);

        Node *temp = current->next;

        current->next = temp->next;

        free(temp);
    }
    
    else if(currPos < i - 1 || current->next == NULL){
        printf("Node #%d doesn't exist.\n", i);
        return;
    }
}


void printLinkedList(Node *head){
    printf("------------------Linked List-------------------\n");
    Node *current = head;
    int n = 1;
    while(current != NULL){
        printf("Node #%d: number = %0.3f\n", n, current->number);
        current = current->next;
        n++;
    }
}


int main() {
    int MIN = 100;
    int MAX = 1000;
    int AEM = 2222; 

    srand(4402);

    Node *head = (Node *) malloc(sizeof(Node));
    if (head == NULL){
        printf("Error allocating memory!");
            return 1;
    }

    head->next = NULL;

    float randomNumber;
int i=0;
    for(i = 0; i < 100; i++){
       

        randomNumber = MIN + rand() % (MAX - MIN + 1);


        if(i == 0){
            head->number = randomNumber;
            continue;
        }

        addNumber(head, randomNumber);
    }

    printLinkedList(head);
    printf("\n\n");

    printf("1. ");
    printNumberAtNodeI(head, 75);
    printf("2. ");
    deleteNumberAtNodeI(&head, 33);

    printf("3. ");
    printNumberAtNodeI(head, 66);
    return 0;
}
