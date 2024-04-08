#include <stdio.h>
#include <stdlib.h>    
#include <time.h>

#define AEM 4402

int randomPriority(){
    return rand() % 101; 
}

typedef struct Patient{
    int pId;
    int priority;
    int careTime;
    struct tm arrivalTime;
    struct tm serviceTime;
} Patient;


void defaultPatient(Patient *p){
    p->pId = -1;
    p->priority = -1;
    p->careTime = -1;
}

void initPatient(Patient *newPatient, int pid, int priority, struct tm simTime){
    newPatient->pId = pid;
    newPatient->priority = priority;
    
    newPatient->arrivalTime = simTime;

    newPatient->careTime = 0;
}


int isDefaultPatient(Patient p){
    if(p.pId == -1 && p.priority == -1 && p.careTime == -1){
        return 1;
    }
    else{
        return 0;
    }
}

void printPatientData(Patient p){
    printf("PatientID : %d - Priority : %d - Arrival time : %02d:%02d:%02d - Care time : %d secs - Service Time : %02d:%02d:%02d \n", 
            p.pId, p.priority, p.arrivalTime.tm_hour, p.arrivalTime.tm_min, p.arrivalTime.tm_sec, p.careTime, p.serviceTime.tm_hour, p.serviceTime.tm_min, p.serviceTime.tm_sec);
}

typedef struct Heap {
    Patient *array;
    int size;
    int currentSize;
} Heap;


int careTime(Patient p){
    return 100 + 10 * p.priority;
}

void swap(Patient *a, Patient *b){
    Patient temp = *b;
    *b = *a;
    *a = temp;
}

int parentIdxOfElem(int i){
    return (i - 1)/2;
}

int leftIdx(int i){
    return (2 * i + 1);
}

int rightIdx(int i){
    return (2 * i + 2);
}

void printHeap(Heap *heap){
    if(heap == NULL){
        printf("Not a heap!\n");
        return;
    }
    
    if(heap->array == NULL){
        printf("Error - Unitialized Heap!\n");
        return;
    }
    
    if(heap->currentSize == 0){
        printf("There are not patients!\n");
    }
    int i;
    for( i=0; i < heap->currentSize ; i++){
        printf("i = %d - leftChild = %d - rightChild = %d: ", i, leftIdx(i), rightIdx(i));
        printPatientData(heap->array[i]);
    }
}


void initHeap(Heap *heap, int initialSize){
    if(initialSize <= 0){
        printf("Invalid initial size!\n");
        return;
    }
    
    heap->array = (Patient*) malloc(initialSize * sizeof(Patient));
    heap->size = initialSize;
    heap->currentSize = 0;
}

int growHeapArray(Heap *heap){
    //printf("Growing array by one!\n");
    
    if(heap == NULL){
        printf("Not a heap!\n");
        return 0;
    }
    
    if(heap->array == NULL){
        heap->array = (Patient*) malloc(1 * sizeof(Patient));
        heap->size = 1;
        heap->currentSize = 0;
        //printf("Error - Unitialized Heap!\n");
        return 1;
    }
    
    Patient **array = &(heap->array);

    int newSize = heap->size + 1;
    
    Patient *tempNewArray = (Patient*)realloc(*array, (newSize * sizeof(Patient)));
    
    if (tempNewArray == NULL){
        printf("Failed to allocate memory.\n");
        return 0;
        
    }
    else{
        *array = tempNewArray;
        heap->size = newSize;
        return 1;
    }
    
    return 0;
}

int shrinkHeapArray(Heap *heap){
    //printf("Resizing array to fit exactly!\n");
    
    if(heap == NULL){
        printf("Not a heap!\n");
        return 0;
    }
    
    if(heap->array == NULL){
        printf("Error - Unitialized Heap!\n");
        return 0;
    }
    
    Patient **array = &(heap->array);
    int newSize = heap->currentSize;
    
    if(newSize == 0){
        //Leave the slot! The heap->size = 1!!
        /*heap->size = 1;
        heap->array = (Patient*)malloc(1 * sizeof(Patient));
        
        if(heap->array == NULL){
            printf("Failed to allocate memory.\n");
            return 0;
        }
        */
        return 1;
    }
    
    Patient *tempNewArray = (Patient*)realloc(*array, (newSize * sizeof(Patient)));
    
    if(tempNewArray == NULL){
        printf("Failed to free memory.\n");
        return 0;
    }
    else {
        *array = tempNewArray;
        heap->size = newSize;
        return 1;
    }
    return 0;
}




void insertNode(Heap *heap, Patient p){
    if(heap == NULL){
        return;
    }
    
    if(heap->array == NULL){
        printf("Error - Unitialized Heap!\n");
        int ret = growHeapArray(heap);
        if(ret != 1){
            printf("Failed to increase size! No new node added!\n");
            return;
        }
        
    }
    
    if(heap->currentSize >= heap->size){
        int ret = growHeapArray(heap);
        if(ret != 1){
            printf("Failed to increase size! No new node added!\n");
            return;
        }
    }
    
    int idx = heap->currentSize;
    heap->array[idx] = p;
    heap->currentSize++;
    
    int parent = parentIdxOfElem(idx);
    
    while(idx != 0 && (heap->array[parent]).priority < (heap->array[idx]).priority){
        swap(&(heap->array[parent]), &(heap->array[idx]));
        idx = parent;
        parent = parentIdxOfElem(idx);
    }
}


void heapify(Heap *heap, int i){
    if(heap == NULL){
        return;
    }
    else if(heap->currentSize <= 0){
        //printf("Empty heap!\n");
        return;
    }
    else{
        
        int size = heap->currentSize;
        
        int left = leftIdx(i);
        int right = rightIdx(i);
        int largest = i;
        
        if(left <= size && ((heap->array[left]).priority > (heap->array[largest]).priority)) {
            largest = left;
        }
     
        if(right <= size && ((heap->array[right]).priority > (heap->array[largest]).priority)) {
            largest = right;
        }
    
        if(largest != i){
            swap(&(heap->array[largest]), &(heap->array[i]));
            heapify(heap, largest);
        }
    }
}

Patient deleteNode(Heap *heap){
    Patient firstPatient;
    defaultPatient(&firstPatient);

    
    if(heap == NULL){
        return firstPatient;
    }
    
    if(heap->array == NULL || heap->currentSize <= 0){
        //printf("Error - Unitialized Heap!\n");
        return firstPatient;
    }
    
    firstPatient = heap->array[0];
    heap->currentSize--;
    
    Patient lastPatient = heap->array[heap->currentSize];
    
    heap->array[0] = lastPatient;
    heapify(heap, 0);
    
    if(heap->currentSize <= heap->size){
        int ret = shrinkHeapArray(heap);
        if(ret != 1){
            printf("Failed to shrink heap array to true size!\n");
        }
    }
    
    return firstPatient;
}



Heap* buildHeapFromArray(Patient p[], int numOfPatients){
    Heap *heap;
    initHeap(heap, numOfPatients);
    int i;
    for(i = 0; i < numOfPatients; i++){
        heap->array[i] = p[i];
        heap->currentSize++;
    }
    
    for( i = numOfPatients / 2; i >= 0; i--){
        heapify(heap, i);
    }
    
    return heap;
}


void destructHeap(Heap *heap){
    //printf("Destructing Heap!\n");
    if(heap == NULL){
        printf("Empty heap!");
        return;
    }

    if(heap->array == NULL){
        printf("Empty heap!");
        return;
    }
    
    free(heap->array);
    heap->array = NULL; 
    heap->size = 0;
    heap->currentSize = 0;
}

struct tm increaseBy15Mins(struct tm *now){
    time_t rawtime = mktime(now);
    
    rawtime += 15 * 60;
    
    struct tm *newS = localtime(&rawtime);
        
    return *newS;
}

struct tm increaseBySecs(struct tm *now, int seconds){
    time_t rawtime = mktime(now);
    
    rawtime += seconds;
    
    struct tm *newS = localtime(&rawtime);

    return *newS;
}


struct tm computeServiceTime(struct tm *now, int careTime){
    time_t rawtime = mktime(now);
    
    rawtime += careTime;
    
    struct tm *newS = localtime(&rawtime);
        
    return *newS;
}

int totalSecsSinceArrival(struct tm *start, struct tm *end){
    time_t rawTimeStart = mktime(start);
    time_t rawTimeEnd = mktime(end);
    
    int totalSecs = rawTimeEnd - rawTimeStart;
    return totalSecs;
}

int areTimesEqual(struct tm simTime, struct tm serviceTime){
    if(simTime.tm_hour == serviceTime.tm_hour && simTime.tm_min == serviceTime.tm_min && simTime.tm_sec == serviceTime.tm_sec)
        return 1;
    else
        return 0;
}

int main()
{
    Heap heap;
    srand(AEM); 

    int numOfPatients = 20;
    
    time_t unixNow = time(NULL);
    struct tm *now = localtime(&unixNow);
    struct tm startHour = *now;
    
    startHour.tm_hour = 0;
    startHour.tm_min = 0;
    startHour.tm_sec = 0;
    
    struct tm simTime = startHour;

    initHeap(&heap, numOfPatients);
    int i;
    for( i=0; i < numOfPatients ; i++){
        Patient p;
        p.pId = i;
        p.priority = randomPriority();
        p.arrivalTime = startHour;
        insertNode(&heap, p);
    }
    
    int numOfTotalPatients = numOfPatients; 
    int waitState = 0;
    long int totalCareTime = 0;
    long int totalSecsWaitingSinceArrival = 0;
    int waitingPeriod = 0;
    
    Patient currentPatient;

    while(simTime.tm_hour <= 12){
        if(simTime.tm_hour == 0 && simTime.tm_min == 0 && simTime.tm_sec == 0){
            currentPatient = deleteNode(&heap);      
            currentPatient.careTime = careTime(currentPatient);
            currentPatient.serviceTime = computeServiceTime(&simTime, currentPatient.careTime);
        }

        if((simTime.tm_hour != 11 && simTime.tm_sec == 0 && ((simTime.tm_hour != 0 && simTime.tm_min == 0) || 
                     simTime.tm_min == 15 || simTime.tm_min == 30 || simTime.tm_min == 45)) 
            || (simTime.tm_hour == 11 && simTime.tm_min == 0 && simTime.tm_sec == 0)){
            //printf("New Patient arrived at %02d:%02d:%02d\n", simTime.tm_hour, simTime.tm_min, simTime.tm_sec);
            Patient newPatient;
            numOfTotalPatients++;
            initPatient(&newPatient, numOfTotalPatients, randomPriority(), simTime);
            insertNode(&heap, newPatient);
        }
    
        if(areTimesEqual(simTime, currentPatient.serviceTime) || waitState == 1){
            if(waitState != 1){
                //printf("Total -> %d secs", totalSecsSinceArrival(&(currentPatient.arrivalTime), &(currentPatient.serviceTime)));
                totalSecsWaitingSinceArrival += totalSecsSinceArrival(&(currentPatient.arrivalTime), &(currentPatient.serviceTime));
                printPatientData(currentPatient);
            }
            
            if(simTime.tm_hour == 11 && simTime.tm_min > 0){
                break;
            }

            currentPatient = deleteNode(&heap);        
            if(isDefaultPatient(currentPatient)){
                //printf("Waiting!\n");
                simTime = increaseBySecs(&simTime, 1);
                waitingPeriod += 1;
                waitState = 1;
                currentPatient.serviceTime = simTime;
                continue;
            }
            waitState = 0;
            currentPatient.careTime = careTime(currentPatient);
            currentPatient.serviceTime = computeServiceTime(&simTime, currentPatient.careTime);
            totalCareTime += currentPatient.careTime;
        }

        simTime = increaseBySecs(&simTime, 1);
    }
    
    printf("End of service time %02d:%02d:%02d\n", simTime.tm_hour, simTime.tm_min, simTime.tm_sec);

    printf("Total number of patients: %d\n", numOfTotalPatients);
    
    int hours = totalCareTime / 3600;
    int mins = (totalCareTime - 3600*hours)/60;
	int secs = totalCareTime - (3600*hours) - (mins*60);
    
    printf("Total care time: %02d:%02d:%02d\n", hours, mins, secs);
    
    int averageCareTime = totalCareTime / numOfTotalPatients;
    hours = averageCareTime / 3600;
    mins = (averageCareTime - (3600*hours))/60;
	secs = averageCareTime - (3600*hours) -  (mins*60);
    
    printf("Average care time: %02d:%02d:%02d\n", hours, mins, secs);
    
    hours = waitingPeriod / 3600;
    mins = (waitingPeriod - (3600*hours))/60;
	secs = waitingPeriod - (3600*hours) -  (mins*60);
    
    printf("Waiting-Inactive time: %02d:%02d:%02d\n", hours, mins, secs);
     
    int averageSecsWaitingSinceArrival = totalSecsWaitingSinceArrival / numOfTotalPatients;
    hours = averageSecsWaitingSinceArrival / 3600;
    mins = (averageSecsWaitingSinceArrival - (3600*hours))/60;
	secs = averageSecsWaitingSinceArrival - (3600*hours) -  (mins*60);
   
    printf("Average time a patient had to wait for until service: %02d:%02d:%02d\n", hours, mins, secs);

    destructHeap(&heap);

    return 0;
}
