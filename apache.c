#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdio_ext.h>
//Programa final
int freqhorapico;
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
typedef struct ipsrepetidos{
	char ip[50];
	int cont;
	struct ipsrepetidos *prox;

}ips;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
typedef struct usrrepetidos{
	char usuario[255];
	int cont;
	struct usrrepetidos *prox;

}usrs;
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
typedef struct horarep{
	char horastr[50];
	int hora;
	int cont;
	struct horarep *prox;

}horarep;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

typedef struct registro{
    char ip[50];
    char usuario[255];
    char data[50];
	char hora[50];
	char zona[50];
    char metodo[255];
    char path[255];
	char protocolo[255];
    char http[255];
    int status;
    long bytes;
    char agente[255];
}registro;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

typedef struct no{
    struct registro info;
    struct no *prox;
    struct no *ant;
}no;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
ips *novoip(char novoip[50]){
	ips *novo=(ips*)malloc(sizeof(ips));
	if(novo){
		strcpy(novo->ip,novoip);
		novo->cont=0;
		novo->prox=NULL;
	}else{
		printf("Erro de alocacao");
		return 0;
	}
	return novo;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
usrs *novousr(char novousr[255]){
	usrs *novo=(usrs*)malloc(sizeof(usrs));
	if(novo){
		strcpy(novo->usuario,novousr);
		novo->cont=0;
		novo->prox=NULL;
	}else{
		printf("Erro de alocacao");
		return 0;
	}
	return novo;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
horarep *novohora(int hora,char horastr[50]){
	horarep *novo=(horarep*)malloc(sizeof(horarep));

	if(novo){
		novo->hora=hora;
		strcpy(novo->horastr,horastr);
		novo->cont=1;
		novo->prox=NULL;
	}else{
		printf("Erro de alocacao");
		return 0;
	}
	return novo;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
horarep *horar(no *L,horarep *lst){
	no *aux=L;
	horarep *auxhr=NULL, *auxhr2=NULL, *novo=NULL;
	char temp[50];
	int hora,minuto,segundo;
	char horasep[2],minutosep[2],segundosep[2];

	if(L!=NULL){
	while(aux!=NULL){
		strcpy(temp,aux->info.hora);
		horasep[0]=temp[0];
		horasep[1]=temp[1];
		minutosep[0]=temp[3];
		minutosep[1]=temp[4];
		segundosep[0]=temp[6];
		segundosep[1]=temp[7];
		hora=atoi(horasep);
		minuto=atoi(minutosep);
		segundo=atoi(segundosep);
		
		if(lst==NULL){
			novo=novohora(hora,temp);
			lst=novo;
			novo->cont=1;
		}
		else{
		auxhr=lst;
		while(auxhr!=NULL && hora!=auxhr->hora){
			auxhr2=auxhr;
			auxhr=auxhr->prox;
		}
		if(auxhr==NULL){
			novo=novohora(hora,temp);
			auxhr2->prox=novo;
		}else{
			auxhr->cont++;
		}
		}
		aux=aux->prox;
	}
	return lst;
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void minr(no *L,int horapico){
	no *aux=L;
	char temp[50];
	int minuto,hora,cont30=0,cont1h=0;
	char minutosep[2],horasep[2];

	if(L!=NULL){
	while(aux!=NULL){
		strcpy(temp,aux->info.hora);
		horasep[0]=temp[0];
		horasep[1]=temp[1];
		minutosep[0]=temp[3];
		minutosep[1]=temp[4];
		hora=atoi(horasep);
		minuto=atoi(minutosep);
		if(hora==horapico){
		if(minuto<30) cont30++;
		else cont1h++;
		}
		aux=aux->prox;
	}
	if(cont30>0.75*freqhorapico){
		printf("O horario de pico e entre %i:00 e %i:30\n",horapico,horapico);
	}
	else{
		if(cont1h>0.75*freqhorapico)	printf("O horario de pico e entre %i:31 e %i:59\n",horapico,horapico);
		else printf("O horario de pico e entre %i:00 e %i:59\n",horapico,horapico);
		}
	}
	else printf("Registro vazio.\n");
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
ips *iprep(no *L,ips *lst){
	no *aux=L;
	ips *auxip=NULL, *auxip2=NULL, *novo=NULL;
	char temp[50];
	if(L!=NULL){
	while(aux!=NULL){
		strcpy(temp,aux->info.ip);
		if(lst==NULL){
			novo=novoip(temp);
			lst=novo;
			novo->cont=0;
		}
		else{
		auxip=lst;
		while(auxip!=NULL && strcmp(aux->info.ip,auxip->ip)!=0){
			auxip2=auxip;
			auxip=auxip->prox;
		}
		if(auxip==NULL){
			novo=novoip(temp);
			auxip2->prox=novo;
		}else{
			auxip->cont=1;
		}
		}
		aux=aux->prox;
	}
	return lst;
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
usrs *usrrep(no *L,usrs *lst2){
	no *aux=L;
	usrs *auxusr=NULL, *auxusr2=NULL, *novo=NULL;
	char temp[255];
	if(L!=NULL){
	while(aux!=NULL){
		strcpy(temp,aux->info.usuario);
		if(lst2==NULL){
			novo=novousr(temp);
			lst2=novo;
			novo->cont=0;
		}
		else{
		auxusr=lst2;
		while(auxusr!=NULL && strcmp(aux->info.usuario,auxusr->usuario)!=0){
			auxusr2=auxusr;
			auxusr=auxusr->prox;
		}
		if(auxusr==NULL){
			novo=novousr(temp);
			auxusr2->prox=novo;
		}else{
			auxusr->cont=1;
		}
		}
		aux=aux->prox;
	}
	return lst2;
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
no *novoNo(char ip[50],char usuario[255], char data[50],char hora[50],char zona[50],char metodo[255],char path[255],char protocolo[255],int status,long bytes,char http[255],char agente[255]){
    no *novo=(no*)malloc(sizeof(no));
    if(novo){
		strcpy(novo->info.ip,ip);
		strcpy(novo->info.usuario,usuario);
		strcpy(novo->info.data,data);
		strcpy(novo->info.hora,hora);
		strcpy(novo->info.zona,zona);
		strcpy(novo->info.metodo,metodo);
		strcpy(novo->info.path,path);
		strcpy(novo->info.protocolo,protocolo);
		strcpy(novo->info.http,http);
		novo->info.status=status;
		novo->info.bytes=bytes;
		strcpy(novo->info.agente,agente);
		novo->prox=NULL;
		novo->ant=NULL;

	}
    else{
        printf("Erro de alocacao.\n");
        return 0;
    }
    return novo;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

no *insereFim(no *L, no *novo){
	no *aux=L;
	if(aux==NULL) return novo;
	while(aux->prox!=NULL)
		aux=aux->prox;
	aux->prox=novo;
	novo->ant=aux;
	return L;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

no *leArq(){
	no *lst=NULL;
    FILE *arq;
    char ip[50];
    char usuario[255];
    char data[50];
	char hora[50];
	char zona[50];
    char metodo[255];
    char path[255];
	char protocolo[255];
    char http[255];
    int status;
    long bytes;
    char agente[255];
    arq=fopen("logs.txt","r");
    if(arq==NULL);
    else
	while(fscanf(arq,"%s - %s [%11s:%8s %5s] %s %s %s %i %li %s %[^\n]s ",ip,usuario,data,hora,zona,metodo,path,protocolo,&status,&bytes,http,agente)!=EOF){

		lst=insereFim(lst,novoNo(ip,usuario,data,hora,zona,metodo,path,protocolo,status,bytes,http,agente));

	}
	fclose(arq);
	return lst;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int horafreq(horarep *lst){
	horarep *aux=lst;
	int pico=0,conthora=0;
	while(aux!=NULL){
		if(aux->cont>conthora){
			pico=aux->hora;
			conthora=aux->cont;
		}
		aux=aux->prox;
	}
	freqhorapico=conthora;
	return pico;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void imprimeLista(no *Lista){
	no *aux=Lista;
	if(aux==NULL) printf("Registro vazio.\n");
	while(aux!=NULL){
		printf("%s %s %s %s %s %s %s %s %i %li %s %s\n\n",aux->info.ip,aux->info.usuario,aux->info.data,aux->info.hora,aux->info.zona,aux->info.metodo,aux->info.path,aux->info.protocolo,aux->info.status,aux->info.bytes,aux->info.http,aux->info.agente);
		aux=aux->prox;
	}

}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void imprimeIP(ips *lst){
	ips *aux=lst;
	int ver=0;
	while(aux!=NULL){
		if(aux->cont>0){
		printf("IP: %s Foi repetido\n",aux->ip);
		ver=1;
		}
		aux=aux->prox;
	}
	if(ver==0) printf("Nada foi repetido.\n");
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void imprimeUSR(usrs *lst2){
	usrs *aux=lst2;
	int ver=0;
	while(aux!=NULL){
		if(aux->cont>0){
		printf("Usuario: %s Foi repetido\n",aux->usuario);
		ver=1;
		}
		aux=aux->prox;
	}
	if(ver==0) printf("Nada foi repetido.\n");
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

no *buscaremocaoS(no *L, char chavebusca[255], int op){
	no *aux=L,*aux2=NULL;
	if(aux!=NULL){
		if(op==1){
			while(aux!=NULL){
				if(strcmp(aux->info.ip,chavebusca)==0){
					if(aux->prox==NULL){
						if(aux->ant==NULL){
							free(aux);
							return NULL;
						}
						aux->ant->prox=aux->prox;
						aux2=aux;
						aux=NULL;
						free(aux2);
					}
					else{
						if(aux->ant==NULL){
							aux=L;
							L=L->prox;
							L->ant=NULL;
							free(aux);
							aux=L;
						}
						else{
							aux->ant->prox=aux->prox;
							aux->prox->ant=aux->ant;
							aux2=aux;
							aux=aux->prox;
							free(aux2);
						}
					}
				}
				else
				aux=aux->prox;
			}
		}
		if(op==2){
			while(aux!=NULL){
				if(strcmp(aux->info.usuario,chavebusca)==0){
					if(aux->prox==NULL){
						if(aux->ant==NULL){
							free(aux);
							return NULL;
						}
						aux->ant->prox=aux->prox;
						aux2=aux;
						aux=NULL;
						free(aux2);
					}
					else{
						if(aux->ant==NULL){
							aux=L;
							L=L->prox;
							L->ant=NULL;
							free(aux);
							aux=L;
						}
						else{
							aux->ant->prox=aux->prox;
							aux->prox->ant=aux->ant;
							aux2=aux;
							aux=aux->prox;
							free(aux2);
						}
					}
				}
				else
				aux=aux->prox;
			}
		}
		if(op==3){
			while(aux!=NULL){
				if(strcmp(aux->info.data,chavebusca)==0){
					if(aux->prox==NULL){
						if(aux->ant==NULL){
							free(aux);
							return NULL;
						}
						aux->ant->prox=aux->prox;
						aux2=aux;
						aux=NULL;
						free(aux2);
					}
					else{
						if(aux->ant==NULL){
							aux=L;
							L=L->prox;
							L->ant=NULL;
							free(aux);
							aux=L;
						}
						else{
							aux->ant->prox=aux->prox;
							aux->prox->ant=aux->ant;
							aux2=aux;
							aux=aux->prox;
							free(aux2);
						}
					}
				}
				else
				aux=aux->prox;
			}
		}
		if(op==4){
			while(aux!=NULL){
				if(strcmp(aux->info.hora,chavebusca)==0){
					if(aux->prox==NULL){
						if(aux->ant==NULL){
							free(aux);
							return NULL;
						}
						aux->ant->prox=aux->prox;
						aux2=aux;
						aux=NULL;
						free(aux2);
					}
					else{
						if(aux->ant==NULL){
							aux=L;
							L=L->prox;
							L->ant=NULL;
							free(aux);
							aux=L;
						}
						else{
							aux->ant->prox=aux->prox;
							aux->prox->ant=aux->ant;
							aux2=aux;
							aux=aux->prox;
							free(aux2);
						}
					}
				}
				else
				aux=aux->prox;
			}
		}
		if(op==5){
			while(aux!=NULL){
				if(strcmp(aux->info.zona,chavebusca)==0){
					if(aux->prox==NULL){
						if(aux->ant==NULL){
							free(aux);
							return NULL;
						}
						aux->ant->prox=aux->prox;
						aux2=aux;
						aux=NULL;
						free(aux2);
					}
					else{
						if(aux->ant==NULL){
							aux=L;
							L=L->prox;
							L->ant=NULL;
							free(aux);
							aux=L;
						}
						else{
							aux->ant->prox=aux->prox;
							aux->prox->ant=aux->ant;
							aux2=aux;
							aux=aux->prox;
							free(aux2);
						}
					}
				}
				else
				aux=aux->prox;
			}
		}
		if(op==6){
			while(aux!=NULL){
				if(strcmp(aux->info.metodo,chavebusca)==0){
					if(aux->prox==NULL){
						if(aux->ant==NULL){
							free(aux);
							return NULL;
						}
						aux->ant->prox=aux->prox;
						aux2=aux;
						aux=NULL;
						free(aux2);
					}
					else{
						if(aux->ant==NULL){
							aux=L;
							L=L->prox;
							L->ant=NULL;
							free(aux);
							aux=L;
						}
						else{
							aux->ant->prox=aux->prox;
							aux->prox->ant=aux->ant;
							aux2=aux;
							aux=aux->prox;
							free(aux2);
						}
					}
				}
				else
				aux=aux->prox;
			}
		}
		if(op==7){
			while(aux!=NULL){
				if(strcmp(aux->info.path,chavebusca)==0){
					if(aux->prox==NULL){
						if(aux->ant==NULL){
							free(aux);
							return NULL;
						}
						aux->ant->prox=aux->prox;
						aux2=aux;
						aux=NULL;
						free(aux2);
					}
					else{
						if(aux->ant==NULL){
							aux=L;
							L=L->prox;
							L->ant=NULL;
							free(aux);
							aux=L;
						}
						else{
							aux->ant->prox=aux->prox;
							aux->prox->ant=aux->ant;
							aux2=aux;
							aux=aux->prox;
							free(aux2);
						}
					}
				}
				else
				aux=aux->prox;
			}
		}
		if(op==8){
			while(aux!=NULL){
				if(strcmp(aux->info.protocolo,chavebusca)==0){
					if(aux->prox==NULL){
						if(aux->ant==NULL){
							free(aux);
							return NULL;
						}
						aux->ant->prox=aux->prox;
						aux2=aux;
						aux=NULL;
						free(aux2);
					}
					else{
						if(aux->ant==NULL){
							aux=L;
							L=L->prox;
							L->ant=NULL;
							free(aux);
							aux=L;
						}
						else{
							aux->ant->prox=aux->prox;
							aux->prox->ant=aux->ant;
							aux2=aux;
							aux=aux->prox;
							free(aux2);
						}
					}
				}
				else
				aux=aux->prox;
			}
		}
		if(op==11){
			while(aux!=NULL){
				if(strcmp(aux->info.http,chavebusca)==0){
					if(aux->prox==NULL){
						if(aux->ant==NULL){
							free(aux);
							return NULL;
						}
						aux->ant->prox=aux->prox;
						aux2=aux;
						aux=NULL;
						free(aux2);
					}
					else{
						if(aux->ant==NULL){
							aux=L;
							L=L->prox;
							L->ant=NULL;
							free(aux);
							aux=L;
						}
						else{
							aux->ant->prox=aux->prox;
							aux->prox->ant=aux->ant;
							aux2=aux;
							aux=aux->prox;
							free(aux2);
						}
					}
				}
				else
				aux=aux->prox;
			}
		}
		if(op==12){
			while(aux!=NULL){
				if(strcmp(aux->info.agente,chavebusca)==0){
					if(aux->prox==NULL){
						if(aux->ant==NULL){
							free(aux);
							return NULL;
						}
						aux->ant->prox=aux->prox;
						aux2=aux;
						aux=NULL;
						free(aux2);
					}
					else{
						if(aux->ant==NULL){
							aux=L;
							L=L->prox;
							L->ant=NULL;
							free(aux);
							aux=L;
						}
						else{
							aux->ant->prox=aux->prox;
							aux->prox->ant=aux->ant;
							aux2=aux;
							aux=aux->prox;
							free(aux2);
						}
					}
				}
				else
				aux=aux->prox;
			}
		}
	}
	return L;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

no *buscaremocaoI(no *L, long chavebusca1,int chavebusca2, int op){
	no *aux=L,*aux2=aux;
	if(aux!=NULL){
		if(op==9){
			while(aux!=NULL){
				if(aux->info.status==chavebusca2){
					if(aux->prox==NULL){
						if(aux->ant==NULL){
							free(aux);
							return NULL;
						}
						aux->ant->prox=aux->prox;
						aux2=aux;
						aux=NULL;
						free(aux2);
					}
					else{
						if(aux->ant==NULL){
							aux=L;
							L=L->prox;
							L->ant=NULL;
							free(aux);
							aux=L;
						}
						else{
							aux->ant->prox=aux->prox;
							aux->prox->ant=aux->ant;
							aux2=aux;
							aux=aux->prox;
							free(aux2);
						}
					}
				}
				else
				aux=aux->prox;
			}
		}
		if(op==10){
			while(aux!=NULL){
				if(aux->info.bytes==chavebusca1){
					if(aux->prox==NULL){
						if(aux->ant==NULL){
							free(aux);
							return NULL;
						}
						aux->ant->prox=aux->prox;
						aux2=aux;
						aux=NULL;
						free(aux2);
					}
					else{
						if(aux->ant==NULL){
							aux=L;
							L=L->prox;
							L->ant=NULL;
							free(aux);
							aux=L;
						}
						else{
							aux->ant->prox=aux->prox;
							aux->prox->ant=aux->ant;
							aux2=aux;
							aux=aux->prox;
							free(aux2);
						}
					}
				}
				else
				aux=aux->prox;
			}
		}
	}
	return L;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
	int escolha=0, tipo=0,id,horapico;
	long li;
	char string[255],stringt[255];
	no *L=NULL;
	ips *lst=NULL;
	usrs *lst2=NULL;
	horarep *lst3=NULL;

	do{
		printf("\n1 - Carregar e Imprimir Log Apache\n2 - Excluir registro\n3 - IPs Repetidos\n4 - Usuários repetidos \n5 - Periodo de maior utilizacao da rede\n6 - Imprimir Log Carregado\n7 - Sair\nOpcao: ");
		scanf("%i",&escolha);
		printf("\n");
		switch(escolha){
		case 1:
			free(lst);
			free(lst2);
			free(lst3);
			lst=NULL;
			lst2=NULL;
			lst3=NULL;
			horapico=0;
			L=leArq();
			imprimeLista(L);
			lst=iprep(L,lst);
			lst2=usrrep(L,lst2);
			lst3=horar(L,lst3);
			horapico=horafreq(lst3);
		break;
		case 2:
			printf("\n    Deletar por:\n  1 - IP\n  2 - Usuario\n  3 - Data\n  4 - Hora\n  5 - Zona\n  6 - Metodo\n  7 - Path\n  8 - Protocolo\n  9 - status\n  10 - bytes\n  11 - http\n  12 - Agente\nOpcao: ");
			scanf("%i",&tipo);
			printf("\n");
			switch(tipo){
			case 1:
				printf("Entre com o ip: ");
				__fpurge(stdin);
				scanf("%s",string);
				L=buscaremocaoS(L,string,1);
				free(lst);
				lst=NULL;
				lst=iprep(L,lst);
				free(lst2);
				lst2=NULL;
				lst2=usrrep(L,lst2);
			break;
			case 2:
				printf("Entre com o usuario: ");
				scanf("%s",string);
				L=buscaremocaoS(L,string,2);
				free(lst);
				lst=NULL;
				lst=iprep(L,lst);
				free(lst2);
				lst2=NULL;
				lst2=usrrep(L,lst2);
			break;
			case 3:
				printf("Entre com a data: ");
				scanf("%s",string);
				L=buscaremocaoS(L,string,3);
				free(lst);
				lst=NULL;
				lst=iprep(L,lst);
				free(lst2);
				lst2=NULL;
				lst2=usrrep(L,lst2);
			break;
			case 4:
				printf("Entre com a hora: ");
				scanf("%s",string);
				L=buscaremocaoS(L,string,4);
				free(lst);
				lst=NULL;
				lst=iprep(L,lst);
				free(lst2);
				lst2=NULL;
				lst2=usrrep(L,lst2);
			break;
			case 5:
				printf("Entre com a zona: ");
				scanf("%s",string);
				L=buscaremocaoS(L,string,5);
				free(lst);
				lst=NULL;
				lst=iprep(L,lst);
				free(lst2);
				lst2=NULL;
				lst2=usrrep(L,lst2);
			break;
			case 6:
				printf("Entre com o metodo: ");
				scanf("%s",string);
				strcat(stringt,"\"");
				strcat(stringt,string);
				L=buscaremocaoS(L,stringt,6);
				free(lst);
				lst=NULL;
				lst=iprep(L,lst);
				free(lst2);
				lst2=NULL;
				lst2=usrrep(L,lst2);
			break;
			case 7:
				printf("Entre com o path: ");
				scanf("%s",string);
				L=buscaremocaoS(L,string,7);
				free(lst);
				lst=NULL;
				lst=iprep(L,lst);
				free(lst2);
				lst2=NULL;
				lst2=usrrep(L,lst2);
			break;
			case 8:
				printf("Entre com o protocolo: ");
				scanf("%s",string);
				strcat(stringt,string);
				strcat(stringt,"\"");
				L=buscaremocaoS(L,stringt,8);
				free(lst);
				lst=NULL;
				lst=iprep(L,lst);
				free(lst2);
				lst2=NULL;
				lst2=usrrep(L,lst2);
			break;
			case 9:
				printf("Entre com o status: ");
				scanf("%i",&id);
				L=buscaremocaoI(L,0,id,9);
				free(lst);
				lst=NULL;
				lst=iprep(L,lst);
				free(lst2);
				lst2=NULL;
				lst2=usrrep(L,lst2);
			break;
			case 10:
				printf("Entre com os bytes: ");
				scanf("%li",&li);
				L=buscaremocaoI(L,li,0,10);
				free(lst);
				lst=NULL;
				lst=iprep(L,lst);
				free(lst2);
				lst2=NULL;
				lst2=usrrep(L,lst2);
			break;
			case 11:
				printf("Entre com o http: ");
				scanf("%s",string);
				strcat(stringt,"\"");
				strcat(stringt,string);
				strcat(stringt,"\"");
				L=buscaremocaoS(L,stringt,11);
				free(lst);
				lst=NULL;
				lst=iprep(L,lst);
				free(lst2);
				lst2=NULL;
				lst2=usrrep(L,lst2);
			break;
			case 12:
				printf("Entre com o agente: ");
				scanf("%s",string);
				strcat(stringt,"\"");
				strcat(stringt,string);
				strcat(stringt,"\"");
				L=buscaremocaoS(L,stringt,12);
				free(lst);
				lst=NULL;
				lst=iprep(L,lst);
				free(lst2);
				lst2=NULL;
				lst2=usrrep(L,lst2);
			break;
			default:printf("\nopcao invalida\n");
			}
		break;
		case 3:
				imprimeIP(lst);
		break;
		case 4:
				imprimeUSR(lst2);
		break;
		case 5:
				minr(L,horapico);
		break;
		case 6: 
				imprimeLista(L);
		break;
		case 7:
		break;
		default:printf("\nOpcao invalida\n");
		}
	}while(escolha!=7);
return 0;
}
