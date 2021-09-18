#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <stdbool.h>
#include <string.h>
#define TAM 10
#define TAM_MOD 50

struct veiculo {
    char marca[50];
    char modelo[TAM_MOD];
    int ano;
    char placa[8];
};

void MoveVeiculos(struct veiculo veiculos[TAM], int pos) {
    int i = pos + 1;
    do {
        veiculos[i++] = veiculos[pos];
    } while(veiculos[i].ano && i < TAM);
}

void CadastrarVeiculos(struct veiculo veiculos[TAM]) {
    printf("\n=== Cadastrar veículos ===\n");

    while(true) {
        int count;
        for(count=0; count < TAM; count++) {
            if (!veiculos[count].ano)
                break;
        }

        switch (count)
        {
            case 10:
                printf("\nLimite de %d veiculos atingido!\n", count);
                return;
                break;
            case 0:
                printf("\nNenhum veículo cadastrado\n");
                break;
            case 1:
                printf("\n1 veiculo cadastrado\n");
                break;
            
            default:
                printf("\n%d veiculos cadastrados\n", count);
                break;
        }

        printf("\nUse marca \"sair\" para sair\n");

        struct veiculo novo;
        
        printf("\nMarca:\n");
        scanf("%s%*c", novo.marca);

        if (!strcasecmp(novo.marca, "sair"))
            return;

        printf("\nModelo:\n");
        scanf("%s%*c", novo.modelo);

        printf("\nAno:\n");
        scanf("%d", &novo.ano);

        printf("\nPlaca:\n");
        scanf("%s%*c", novo.placa);

        int pos;
        for(pos = 0; pos < TAM; pos++) {
            if (!veiculos[pos].ano || novo.ano < veiculos[pos].ano)
                break;
        }

        if (veiculos[pos].ano)
            MoveVeiculos(veiculos, pos);

        veiculos[pos] = novo;
    }
}

void ListarVeiculos(struct veiculo veiculos[TAM]) {
    printf("\n=== Listar veículos ===\n");

    for(int i=0; i < TAM; i++) {
        if (!veiculos[i].ano)
            break;

        printf("\nMarca: %s\n", veiculos[i].marca);
        printf("\nModelo: %s\n", veiculos[i].modelo);
        printf("\nAno: %d\n", veiculos[i].ano);
        printf("\nPlaca: %s\n", veiculos[i].placa);
        printf("\n=========\n");
    }
}

void ListarVeiculosPorAno(struct veiculo veiculos[TAM], int ano) {
    printf("\n=== Listar veículos ===\n");

    for(int i=0; i < TAM; i++) {
        if (!veiculos[i].ano)
            break;

        if (veiculos[i].ano != ano)
            continue;

        printf("\nMarca: %s\n", veiculos[i].marca);
        printf("\nModelo: %s\n", veiculos[i].modelo);
        printf("\nAno: %d\n", veiculos[i].ano);
        printf("\nPlaca: %s\n", veiculos[i].placa);
        printf("\n=========\n");
    }
}

void ListarVeiculosAcimaAno(struct veiculo veiculos[TAM], int ano) {
    printf("\n=== Listar veículos ===\n");

    for(int i=0; i < TAM; i++) {
        if (!veiculos[i].ano)
            break;

        if (veiculos[i].ano < ano)
            continue;

        printf("\nMarca: %s\n", veiculos[i].marca);
        printf("\nModelo: %s\n", veiculos[i].modelo);
        printf("\nAno: %d\n", veiculos[i].ano);
        printf("\nPlaca: %s\n", veiculos[i].placa);
        printf("\n=========\n");
    }
}

void ListarVeiculosPorModelo(struct veiculo veiculos[TAM], char modelo[TAM_MOD]) {
    printf("\n=== Listar veículos ===\n");

    for(int i=0; i < TAM; i++) {
        if (!veiculos[i].ano)
            break;

        if (strcasecmp(veiculos[i].modelo, modelo))
            continue;

        printf("\nMarca: %s\n", veiculos[i].marca);
        printf("\nModelo: %s\n", veiculos[i].modelo);
        printf("\nAno: %d\n", veiculos[i].ano);
        printf("\nPlaca: %s\n", veiculos[i].placa);
        printf("\n=========\n");
    }
}

int main(int argc, char *argv[]) {
    struct veiculo veiculos[TAM];

    //inicializando
    for (int i = 0; i < TAM; i++) {
        veiculos[i].marca[0] = '\000';
        veiculos[i].modelo[0] = '\000';
        veiculos[i].ano = 0;
        veiculos[i].placa[0] = '\000';
    }

    printf("\n=== Cadastro de veículos ===\n");

    while(true) {
        printf("\n=== Opções ===\n");
        printf("\n1- Cadastrar veículos\n");
        printf("\n2- Listar veículos\n");
        printf("\n3- Listar filtrando por ano\n");
        printf("\n4- Listar filtrando a partir do ano\n");
        printf("\n5- Listar filtrando por modelo\n");
        printf("\n6- Sair\n");
        int op;
        scanf("%d", &op);

        switch (op)
        {
            case 1:
                CadastrarVeiculos(veiculos);
                break;
            case 2:
                ListarVeiculos(veiculos);
                getchar();
                break;
            case 3:
                int ano;
                printf("\nAno : \n");
                scanf("%d", &ano);
                ListarVeiculosPorAno(veiculos, ano);
                getchar();
                break;
            case 4:
                int ano_acima;
                printf("\nAno : \n");
                scanf("%d", &ano_acima);
                ListarVeiculosAcimaAno(veiculos, ano_acima);
                getchar();
                break;
            case 5:
                char modelo[TAM_MOD];
                printf("\nModelo : \n");
                scanf("%s%*c", modelo);
                ListarVeiculosPorModelo(veiculos, modelo);
                getchar();
                break;
            
            default:
                return 0;
                break;
        }
    }

    return 0;
}