#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <iostream>
#include <time.h>
//===Estruturas===
typedef struct datanode
{
    unsigned long int primo;
} DataNode;

typedef struct node
{
    DataNode number;
    struct node *next;
} Node;

typedef struct list
{
    int size;
    Node *head;
    Node *last;
} list;

//===Classes===

//===Prototipo das Funcoes===
list *createList();                                 //Cria a lista
void push(list *lista, datanode data);              //Insere um node no inicio da lista
void pop(list *lista);                              //Apaga o primeiro node da lista
void insert(list *lista, DataNode data, int index); //Insere um node em um ponto especifico
void erase(list *lista, int index);                 //Exclui um node em um ponto especifico
bool isEmpty(list *lista);                          //Verifica se a lista esta vazia
int indexOf(list *lista, Node *node);               //Busca a posicao de um node
Node *atPos(list *lista, int index);                //Busca um node em uma determinada posicao
void printList(list *lista);                        //Imprime a lista
void final(list *lista, DataNode data);             //Adiciona no fim da lista

//===Variaveis globais===
unsigned long int num, cont, primo = 1, nprimo = 0, teste, lastPrimo = 1, point = 0;

double i = 0, calcSeg;

//===Funcao Main===
int main()
{
    //Cria a lista
    list *l = createList();
    DataNode data;

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
        //Le o arquivo e salva o numero na lista
        data.primo = lastPrimo;
        final(l,data);
        point++;

    }

    //Fechar arquivo
    fclose(fp);

    //Se estiver vazia, grava o numero 2
    if (lastPrimo == 1) {
        fp = fopen("primos.txt", "a");
        if (fp == NULL)
        {
            printf("Erro ao abrir o arquivo\n");
            return 1;
        }

        fprintf(fp,"%i\n", 2);
        data.primo = 2;
        final(l, data);
        point++;
        fclose(fp);
    }
    

    printf("Ultimo Primo = %i\n", lastPrimo);
    printf("Tamanho da lista = %i\n", l->size);
    printf("Point = %i\n", point);
    printList(l);
    system("PAUSE");

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
    
    //Calculo
    for (num = lastPrimo; num <= teste; num++)
    {
        point = 1;
        while ((atPos(l,point - 1)->number.primo) <= sqrt(num) && primo == 1)
        {
            if (fmod(num, (atPos(l, point - 1)->number.primo)) == 0)
            {
                i++;
                if (primo == 1)
                {
                    primo = 0;
                }
            }

            point++;
        }

        if (primo == 1)
        {
            
            //printf("%i primo\n", num);  //Printa primo
            //fprintf(fp, "%i\n", num);   //Grava primo
            //nprimo++;                   //Incrementa o N de primos
            

            data.primo = num;
            final(l, data);
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
    printf("Primos encontrados: %i\n", l->size);

    printf("First: %i\n", (atPos(l, 0))->number.primo);
    printf("Second: %i\n", (atPos(l, 1))->number.primo);
    printf("Thrind: %i\n", (atPos(l, 2))->number.primo);
    printf("Fourty: %i\n", (atPos(l, 3))->number.primo);
    system("PAUSE");

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
        //Le o arquivo e salva o numero na lista
    }

    //Fechar arquivo
    fclose(fp);

    printf("Gravando TXT\n");
    if (l->last->number.primo > lastPrimo) {
        fp = fopen("primos.txt", "r");
        Node *aux = l->head;
        while((aux->number.primo) <= lastPrimo){
            aux = aux->next;
        }
        fclose;

        fp = fopen("primos.txt", "a");
        while(aux->next != NULL){
            fprintf(fp,"\n%i", aux->number.primo);
            aux = aux->next;
        }
        fclose(fp);
        printf("Gravado");
        system("PAUSE");
        
    }
    
    return 0;
}
//===Funcoes===
list *createList()
{
    list *lista = (list *)malloc(sizeof(list));
    lista->size = 0;
    lista->head = NULL;
    lista->last = NULL;

    return lista;
}

void push(list *lista, DataNode num)
{
    Node *newNode = (Node *)malloc(sizeof(Node));

    newNode->number = num;
    newNode->next = lista->head;
    lista->head = newNode;
    lista->last = newNode;
    lista->size++;

    //Verificar final da lista
}

void printList(list *lista)
{

    if (isEmpty(lista))
    {
        printf("Lista vazia\n");
    }
    else
    {
        Node *pointer = lista->head;
        while (pointer != NULL)
        {
            printf("%d\n", pointer->number.primo);
            pointer = pointer->next;
        }
    }
}

bool isEmpty(list *lista)
{
    return (lista->size == 0);
}

void pop(list *lista)
{
    if (!isEmpty(lista))
    {
        Node *pointer = lista->head;
        lista->head = pointer->next;

        free(pointer);
        lista->size--;
    }
}

Node *atPos(list *lista, int index)
{
    if (index >= 0 && index < lista->size)
    {
        Node *pointer = lista->head;
        int i;
        for (i = 0; i < index; i++)
        {
            pointer = pointer->next;
        }
        return pointer;
    }
    printf("Indice Invalido\n");
    return NULL;
}

int indexOf(list *lista, Node *node)
{
    if (node != NULL)
    {
        Node *pointer = lista->head;
        int index = 0;

        while (pointer != node && pointer != NULL)
        {
            pointer = pointer->next;
            index++;
        }

        if (pointer != NULL)
        {
            return index;
        }
    }
    printf("Node nao pertence a lista\n");
    return -1;
}

void erase(list *lista, int index)
{
    if (index == 0)
    {
        pop(lista);
    }
    else
    {
        Node *current = atPos(lista, index);
        if (current != NULL)
        {
            Node *previous = atPos(lista, index - 1);
            previous->next = current->next;

            free(current);
            lista->size--;
        }
    }
}

void insert(list *lista, DataNode data, int index)
{
    if (index == 0)
    {
        push(lista, data);
    }
    else
    {
        Node *current = atPos(lista, index);
        if (current != NULL)
        {
            Node *previous = atPos(lista, index - 1);
            Node *newNode = (Node *)malloc(sizeof(Node));

            newNode->number = data;

            previous->next = newNode;
            newNode->next = current;
            lista->size++;
        }
    }
}

void final(list *lista, DataNode data)
{
    if (lista->head != NULL)
    {
        //Adicionar ao final da lista
        Node *last = lista->last;
        if (last->next == NULL)
        {
            Node *newNode = (Node *)malloc(sizeof(Node));
            newNode->number = data;
            newNode->next = last->next;

            last->next = newNode;

            lista->size++;
            lista->last = newNode;
        }
    }
    else
    {
        push(lista, data);
    }
}