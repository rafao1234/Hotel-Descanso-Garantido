#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <locale.h>

int localiza_estada(FILE*estadia,float codigo);

struct testada
{
    float entradadia,entradames,saidadia,saidames,registro,entradaano,saidaano;
};
typedef struct testada estada;

int localiza_cliente(FILE*registroCliente,float codigo);

struct tcliente
{
    char nome[50],endereco[50];
    float telefone,codigo;
};
typedef struct tcliente cliente;

int localiza_funcionario(FILE*registrofuncionarios,float codigo);

struct tfuncionario
{
    char nome[50],cargo[50];
    float telefone,salario,codigo;
};
typedef struct tfuncionario funcionario;

struct sistema_quarto
{
    int id;
    int quanthosp;
    float valor;
    int status;
};
typedef struct sistema_quarto quarto;

int main(){
	setlocale(LC_ALL,"portuguese");
	int a;
	printf("<---- Hotel Descanso Garantido ---->\n");
	printf("Escolha um dos setores do sistema: \n");
	printf("[1] - Quartos / [2] - Estadia / [3] - Funcionarios / [4] - Clientes / [5] - Sair\n");
	
	scanf("%d", &a);
	
	
		switch(a){
			case 1:
				system("cls");
				printf("\nEntrando no sistema dos quartos...\n");
				mainquarto();
				break;
			case 2:
				system("cls");
				printf("\nEntrando no sistema da estadia...\n");
				mainestadia();
				break;
			case 3:
				system("cls");
				printf("\nEntrando no sistema dos funcionarios...\n");
				mainfuncionarios();
				break;
			case 4:
				system("cls");
				printf("\nEntrando no sistema dos funcionarios...\n");
				maincliente();
				break;
			case 5:
				system("cls");
    			printf("\nSaindo do programa...\n");
    			break;
			default:
    			system("cls");
    			printf("\nErro, por favor selecione uma das categorias.\n");
    			
		}
	
	
}

int mainquarto()
{
	setlocale(LC_ALL,"portuguese");
	char op;
    FILE *quartos;
    if ((quartos = fopen("quartos.dat", "r+b")) == NULL)
    {
        printf("Arquivo nao existia, criando o arquivo!\n");
        if ((quartos = fopen("quartos.dat", "w+b")) == NULL)
        {
            printf("Erro na criacao do arquivo!\n");
            exit(1);
        }
        system("pause");
    }
    
    do{
    	printf("\nEscolha.........:\n");
    	printf("a - cadastrar quarto\n");
    	printf("b - listar os quartos\n");
    	printf("c - deletar todos os quartos\n");
    	printf("d - voltar ao main menu\n");
    	printf("e - sair do sistema\n");
    	op = getch();
    	switch(op){
    		case 'a':
    			system("cls");
    			printf("\nPreenchendo os quartos...\n");
    			incluir_quarto(quartos);
    		break;
    		
    		case 'b':
    			system("cls");
    			printf("\nListando os quartos...\n");
    			imprimir_arquivo(quartos);
    		break;
    		
    		case 'c':
    			system("cls");
    			printf("\nDeletando os quartos...\n");
    			deletar_quartos(quartos);
    		break;
    		
    		case 'd':
    			system("cls");
    			printf("\nVoltando ao menu...\n");
    			main();
    		break;
    		
    		default:
    			system("cls");
    			printf("\nErro, por favor selecione uma das categorias.\n");
    			continue;
		}
	}		
	while(op != 'e');
	{
		fclose(quartos);
		return 0;
	}
}

int localiza_quarto(FILE *quartos, int id)
{
    int posicao = -1, achou = 0;
    quarto q;
    fseek(quartos, 0, SEEK_SET);
    fread(&q, sizeof(q), 1, quartos);
    while (!feof(quartos) && !achou)
    {
        posicao++;
        if (q.id == id)
        {
            achou = 1;
        }
        fread(&q, sizeof(q), 1, quartos);
    }
    if (achou)
    {
        return posicao;
    }
    else
    {
        return -1;
    }
}

void incluir_quarto(FILE *quartos)
{
    quarto q;
    char stat[10];
    int pos;
    printf("\nDigite o codigo do quarto!\n");
    fflush(stdin);
    scanf("%d", &q.id);
    pos = localiza_quarto(quartos,q.id);
    if(pos == -1){

        printf("\nDigite a quantidade máxima de hospedes:\n");
        fflush(stdin);
        scanf("%d",&q.quanthosp);

        printf("\nDigite o valor da diária:\n");
        fflush(stdin);
        scanf("%f",&q.valor);
        
        q.status = 0;
        
        printf("\nQuarto cadastrado com sucesso!\n");

        fseek(quartos,0,SEEK_END);
        fwrite(&q,sizeof(q),1,quartos);
        fflush(quartos);
    }
    else{
        printf("\nCodigo %d ja existe no arquivo. Inclusao nao realizada!\n", q.id);
    }
}

void imprimir_arquivo(FILE *quartos){
	quarto q;
	fseek(quartos,0,SEEK_SET);
	fread(&q,sizeof(q),1,quartos);
	while(!feof(quartos)){
		printf("\nQuarto número %d: \n", q.id);
		printf("Codigo......: %d\n", q.id);
		printf("Quantidade de hóspedes......: %d\n", q.quanthosp);
		printf("Valor da diária......: %.2f\n", q.valor);
		printf("Status......: %s\n", q.status == 1 ? "Ocupado" : "Desocupado");
		fread(&q,sizeof(q),1,quartos);
	}
}

void deletar_quartos(FILE * quartos){
	fopen("quartos.dat","w");
}


int mainestadia()
{
    FILE*estadia;
    if ((estadia = fopen("estadia.txt", "r+b"))==NULL)
    {
        printf("Arquivo não existia ... criando arquivo!\n");
        if((estadia = fopen("estadia.txt", "w+b"))==NULL)
        {
            printf("Erro na criação do arquivo!!");
            exit(1);
        }
        system("pause");
    }
    setlocale(LC_ALL, "portuguese");
    int exec = 1,caso;
    while(exec == 1)
    {
        printf("O que você deseja?\n");
        printf("[1]-Cadastrar uma estadia\n");
        printf("[2]-Checar as estadias\n");
        printf("[3]-Alterar os dados de uma estadia\n");
        printf("[4]-Voltar ao main menu\n");
        scanf("%d",&caso);
        switch(caso)
        {
        case 1:
            cadastro(estadia);
            break;
        case 2:
            checar(estadia);
            break;
        case 3:
            alterarestadia(estadia);
            break;
        case 4:
        	system("cls");
            main();
            break;
        }
        printf("\n\nDeseja continuar a execução?  [Sim = 1 / Não = 0]");
        scanf("%d", &exec);
        system("cls");
    }
    return 0;
}

void cadastro(FILE*estadia)
{
    estada e;
    int local;
    printf("Codigo da estadia: \n");
    fflush(stdin);
    scanf("%f",&e.registro);
    local=localiza_estada(estadia,e.registro);
    if (local==-1)
    {
        printf("Digite a data de entrada: (dia) \n");
        fflush(stdin);
        scanf("%f",&e.entradadia);
        printf("Digite a data de entrada: (mês)\n");
        fflush(stdin);
        scanf("%f",&e.entradames);
        if(e.entradames>12)
        {
            while(e.entradames>12)
            {
                printf("ERRO: (Numero do mês invalido) \n");
                printf("Digite a data de entrada: (mês)\n");
                fflush(stdin);
                scanf("%f",&e.entradames);
            }
        }
        printf("Digite a data de entrada: (ano) \n");
        fflush(stdin);
        scanf("%f",&e.entradaano);
        if(e.entradaano<2021)
        {
            while(e.entradaano<2021)
            {
                printf("ERRO: (Ano invalido) \n");
                printf("Digite a data de entrada: (ano)\n");
                fflush(stdin);
                scanf("%f",&e.entradaano);
            }
        }
        printf("Digite a data de saida: (dia)\n");
        fflush(stdin);
        scanf("%f",&e.saidadia);
        printf("Digite a data de saida: (mês)\n");
        fflush(stdin);
        scanf("%f",&e.saidames);
        if(e.entradames>12)
        {
            while(e.saidames>12)
            {
                printf("ERRO: (Numero do mês invalido) \n");
                printf("Digite a data de saida: (mês)\n");
                fflush(stdin);
                scanf("%f",&e.saidames);
            }
        }
        printf("Digite a data de saida: (ano)\n");
        fflush(stdin);
        scanf("%f",&e.saidaano);
        if(e.saidaano<2021)
        {
            while(e.saidaano<2021)
            {
                printf("ERRO: (Ano invalido) \n");
                printf("Digite a data de saida: (ano)\n");
                fflush(stdin);
                scanf("%f",&e.saidaano);
            }
        }
        if(e.entradaano>e.saidaano)
        {
            while(e.entradaano>e.saidaano)
            {
                printf("ERRO: (Ano de saida menor que o ano de entrada) \n");
                printf("Digite a data de saida: (ano)\n");
                fflush(stdin);
                scanf("%f",&e.saidaano);
            }
            if(e.entradaano==e.saidaano)
            {
                if(e.entradames>e.saidames)
                {
                    while(e.entradames>e.saidames)
                    {
                        printf("ERRO: (Mês de saida menor que o mês de entrada) \n");
                        printf("Digite a data de saida: (mês)\n");
                        fflush(stdin);
                        scanf("%f",&e.saidames);
                    }
                }
                if(e.entradames==e.saidames)
                {
                    if(e.entradadia>e.saidadia)
                    {
                        while(e.entradadia>e.saidadia)
                        {
                            printf("ERRO: (Mês de saida menor que o mês de entrada) \n");
                            printf("Digite a data de saida: (dia)\n");
                            fflush(stdin);
                            scanf("%f",&e.saidadia);
                        }
                    }
                }
            }
        }
        fseek(estadia,0,SEEK_END);
        fwrite(&e, sizeof(e),1,estadia);
        fflush(estadia);
        printf("[ESTADIA REGISTRADA]\n");
        printf("DATA ENTRADA: %.0f /%.0f/%.0f\n",e.entradadia,e.entradames,e.entradaano);
        printf("DATA SAIDA: %.0f /%.0f/%.0f\n",e.saidadia,e.saidames,e.saidaano);
        printf("REGISTRO: %.0f\n",e.registro);

        int diaEnt = e.entradadia, diaSai = e.saidadia, mesEnt = e.entradames, mesSai = e.saidames, anoEnt = e.entradaano, anoSai = e.saidaano;

        printf("Diarias: %i",diarias(diaEnt,mesEnt, diaSai, mesSai,anoEnt,anoSai));
    }
    else
    {
        printf("Código %.0f já existe no arquivo. Inclusão não realizada!\n", e.registro);
    }
}

void checar(FILE*estadia)
{
    estada e;
    fseek(estadia,0,SEEK_SET);
    fread(&e, sizeof(e),1, estadia);
    while (!feof(estadia))
    {
        printf("DATA DE ENTRADA: %.0f /%.0f/%.0f \n",e.entradadia,e.entradames,e.entradaano);
        printf("DATA DE SAIDA: %.0f /%.0f/%.0f \n",e.saidadia,e.saidames,e.saidaano);
        printf("REGISTRO: %.0f\n",e.registro);
        printf("\n");
        fread(&e, sizeof(e),1, estadia);
    }
}

void alterarestadia(FILE*estadia)
{
    estada e;
    int local;
    printf("Digite o registro da estadia: \n");
    fflush(stdin);
    scanf("%f",&e.registro);
    local=localiza_estada(estadia,e.registro);
    if (local!=-1)
    {
        fseek(estadia,sizeof(e)*(local),SEEK_SET);
        fread(&e, sizeof(e),1, estadia);
        printf("Digite a data de entrada para altera-la: (dia) \n");
        fflush(stdin);
        scanf("%f",&e.entradadia);
        printf("Digite a data de entrada para altera-la: (mes) \n");
        fflush(stdin);
        scanf("%f",&e.entradames);
        printf("Digite a data de entrada para altera-la: (ano) \n");
        fflush(stdin);
        scanf("%f",&e.entradaano);
        printf("Digite a data de saida para altera-la: (dia) \n");
        fflush(stdin);
        scanf("%f",&e.saidadia);
        printf("Digite a data de saida para altera-la: (mes) \n");
        fflush(stdin);
        scanf("%f",&e.saidames);
        printf("Digite a data de saida para altera-la: (ano) \n");
        fflush(stdin);
        scanf("%f",&e.saidaano);
        fseek(estadia,sizeof(e)*(local),SEEK_SET);
        fwrite(&e, sizeof(e),1,estadia);
        fflush(estadia);
        printf("[DADOS ALTERADOS]\n");
        printf("DATA DE ENTRADA: %.0f/%.0f/%.0f \n",e.entradadia,e.entradames,e.entradaano);
        printf("DATA DE SAIDA: %.0f/%.0f/%.0f \n",e.saidadia,e.saidames,e.saidaano);
        printf("REGISTRO: %.0f\n",e.registro);
    }
    else
    {
        printf("Registro %.0f não existe no arquivo. Não é possível alterar.\n", e.registro);
    }
}

int localiza_estada(FILE*estadia,float registro)
{
    int local=-1,achou=0;
    estada e;
    fseek(estadia,0,SEEK_SET);
    fread(&e, sizeof(e),1, estadia);
    while (!feof(estadia) && !achou)
    {
        local++;
        if (e.registro==registro)
        {
            achou=1;
        }
        fread(&e, sizeof(e),1, estadia);
    }
    if(achou)
    {
        return local;
    }
    else
    {
        return -1;
    }
}

int valorDiaria(float custo,float nDiaria)
{
    float total;

    total = custo * nDiaria;

    return total;
}

int contDias(mes,ano)
{
    int mes31[7] = {1,3,5,7,8,10,12}, mes30[4] = {4,6,9,11};

    int n = 0, i;

    for (i = 0; i<4; i++)
    {
        if (mes==mes30[i])
        {
            return 30;
        }
    }


    if (mes==2)
    {
        if(ano % 4 == 0)
        {
            return 28;
        }
        else
        {
            return 29;
        }
    }


    return 31;
}



int maincliente()
{
    FILE*registroCliente;

    registroCliente=fopen("registroCliente.txt", "r+b");
    setlocale(LC_ALL, "portuguese");

    if ((registroCliente = fopen("registro_cliente.txt", "r+b"))==NULL) // arquivo existe
    {
        printf("\n Arquivo não existia ... criando arquivo! \n");
        if((registroCliente = fopen("registro_cliente.txt", "w+b"))==NULL) //arq não existe
        {
            printf("\n Erro na criação do arquivo!! \n");
            exit(1);
        }
        system("pause");
    }

    int exec = 1,caso;
    while(exec == 1)
    {
        printf("O que você deseja?\n");
        printf("[1]-Registrar um cliente.\n");
        printf("[2]-Checar os dados de um cliente.\n");
        printf("[3]-Voltar pro main menu.\n");
        scanf("%d",&caso);
        switch(caso)
        {
        case 1:
            registroc(registroCliente);
            break;
        case 2:
            checagemc(registroCliente);
            break;
        case 3:
            main();
            break;
        }
        printf("\n\nDeseja continuar a execução?  [Sim = 1 / Não = 0]");
        scanf("%d", &exec);
        system("cls");
    }
    return 0;
}
void registroc(FILE*registroCliente)
{
    cliente m;
    int posicao;
    printf("Digite o código do cliente: \n");
    fflush(stdin);
    scanf("%f",&m.codigo);
    posicao=localiza_cliente(registroCliente,m.codigo);
    if (posicao==-1)
    {
        printf("Digite o nome do cliente: \n");
        fflush(stdin);
        gets(m.nome);
        printf("Digite o endereco do cliente: \n");
        fflush(stdin);
        gets(m.endereco);
        printf("Digite o telefone do cliente: \n");
        fflush(stdin);
        scanf("%f",&m.telefone);
        fseek(registroCliente,0,SEEK_END);
        fwrite(&m, sizeof(m),1,registroCliente);
        fflush(registroCliente);
        printf("[CLIENTE REGISTRADO]\n");
        printf("NOME: %s\n",m.nome);
        printf("ENDERECO: %s\n",m.endereco);
        printf("TELEFONE: %.0f\n",m.telefone);
    }
    else
    {
        printf("Código %.0f já existe no arquivo. Inclusão não realizada!\n", m.codigo);
    }
}
int localiza_cliente(FILE*registroCliente,float codigo)
{
    int posicao=-1,achou=0;
    cliente m;
    fseek(registroCliente,0,SEEK_SET);
    fread(&m, sizeof(m),1, registroCliente);
    while (!feof(registroCliente) && !achou)
    {
        posicao++;
        if (m.codigo==codigo)
        {
            achou=1;
        }
        fread(&m, sizeof(m),1, registroCliente);
    }
    if(achou)
    {
        return posicao;
    }
    else
    {
        return -1;
    }
}
void checagemc(FILE*registroCliente)
{
    cliente m;
    fseek(registroCliente,0,SEEK_SET);
    fread(&m, sizeof(m),1, registroCliente);
    while (!feof(registroCliente))
    {
        printf("NOME: %s\n",m.nome);
        printf("ENDERECO: %s\n",m.endereco);
        printf("TELEFONE: %.0f\n",m.telefone);
        printf("CODIGO: %.0f\n",m.codigo);
        printf("\n");
        fread(&m, sizeof(m),1, registroCliente);
    }
}

int diarias(diaEnt,mesEnt,diaSai,mesSai, anoEnt, anoSai)
{
    int d = 0;
    int diariaTotal = 0;
    if (anoEnt != anoSai)
    {
    	int a;
    	
        for(a = anoEnt; a <= anoSai; a++)
        {
            if(a == anoEnt)
            {
            	int m;
            	
                for(m = mesEnt; m <= 12; m++)
                {
                    diariaTotal += contDias(m,a);
                }
            }
            else if (a > anoEnt && a < anoSai)
            {
            	int m;
            	
                for(m = 1; m <= 12; m++)
                {
                    diariaTotal += contDias(m,a);
                }
            }
            else if (a == anoSai)
            {
            	int m;
            	
                for (m = 1; m < mesSai; m++)
                {
                    diariaTotal += contDias(m,a);
                }
            }
        }
    }

    else if(anoEnt==anoSai)
    {
    	int m;
        for(m = mesEnt; m < mesSai; m++)
        {
            diariaTotal += contDias(m,anoEnt);
        }
    }

    diariaTotal += diaSai -1;
    diariaTotal -= diaEnt -1;

    return diariaTotal;
}



int mainfuncionarios()
{
    FILE*registrofuncionarios;
    if ((registrofuncionarios = fopen("registrofuncionarios.txt", "r+b"))==NULL) // arquivo existe
    {
        printf("Arquivo não existia ... criando arquivo!");
        if((registrofuncionarios = fopen("registrofuncionarios.txt", "w+b"))==NULL) //arq não existe
        {
            printf("Erro na criação do arquivo!!");
            exit(1);
        }
        system("pause");
    }
    setlocale(LC_ALL, "portuguese");
    int exec = 1,caso;
    while(exec == 1)
    {
        printf("O que você deseja?\n");
        printf("[1]-Registrar um funcionário\n");
        printf("[2]-Checar os dados de um funcionário\n");
        printf("[3]-Alterar os dados de um funcionário\n");
        printf("[4]-Voltar ao main menu.\n");
        scanf("%d",&caso);
        switch(caso)
        {
        case 1:
            registrof(registrofuncionarios);
            break;
        case 2:
            checagemf(registrofuncionarios);
            break;
        case 3:
            alterarf(registrofuncionarios);
            break;
        case 4:
        	system("cls");
            main();
            break;
        }
        printf("\n\nDeseja continuar a execução?  [Sim = 1 / Não = 0]");
        scanf("%d", &exec);
        system("cls");
    }
    return 0;
}
void registrof(FILE*registrofuncionarios)
{
    funcionario m;
    int posicao;
    printf("Digite o código do funcionário: \n");
    fflush(stdin);
    scanf("%f",&m.codigo);
    posicao=localiza_funcionario(registrofuncionarios,m.codigo);
    if (posicao==-1)
    {
        printf("Digite o nome do funcionário: \n");
        fflush(stdin);
        gets(m.nome);
        printf("Digite o cargo do funcionario: \n");
        fflush(stdin);
        gets(m.cargo);
        printf("Digite o telefone do funcionario: \n");
        fflush(stdin);
        scanf("%f",&m.telefone);
        printf("Digite o salario do funcionario: \n");
        fflush(stdin);
        scanf("%f",&m.salario);
        fseek(registrofuncionarios,0,SEEK_END);
        fwrite(&m, sizeof(m),1,registrofuncionarios);
        fflush(registrofuncionarios);
        printf("[FUNCIONÁRIO REGISTRADO]\n");
        printf("NOME: %s\n",m.nome);
        printf("CARGO: %s\n",m.cargo);
        printf("TELEFONE: %.0f\n",m.telefone);
        printf("SALÁRIO: %.2f\n",m.salario);
        printf("CODIGO: %.0f\n",m.codigo);
    }
    else
    {
        printf("Código %.0f já existe no arquivo. Inclusão não realizada!\n", m.codigo);
    }
}
int localiza_funcionario(FILE*registrofuncionarios,float codigo)
{
    int posicao=-1,achou=0;
    funcionario m;
    fseek(registrofuncionarios,0,SEEK_SET);
    fread(&m, sizeof(m),1, registrofuncionarios);
    while (!feof(registrofuncionarios) && !achou)
    {
        posicao++;
        if (m.codigo==codigo)
        {
            achou=1;
        }
        fread(&m, sizeof(m),1, registrofuncionarios);
    }
    if(achou)
    {
        return posicao;
    }
    else
    {
        return -1;
    }
}

void checagemf(FILE*registrofuncionarios){
    funcionario m;
    fseek(registrofuncionarios,0,SEEK_SET);
    fread(&m, sizeof(m),1, registrofuncionarios);
    while (!feof(registrofuncionarios))
    {
        printf("NOME: %s\n",m.nome);
        printf("CARGO: %s\n",m.cargo);
        printf("TELEFONE: %.0f\n",m.telefone);
        printf("SALÁRIO: %.2f\n",m.salario);
        printf("CODIGO: %.0f\n",m.codigo);
        printf("\n");
        fread(&m, sizeof(m),1, registrofuncionarios);
}
}

void alterarf(FILE*registrofuncionarios)
{
    funcionario m;
    int posicao;
    printf("Digite o código do funcionário: \n");
    fflush(stdin);
    scanf("%f",&m.codigo);
    posicao=localiza_funcionario(registrofuncionarios,m.codigo);
    if (posicao!=-1)
    {
        fseek(registrofuncionarios,sizeof(m)*(posicao),SEEK_SET);
        fread(&m, sizeof(m),1, registrofuncionarios);
        printf("Digite o nome do funcionário para altera-lo: \n");
        fflush(stdin);
        gets(m.nome);
        printf("Digite o cargo do funcionario para altera-lo: \n");
        fflush(stdin);
        gets(m.cargo);
        printf("Digite o telefone do funcionario para altera-lo: \n");
        fflush(stdin);
        scanf("%f",&m.telefone);
        printf("Digite o salario do funcionario para altera-lo: \n");
        fflush(stdin);
        scanf("%f",&m.salario);
        fseek(registrofuncionarios,sizeof(m)*(posicao),SEEK_SET);
        fwrite(&m, sizeof(m),1,registrofuncionarios);
        fflush(registrofuncionarios);
        printf("[DADOS ALTERADOS]\n");
        printf("NOME: %s\n",m.nome);
        printf("CARGO: %s\n",m.cargo);
        printf("TELEFONE: %.0f\n",m.telefone);
        printf("SALÁRIO: %.2f\n",m.salario);
        printf("CODIGO: %.0f\n",m.codigo);
    }
    else
    {
        printf("Código %.0f não existe no arquivo. Não é possível alterar.\n", m.codigo);
    }
}

