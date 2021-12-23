#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

struct cadastro{//Estrutura basica para o cadastro
    char nome[100];
    char cpf[15];
    char tel[15];
    char cep[9];
    char end[200]; //(rua, num, bairro, cidade, estado)
    char email[30];
    char dd[15];
    char cmd[100];
}cad;

struct nascimento{//Estrutura para data de nascimento
    char dia[3];
    char mes[3];
    char ano[5];
}dn;

//Prototipo das funcoes
void cadastrar();
void salvar();
void send(sendid);

int main(){

    //login: admin
    //senha: admin

    setlocale(LC_ALL, "Portuguese");//Regras da Lingua Portuguesa

    FILE *fp;
    fp=fopen("Cadastro.txt","a");//Arquivo para armazenar os dados do cadastro

    FILE *send;
    send=fopen("Secretaria.txt","a");//Arquivo para armazenar os dados de envio a Secretaria de Saude

    char login[6]="admin";
    char senha[6]="admin";
    char login1[6];
    char senha1[6];
    int opc;

    printf("   ===================================== \n");
    printf("   ==== BEM VINDO! REALIZE O LOGIN. ==== \n");
    printf("   ===================================== \n\n");
    printf("Login: ");
    scanf("%s",&login1);
    printf("Senha: ");
    scanf("%s",&senha1);

    if(strcmp(login,login1)==0 && strcmp(senha,senha1)==0){//Validacao do login e senha com a funcao "strcmp"
        printf("\n!!! Logado com sucesso !!!\n");
    }
    else{
        printf("\nATEN��O |Login e senha inv�lidos. Tente outra vez.| ATEN��O\n");
        return main();
    }

    do{
        printf("\nEscolha uma op��o para prosseguir!\n");
        printf("1 - Cadastrar Paciente\n2 - Sair do Sistema\n");
        fflush(stdin);
        scanf("%d",&opc);

        switch(opc){

            case 1:
                cadastrar();
                break;

            case 2:
                printf(" \n\n::::: SISTEMA ENCERRADO :::::\n\n");
                exit(1);
                break;

            default:
                printf("Op��o Inv�lida!\n");
                break;
        }
    }while(opc!=2);

return 0;
}

//Funcao criada para realizacao do cadastro
void cadastrar(){

    int lmt;
    int oCmd;
    int anoid;
    int idade;

    printf(" \n>>> Insira abaixo os dados do Paciente. <<< \n");

    printf("Nome do paciente: \n");
    fflush(stdin);
    scanf("%[^\n]s",&cad.nome);

    printf("CPF (somente n�meros): \n");
    fflush(stdin);
    scanf("%[^\n]s",&cad.cpf);

    printf("Telefone (somente n�meros): \n");
    fflush(stdin);
    scanf("%[^\n]s",&cad.tel);

    printf("CEP (Somente oito d�gitos): \n");
    fflush(stdin);
    scanf("%[^\n]s",&cad.cep);

    lmt=strlen(cad.cep);//Variavel "lmt" recebe a quantidade de caracteres inseridas pelo usuario e valida se esta excendendo
    if(lmt>8){
        printf("\nATEN��O |Quantidade de caracteres do campo CEP excedida. Tente outra vez.| ATEN��O \n");
        exit(1);
    }

    printf("Endere�o - Rua, N�mero, Bairro, Cidade e Estado: \n");
    fflush(stdin);
    scanf("%[^\n]s",&cad.end);

    printf("Data de Nascimento: \n");
    printf("DD MM AAAA (separe com espa�os): \n");
    fflush(stdin);
    scanf("%s %s %s",&dn.dia,&dn.mes,&dn.ano);

    lmt=strlen(dn.ano);//Variavel "lmt" recebe a quantidade de caracteres inseridas pelo usuario e valida se esta excendendo
    if(lmt>4){
        printf("\nATEN��O |Quantidade de caracteres do campo ANO excedida. Tente outra vez.| ATEN��O \n");
        exit(1);
    }

    printf("E-mail: \n");
    fflush(stdin);
    scanf("%[^\n]s",&cad.email);

    printf("Data do Diagn�stico (separe com barra '/'): \nDD/MM/AAAA\n");
    fflush(stdin);
    scanf("%[^\n]s",&cad.dd);

    printf("Possui alguma comorbidade? Escolha uma op��o!\n[1] - Sim\n[2] - N�o\n");
    fflush(stdin);
    scanf("%d",&oCmd);

    if(oCmd==1){
        printf("Qual(is)? Especifique: \n");
        fflush(stdin);
        scanf("%[^\n]s",&cad.cmd);

        salvar();
        printf(">>> Cadastro finalizado. <<< \n");

        anoid=atoi(dn.ano);//Funcao "atoi" utilizada para receber a string e transformar em inteiro
        idade=2021-anoid;//Operacao matem�tica para que a vari�vel "idade" receba a idade do paciente em anos

        if(oCmd==1 && idade>65){//Valida se esta nas condicoes de Grupo de Risco e ja realiza envio para a Secretaria de Saude

            printf("\n\nATEN��O |O paciente %s faz parte do Grupo de Risco| ATEN��O \n\n",&cad.nome);
            printf("%s tem %d Anos e possui: %s\n",&cad.nome,idade,&cad.cmd);
            printf("\n>>> Paciente do Grupo de Risco deve ter o cadastro enviado para a Secretaria de Sa�de. <<<\n");
            send(idade);
        }
    }
}

void salvar(){

    FILE *fp;

    fp=fopen("Cadastro.txt","a");

    if(fp==NULL){
        printf("ATEN��O |Erro ao Salvar os dados| ATEN��O\n");
        exit(1);
    }
    else{
    fprintf(fp,"Nome: %s\n",&cad.nome);
    fprintf(fp,"CPF: %s\n",&cad.cpf);
    fprintf(fp,"Telefone: %s\n",&cad.tel);
    fprintf(fp,"CEP: %s\n",&cad.cep);
    fprintf(fp,"Endere�o: %s\n",&cad.end);
    fprintf(fp,"Data de Nascimento: %s/%s/%s\n",&dn.dia,&dn.mes,&dn.ano);
    fprintf(fp,"E-mail: %s\n",&cad.email);
    fprintf(fp,"Data do Diagn�stico: %s\n",&cad.dd);
    fprintf(fp,"Comorbidade: %s\n\n\n",&cad.cmd);

    printf(" \n!!! Cadastro salvo com sucesso !!! \n\n");
    }

    fclose(fp);
}

void send(int id){

    FILE *send;

    send=fopen("Secretaria.txt","a");

    if(send==NULL){
        printf("ATEN��O |Erro ao enviar cadastro| ATEN��O\n");
        exit(1);
    }
    else{
    fprintf(send,"CEP: %s\n",&cad.cep);
    fprintf(send,"Idade: %d\n\n\n",id);

    printf("\n!!! Cadastro do Paciente enviado com sucesso � Secretaria de Sa�de !!! \n\n");
    }

    fclose(send);
}
