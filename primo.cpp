#include <iostream>
#include <stdio.h>
#include <malloc.h>
#include <conio.h>
#include <math.h>
#include <time.h>
#include <fstream>
#include <string>

using namespace std;

// Estruturas
struct nodo{
    int num;
    struct nodo *prox, *ant;
};

struct header{
    struct nodo *inicio, *fim;
    int qntd;
};

// Prototipo das funcoes
void cria_lista (struct header **listad);
void insere_direita (struct header  *listad , int valor);
void mostra_lista (struct header *listad );
bool check_primo (int n, struct header *listad);
void iniciar_lista(struct header *listad);
void check_redundancia(struct header *listad);
void insere_primo(struct header *listad, int n);
void libera_lista (struct header **listad );
void menu(struct header *listad);
void valor_unico(struct header *listad);
void valor_intervalo(struct header *listad);
void db_read(struct header *listad);
void db_write(struct header *listad);
// Main
int main()
{
    struct header *L;
    int num;

    cria_lista(&L);
    iniciar_lista(L);
    /*
    mostra_lista(L);
    insere_primo(L,2);
    mostra_lista(L);
    insere_primo(L,3);
    mostra_lista(L);
    insere_primo(L,4);
    mostra_lista(L);
    insere_primo(L,7);
    mostra_lista(L);
    insere_primo(L,5);
    mostra_lista(L);

    libera_lista(&L);
    */

    menu(L);
}

// Funcoes
void cria_lista (struct header **listad)
{
   struct header *lista=NULL;
   lista = (struct header *) malloc(sizeof(struct header));

   lista->inicio = NULL;
   lista->qntd   = 0;
   lista->fim    = NULL;

   *listad=lista;
}

void insere_direita (struct header  *listad , int valor)
{
 	struct nodo  *p, *aux;
	p= (struct nodo *) malloc(sizeof(struct nodo));
    p->num = valor;
    p->ant = listad->fim;
    if (p->ant != NULL)
    {
        aux = listad->fim;
        aux->prox = p;
    }
    p->prox = NULL;
    listad->fim  = p;
    (listad->qntd)++;

    if (listad->inicio == NULL)  //Se lista estava vazia...
    {
        listad->inicio = p;
    }
}

void mostra_lista (struct header *listad)
{
  struct nodo *aux ;
  aux = listad->inicio;
  printf("\nLista ===> \n");
  while (aux != NULL)
  {
      printf("Valor: %i - ", aux->num);
      aux = aux->prox;
   }
  printf("\n");
}

bool check_primo (int n, struct header *listad)
{
    if (n < 1)
    {
        return false;
    }else{
        if (listad->qntd != 0)
        {
            struct nodo *aux;
            aux = listad->inicio;

            bool status = true;

            float limit = sqrt(n);

            while ((aux->num <= limit) and (status))
            {
                if ((fmod(n, aux->num)) == 0)
                {
                    status = false;
                }

                aux = aux->prox;
                
            }

            return status;

        }else
        {
            float limit = sqrt(n);
            bool status = true;
            int i = 2;

            while ((i <= limit) and (status == true))
            {
                if ((fmod(n, i)) == 0)
                {
                    status = false;
                }

                i++;
            }

            if (status)
            {
                insere_direita(listad, n);
            }
            
            return status;
            
        }
    }
    
    
}

void iniciar_lista(struct header *listad)
{
    if (listad->qntd == 0)
    {
        insere_direita(listad, 2);
    }
}

void check_redundancia(struct header *listad, int num)
{
    // O numero ja existe na lista
    // retorna True
    //
    // Caso não, retorna False
    struct nodo *aux, *prev;
    aux = listad->inicio;
    prev = NULL;
    bool status = false;

    if (listad->qntd >= 1)
    {
        while ((aux != NULL) and (status == false) and (aux->num <= num))
        {
            if (aux->num == num)
            {
                status = true;
            }else
            {
                prev = aux;
            }
            
            aux = aux->prox;
        }

        if (prev != NULL)
        {
            if (status == false)
            {
                if (prev == (listad->fim))
                {
                    insere_direita(listad, num);
                }else
                {
                    // Insere a direita do node prev
                    struct nodo *novo;
                    novo = (struct nodo *)malloc(sizeof(struct nodo));

                    novo->num = num;
                    novo->ant = prev;
                    novo->prox = prev->prox;

                    prev->prox = novo;
                    novo->prox->ant = novo;

                    listad->qntd++;
                }
            }
        }
        
        
        
    }
}

void insere_primo(struct header *listad, int n)
{
            bool status = check_primo(n, listad);

        //printf("NUM = %i | Status = %i\n", n, status);

        if(status == true)
        {
            if (listad->qntd > 1)
            {
                if (n > listad->fim->num)
                {
                    insere_direita(listad, n);
                }else{
                    struct nodo *aux = listad->inicio;

                    while (aux->num < n)
                    {
                        aux = aux->prox;
                    }

                    if (aux == listad->inicio)
                    {
                        struct nodo *p, *aux;
                        aux = listad->inicio;

                        p = (struct nodo *)malloc(sizeof(struct nodo));
                        p->num = n;
                        p->prox = aux;
                        p->ant = aux->ant;

                        listad->inicio = p;
                    }else{
                        struct nodo *p;
                        p = (struct nodo *)malloc(sizeof(struct nodo));
                        p->num = n;
                        p->prox = aux;
                        p->ant = aux->ant;

                        aux->ant->prox = p;
                        aux->ant = p;
                    }
                    listad->qntd++;
                }
            }else if(listad->qntd == 1){
                if (n > listad->inicio->num)
                {
                    insere_direita(listad, n);
                }else{
                    struct nodo *p, *aux;
                    aux = listad->inicio;

                    p = (struct nodo *)malloc(sizeof(struct nodo));
                    p->num = n;
                    p->prox = aux;
                    p->ant = aux->ant;

                    listad->inicio = p;
                    listad->qntd++;
                }
                
            }   
        }else{
            //printf("%i nao eh primo\n", n);
        }
    
}

void libera_lista (struct header **listad )
{
    struct nodo *aux, *p ;
    aux = (*listad)->inicio;

    while (aux != NULL)
    {
        p = aux-> prox;
        free(aux);
        aux = p;
    }
}

void menu(struct header *listad)
{
    int op = 9;

    while (op != 0)
    {
        printf("=== MENU ===\n");
        printf("1 - Testar valor unico\n");
        printf("2 - Testar intervalo\n");
        printf("3 - Carregar Base de Dados\n");
        printf("4 - Gravar Base de Dados\n");
        printf("0 - Sair\n");

        scanf("%i", &op);

        switch (op)
        {
        case 1 :
            valor_unico(listad);
            break;
        
        case 2 :
            valor_intervalo(listad);
            break;
        
        case 3 :
            db_read(listad);
            break;
        
        case 4 :
            db_write(listad);
            break;
        
        case 0 :
            /* code */
            break;
        default:
            printf("Opcao invalida!\n");
            getch();
            break;
        }
    }
    printf("Saindo do Menu\n");
}

void valor_unico(struct header *listad)
{
    printf("=== VALOR UNICO ===\n");
    getch();
}

void valor_intervalo(struct header *listad)
{
    int num;
    printf("=== TESTAR INTERVALO ===\n");
    printf("Digite o numero desejado: ");
    scanf("%i", &num);

    printf("Testando todos os numeros primos até %i\n", num);

    clock_t Ticks[2];
    Ticks[0] = clock();

    for (int i = ((listad->fim->num) + 1); i <= num; i++)
    {
        insere_primo(listad, i);
    }

    Ticks[1] = clock();
    double Tempo = (Ticks[1] - Ticks[0]) * 1000.0 / CLOCKS_PER_SEC;

    printf("Total primos encontrados: %i\n", listad->qntd);
    printf("Tempo gasto: %g ms.\n", Tempo);
    //getch();

    
    printf("Deseja ver a lista completa?[s/n] ");
    char op = getch();

    if (op == 's')
    {
        mostra_lista(listad);
    }
}

void db_read(struct header *listad)
{
    printf("=== Carregar Base de Dados ===\n");

    int aux;
    string line;
    ifstream myfile ("10M.txt");
    if (myfile.is_open())
    {
        printf("Lendo arquivo...\n");
        while ( getline (myfile,line) )
        {
            aux = stoi(line);
            if(listad->fim->num != aux)
            {
                insere_direita(listad, aux);
            }
        }
        myfile.close();
        printf("Arquivo lido com sucesso!");
    }

  else cout << "Unable to open file"; 

    getch();
}

void db_write(struct header *listad)
{
    printf("=== Gravar Base de Dados ===\n");

    struct nodo *aux;
    aux = listad->inicio;

    ofstream myfile ("output.txt");
    if (myfile.is_open())
    {
        printf("Gravando arquivo...\n");
        while (aux != NULL)
        {
            myfile << aux->num << "\n";
            aux = aux->prox;
        }

        myfile.close();
        printf("Gravado com sucesso!\n");
    }
    else{
        cout << "Unable to open file";
    }
    getch();
}
