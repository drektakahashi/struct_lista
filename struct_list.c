#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//André Kenji Takahashi

typedef struct lista{
    char nome[80];
    int telefone;
    char email[80];
    struct lista *next;
} Lista;

typedef struct {
    Lista *inicio;
    int tam;
} Data;

void create_list(Data *data){
    data->inicio = NULL;
    data->tam = 0;
}

void inserir_inicio(Data *data){
    char nome[80];
    int telefone;
    char email[80];
    printf("Nome: ");
    fflush(stdin);
    fgets(nome, sizeof(nome), stdin);
    nome[strlen(nome) - 1] = '\0';
    printf("Email: ");
    fgets(email, sizeof(email), stdin);
    email[strlen(email) - 1] = '\0';
    printf("Telefone: ");
    scanf("%d", &telefone);
    getchar();

    Lista *newno = (Lista *)malloc(sizeof(Lista));

       // Tratamento de erro
    if (newno == NULL) {
        printf("Erro ao alocar memoria!\n");
        return;
    }

    // Preencher
    strcpy(newno->nome, nome);
    newno->telefone = telefone;
    strcpy(newno->email, email);

    // Configurar a próxima ligação para o nó atual do início
    newno->next = data->inicio;

    // Atualizar o início para apontar para o novo nó
    data->inicio = newno;

    data->tam++;
}

void inserir_meio(Data *data){

    char nome[80];
    int telefone;
    char email[80];
    printf("Nome: ");
    fflush(stdin);
    fgets(nome, sizeof(nome), stdin);
    nome[strlen(nome) - 1] = '\0';
    printf("Email: ");
    fgets(email, sizeof(email), stdin);
    email[strlen(email) - 1] = '\0';
    printf("Telefone: ");
    scanf("%d", &telefone);
    getchar();

    Lista *newno = (Lista *)malloc(sizeof(Lista));

    //Tratamento de erro
    if (newno == NULL) {
        printf("Erro ao alocar memoria!\n");
        return;
    }

    //Preencher
    strcpy(newno->nome, nome);
    newno->telefone = telefone;
    strcpy(newno->email, email);

    //Verificando se inicio é igual a null
    if (data->inicio == NULL || data->tam == 0){
        newno->next = data->inicio;
        data->inicio = newno;
    } else {
        //finding the middle
        Lista *rapido = data->inicio;
        Lista *lento = data->inicio;
        Lista *anterior = NULL;

        while(rapido != NULL && rapido->next != NULL){
            rapido = rapido->next->next;
            anterior = lento;
            lento = lento->next;
        }

        newno->next = lento;
        anterior->next = newno;
    }

    data->tam++;
}

void inserir_final(Data *data){
    char nome[80];
    int telefone;
    char email[80];
    printf("Nome: ");
    fflush(stdin);
    fgets(nome, sizeof(nome), stdin);
    nome[strlen(nome) - 1] = '\0';
    printf("Email: ");
    fgets(email, sizeof(email), stdin);
    email[strlen(email) - 1] = '\0';
    printf("Telefone: ");
    scanf("%d", &telefone);
    getchar();

    Lista *newno = (Lista *)malloc(sizeof(Lista));

    // Tratamento de erro
    if (newno == NULL) {
        printf("Erro ao alocar memoria!\n");
        return;
    }

    // Preencher
    strcpy(newno->nome, nome);
    newno->telefone = telefone;
    strcpy(newno->email, email);

    newno->next = NULL; // new node will be the last

    // tratamento
    if (data->inicio == NULL) {
        data->inicio = newno;
    } else {
        // finding last node
        Lista *ultimo = data->inicio;
        while (ultimo->next != NULL) {
            ultimo = ultimo->next;
        }
        //atribuindo
        ultimo->next = newno;
    }

    data->tam++;
}


void imprimir(Data *data){
    Lista *lista = data->inicio;
    printf("\nLista de contatos: \n");
    while(lista != NULL){
        printf("Nome: %s\n", lista->nome);
        printf("Telefone: %d\n", lista->telefone);
        printf("Email: %s\n", lista->email);
        printf("\n");
        lista = lista->next;
    }
    printf("\n");
}

void buscar(Data *data){

    int telefone;
    int find = 0;
    printf("Informe o telefone para pesquisar o cadastro desejado: ");
    scanf("%d", &telefone);

    Lista *atual = data->inicio;

    while(atual != NULL){
        if(atual->telefone == telefone){
            printf("\nContato encontrado: \n");
            printf("Nome: %s\n", atual->nome);
            printf("Telefone: %d\n", atual->telefone);
            printf("Email: %s\n", atual->email);
            find = 1;
            break;
        }
        atual = atual->next;
    }
    if(find == 0){
        printf("Contato nao encontrado !!\n");
    }
}

void remover(Data *data){

    int telefone;
    int find = 0;
    printf("Informe o telefone para pesquisar o cadastro desejado: ");
    scanf("%d", &telefone);

    Lista *removeu = data->inicio;
    Lista *anterior = NULL;

    while(removeu != NULL){
        //
        if(removeu->telefone == telefone){
            //
            if(anterior != NULL){
                anterior->next = removeu->next;
            } else {
                data->inicio = removeu->next;
            }

            free(removeu);
            data->tam--;
            find = 1;
            printf("\nContato removido com sucesso !\n");
            break;
        }
        anterior = removeu;
        removeu = removeu->next;
    }
    if(find == 0){
        printf("Contato nao encontrado !!\n");
    }
}



main(){
    Data data;
    create_list(&data);
    int op;

    printf("\n\n----Lista de Contatos----\n");

    while(1){

        printf("\n [1] - Inserir no Inicio");
        printf("\n [2] - Inserir no Meio (Verificar disponibilidade!)");
        printf("\n [3] - Inserir no Final");
        printf("\n [4] - Exibir Contatos");
        printf("\n [5] - Buscar Contato");
        printf("\n [6] - Remover Contato");
        printf("\n [7] - Sair");

        printf("\n\nOpcao desejada: ");
        scanf("%d", &op);

        switch(op){

        case 1:
            inserir_inicio(&data);
            break;

        case 2:
            inserir_meio(&data);
            break;

        case 3:
            inserir_final(&data);
            break;

        case 4:
            imprimir(&data);
            break;

        case 5:
            buscar(&data);
            break;

        case 6:
            remover(&data);
            break;

        case 7:
            printf("Leaving the software..");
            return 0;

        default:
            printf("\nOpcao invalida!!");
        }

    }
}
