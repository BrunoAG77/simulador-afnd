//
// Created by enzoribeiroz on 3/28/25.
//

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAX_STATES 20
#define MAX_ALPHABET 10
#define MAX_WORDS 100

// estrutura de dado do AFND
typedef struct {
    int num_states; // numero de estados
    int alphabet_size; // tamanho do alfabeto
    int transition[MAX_STATES][MAX_ALPHABET][MAX_STATES]; // transicoes
    int initial_state; // estado inicial
    bool is_final[MAX_STATES]; // bool - estado final ou nao
} AFND;

// funcao para que inicia o AFND e armazena suas transicoes, numero de estados, tamanho do alfabeto, estado inicial e final
void init_afnd(AFND *afnd, int num_states, int alphabet_size, int initial_state) {
    afnd->num_states = num_states;
    afnd->alphabet_size = alphabet_size;
    afnd->initial_state = initial_state;

    for (int i = 0; i < MAX_STATES; i++) {
        for (int j = 0; j < MAX_ALPHABET; j++) {
            for (int k = 0; k < MAX_STATES; k++) {
                afnd->transition[i][j][k] = -1;
            }
        }
        afnd->is_final[i] = false;
    }
}

// funcao para adicionar transicoes ao AFND
void add_transition(AFND *afnd, int from_state, char symbol, int to_state) {
    int symbol_idx = symbol - 'a';
    for (int i = 0; i < MAX_STATES; i++) {
        if (afnd->transition[from_state][symbol_idx][i] == -1) {
            afnd->transition[from_state][symbol_idx][i] = to_state;
            break;
        }
    }
}

// funcao de retorno do estado final do AFND
void set_final_state(AFND *afnd, int state) {
    afnd->is_final[state] = true;
}

// simulacao do AFND completo
bool simulate_afnd(AFND *afnd, int current_state, const char *input, int pos) {
    if (input[pos] == '\0') {
        return afnd->is_final[current_state];
    }
    int symbol_idx = input[pos] - 'a';
    // recursivamente, a funcao e chamada para testar todas as transicoes possiveis ate o fim da palavra
    for (int i = 0; i < MAX_STATES; i++) {
        int next_state = afnd->transition[current_state][symbol_idx][i];
        if (next_state != -1) {
            if (simulate_afnd(afnd, next_state, input, pos + 1)) {
                return true;
            }
        }
    }
    return false;
}

int main() {
    AFND afnd;

    char alphabet_string[MAX_ALPHABET];
    int num_states, num_finals, num_transitions, alphabet_size, inputs;
    FILE *file = fopen("afnd.txt", "r");
    if (file == NULL){
        printf("Erro ao abrir o arquivo.\n");
    }
    fscanf(file, "%s", alphabet_string); // leitura do alfabeto
    fscanf(file, "%d", &num_states); // leitura do número de estados
    fscanf(file, "%d", &num_finals); // leitura do número de estados finais

    alphabet_size = strlen(alphabet_string);
    init_afnd(&afnd, num_states, alphabet_size, 0);

    int final_states[num_finals];
    for (int i = 0; i < num_finals; i++){
        fscanf(file, "%d", &final_states[i]); // leitura dos estados finais
        set_final_state(&afnd, final_states[i]);
    }
    fscanf(file, "%d", &num_transitions);
    for (int i = 0; i < num_transitions; i++){
        int actual_state, next_state;
        char data;
        fscanf(file, "%d %c %d", &actual_state, &data, &next_state);
        add_transition(&afnd, actual_state, data, next_state);
    }
    fscanf(file, "%d", &inputs); // leitura do número de entradas de palavras a ser testadas
    char words[inputs][MAX_WORDS];
    for (int i = 0; i < inputs; i++){
        fscanf(file, "%s", words[i]); // leitura das entradas de palavras
        if (simulate_afnd(&afnd, afnd.initial_state, words[i], 0)) {
            printf("%d: '%s' OK\n", i + 1, words[i]);
        } else {
            printf("%d: '%s' not OK\n", i + 1, words[i]);
        }
    }
    fclose(file);

    return 0;
}
