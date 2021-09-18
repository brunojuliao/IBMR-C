#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <stdbool.h>
#include <string.h>

struct pessoa {
    char nome[50];
    char email[80];
};

int main(int argc, char *argv[]) {
    struct pessoa p1;

    printf("\n=== Cadastro de Usuário ===\n");

    printf("Nome : ");
    scanf("%s%*c", p1.nome);

    printf("Email : ");
    //flush stdin para ler o teclado e fgets() para atribuir na string
    fflush(stdin);
    fgets(p1.email, 80, stdin);

    printf("\n === IMPRIMINDO === \n");
    printf("\n Nome : ");
    //também temos o puts para imprimir a string
    puts(p1.nome);
    printf("\n Email : %s", p1.email);

    getchar();

    return 0;
}