//Bruno Antico Galin 10417318
//Enzo Ribeiro 10418262
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define max_estados 20
#define max_alfabeto 10
#define max_palavras 100

struct node{
  char data;
  struct node *next;
  char connection;  
} typedef node;

node* connect_estados(node* q0, char data, char connection){
  
}

int create_afnd(char q0, char palavras[], char data, int estados, bool verifica){
  return 1;
}

int main(void){
  char alfabeto[max_alfabeto];
  int num_estados, num_finais, transit, entradas;
  FILE *file = fopen("afnd.txt", "r");
  if (file == NULL){
    printf("Erro ao abrir o arquivo.\n");
  }
  node* q0[num_estados];
  fscanf(file, "%s", alfabeto);
  fscanf(file, "%d", &num_estados);
  fscanf(file, "%d", &num_finais);
  int estados_finais[num_finais];
  for (int i = 0; i < num_finais; i++){
    fscanf(file, "%d", &estados_finais[i]);
  }
  fscanf(file, "%d", &transit);
  for (int i = 0; i < transit; i++){
    int estado_atual, next_estado;
    char data;
    fscanf(file, "%d %c %d", &estado_atual, &data, &next_estado);
    q0[estado_atual] = connect_estados(q0, data, next_estado);
  }
  fscanf(file, "%d", &entradas);
  char palavras[entradas][max_palavras];
  for (int i = 0; i < entradas; i++){
    fscanf(file, "%s", palavras[i]);
  }
  fclose(file);

  int verifica[num_estados];
  for (int i = 0; i < num_estados; i++){
    verifica[i] = 0;
  }
  for (int i = 0; i < num_finais; i++){
    verifica[estados_finais[i]] = 1;
  }

  for (int i = 0; i < entradas; i++){
    int res = create_afnd(q0, palavras[i], alfabeto, num_estados, verifica);
    if (res == 1){
      printf("OK\n");
    }
    else{
      printf("not OK\n");
    }
  }
  return 0;
}
