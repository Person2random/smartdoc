#include <stddef.h>

int push(int* stack, size_t size,int* stackp ,int c){
  if(*stackp+1 >= size) return -1;
  (*stackp)++;
  stack[*stackp] = c;
  return 0;  
}


int pop(int* stack, int* stackp){
  if(*stackp < 0) return -1;

  int c = stack[*stackp];

  (*stackp)--;

  return c;
}
