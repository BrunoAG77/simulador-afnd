//Bruno Antico Galin 10417318
//Enzo Ribeiro 10418262
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

#define max_estados 20
#define max_alfabeto 10
#define max_palavras 100

struct node{
  char data;
  struct node *next;
  char connection;  
} typedef node;

node* connect_estados(node* qi, char data, char connection){
  node* new_node = (node*) malloc(sizeof(node));
  new_node->data = data;
  new_node->next = NULL;
  new_node->connection = connection;
  if(qi == NULL){
    qi = new_node;
  }
  else{
    node* aux = qi;
    while(aux->next != NULL){
      aux = aux->next;
    }
    aux->next = new_node;
  }
  return qi;
}

int create_afnd(char q0, char palavras[], char data[], int estados, bool verifica[]){
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
  fscanf(file, "%s", alfabeto); // Leitura do alfabeto
  fscanf(file, "%d", &num_estados); // Leitura do número de estados
  fscanf(file, "%d", &num_finais); // Leitura do número de estados finais
  int estados_finais[num_finais];
  for (int i = 0; i < num_finais; i++){
    fscanf(file, "%d", &estados_finais[i]); // Leitura dos estados finais
  }
  fscanf(file, "%d", &transit); // Leitura do número de transições
  for (int i = 0; i < transit; i++){
    int estado_atual, next_estado;
    char data;
    fscanf(file, "%d %c %d", &estado_atual, &data, &next_estado); // Leitura das transições
    q0[estado_atual] = connect_estados(q0[estado_atual], data, next_estado);
  }
  fscanf(file, "%d", &entradas); // Leitura do número de entradas de palavras a ser testadas
  char palavras[entradas][max_palavras];
  for (int i = 0; i < entradas; i++){
    fscanf(file, "%s", palavras[i]); // Leitura das entradas de palavras
  }
  fclose(file);

  // Verificação dos estados finais
  int verifica[num_estados];
  for (int i = 0; i < num_estados; i++){
    verifica[i] = 0;
  }
  for (int i = 0; i < num_finais; i++){
    verifica[estados_finais[i]] = 1;
  }

  // Verificada cada entrada de palavras
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
