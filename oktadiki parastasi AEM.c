#include <stdio.h>
#include <math.h>

int MAXSIZE = 5;       
int stack[5];     
int top = -1;           
int ant;

int isempty() {

   if(top == -1)
      return 1;
   else
      return 0;
}
   
int isfull() {

   if(top == MAXSIZE)
      return 1;
   else
      return 0;
}

int peek() {
   return stack[top];
}

int pop() {
   int data;
	
   if(!isempty()) {
      data = stack[top];
      top = top - 1;   
      return data;
   } else {
      printf("Could not retrieve data, Stack is empty.\n");
   }
}

int push(int data) {

   if(!isfull()) {
      top = top + 1;   
      stack[top] = data;
   } else {
      printf("Could not insert data, Stack is full.\n");
   }
}

int main() {
   push(3456);
   push(4376);
   push(4402);


   printf("Element at top of the stack: %d\n" ,peek());
   printf("Elements: \n");

   
   while(!isempty()) {
      int data = pop();
      printf("%d\n",data);
   }

   printf("Stack full: %s\n" , isfull()?"true":"false");
   printf("Stack empty: %s\n" , isempty()?"true":"false");
   

printf("η οκταδικη παρασταση του ΑΕΜ σας ειναι:%o\n",stack[2]);
ant=2*10000+6*1000+4*100+0*10+1*1;
 printf("διαβαζοντας απο το τελος προς την αρχη εχουμε:%d",ant);
 printf("\nΑρα ο αριθμος δεν ειναι παλινδρομικος");
   return 0;
}









