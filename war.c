#include <stdio.h>
#include <string.h>

// Definição da estrutura War
struct War
{
    char nome[30];
    char cor[10];
    int tropas;
};

int main()
{
// array de estruturas War
    struct War territorios[5];

// cadastro dos territorios
    for (int i = 0; i < 5; i++)
    {
        printf("Digite o nome do territorio %d: ", i + 1);
        scanf("%s", territorios[i].nome);

        printf("Digite a cor do territorio %d: ", i + 1);
        scanf("%s", territorios[i].cor);

        printf("Digite a quantidade de tropas do territorio %d: ", i + 1);
        scanf("%d", &territorios[i].tropas);

        printf("\n");
    }

// exibição dos territorios
    printf("\n--- Territorios cadastrados ---\n");
    for (int i = 0; i < 5; i++)
    {
        printf("Territorio %d\n", i + 1);
        printf("Nome: %s\n", territorios[i].nome);
        printf("Cor: %s\n", territorios[i].cor);
        printf("Tropas: %d\n\n", territorios[i].tropas);
    }

    return 0;
}
