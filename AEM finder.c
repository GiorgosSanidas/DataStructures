#include <stdio.h>
#include <stdlib.h>
#include <time.h>


int i,v,aem[401],Number,count,ar[401];
float Grades[401];
main(){

 
 int count=0;
 
  for(Number = 2000; Number <=2400 ; Number++)
  {
    count = 0;
    for (i = 2; i <= Number/2; i++)
    {
      if(Number%i == 0)
      {
  	count++;
  	break;
      }
    }
    if(count == 0 && Number != 1 )
    { 
    	v=Number;
  //    printf(" %d ", Number);
      
//     printf("%d",v);
    }  
  }


	for (i=2000; i<=2400;i++)
	{ 
	aem[i]=i;
	}
	srand(4402);
    for (i=2000; i<=2400;i++)
	{
		
		Grades[i]=rand()%100;
		Grades[i]=Grades[i]/10;
//		printf(" \t%d : %.1f",aem[i],Grades[i]);
		
	}

for (i=2000;i<=2400;i++)
{   v=Grades[i];
	printf("δωσε αριθμο μητωρου για αναζητηση : ");
	scanf("%d",ar);
	if (ar[i]=aem[i])
	{
		printf("ο αριθμος μητρωου βρεθηκε στην θεση %d και η βαθμολογια του ειναι : %0.1d ",aem[i],v);
		
	   
		
		break;
	}
}
for (i=2000;i<=2400;i++)
{
	if (Grades[i]>v)
	{
		count++;
	}
	
}
printf(" \nΥπαρχουν %d καταχωρημενοι φοιτητες με μεγαλυτερη βαθμολογια",count);
return 0;
}




