#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MaxLivros 800

typedef enum{
    TelaSaida = -1,
    TelaIni ,
    TelaCad ,
    TelaDesCad,  
    TelaLista,
} Telas;

typedef struct{
    char nome[128];
    char ano[64];
} Livro;

typedef struct{
    Telas menu;
    int LivrosTotais;
    Livro livros[MaxLivros];
}OrganizadorLivro;

int main()
{
   OrganizadorLivro organizador;
    memset(&organizador, 0x0, sizeof(organizador)); 
    

    organizador.menu = TelaIni;

    FILE * memoria = fopen("livros.bin","rb");
    if(memoria == NULL)
    {printf("Erro ao abrir arquivo de memoria do organizador\n");
     printf("Você deve criar o arquivo 'livros.bin' na primeira execução\n");
     return 1;
    }
    
    size_t lidos = fread(organizador.livros, sizeof(Livro),MaxLivros,memoria);
    printf("Lidos %zd livros\n", lidos);
    organizador.LivrosTotais = (int)lidos;
    fclose(memoria);
    
    
    
    while (organizador.menu != TelaSaida){
        switch (organizador.menu){
            
            case TelaIni:
            {
                printf("----------------------------------------\n");
                printf("\tOrganizador de Livros\n");
                printf("----------------------------------------\n");
                int opcao = -1;
                do
                {
                    printf("Escolha uma opcão:\n");
                    printf("\tdigite 1 para cadastrar livro: \n");
                    printf("\tdigite 2 para remover livro: \n");
                    printf("\tdigite 3 para listar todos os livros: \n");
                    printf("\tdigite 0 para sair do programa: \n");
                    scanf("%d", &opcao);
                   int c = 0;
                   while((c = getchar()) != '\n' && c != EOF) {}
               }while (opcao < 0 || opcao > 3);
            
                
                if (opcao == 0){
                    organizador.menu = TelaSaida;
                }
                
                if (opcao == 1){
                    organizador.menu = TelaCad;
                    if (organizador.LivrosTotais >= MaxLivros){
                        printf("\tOrganizador está lotado, não é possivel adiconar novos livros");
                        organizador.menu = TelaIni;
                    }
                }
                
                if (opcao == 2){
                    organizador.menu = TelaDesCad;
                    if (organizador.LivrosTotais == 0){
                        printf("\tNão há nenhum livro cadastrado para remover\n");
                        organizador.menu = TelaIni;
                    }
                }
                
                if (opcao ==3){
                    organizador.menu = TelaLista;
                    if (organizador.LivrosTotais == 0){
                        printf("\tOrganizador não tem nenhum contato para listar\n");
                        organizador.menu = TelaIni;
                    }
                }
                
            }
            break;
            
            case TelaCad:
            {
            printf("----------------------------------------\n");
            printf("\tTela de Cadastro:\n");
            printf("----------------------------------------\n");
            Livro novo;
            char opcao = 's';
           
            
            
            do
            {memset(&novo, 0x0, sizeof(novo));
            printf("Digite um novo nome para o livro: \n");
            fgets(novo.nome, 128, stdin);
            int id = 0;
            while(novo.nome[id] != '\0' && novo.nome[id] != '\n'){
              id++;
                
            }
              novo.nome[id] = '\0';
              printf("Digite o Ano que o livro foi lido:\n");
              fgets(novo.ano, 64, stdin);
              id = 0;
              while(novo.ano[id] != '\0' && novo.ano[id] != '\n' )
             { id++;
             }
              novo.ano[id] = '\0';
              printf("Tem certeza que quer adicionar este livro? [s/n]\n");
              opcao = getchar();
              int c = 0;
              while ((c = getchar()) != '\n' && c != EOF) { }
            } while (opcao == 'n'|| opcao == 'N');
            organizador.livros[organizador.LivrosTotais] = novo;
            organizador.LivrosTotais++;
            memoria = fopen("livros.bin", "w+b");
            if (memoria == NULL)
            {  printf("Erro ao abrir livros.bin \n");
            return 0;
            }
            size_t salvos = fwrite(organizador.livros, sizeof(Livro),
            organizador.LivrosTotais, memoria);
            if (salvos != (size_t)organizador.LivrosTotais)
            {printf("Erro ao salvar livro na memoria livros.bin \n");
            return 1;
            }fclose(memoria);
            
                organizador.menu = TelaIni;
            }
            break;
            
           case TelaDesCad:
{
    printf("----------------------------------------\n");
    printf("\tTela de Descad\n");
    printf("----------------------------------------\n");
    int livroRemover = -1;
    do
    {
        printf("Digite o número do livro que deseja remover de 0 até 800: \n");
        for (int i = 0; i < organizador.LivrosTotais; i++)
   {
            printf("%d %s\n", i, organizador.livros[i].nome);
        }
        scanf("%d", &livroRemover);
        int c = 0;
        while((c = getchar()) != '\n' && c != EOF) {}
    } while (livroRemover < 0 || livroRemover >= organizador.LivrosTotais);
    
  
    int num = livroRemover;
    for (int i = num; i < organizador.LivrosTotais - 1; i++)
    {
        organizador.livros[i] = organizador.livros[i + 1];
    }
    organizador.LivrosTotais--;
    
 
    FILE *memoria = fopen("livros.bin", "wb");
    if (memoria == NULL)
    {
        printf("Erro ao abrir arquivo de memoria do organizador\n");
        return 1;
    }
    size_t salvos = fwrite(organizador.livros, sizeof(Livro), organizador.LivrosTotais, memoria);
    printf("Erro ao salvar livros na memoria");
    fclose(memoria);
    
    organizador.menu = TelaIni;
}
break;
            
            case TelaLista:
            {printf("----------------------------------------\n");
             printf("\tListando Livros\n");
             printf("----------------------------------------\n");
             int i;
             for(i = 0; i < organizador.LivrosTotais; i++)
             {printf("Livro %d\n", i);
             printf("\tLivro: %s\n", organizador.livros[i].nome);
             printf("\tAno lido: %s\n", organizador.livros[i].ano);
             printf("----------------------------------------\n");
             }
            
                organizador.menu = TelaIni;
            }
            break;
            
            default:
                organizador.menu = TelaIni;
                break;
        }
    }
    return 0;
}
