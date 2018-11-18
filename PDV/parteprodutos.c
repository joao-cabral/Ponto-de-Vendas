#include <stdio.h>
#include <stdlib.h>
#include<locale.h>
#include<string.h>
#include<ctype.h>
#include<locale.h>

struct Validade{
    int dia, mes, ano;
};
struct PRODUTOS{
    char codigo[20];
    char descricao[100];
    char marca[50];
    char modelo[50];
    char fornecedor[50];
    int quatidade;
    int vendido;
    int ativo;
    float valordevenda, valordecompra;
	struct Validade validade;
}produto, *pp;

void cadastroP(int tam){
    system("cls");

    pp = &produto;
    int aux1 = 0;
    char aux_codigo[20], aux_marca[50], aux_modelo[50];
    FILE *arq;
    int i;

    arq = fopen("produtos.txt","a+");
        if(arq == NULL){
            printf("ERRO!");
            exit(1);
        }else{

        for(i=0; i<tam; i++){
            fflush(stdin);
            system("cls");
            printf("\n\nDigite modelo do produto..:");
               gets(pp->modelo);
               strcpy(aux_modelo, pp->modelo);
            printf("\n\nDigite a marca do produto..:");
                gets(pp->marca);
                strcpy(aux_marca, pp->marca);
            printf("\n\nCodigo do produto..:");
                gets(pp->codigo);
                strcpy(aux_codigo, pp->codigo);

                do{
                    aux1 = 0;
                    rewind(arq);
                    while(!feof(arq)){
                        if(fread(&produto, sizeof(struct PRODUTOS), 1, arq) == 1){
                            if(strcmp(aux_codigo, pp->codigo) == 0){
                                if(pp->ativo == 1){
                                    aux1++;
                                }
                            }
                        }
                    }
                    if(aux1 == 1){
                        printf("\nInforme um novo código, pois esse já existe: ");
                            gets(pp->codigo);
                            strcpy(aux_codigo, pp->codigo);
                    }
                }while(aux1 != 0);

                strcpy(pp->marca , aux_marca);
                strcpy(pp->modelo, aux_modelo);
                strcpy(pp->codigo, aux_codigo);

            printf("\n\nDescrição do produto..:");
                gets(pp->descricao);

            printf("\n\nfornecedor..:");
                gets(pp->fornecedor);
            fflush(stdin);

            printf("\n\nquantidade..:");
                scanf("%d",&pp->quatidade);
            printf("\n\nvalor de compra..:");
                scanf("%f",&pp->valordecompra);
            printf("\n\nvalor de venda..:");
                scanf("%f",&pp->valordevenda);

            pp->vendido = 0;
            pp->ativo = 1;
            printf("\n");

        fwrite(&produto, sizeof(struct PRODUTOS), 1, arq);
        printf("\nProduto cadastrado com sucesso\n");
    }
    }
    fclose(arq);
    getch();
}

void consultarP(int tam){
    system("cls");
    pp = &produto;
    FILE *fp;
    char descricao[100];
    int aux = 0;

    fp = fopen("produtos.txt","r");
    if(fp == NULL){
        printf("Erro!");
        exit(1);
    }

    fflush(stdin);
    printf("Informe a descrição do produto: ");
    gets(descricao);

    while(!feof(fp)){
        while(fread(&produto, sizeof(struct PRODUTOS),1, fp) == 1){
            pp = &produto;
            if(strcasecmp(descricao, pp->descricao) == 0){
                if(pp->ativo == 1){
                    printf("\n\tINFORMAÇOES DO PRODUTO\n");
                    printf("\nModelo: %s ", pp->modelo);
                    printf("\nMarca: %s", pp->marca);
                    printf("\nDescrição: %s",pp->descricao);
                    printf("\nCodigo: %s",pp->codigo);
                    printf("\nQuantidade: %d",pp->quatidade);
                    printf("\nValor de Compra: R$%.2f",pp->valordecompra);
                    printf("\nValor de Venda: R$%.2f",pp->valordevenda);
                    printf("\n-------------------------------------------------------------\n");
                    aux = 1;
                }
            }
        }
    }
    if(aux != 1){
        printf("\nProduto não encontrado!\n");
    }

fclose(fp);
getch();
}

void excluirP(){
    system("cls");
    pp = &produto;
    FILE *fp;
    int pos = 0, aux = 0;
    char CODIGO[20], opcao;
    fp = fopen("produtos.txt","r+");

    if(fp == NULL){
        printf("Não entrou no arquivo\n");
        exit(1);
    }else{
        fflush(stdin);
        printf("Informe o codigo para excluir o produto: ");
        gets(CODIGO);
        while(!feof(fp)){
            if(fread(&produto, sizeof(struct PRODUTOS),1, fp) == 1){
                if(strcmp(CODIGO, pp->codigo) == 0){
                    if(pp->ativo == 1){
                        printf("\n\tINFORMAÇOES DO PRODUTO\n");
                        printf("\nModelo: %s ", pp->modelo);
                        printf("\nMarca: %s", pp->marca);
                        printf("\nDescrição: %s",pp->descricao);
                        printf("\nCodigo: %s",pp->codigo);
                        printf("\nQuantidade: %d",pp->quatidade);
                        printf("\nValor de Compra: R$%.2f",pp->valordecompra);
                        printf("\nValor de Venda: R$%.2f",pp->valordevenda);

                        }
                        aux = pos + 1;
                        getch();
                        break;
                    }
                }
                pos++;
            }
    }
    if(aux == 0){
        printf("\nProduto não encontrado\n");
        getchar();
    }else{
        do{
            system("cls");
            fflush(stdin);
            printf("\n\nDeseja mesmo exluir esse produto (s\\n)?\n");
            scanf("%c", &opcao);
            opcao = tolower(opcao);
            if(opcao == 's'){
                pp->ativo = 0;
                fseek(fp, sizeof(struct PRODUTOS)*(aux-1), SEEK_SET);
                fwrite(&produto, sizeof(struct PRODUTOS), 1, fp);
                printf("Produto excluido com sucesso:");
            }else if(opcao == 'n'){
                printf("\nOkay, aperte qualquer tecla para voltar ao menu\n");
            }else if(opcao != 'n' && opcao != 's'){
                printf("\nOpcão Invalida\n");
                getch();
            }
        }while(opcao != 'n' && opcao != 's');
    fclose(fp);
    getch();
    }
}

void alterarP(){
    system("cls");
    char decri[50], opcao;
    int aux = 0, pos = 0;

    pp = &produto;
    FILE *fp;

    fp = fopen("produtos.txt","r+");
    if(fp == NULL){
        printf("Erro!");
        exit(1);
    }

    fflush(stdin);
    printf("Informe a descrição do produto que deseja alterar os dados:");
        gets(decri);

    while(!feof(fp)){
        if(fread(&produto, sizeof(struct PRODUTOS),1, fp) == 1){
            if(strcmp(decri, pp->descricao) == 0){
                if(pp->ativo == 1){
                  printf("\n\tINFORMAÇOES DO PRODUTO\n");
                    printf("\nModelo: %s ", pp->modelo);
                    printf("\nMarca: %s", pp->marca);
                    printf("\nDescrição: %s",pp->descricao);
                    printf("\nCodigo: %s",pp->codigo);
                    printf("\nQuantidade: %d",pp->quatidade);
                    printf("\nValor de Compra: R$%.2f",pp->valordecompra);
                    printf("\nValor de Venda: R$%.2f",pp->valordevenda);
                    aux = pos + 1;
                    getch();
                break;
                }
            }
        }
    pos++;
    }
    if(aux == 0){
        printf("\nProduto não encontrado\n");
    }else{
        do{
        system("cls");
        fflush(stdin);
        printf("\nDeseja mesmo alterar dados (s\\n)?\n");
        scanf("%c", &opcao);
        opcao = tolower(opcao);
        if(opcao == 's'){
            fflush(stdin);
            printf("\nInforme o modelo: ");
            gets(pp->modelo);
            printf("\nInforme o marca: ");
                gets(pp->marca);
            fflush(stdin);
            printf("\nInforme o fornecedor: ");
                gets(pp->fornecedor);
            printf("\nInforme a descrição: ");
                scanf("%d", &pp->descricao);
            fflush(stdin);
            printf("\nInforme o código: ");
            	scanf("%s",&pp->codigo);
            fflush(stdin);
            printf("\nquantidade: ");
                scanf("%d",&pp->quatidade);
            printf("\nValor de compra: ");
                scanf("%f",&pp->valordecompra);
            printf("\nValor de venda: ");
                scanf("%f",&pp->valordevenda);
            printf("\n");

            fseek(fp, sizeof(struct PRODUTOS)*(aux-1), SEEK_SET);
            fwrite(&produto, sizeof(struct PRODUTOS), 1, fp);

            printf("\nProduto alterado com sucesso\n");
        }else if(opcao == 'n'){
            printf("\nOkay, aperte qualquer tecla para voltar ao menu\n");
        }else if(opcao != 'n' && opcao != 's'){
                printf("\nOpcão Invalida\n");
                getch();
            }
        }while(opcao != 'n' && opcao != 's');
    }
    fclose(fp);
    getch();
}
