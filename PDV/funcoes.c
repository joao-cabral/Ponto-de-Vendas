#include <stdio.h>
#include <stdlib.h>
#include<locale.h>
#include<string.h>
#include<ctype.h>

struct Nascimento{
	int dia, mes, ano;
};
struct Endereco{
	 char rua[50], bairro[50], cidade[50];
	 int numero;
	 char uf[3];
};
struct Clientes{
	char nome[50];
	char cpf[20];
	int ativo;
	struct Nascimento nascimento;
	struct Endereco endereco;
}clientes, *p;

void cadastro(int tam){
	p = &clientes;
	int aux1;
	char aux_cpf[20], aux_nome[50];

    FILE *fp;
    fp = fopen("trabalho.txt","a+");
    if(fp == NULL){
        printf("Erro!");
        exit(1);
    }

    int i;

    for(i=0; i<tam; i++){
        system("cls");
        printf("\t\t\tPREENCHER DADOS:");
        fflush(stdin);
        printf("\nInforme o nome: ");
            gets(p->nome);
            strcpy(aux_nome, p->nome);
        printf("\nInforme o CPF: ");
            gets(p->cpf);
            strcpy(aux_cpf, p->cpf);

            do{
                aux1 = 0;
                rewind(fp);
                while(!feof(fp)){
                    if(fread(&clientes, sizeof(struct Clientes), 1, fp) == 1){
                        if(strcmp(aux_cpf, p->cpf) == 0){
                            if(p->ativo == 1){
                                aux1++;
                                }
                            }
                        }
                    }
                fflush(stdin);
                if(aux1 == 1){
                    printf("\nInforme um novo CPF, pois esse já existe: ");
                        gets(p->cpf);
                        strcpy(aux_cpf, p->cpf);
                    }
                }while(aux1 != 0);

                strcpy(p->nome, aux_nome);
                strcpy(p->cpf, aux_cpf);

        printf("\nInforme a data de nascimento:");
        printf("\nDia: ");
            scanf("%d", &p->nascimento.dia);
        printf("\nMes: ");
            scanf("%d", &p->nascimento.mes);
        printf("\nAno: ");
            scanf("%d", &p->nascimento.ano);
        fflush(stdin);
        printf("\nInforme o endereço: ");
        printf("\nRua: ");
            gets(p->endereco.rua);
        printf("\nNumero: ");
            scanf("%d", &p->endereco.numero);
        fflush(stdin);
        printf("\nBairro: ");
            gets(p->endereco.bairro);
        printf("\nCidade: ");
            gets(p->endereco.cidade);
        printf("\nUF: ");
            gets(p->endereco.uf);
            p->ativo = 1;
        printf("\n");

        fwrite(&clientes, sizeof(struct Clientes), 1, fp);
        printf("\nCliente cadastrado com sucesso\n");
    }
    fclose(fp);
    getch();
}

void consultar(int tam){
    system("cls");
    FILE *fp;

    fp = fopen("trabalho.txt","r");
    if(fp == NULL){
        printf("Erro!");
        exit(1);
    }

    while(fread(&clientes, sizeof(struct Clientes),1, fp) == 1){
        p = &clientes;
        if(p->ativo == 1){
            printf("\n\tINFORMAÇOES DO CLIENTE\n");
            printf("\nNome: %s ", p->nome);
            printf("\nCPF: %s", p->cpf);
            printf("\nData de nasimento: %d/%d/%d", p->nascimento.dia, p->nascimento.mes, p->nascimento.ano);
            printf("\n\n\tENDEREÇO\n");
            printf("\nRua: %s", p->endereco.rua);
            printf("\nNumero: %d", p->endereco.numero);
            printf("\nBairro: %s", p->endereco.bairro);
            printf("\nCidade: %s", p->endereco.cidade);
            printf("\nUF: %s\n", p->endereco.uf);
            printf("\n-------------------------------------------------------------\n");
        }
    }

fclose(fp);
getch();
}

void excluir(){
    system("cls");
    char cpf[20], opcao;
    int pos = 0, aux = 0;

    p = &clientes;
    FILE *fp;
    fp = fopen("trabalho.txt","r+");
    if(fp == NULL){
        printf("Erro!");
        exit(1);
    }

    if(fp == NULL){
        printf("Não entrou no arquivo\n");
        getch();
    }else{

        fflush(stdin);
        printf("Informe o CPF para excluir o cadastro: ");
        gets(cpf);

        while(!feof(fp)){
            if(fread(&clientes, sizeof(struct Clientes),1, fp) == 1){
                if(strcmp(cpf, p->cpf) == 0){
                    if(p->ativo == 1){
                        printf("\n\tINFORMAÇOES DO CLIENTE\n");
                        printf("\nNome: %s ", p->nome);
                        printf("\nCPF: %s", p->cpf);
                        printf("\nData de nasimento: %d/%d/%d", p->nascimento.dia, p->nascimento.mes, p->nascimento.ano);
                        printf("\n\n\tENDEREÇO\n");
                        printf("\nRua: %s", p->endereco.rua);
                        printf("\nNumero: %d", p->endereco.numero);
                        printf("\nBairro: %s", p->endereco.bairro);
                        printf("\nCidade: %s", p->endereco.cidade);
                        printf("\nUF: %s\n", p->endereco.uf);
                        aux = pos + 1;
                        getch();
                        break;
                    }
                }
            }
    pos++;
    }
    if(aux == 0){
        printf("\nCliente não encontrado\n");
        getchar();
    }else{
        do{
            system("cls");
            fflush(stdin);
            printf("\n\nDeseja mesmo exluir esse cliente (s\\n)?\n");
            scanf("%c", &opcao);
            opcao = tolower(opcao);
            if(opcao == 's'){
                p->ativo = 0;
                fseek(fp, sizeof(struct Clientes)*(aux-1), SEEK_SET);
                fwrite(&clientes, sizeof(struct Clientes), 1, fp);
                printf("Cliente excluido com sucesso:");
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
}

void alterar(){
    system("cls");
    char nome[50], opcao;
    int aux = 0, pos = 0;

    p = &clientes;
    FILE *fp;

    fp = fopen("trabalho.txt","r+");
    if(fp == NULL){
        printf("Erro!");
        exit(1);
    }

    fflush(stdin);
    printf("Informe o nome do cliente que deseja alterar os dados:");
        gets(nome);

    while(!feof(fp)){
        if(fread(&clientes, sizeof(struct Clientes),1, fp) == 1){
            if(strcmp(nome, p->nome) == 0){
                if(p->ativo == 1){
                    printf("\n\tINFORMAÇOES DO CLIENTE\n");
                    printf("\nNome: %s ", p->nome);
                    printf("\nCPF: %s", p->cpf);
                    printf("\nData de nasimento: %d/%d/%d", p->nascimento.dia, p->nascimento.mes, p->nascimento.ano);
                    printf("\n\n\tENDEREÇO\n");
                    printf("\nRua: %s", p->endereco.rua);
                    printf("\nNumero: %d", p->endereco.numero);
                    printf("\nBairro: %s", p->endereco.bairro);
                    printf("\nCidade: %s", p->endereco.cidade);
                    printf("\nUF: %s\n", p->endereco.uf);
                    aux = pos + 1;
                    getch();
                break;
                }
            }
        }
    pos++;
    }
    if(aux == 0){
        printf("\nCliente não encontrado\n");
    }else{
        do{
        system("cls");
        fflush(stdin);
        printf("\nDeseja mesmo alterar dados (s\\n)?\n");
        scanf("%c", &opcao);
        opcao = tolower(opcao);
        if(opcao == 's'){
            fflush(stdin);
            printf("\nInforme o nome: ");
            gets(p->nome);
            printf("\nInforme o CPF: ");
                gets(p->cpf);
            printf("\nInforme a data de nascimento:");
            printf("\nDia: ");
                scanf("%d", &p->nascimento.dia);
            printf("\nMes: ");
                scanf("%d", &p->nascimento.mes);
            printf("\nAno: ");
                scanf("%d", &p->nascimento.ano);
            fflush(stdin);
            printf("\nInforme o endereço: ");
            printf("\nRua: ");
                gets(p->endereco.rua);
            printf("\nNumero: ");
                scanf("%d", &p->endereco.numero);
            fflush(stdin);
            printf("\nBairro: ");
                gets(p->endereco.bairro);
            printf("\nCidade: ");
                gets(p->endereco.cidade);
            printf("\nUF: ");
                gets(p->endereco.uf);
            printf("\n");

            fseek(fp, sizeof(struct Clientes)*(aux-1), SEEK_SET);
            fwrite(&clientes, sizeof(struct Clientes), 1, fp);
            printf("\nCliente alterado com sucesso\n");
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
