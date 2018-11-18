#include <stdio.h>
#include <stdlib.h>
#include<locale.h>
#include<string.h>
#include<conio.c>
#include<windows.h>
#include<ctype.h>
#include "funcoes.c"
#include "parteprodutos.c"
#include "RCL.c"

int main(){

    int cont=0;
	char vet[30]="";

	while(cont <= 100){
		gotoxy(5,10);
		printf("Carregando...\n");
		gotoxy(5,12);
		strcat(vet,"\xDB");
		printf("%s %d%%",vet, cont );
		Sleep(50);
		if(cont!=100)
		system("cls");
		cont+=4;

	}


	getch();

	setlocale(LC_ALL, "PTB");

    int opcao, tam = 1;
    char resp;
    do{
        fflush(stdin);
        opcao = 66;
        system("cls");
        printf("\n  1 - Cadastrar Clientes\t\t\t5 - Cadastrar produto");
        printf("\n  2 - Consultar Clientes Cadastrados\t\t6 - Consultar produto por descrição");
        printf("\n  3 - Excluir Cliente por CPF\t\t\t7 - Excluir Produto por código");
        printf("\n  4 - Alterar dados de Cliente\t\t\t8 - Alterar dados do produto");
        printf("\n\n");
        printf("\t\t\t\t9 - Realizar vendas");
        printf("\n\t\t\t\t10 - Consultar Estoque");
        printf("\n\t\t\t\t11 - Lista produto vendidos com lucro");
        printf("\n\t\t\t\t0 - SAIR");
        printf("\n\n");


            printf("Digite uma opção: ");
                scanf("%d", &opcao);

            switch(opcao){
                case 0:
                    printf("Volte Sempre\n"); getch(); break;
                case 1:
                    cadastro(tam); break;
                case 2:
                    consultar(tam); break;
                case 3:
                    excluir(); break;
                case 4:
                    alterar(); break;
                case 5:
                    cadastroP(tam); break;
                case 6:
                    consultarP(tam); break;
                case 7:
                    excluirP(); break;
                case 8:
                    alterarP(); break;
                case 9:
                    realizar_venda(); break;
                case 10:
                    estoque(); break;
                case 11:
                    lpvcl(); break;
                default:
                    printf("\nNumero invalido\n");
                    getch();
            }
        }while(opcao != 0);

        getch();

return 0;
}
