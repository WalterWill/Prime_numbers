#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <iostream>
#include <time.h>
//===Estruturas===

//===Classes===

//===Prototipo das Funcoes===

//===Variaveis globais===
unsigned long int num, cont, primo = 1, nprimo = 0, teste, lastPrimo = 1;
double i = 0, calcSeg;

//===Funcao Main===
int main()
{
    //Cria arquivo se não existir
    FILE *fp;
    fp = fopen("primos.txt", "a");
    if (fp == NULL)
    {
        printf("Erro ao criar o arquivo\n");
        return 1;
    }
    fclose(fp);

    //Abrir arquivo para leitura
    fp = fopen("primos.txt", "r");
    if (fp == NULL)
    {
        printf("Erro ao abrir o arquivo\n");
        return 1;
    }
    printf("Arquivo PRIMOS aberto com sucesso.\n");

    //Ir para o final do arquivo
    while ((fscanf(fp, "%i\n", &lastPrimo)) != EOF)
    {
        //Le o arquivo e salva o numero
    }

    printf("Ultimo Primo = %i\n", lastPrimo);
    //Fechar arquivo
    fclose(fp);

    //Atualiza o ultimo numero calculado
    lastPrimo++;

    //Le um novo numero
    printf("Calcular ate: ");
    scanf("%i", &teste);

    //Verifica se o usuario digitou um numero maior
    if (teste < lastPrimo)
    {
        printf("Entrada invalida");
        return 0;
    }

    //Abre no final do arquivo
    fp = fopen("primos.txt", "a");
    if (fp == NULL)
    {
        printf("Erro ao abrir o arquivo\n");
        return 1;
    }

    //Iniciando relogio
    clock_t Ticks[2];
    Ticks[0] = clock();
    for (num = lastPrimo; num <= teste; num++)
    {
        cont = 2;
        while (cont <= sqrt(num) && primo == 1)
        {
            i++;
            if (fmod(num, cont) == 0)
            {
                if (primo == 1)
                {
                    primo = 0;
                }
            }
            cont++;
        }

        if (primo == 1)
        {
            printf("%i primo\n", num);
            fprintf(fp, "%i\n", num);
            nprimo++;
        }
        primo = 1;
    }

    Ticks[1] = clock();

    //Fechar arquivo
    fclose(fp);
    double Tempo = (Ticks[1] - Ticks[0]) * 1000.0 / CLOCKS_PER_SEC;
    Tempo = Tempo / 1000;
    printf("Tempo gasto: %.3f Segundos.\n", Tempo);

    printf("Calculos realizados: %.0lf\n", i);

    calcSeg = i / Tempo;
    printf("%.1f Calculos/Seg\n", calcSeg);
    printf("Primos encontrados: %i\n", nprimo);
    system("PAUSE");
    return 0;
}
//===Funcoes===
