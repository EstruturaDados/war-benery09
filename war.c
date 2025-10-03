#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

// Estrutura do Territorio
struct Territorio
{
    char nome[30];
    char cor[10];
    int tropas;
    char *missao; // armazenada dinamicamente
};

// Cadastro de territórios
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

// Exibição dos territórios
void exibirTerritorios(struct Territorio *mapa, int n)
{
    printf("\n========== MAPA DO MUNDO ==========\n");
    for (int i = 0; i < n; i++)
    {
        printf("%d. %-10s (Cor: %-8s, Tropas: %-2d, Missao: %s)\n",
               i + 1,
               mapa[i].nome,
               mapa[i].cor,
               mapa[i].tropas,
               mapa[i].missao);
    }
    printf("===================================\n");
}

// Atribuir missão aleatória
void atribuirMissao(struct Territorio *territorio, const char *missoes[], int totalMissoes)
{
    int indice = rand() % totalMissoes;
    int tamanho = strlen(missoes[indice]) + 1;
    territorio->missao = (char *)malloc(tamanho * sizeof(char));
    if (!territorio->missao)
    {
        printf("Erro ao alocar memoria para a missao!\n");
        exit(1);
    }
    strcpy(territorio->missao, missoes[indice]);
}

// Ataque
void atacar(struct Territorio *atacante, struct Territorio *defensor)
{
    if (strcmp(atacante->cor, defensor->cor) == 0)
    {
        printf("\n>> Nao pode atacar um territorio da mesma cor!\n");
        return;
    }
    if (atacante->tropas < 2)
    {
        printf("\n>> O atacante precisa ter pelo menos 2 tropas!\n");
        return;
    }

    int dadoAtacante = (rand() % 6) + 1;
    int dadoDefensor = (rand() % 6) + 1;

    printf("\n%s (Cor: %s) atacou %s (Cor: %s)\n",
           atacante->nome, atacante->cor,
           defensor->nome, defensor->cor);

    printf("Dado Atacante: %d | Dado Defensor: %d\n", dadoAtacante, dadoDefensor);

    if (dadoAtacante > dadoDefensor)
    {
        printf(">> Atacante venceu!\n");
        strcpy(defensor->cor, atacante->cor);
        defensor->tropas = atacante->tropas / 2;
    }
    else
    {
        printf(">> Defensor resistiu!\n");
        atacante->tropas -= 1;
    }
}

// Verificação simples de missão
int verificarMissao(char *missao, struct Territorio *mapa, int tamanho)
{
    if (strcmp(missao, "Conquistar 3 territorios seguidos") == 0)
    {
        for (int i = 0; i < tamanho - 2; i++)
        {
            if (strcmp(mapa[i].cor, mapa[i + 1].cor) == 0 &&
                strcmp(mapa[i].cor, mapa[i + 2].cor) == 0)
                return 1;
        }
        return 0;
    }
    else if (strcmp(missao, "Eliminar todas as tropas da cor Vermelho") == 0)
    {
        for (int i = 0; i < tamanho; i++)
        {
            if (strcmp(mapa[i].cor, "Vermelho") == 0 && mapa[i].tropas > 0)
                return 0;
        }
        return 1;
    }
    else if (strcmp(missao, "Manter 5 territorios com 3 ou mais tropas cada") == 0)
    {
        int count = 0;
        for (int i = 0; i < tamanho; i++)
            if (mapa[i].tropas >= 3)
                count++;
        return (count >= 5) ? 1 : 0;
    }
    else
    {
        return 0; // para outras missões simples ainda não implementadas
    }
}

// Liberação de memória
void liberarMemoria(struct Territorio *mapa, int n)
{
    for (int i = 0; i < n; i++)
        free(mapa[i].missao);
    free(mapa);
}

// Verifica se algum jogador cumpriu a missão e declara vencedor
int checarVencedor(struct Territorio *mapa, int n)
{
    for (int i = 0; i < n; i++)
    {
        if (verificarMissao(mapa[i].missao, mapa, n))
        {
            printf("\n>>> Territorio %s cumpriu sua missao: %s <<<\n", mapa[i].nome, mapa[i].missao);
            return 1;
        }
    }
    return 0;
}

int main()
{
    srand(time(NULL));

    const char *missoes[] = {
        "Conquistar 3 territorios seguidos",
        "Eliminar todas as tropas da cor Vermelho",
        "Manter 5 territorios com 3 ou mais tropas cada"};

    int qtdMissoes = sizeof(missoes) / sizeof(missoes[0]);

    int n;
    printf("Quantos territorios deseja cadastrar? ");
    scanf("%d", &n);

    struct Territorio *mapa = (struct Territorio *)calloc(n, sizeof(struct Territorio));
    if (!mapa)
    {
        printf("Erro na alocacao de memoria!\n");
        return 1;
    }

    cadastrarTerritorios(mapa, n);

    // atribuir missao
    for (int i = 0; i < n; i++)
        atribuirMissao(&mapa[i], missoes, qtdMissoes);

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

            // checar missao ao final do turno
            if (checarVencedor(mapa, n))
            {
                printf("\n>>> Missao cumprida! Fim do jogo. <<<\n");
                opcao = 0; // encerra o jogo
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

    liberarMemoria(mapa, n);
    return 0;
}
