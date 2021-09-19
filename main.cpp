#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TAM 10
#define TAM_NOME 30

struct cliente {
    char nome[TAM_NOME];
    int ano_nascimento;
    float gastos;
};

int qtd;
int usado;

struct cliente PegarClienteVazio() {
    struct cliente vazio;

    vazio.nome[0] = '\000';
    vazio.ano_nascimento = 0;
    vazio.gastos = 0.0;

    return vazio;
}

struct cliente* CadastrarCliente(struct cliente* clientes) {
    printf("\n=== Cadastrar cliente ===\n");

    int count = ++usado;

    switch (count)
    {
        case 0:
            printf("\nNenhum cliente cadastrado\n");
            break;
        case 1:
            printf("\n1 cliente cadastrado\n");
            break;
        
        default:
            printf("\n%d clientes cadastrados\n", count - 1);
            if (count > TAM) {
                clientes = (cliente*)realloc(clientes, count * sizeof(cliente));
            }
            break;
    }

    struct cliente novo;

    printf("\nNome:\n");
    scanf("%s%*c", novo.nome);

    printf("\nAno de nascimento:\n");
    scanf("%d", &novo.ano_nascimento);

    novo.gastos = 0.0;

    clientes[count] = novo;

    return clientes;
}

int BuscarCliente(struct cliente* clientes) {
    int pos;

    printf("\n=== Busca cliente ===\n");
    printf("\nA busca suporta nome parcial\n");

    char nome[TAM_NOME];
    printf("\nNome:\n");
    scanf("%s%*c", nome);

    for(int i = 0; i < usado; i++) {
        if (strstr(clientes[i].nome, nome) == NULL)
            continue;

        printf("\nÉ \"%s\" o cliente desejado? (s/n)\n", clientes[i].nome);
        char op;
        scanf("%c", &op);

        if (op == 's')
            return i;
        
        printf("\nBuscando o próximo...\n");
    }

    printf("\nCliente não encontrado\n");

    return -1;
}

void RemoverCliente(struct cliente* clientes) {
    printf("\n=== Remover cliente ===\n");

    int pos = BuscarCliente(clientes);

    if (pos == -1) {
        printf("\nAbortando operação\n");
        return;
    }

    int i = pos + 1;
    do {
        clientes[pos] = clientes[i++];
    } while(clientes[i].ano_nascimento && i < usado);

    //Como usado é a quantidade de posições e não o índice,
    //preciso decrementar o usado 2x para chegar no índice e 
    //zerar o cliente da posição
    clientes[--usado - 1] = PegarClienteVazio();
}

void AtualizarMontanteCliente(struct cliente* clientes) {
    printf("\n=== Atualizar montante cliente ===\n");

    int pos = BuscarCliente(clientes);

    if (pos == -1) {
        printf("\nAbortando operação\n");
        return;
    }

    float novo;
    printf("\nMontante atual: %f\nValor a acrescentar : \n", clientes[pos].gastos);
    scanf("%f", &novo);

    clientes[pos].gastos += novo;
    printf("\nNovo montante: %f\n", clientes[pos].gastos);
}

void ViradaMes(struct cliente* clientes) {
    printf("\n=== Virada do mês ===\n");

    if (usado == 0) {
        printf("\nNão há clientes para zerar\n");
        return;
    }

    printf("\nComeçando a zerar os gastos dos %d clientes\n", usado);
    for(int i = 0; i < usado; i++) {
        clientes[i].gastos = 0.0;
    }
    printf("\nFim. Todos of %d clientes estão com gastos zerados\n", usado);
}

void MelhorComprador(struct cliente* clientes) {
    printf("\n=== Melhor comprador ===\n");

    int pos_maior = -1, maior = 0;

    for(int i = 0; i < usado; i++) {
        if (clientes[i].gastos <= maior)
            continue;
        pos_maior = i;
        maior = clientes[i].gastos;
    }

    if (pos_maior == -1) {
        printf("\nNão encontrado.\n");
        return;
    }

    printf("\n%s com %f de montante\n", clientes[pos_maior].nome, clientes[pos_maior].gastos);
}

void MontanteAtual(struct cliente* clientes) {
    printf("\n=== Atualizar montante cliente ===\n");

    int pos = BuscarCliente(clientes);

    if (pos == -1) {
        printf("\nAbortando operação\n");
        return;
    }

    float novo;
    printf("\nMontante atual: %f\n", clientes[pos].gastos);
}

int main(int argc, char *argv[]) {
    qtd = TAM;
    usado = 0;
    struct cliente* clientes = (cliente *)calloc(qtd, sizeof(cliente));

    //inicializando
    for (int i = 0; i < TAM; i++) {
        clientes[i] = PegarClienteVazio();
    }

    printf("\n=== Cadastro de clientes ===\n");

    while(true) {
        printf("\n=== Opções ===\n");
        printf("\n1- Cadastrar cliente\n");
        printf("\n2- Remover cliente\n");
        printf("\n3- Atualizar montante de compras do mês do cliente\n");
        printf("\n4- Zerar todos os montantes (virada do mês)\n");
        printf("\n5- Listar o cliente melhor comprador\n");
        printf("\n6- Exibir montante atual do cliente\n");
        printf("\n7- Sair\n");
        int op;
        scanf("%d", &op);

        switch (op)
        {
            case 1:
                clientes = CadastrarCliente(clientes);
                break;
            case 2:
                RemoverCliente(clientes);
                break;
            case 3:
                AtualizarMontanteCliente(clientes);
                break;
            case 4:
                ViradaMes(clientes);
                break;
            case 5:
                MelhorComprador(clientes);
                break;
            case 6:
                MontanteAtual(clientes);
                break;
            
            default:
                return 0;
                break;
        }
    }

    return 0;
}