#include <stdio.h>
#include <stdlib.h>
#include<locale.h>
#include<string.h>
#include<ctype.h>
#include<locale.h>

struct Validade_p{
    int dia, mes, ano;
};
struct PRODUTOS_p{
    char codigo[20];
    char descricao[100];
    char marca[50];
    char modelo[50];
    char fornecedor[50];
    int quatidade;
    int vendido;
    int ativo;
    float valordevenda, valordecompra;
	struct Validade_p validade;
}produto_p, *p_p;

struct Nascimento1{
	int dia, mes, ano;
};
struct Endereco1{
	 char rua[50], bairro[50], cidade[50];
	 int numero;
	 char uf[3];
};
struct Clientes1{
	char nome[50];
	char cpf[20];
	int ativo;
	struct Nascimento1 nascimento;
	struct Endereco1 endereco;
}clientess, *p3;

struct Lucro{
    float lucro_bruto;
}lucro, *pl;

void realizar_venda(){
    system("cls");
    char nome[50], cpf[20], codigo[20];
    int aux = 0, pos =0, ns, quantidade;
    p3 = &clientess;
    p_p = &produto_p;
    pl = &lucro;
    FILE *fp, *fp_p, *fp_l;

    fp = fopen("trabalho.txt","r+");
    fp_p = fopen("produtos.txt","r+");
    fp_l = fopen("lucro_bruto.txt","a+");

    if(fp == NULL){
        printf("Erro1!");
        exit(1);
    }if(fp_p == NULL){
        printf("Erro2!");
        exit(1);
    }if(fp_l == NULL){
        printf("Erro3!");
        exit(1);
    }

    fflush(stdin);
    printf("Informe o CPF para realizar compra: ");
        gets(cpf);

    fflush(stdin);
    while(!feof(fp)){
        if(fread(&clientess, sizeof(struct Clientes1),1, fp) == 1){
            if(strcmp(cpf, p3->cpf) == 0){
                if(p3->ativo == 1){
                    printf("\nNome: %s ", p3->nome);
                    printf("\nCPF: %s", p3->cpf);
                    aux = pos + 1;
                    ns = 1;
                    printf("\n\nPode realizar a compra!\n");
                    getch();
                    break;
                }
            }
        }
    pos++;
    }
    if(aux == 0){
        printf("\nCliente não encontrado, precisa realizar o cadastro!\n");
        getchar();
    }else if(ns == 1){
        system("cls");
        printf("ESCOLHA UM PRODUTO:\n\n");
        while(fread(&produto_p, sizeof(struct PRODUTOS_p),1, fp_p) == 1){
            p_p = &produto_p;
            if(p_p->ativo == 1){
                printf("\n\tPRODUTO\n");
                printf("\nModelo: %s ", p_p->modelo);
                printf("\nMarca: %s", p_p->marca);
                printf("\nDescrição: %s", p_p->descricao);
                printf("\nCodigo: %s", p_p->codigo);
                printf("\nValor de Venda: R$%.2f", p_p->valordevenda);
                printf("\nQuantidade: %d",p_p->quatidade);
                printf("\n-------------------------------------------------------------\n");
            }
        }

        pos = 0;
        aux = 0;
        ns = 0;

        fflush(stdin);
        printf("Informe o codigo do produto que você deseja: ");
            gets(codigo);

        rewind(fp_p);
        while(!feof(fp_p)){
            if(fread(&produto_p, sizeof(struct PRODUTOS_p),1, fp_p) == 1){
                if(strcmp(codigo, p_p->codigo) == 0){
                    if(p_p->ativo == 1){
                        printf("\nModelo: %s ", p_p->modelo);
                        printf("\nMarca: %s", p_p->marca);
                        printf("\nDescrição: %s", p_p->descricao);
                        printf("\nCodigo: %s", p_p->codigo);
                        printf("\nValor de Venda: R$%.2f", p_p->valordevenda);
                        ns = 1;
                        aux = pos + 1;
                        getch();
                        break;
                        }
                    }
            }
        pos++;
        }
        printf("%d", aux);
        if(aux == 0){
            printf("\nProduto não encontrado!\n");
            getch();
        }else if(ns == 1){
            fflush(stdin);
            printf("\n\nInforme a quantidade de produto que você deseja comprar: ");
                scanf("%d", &quantidade);
            printf("Informe a garantia do produto: dd/mm/aa\n");
            printf("Dia: ");
                scanf("%d", &p_p->validade.dia);
            printf("Mês: ");
                scanf("%d", &p_p->validade.mes);
            printf("Ano: ");
                scanf("%d", &p_p->validade.ano);

            fseek(fp_p, sizeof(struct PRODUTOS_p)*(aux-1), SEEK_SET);

            if(quantidade > 0 && quantidade <= p_p->quatidade){
                pl->lucro_bruto = (quantidade * p_p->valordevenda) - (quantidade * p_p->valordecompra);
                p_p->quatidade = p_p->quatidade - quantidade;
                p_p->vendido = 1;
                p_p->ativo = 1;

                fwrite(&produto_p, sizeof(struct PRODUTOS_p), 1, fp_p);
                fwrite(&lucro, sizeof(struct Lucro), 1, fp_l);
                printf("\nCompra realizada com sucesso!\n");
            }else{
                system("cls");
                printf("\nQUANTIDADE DIGITADA NÃO CORRESPONDE A QUANTIDADE EM ESTOQUE!\n");
            }
        }
    }

fclose(fp);
fclose(fp_p);
fclose(fp_l);
getch();
}

void estoque(){
    system("cls");
    p_p = &produto_p;
    FILE *fp_p;
    fp_p = fopen("produtos.txt","r");
    if(fp_p == NULL){
        printf("Erro!");
        exit(1);
    }

    while(fread(&produto_p, sizeof(struct PRODUTOS_p),1, fp_p) == 1){
        p_p = &produto_p;
        if(p_p->ativo == 1){
            printf("\n\tESTOQUE\n");
            printf("\nModelo: %s ", p_p->modelo);
            printf("\nMarca: %s", p_p->marca);
            printf("\nCodigo: %s",p_p->codigo);
            printf("\nValor de Venda: R$%.2f",p_p->valordevenda);
            printf("\nQuantidade: %d", p_p->quatidade);
            printf("\n-------------------------------------------------------------\n");
        }
    }

fclose(fp_p);
getch();

}

void lpvcl(){
    system("cls");
    float soma = 0;
    p_p = &produto_p;
    pl = &lucro;
    FILE *fp_p, *fp_l;

    fp_p = fopen("produtos.txt","r+");
    fp_l = fopen("lucro_bruto.txt","r+");
    if(fp_p == NULL){
        printf("Erro!");
        exit(1);
    }if(fp_l == NULL){
        printf("Erro!");
        exit(1);
    }

    while(fread(&lucro, sizeof(struct Lucro),1, fp_l) == 1){
        pl = &lucro;
        soma = soma + pl->lucro_bruto;

    }

    while(fread(&produto_p, sizeof(struct PRODUTOS_p),1, fp_p) == 1){
        p_p = &produto_p;
        if(p_p->ativo == 1 && p_p->vendido == 1){
            printf("\n\tPRODUTO VENDIDO\n");
            printf("\nModelo: %s ", p_p->modelo);
            printf("\nMarca: %s", p_p->marca);
            printf("\nDescrição: %s", p_p->descricao);
            printf("\nCodigo: %s", p_p->codigo);
            printf("\nValor de Venda: R$%.2f", p_p->valordevenda);
            printf("\nGarantia ate %d/%d/%d", p_p->validade.dia, p_p->validade.mes, p_p->validade.ano);
            printf("\n-------------------------------------------------------------\n");
        }
    }

    printf("\n\nLUCRO BRUTO = %.2f", soma);


    fclose(fp_p);
    fclose(fp_l);
    getch();
}
