#include <stdio.h>
#include <stdlib.h>
#include <time.h>


#include <assert.h>


#define NUM_MINUTES 720


#define MIN_MINUTES_PER_ARRIVAL 1
#define MAX_MINUTES_PER_ARRIVAL 4
#define MIN_MINUTES_PER_SERVICE 1
#define MAX_MINUTES_PER_SERVICE 4


static int customerArrivalTimes[NUM_MINUTES];

int main()
{
	int i;
    
    unsigned int seed = (unsigned)time( NULL );
    printf( "seeding with %u\n", seed );
    srand( seed );

   
    int nextArrival;

    
    int nextService = -1;


    int longestWait = 0;

    
    int longestQueue = 0;

    
    int queueLength = 0;


    int queueStart = 0;

   
    int queueEnd = 0;
    srand(4402);
    nextArrival = rand() % (MAX_MINUTES_PER_ARRIVAL + 1 - MIN_MINUTES_PER_ARRIVAL) + MIN_MINUTES_PER_ARRIVAL;

    
    for (  i = 0; i < NUM_MINUTES; i++ )
    {
      
        if ( nextArrival == i )
        {
           
            queueLength++;
            if ( queueLength > longestQueue ) longestQueue = queueLength;

           
            printf( "%03d:Νεος πελατης, η ουρα ειναι τωρα: %d.\n", i, queueLength );

            
            customerArrivalTimes[queueEnd++] = i;

           
            nextArrival = rand() % (MAX_MINUTES_PER_ARRIVAL + 1 - MIN_MINUTES_PER_ARRIVAL) + MIN_MINUTES_PER_ARRIVAL + i;

           
            if ( queueLength == 1 )
            {

                assert( nextService == -1 );

               
                nextService = rand() % (MAX_MINUTES_PER_SERVICE + 1 - MIN_MINUTES_PER_SERVICE) + MIN_MINUTES_PER_SERVICE + i;
            }
        }

       
        if ( nextService == i )
        {
            
            printf(
                "%03d:ο πελατης εξυπηρετηθηκε,συνολικος χρονος : %d.\n",
                i, i - customerArrivalTimes[queueStart]
            );

            
            if ( longestWait < i - customerArrivalTimes[queueStart] )
            {
                longestWait = i - customerArrivalTimes[queueStart];
            }

            
            queueStart++;
            queueLength--;

            assert( queueLength >= 0 );

           
            if ( queueLength != 0 )
            {
                
                nextService = rand() % (MAX_MINUTES_PER_SERVICE + 1 - MIN_MINUTES_PER_SERVICE) + MIN_MINUTES_PER_SERVICE + i;
            }
            
            else
            {
                nextService = -1;
            }
        }
    }


    printf( "μεγαλυτερη καθυστερηση: %d\n", longestWait );


    printf( "μεγαλυτερη ουρα : %d\n", longestQueue );

    return 0;
}
