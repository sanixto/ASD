#include <stdio.h>
#include <stdlib.h>

char randomSymbol() {                    
  int numberOfSymbol = rand() % 95 + 32;
  return (char)numberOfSymbol;
}

typedef struct {
  char symbol;
  struct list * next_p;
} list;

list * listInit(char item) {
  list * l_p;
  l_p = malloc( sizeof(list) );

  l_p->symbol = item;
  l_p->next_p = NULL;
  return l_p;
}

list * listAdd(list * l_p, char item) {
  list * node_p;
  node_p = malloc( sizeof(list) );

  node_p->symbol = item;
  node_p->next_p = l_p;
  return node_p;
} 

void printList(list * l_p) {
  list * this_p = l_p;

  while (this_p) {
    printf("Ptr = %d Symbol = %c Next = %d \n", 
      this_p, this_p->symbol, this_p->next_p);

    size_t node_p = this_p->next_p;
    this_p = node_p;
  }
}

list * deleteList(list * l_p) {
  size_t node_p = l_p->next_p;

  if (!l_p) free(l_p);
  return node_p;
}

int main()
{ 
  int n;
  printf("Enter n |n > 0|\n");
  scanf("%d", &n);
  printf("\n");

  list * FIFO = listInit( randomSymbol() );
  
  for (int i = 0; i < n - 1; i++) {
    FIFO = listAdd(FIFO, randomSymbol() );
  }  
  
  list * newList = FIFO;
  list * reversedFIFO = listInit( FIFO->symbol );

  for (int i = 0; i < n - 1; i++) {
    size_t node_p = newList->next_p;
    newList = node_p;
    reversedFIFO = listAdd(reversedFIFO, newList->symbol);
  }
  
  printf("FIFO:\n");
  printList(FIFO);
  printf("\n");

  printf("FIFO reversed:\n");
  printList(reversedFIFO);
  printf("\n");
  
  for (int i = 0; i < n; i++) {
    FIFO = deleteList(FIFO);
  }
  for (int i = 0; i < n; i++) {
    reversedFIFO = deleteList(reversedFIFO);
  }
  
  printList(FIFO);
  printList(reversedFIFO);
}