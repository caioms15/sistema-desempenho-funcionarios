#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// organização dos dados do sitema //////////////////////
#define MAX_FUNC 100
#define MAX_NOTAS 52

typedef struct {
    char nome[50];
    float notas[MAX_NOTAS];   // uma nota por sexta
    int qtdNotas;
} Funcionario;

Funcionario func[MAX_FUNC];
int qtdFunc = 0;

// calcula a média das notas de um funcionário
float calcularMedia(Funcionario *f) {
    if (f->qtdNotas == 0) return 0;
    float soma = 0;
    for (int i = 0; i < f->qtdNotas; i++)
        soma += f->notas[i];
    return soma / f->qtdNotas;
}

// classifica o desempenho pela média
const char *classificar(float media) {
    if (media >= 8) return "Excelente";
    if (media >= 6) return "Bom";
    if (media >= 4) return "Regular";
    return "Precisa melhorar";
}

void cadastrarFuncionario() {
    if (qtdFunc >= MAX_FUNC) {
        printf("Limite de funcionarios atingido!\n");
        return;
    }

    printf("Nome do funcionario: ");
    fgets(func[qtdFunc].nome, 50, stdin);
    func[qtdFunc].nome[strcspn(func[qtdFunc].nome, "\n")] = '\0';  // tira o \n
    func[qtdFunc].qtdNotas = 0;

    qtdFunc++;
    printf("Funcionario cadastrado!\n");
}

void listarFuncionarios() {
    for (int i = 0; i < qtdFunc; i++)
        printf("%d - %s\n", i + 1, func[i].nome);
}

// lança a nota da sexta para um funcionário
void lancarNota() {
    int num;
    float nota;

    if (qtdFunc == 0) {
        printf("Nenhum funcionario cadastrado.\n");
        return;
    }

    listarFuncionarios();
    printf("Numero do funcionario: ");
    if (scanf("%d", &num) != 1 || num < 1 || num > qtdFunc) {
        while (getchar() != '\n');
        printf("Funcionario invalido!\n");
        return;
    }

    Funcionario *f = &func[num - 1];
    if (f->qtdNotas >= MAX_NOTAS) {
        while (getchar() != '\n');
        printf("Esse funcionario ja tem as %d notas do ano!\n", MAX_NOTAS);
        return;
    }

    printf("Nota da sexta (0 a 10): ");
    if (scanf("%f", &nota) != 1 || nota < 0 || nota > 10) {
        while (getchar() != '\n');
        printf("Nota invalida!\n");
        return;
    }
    while (getchar() != '\n');

    f->notas[f->qtdNotas] = nota;
    f->qtdNotas++;
    printf("Nota lancada!\n");
}

// mostra nome, quantidade de notas, média e classificação
void verInformacoes() {
    if (qtdFunc == 0) {
        printf("Nenhum funcionario cadastrado.\n");
        return;
    }

    printf("\n%-20s %-8s %-8s %s\n", "Nome", "Notas", "Media", "Desempenho");
    for (int i = 0; i < qtdFunc; i++) {
        float media = calcularMedia(&func[i]);
        if (func[i].qtdNotas == 0)
            printf("%-20s %-8d %-8s %s\n", func[i].nome, 0, "-", "Sem notas");
        else
            printf("%-20s %-8d %-8.2f %s\n", func[i].nome, func[i].qtdNotas, media, classificar(media));
    }
}

// PARA DEIXAR SALVO MESMO DEPOIS DE RENICIAR A FERRAMENTA///////////
void salvar() {
    FILE *f = fopen("dados.txt", "w");
    if (f == NULL) {
        printf("Erro ao salvar o arquivo!\n");
        return;
    }
    fprintf(f, "%d\n", qtdFunc);
    for (int i = 0; i < qtdFunc; i++) {
        fprintf(f, "%s\n", func[i].nome);
        fprintf(f, "%d", func[i].qtdNotas);
        for (int j = 0; j < func[i].qtdNotas; j++)
            fprintf(f, " %.2f", func[i].notas[j]);
        fprintf(f, "\n");
    }
    fclose(f);
}

void carregar() {
    FILE *f = fopen("dados.txt", "r");
    if (f == NULL) return;          // primeira vez, não existe arquivo
    if (fscanf(f, "%d\n", &qtdFunc) != 1 || qtdFunc < 0 || qtdFunc > MAX_FUNC)
        qtdFunc = 0;
    for (int i = 0; i < qtdFunc; i++) {
        fgets(func[i].nome, 50, f);
        func[i].nome[strcspn(func[i].nome, "\n")] = '\0';
        if (fscanf(f, "%d", &func[i].qtdNotas) != 1 || func[i].qtdNotas < 0 || func[i].qtdNotas > MAX_NOTAS)
            func[i].qtdNotas = 0;
        for (int j = 0; j < func[i].qtdNotas; j++)
            fscanf(f, "%f", &func[i].notas[j]);
        fscanf(f, "\n");
    }
    fclose(f);
}

//  inicio do main ///////////////////////////////////

int main(){

    // Declaraçãoa de variáveis
    int opcao;

    carregar();

    do {
        //Menu do sitema
        printf("\n======================================\n");
        printf("1 ) Fazer cadastro de Funcionario :\n");
        printf("2 ) Ver informacoes dos funcionarios :\n");
        printf("3 ) Lancar nota da sexta :\n");
        printf("0 ) Sair :\n");
        printf("======================================\n");
        printf("Digite a opcao desejada : ");
        if (scanf("%d", &opcao) != 1)
            opcao = -1;

        //limpar o enter (e qualquer lixo) do buffer
        while (getchar() != '\n');

        //estrutura de decisão
        switch(opcao){
            case 1:
                cadastrarFuncionario();
                salvar();
                break;
            case 2:
                verInformacoes();
                break;
            case 3:
                lancarNota();
                salvar();
                break;
            case 0:
                printf("Saindo...\n");
                break;
            default:
                printf("Opcao invalida\n");
        }
    } while (opcao != 0);

    return 0;
}
