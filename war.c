#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

// Definição da estrutura Territorio
struct Territorio
{
    char nome[30];
    char cor[10];
    int tropas;
};


// Cadastra os territórios
void cadastrarTerritorios(struct Territorio *mapa, int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("Digite o nome do territorio %d: ", i + 1);
        scanf("%s", mapa[i].nome);

        printf("Digite a cor do territorio %d: ", i + 1);
        scanf("%s", mapa[i].cor);

        printf("Digite a quantidade de tropas do territorio %d: ", i + 1);
        scanf("%d", &mapa[i].tropas);

        printf("\n");
    }
}

// Exibe todos os territórios
void exibirTerritorios(struct Territorio *mapa, int n)
{
    printf("\n--- Territorios cadastrados ---\n");
    for (int i = 0; i < n; i++)
    {
        printf("Territorio %d\n", i + 1);
        printf("Nome: %s\n", mapa[i].nome);
        printf("Cor: %s\n", mapa[i].cor);
        printf("Tropas: %d\n\n", mapa[i].tropas);
    }
}

// Ataque entre territórios
void atacar(struct Territorio *atacante, struct Territorio *defensor)
{
    // validar se o ataque é possível
    if (strcmp(atacante->cor, defensor->cor) == 0)
    {
        printf("\n>> Nao pode atacar um territorio da mesma cor!\n");
        return;
    }
    if (atacante->tropas < 2)
    {
        printf("\n>> O atacante precisa ter pelo menos 2 tropas para atacar!\n");
        return;
    }

    int dadoAtacante = (rand() % 6) + 1; // dado 1-6
    int dadoDefensor = (rand() % 6) + 1;

    printf("\n%s (Cor: %s) atacou %s (Cor: %s)\n",
           atacante->nome, atacante->cor,
           defensor->nome, defensor->cor);

    printf("Dado Atacante: %d | Dado Defensor: %d\n", dadoAtacante, dadoDefensor);

    if (dadoAtacante > dadoDefensor)
    {
        printf(">> Atacante venceu!\n");
        strcpy(defensor->cor, atacante->cor);    // muda dono
        defensor->tropas = atacante->tropas / 2; // recebe metade das tropas
    }
    else
    {
        printf(">> Defensor resistiu!\n");
        atacante->tropas -= 1; // perde uma tropa
    }
}

// libera memória alocada
void liberarMemoria(struct Territorio *mapa)
{
    free(mapa);
}

int main()
{
    srand(time(NULL)); //aleatoriedade

    int n;
    printf("Quantos territorios deseja cadastrar? ");
    scanf("%d", &n);

    // Alocação dinâmica
    struct Territorio *mapa = (struct Territorio *)calloc(n, sizeof(struct Territorio));

    // Cadastro inicial
    cadastrarTerritorios(mapa, n);

    int opcao;
    do
    {
        printf("\n--- MENU ---\n");
        printf("1 - Exibir territorios\n");
        printf("2 - Atacar\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        switch (opcao)
        {
        case 1:
            exibirTerritorios(mapa, n);
            break;
        case 2:
        {
            int a, d;
            exibirTerritorios(mapa, n);

            printf("Escolha o numero do territorio atacante: ");
            scanf("%d", &a);
            printf("Escolha o numero do territorio defensor: ");
            scanf("%d", &d);

            if (a < 1 || a > n || d < 1 || d > n)
            {
                printf(">> Territorio invalido!\n");
            }
            else if (a == d)
            {
                printf(">> Um territorio nao pode atacar ele mesmo!\n");
            }
            else
            {
                atacar(&mapa[a - 1], &mapa[d - 1]);
            }
            break;
        }
        case 0:
            printf("\nSaindo...\n");
            break;
        default:
            printf("\nOpcao invalida!\n");
        }

    } while (opcao != 0);

    liberarMemoria(mapa);
    return 0;
}
