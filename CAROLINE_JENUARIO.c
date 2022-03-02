//INTEGRANTES :
//CAROLINE JENUARIO RODRIGUES DA SILVA
//ALEXANDRE DOS SANTOS BINDO CABRAL

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include<time.h>

typedef struct {
    int forca, resistencia, agilidade;
    float altura, peso;
    char nome [100];
    int id; //numero de registro
} gladiador;

//funcoes
void imprimeLista(gladiador c);
void imprimeListaGladiador(gladiador *lista, int tam);
void atualizarGladiador(gladiador *lista, int tam);
float poder(gladiador *lista, int tam);
void melhoria(gladiador *lista, int tam);
void dano(gladiador *lista, int tam);
void BatalhaGladiador(gladiador *a, gladiador *b, int tam);
void TentativaSorte (gladiador *lista, int tam);
gladiador LerGladiador();

int main () {
    gladiador *lista, c;
    int opcao;
    int pos = 0;
    lista = NULL;

    FILE *fp;


    fp = fopen("gladiador.txt","ab"); //abre arquivo do tipo ab (binario para leitura e escrita)

    if (fp == NULL)
    {
        printf("Falha ao criar arquivo.");
    }


    do{
      printf ("  %c Selecione uma das opçoes: \n", 006);
      printf ("[1] - Cadastrar Gladiador \n");
      printf( "[2] - Atualizar Gladiador \n");
      printf ("[3] - Listar Gladiadores \n");
      printf ("[4] - Batalha - em dupla \n");
      printf ("[5] - Tentativa da sorte - em dupla \n");
      printf ("[0] - Sair do sistema \n");
      scanf ("%d", &opcao);


      switch (opcao) {
        case 0:
           exit(0);
           break;
        case 1:
            c = LerGladiador(lista, pos);
            // Alocação dinamica: Calcular o numero de bytes necessários, multiplicando 1 pelo tamanho da variavel struckt
            // e utilizar malloc para reservar a quantidade na memoria, converter para o tipo de dado struckt(gladiador*)
            if (pos==0) { //se o contador for igual a zero, realizar a alocacao
                lista = (gladiador*) malloc (1*sizeof(gladiador));
                pos+=1;
                }
            // realloc: mudar o tamanho do espaço alocado na memoria, com tamanho (pos) atualizado
            else {
                pos+=1;
                lista = (gladiador*) realloc (lista, pos* sizeof(gladiador));
                }

            lista[pos-1] = c; //lista com a posicao do contador-1 eh atribuida a c


            break;

       case 2:
            atualizarGladiador (lista,pos);
            break;
       case 3:
            imprimeListaGladiador(lista,pos);
            break;
        case 4:
            BatalhaGladiador(lista, lista, pos);
            break;
        case 5:
             TentativaSorte(lista, pos);
             break;

       default:
            printf ("Opcao inexistente! Escolha entre [0]...[5]!\n");
            break;

            fread (&pos, sizeof(int),1,fp); // retorna o numero de unidades lidas
            fread (&lista, sizeof(gladiador), pos, fp);
            fwrite(&pos,sizeof(int),1,fp);  //retorna o número de itens escritos.
            fwrite(&lista, sizeof(gladiador),pos, fp);
            fclose(fp); //fechar /

      }

    }while(opcao != 0);
  return 0;
}

void imprimeLista(gladiador c) {
    int i;

    printf ("Nome: %s \n", c.nome);
    printf ("Forca: %d \n", c.forca);
    printf ("Resistencia: %d \n", c.resistencia);
    printf ("Agilidade: %d \n", c.agilidade);
    printf ("Altura: %f \n", c.altura);
    printf ("Peso: %f \n", c.peso);
    printf ("Numero do Registro: %d\n", c.id);

}


void imprimeListaGladiador(gladiador *lista, int tam) {
    int i;
    printf("Lista de Gladiadores encontrados = %d : \n", tam);
    for (i=0; i<tam; i++){
        imprimeLista(lista[i]);
    }
}

// funcao para alterar dados
void atualizarGladiador(gladiador *lista, int tam) {

    int id, i;
    int forca, resistencia, agilidade;
    float peso, altura;
    char nome[100];
    printf("Digite o numero de registro do gladiador: \n" );
    scanf("%d", &id);
    for (i=0;i<tam;i++){   //varre o vetor
        if (id == lista[i].id){            // verifica se o id digitado corresponde ao id do vetor
            setbuf(stdin, NULL);
            printf ("Forca do Gladiador: ");
            scanf ("%d",&forca);
            lista[i].forca = forca;
            printf ("Resistencia do Gladiador: ");
            scanf ("%d", &resistencia);
            lista[i].resistencia = resistencia;
            printf ("Agilidade do Gladiador: ");
            scanf ("%d", &agilidade);
            lista[i].agilidade = agilidade;
            printf ("Altura do Gladiador: ");
            scanf ("%f",&altura);
            lista[i].altura = altura;
            printf ("Peso do Gladiador: ");
            scanf ("%f",&peso);
            lista[i].peso = peso;
            setbuf(stdin, NULL);
            printf ("Nome do Gladiador: ");
            fgets (nome, 100, stdin);
            nome[strcspn(nome, "\n")] = 0;
            sprintf(lista[i].nome, "%s",  nome); // sprintf para passar o valor para dentro do vetor
            printf("Atualizado com sucesso!! \n");
        }
    else{
        printf("Id inexistente. \n");
    }

    }
}

//funcao para retornar o poder
float poder(gladiador *lista,int tam) {
    float power;
    int i;
    for (i=0; i<tam; i++) {
        power = (lista[i].forca) * (lista[i].peso) * (lista[i].resistencia) / (lista[i].altura) * (lista[i].agilidade);
    }
     return power;

}

void melhoria(gladiador *lista, int tam){

        lista[tam].forca *= 1 + 0.2; // ganha 20% de forca
        lista[tam].resistencia *= 1 + 0.2;
}

void dano(gladiador *lista, int tam){

         lista[tam].forca *= 1 - 0.1;  // recebe o valor do proprio numero multiplicado por 100%(1) menos a sua porcentagem (10/100)
         lista[tam].resistencia *= 1 - 0.1;
}

void BatalhaGladiador(gladiador *a, gladiador *b, int tam) {
    printf ("BATALHA DE GLADIADORES!! \n");
    int j;
    int i;
    float pa, pb;
    /*/ aqui e utilizado somente as posicoes 1 e 2, ja que o jogo eh limitado a 2 jogadres por vez,
    portanto a comparacao ocorre com os dois primeiros valores atribuidos a struckt /*/
    pa = poder(a,1); //ponteiro a, posicao 1 é atribuida a funcao poder
    pb = poder (b,2);

    // foi utilizado dois comandos for encadeados, já que cada um vai percorrer um ponteiro diferente, i para *a e j para *b
    // o comando i e j <1  sao para que a comparacao ocorra somente uma vez
    for (i=0;i<1;i++) {
        for (j=i+1;j<1;j++) //j e atribuido ao valor de i+1, neste caso eh 2 posicao (1)
           printf("Os valores de poderes sao: %f e %f", pa, pb);
           if (pa>pb){
            melhoria (a, 0); // argumentos: ponteiro a, posicao 1 (0)
            dano (b, 1);
            printf ("%s venceu %s !! \n", a[i].nome, b[j].nome);
           }


           else {
            dano(a, 0);
            melhoria(b, 1);
            printf ("%s venceu %s !! \n", b[j].nome, a[i].nome);
           }

    }



}
void TentativaSorte (gladiador *lista, int tam){
int i, num;
  printf("Tentativa da sorte: A dupla precisa tirar um numero maior que 50 para ganhar 20 %c de forca e menor que 50 para perder! \n", 37);

  printf("Gerando 1 valor aleatorio:\n\n");

  //srand(time(NULL)) objetiva inicializar o gerador de números aleatórios
 //om o valor da função time(NULL).

  srand(time(NULL));

  for (i=0; i <1;i++){
    num = rand() % 100;
    // gerando valores aleatórios na faixa de 0 a 100
    printf("%d \n", num);

  }
  for(i=0;i<tam;i++){
    if (num>50) {
        printf("Parabens!! Voce ganhou mais 20%c de forca. \n", 37);
        lista[i].forca *= 1 + 0.2; // ganha 20% de forca

    }
    else{

         printf("Ops. Nao foi dessa vez. Voce perdeu 20 %c de forca \n",37);
         lista[i].forca *= 1 - 0.2; // ganha 20% de forca
    }
  }

}

gladiador LerGladiador(gladiador *lista, int tam) {

    gladiador c;
    int j;

    setbuf(stdin, NULL);
    printf ("Forca do Gladiador: ");
    scanf ("%d",&c.forca);
    printf ("Resistencia do Gladiador: ");
    scanf ("%d",&c.resistencia);
    printf ("Agilidade do Gladiador: ");
    scanf ("%d", &c.agilidade);
    printf ("Altura do Gladiador: ");
    scanf ("%f",&c.altura);
    printf ("Peso do Gladiador: ");
    scanf ("%f",&c.peso);
    setbuf(stdin, NULL);
    printf ("Nome do Gladiador: ");
    fgets (c.nome, 100, stdin);
    c.nome[strcspn(c.nome, "\n")] = 0;
    printf ("Numero de registro do Gladiador: ");
    scanf("%d", &c.id);
    // verificar se o codigo cadastrado ja existe
     for (j=0;j<tam;j++)  {
         if (c.id == lista[j].id) {
              printf("Codigo ja cadastrado. O codigo sera recadastrado com o numero antecessor ao mesmo. \n");
              //se o codigo ja for cadastrado, recadastrar com um numero anterior ao mesmo.
               c.id = c.id -1;
         return c;
         }
     }


    return c;
}
