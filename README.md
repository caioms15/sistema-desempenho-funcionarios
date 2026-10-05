# Sistema de Análise de Desempenho de Funcionários

Programa em C, executado no terminal. Cadastra funcionários, registra uma nota por sexta-feira (0 a 10, até 52 por ano) e mostra a média e o desempenho de cada um. Os dados ficam salvos em `dados.txt`.

## Como rodar

Precisa de um compilador C (gcc).

```
gcc sistema.c -o sistema
./sistema        # no Windows: .\sistema
```

Sem compilador instalado, cole o conteúdo de `sistema.c` em um compilador online, como o OnlineGDB (onlinegdb.com) ou o Replit.

## Menu

| Opção | Ação |
|-------|------|
| 1 | Cadastrar funcionário |
| 2 | Ver informações (notas, média e desempenho) |
| 3 | Lançar nota da sexta |
| 0 | Sair |

## Classificação pela média

| Média | Desempenho |
|-------|------------|
| 8 ou mais | Excelente |
| 6 a 7,99 | Bom |
| 4 a 5,99 | Regular |
| abaixo de 4 | Precisa melhorar |

Trabalho de faculdade, FAMETRO.
