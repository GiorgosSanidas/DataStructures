#include <stdio.h>
#include <stdlib.h>

#define AEM 2222
#define SIZE 200

typedef struct node {
    int plateNumber;
    int parkingSpot;
    int left;
    int right;
    
} node;

node *binaryTree[SIZE];
int numberOfRecords = 0;

void initBinaryTree(){
	int i;
    for(i = 0; i < SIZE; i++){
        binaryTree[i] = NULL;
    }
}

void destructBinaryTree(){
	int i;
    for(i = 0; i < SIZE; i++){
        if(binaryTree[i] != NULL){
            free(binaryTree[i]);
            binaryTree[i] = NULL;
        }
    }
}

void insert(int plateNumber, int parkingSpot){
    int i = 0;
    //Arxikopoihsh neou kombou
    node *newRecord = (node *)malloc(sizeof(node));
    newRecord->plateNumber = plateNumber;
    newRecord->parkingSpot = parkingSpot;
    newRecord->left = -1;
    newRecord->right = -1;

    printf("Inserting new record: Plates=%d - Spot=%d\n", newRecord->plateNumber, newRecord->parkingSpot);

    if(numberOfRecords == 0){
        binaryTree[numberOfRecords] = newRecord;
        printf("Node added on Binary Tree at i: %d\n", numberOfRecords);
        numberOfRecords++;
        return;
    }

    int flag = 1;
    int index = 0;

    while(flag){
        //printf("Trying index = %d\n", index);
        if(binaryTree[index]->plateNumber == newRecord->plateNumber){
            printf("Same plates!\n");
            break;
        }
        else if(newRecord->plateNumber <= binaryTree[index]->plateNumber){
            if(binaryTree[index]->left == -1){
                binaryTree[index]->left = numberOfRecords;
                flag = 0;
                break;
            }
            index = binaryTree[index]->left;
        }
        else if(newRecord->plateNumber > binaryTree[index]->plateNumber){
            if(binaryTree[index]->right == -1){
                binaryTree[index]->right = numberOfRecords;
                flag = 0;
                break;
            }
            index = binaryTree[index]->right;
        }
    }

    binaryTree[numberOfRecords] = newRecord;
    printf("Node added on Binary Tree at index: %d\n", numberOfRecords);
    numberOfRecords++;
}

void traverseInOrder(node *n){
    if(n == NULL){
        return;
    }

    int rIndex = n->right;
    int lIndex = n->left;

    if(lIndex != -1) {
        traverseInOrder(binaryTree[lIndex]);
    }

    printf("%d \t%d \t%d \t%d\n", lIndex, n->plateNumber, n->parkingSpot, rIndex);

    if(rIndex != -1){
        traverseInOrder(binaryTree[rIndex]);
    }
}

void traverseTree(){
    printf("LeftCld Plate ParkSpot RightCld\n");
    traverseInOrder(binaryTree[0]);
}


int printTree(){
	int i;
    printf("LeftCld Plate ParkSpot RightCld\n");
    for(i=0;i<SIZE; i++){
        if(binaryTree[i] != NULL){
            printf("%d \t%d \t%d \t%d\n", binaryTree[i]->left, binaryTree[i]->plateNumber, binaryTree[i]->parkingSpot, binaryTree[i]->right);
        }
        else {
           printf("Node at index = %d - Empty\n", i);
        }
    }
}

node *minValueNode(node *n){
    node *current = n;

    while(current != NULL && current->left != -1){
        printf("%d\n", current->plateNumber);
        current = binaryTree[current->left];
    }
    return current;
}

node * delete(node *n, int k){
    if(n == NULL){
        return n;
    }

    if(k < n->plateNumber){
        binaryTree[n->left] = delete(binaryTree[n->left], k);
    }
    else if(k > n->plateNumber) {
        binaryTree[n->right] = delete(binaryTree[n->right], k);
    }
    else{
        if(n->left == -1){
            node *ret = binaryTree[n->right];
            free(n);
            return ret;
        }
        else if(n->right == -1){
            node *ret = binaryTree[n->left];
            free(n);
            return ret;
        }

        node *min = minValueNode(binaryTree[n->right]);

        n->plateNumber = min->plateNumber;
        n->parkingSpot = min->parkingSpot;

        binaryTree[n->right] = delete(binaryTree[n->right], min->plateNumber);
    }

    return n;
}

void deleteRoot(){
    binaryTree[0] = delete( binaryTree[0] , binaryTree[0]->plateNumber);
}

int main()
{
    srand(AEM);
    initBinaryTree();

    int k;
    int existingPlates[10000];
    for(k = 0; k < 10000; k++){
        existingPlates[k] = -1;
    }

    int n;
    int plate;
    for(n = 0; n < SIZE; n++){
        plate = 1000 + rand() % 9000;

        //printf("Plate = %d\n", plate);
        while (existingPlates[plate] != -1){
            plate++;
        }
        existingPlates[plate] = 1;
        insert(plate, n);
    }

    traverseTree();

    //traverseTree();
    //deleteRoot();
    //traverseTree();
    destructBinaryTree();
    return 0;
}
