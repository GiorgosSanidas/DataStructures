#include <stdio.h>
#include <stdlib.h>

#define AEM 
#define TSIZE 40009

int hashKey1(long long int key){
    return key % TSIZE;
}

int hashKey2(long long int key){
    return 131 - (key % 131);
}

typedef struct data {
    long long int amka;
    int numOfVisits;
} data;

void printData(data *d){
    printf("AMKA: %lld - Visits: %d\n", d->amka, d->numOfVisits);
}

data *hashTable[TSIZE];
int numberOfRecords;

int i;
void initHashTable(){
    for(i=0; i < TSIZE; i++){
        hashTable[i] = NULL;
    }
}

void destructHashTable(){
    for(i=0; i < TSIZE; i++){
        free(hashTable[i]);
        hashTable[i] = NULL;
    }
}

void insertRecord(unsigned long long int amka, int numOfVisits){
    if(numberOfRecords == TSIZE){
        printf("The hash table is full!");
        return;
    }

    data *d = (data *)malloc(sizeof(data));
    d->amka = amka;
    d->numOfVisits = numOfVisits;

    int index = hashKey1(d->amka);
    

    int finalIndex;

    if(hashTable[index] == NULL){
        hashTable[index] = d;
        finalIndex = index;
    }
    else {

        printf("Collision with AMKA: %lld - initial position : %d - step : %d - final position: %d - Visits: %d\n",
               hashTable[index]->amka, hashKey1(hashTable[index]->amka), hashKey2(hashTable[index]->amka),  index, hashTable[index]->numOfVisits);

        int step = hashKey2(d->amka);
        int hashIndex = 0;
        int i = 1;

        while(i < TSIZE){
            hashIndex = (index + i*step) % TSIZE;
            

            if(hashTable[hashIndex] == NULL){
                hashTable[hashIndex] = d;
                finalIndex = hashIndex;
                break;
            }

            printf("Collision with AMKA: %lld - initial position : %d - step : %d - final position: %d - Visits: %d\n",
                   hashTable[hashIndex]->amka, hashKey1(hashTable[hashIndex]->amka), hashKey2(hashTable[hashIndex]->amka),  hashIndex, hashTable[hashIndex]->numOfVisits);

            i++;

            if(i >= TSIZE){
                printf("Record cannot be inserted!");
                return;
            }
        }
    }

    printf("Inserted record at index %d: ", finalIndex);
    printData(hashTable[finalIndex]);
    numberOfRecords++;
}

int searchRecord(long long int amka){
    int i = 0;

    int index = hashKey1(amka);
    int step = hashKey2(amka);

    printf("Searching record for AMKA : %lld - Initial Index = %d - Step = %d\n", amka, index, step);

    int hashIndex;

    for(i = 0; i < TSIZE; i++ ){
        hashIndex = (index + i * step) % TSIZE;

        //printf("Searching at index %d...\n", hashIndex);

        if(hashTable[hashIndex] != NULL){
            if(hashTable[hashIndex]->amka == amka){
                printf("Record found at %d: ", hashIndex);
                printData(hashTable[hashIndex]);
                printf("Number of Iterations %d: ", i + 1);
                return 1;
            }

        }


    }

    printf("Record for this AMKA not found!\n");
    return 0;
}


void printRecords(){
    printf("\nInserted Records:\n");
    int n = 1;
    for(i = 0; i < TSIZE; i++){
        if(hashTable[i] != NULL){
            printf("%d. Index: %d - ", n, i);
            printData(hashTable[i]);
            n++;
        }
    }
}

int main()
{
    int MinVisits = 5;
    int MaxVisits = 20;

    int NumOfPeople = 20000;
    int i;
    long long int amka;
    int n;

    srand(4402);

    initHashTable();

    for(i = 0; i < NumOfPeople; i++){

        amka = (long long int)1000000000*(1 + rand()%31) +
               (long long int)10000000*(1 + rand()%12) +
               (long long int)100000*(rand() % 100) +
               (long long int)1000*(rand() % 1000) +
               (long long int)rand() % 100;

        n = MinVisits + rand() % (MaxVisits - MinVisits + 1);
        
        insertRecord(amka, n);
    }

    printRecords();

    long long int amkaToFind;
    int ret = -1;

    printf("Search for AMKA:");
    scanf("%lld", &amkaToFind);

   ret = searchRecord(amkaToFind);

   if(ret == 0){
      printf("Adding record!\n");
      insertRecord(amkaToFind, 17);
   }

    destructHashTable();
    return 0;
}
