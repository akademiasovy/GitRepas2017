#define _CRT_SECURE_NO_WARNINGS
#include <cstdlib>
#include <string.h>
#include <iostream>
#include "kniha.h"
#include "citatel.h"
#include "vypozicky.h"
#include <stdbool.h>
#include <stdio.h>
#include <time.h>

using namespace std;
bool controlLoans(int i,Vypozicky *loans,Citatel *reader,int max);
bool checkDate(Datum rent, Datum today);
int main(int argc, char *argv[])
{
    // TO DO
	
	time_t rawtime;								//zistenie a nacitanie aktualneho datumu
	time(&rawtime);
	struct tm *timeinfo = localtime(&rawtime);	//koniec zistovania a nacitavnia aktualneho datumu

	Datum today;
	today.den = timeinfo->tm_mday;
	today.mesiac = timeinfo->tm_mon + 1;
	today.rok = timeinfo->tm_year + 1900;

    Kniha books[100];							//vytvorenie premennej knihy - na nacitanie knih
    Citatel reader[100];						//vytvorenie premennej citatelia - na nacitanie citatelov
    Vypozicky loans[100];						//vytvorenie premennej vypozicky - na nacitanie vypoziciek
    Datum datum[100];							//vytvorenie premennej datum - na nacitanie struktury datum
    int i,j,k;
    FILE *fw;									//vytvorenie smernika na subor na zapisovanie
    
    fw=fopen("Library.txt","a");
    int SNL = readLoansFromFile(loans);			//serial number of loan - teda poradove cislo vypozicky
    int SNB =  readBooksFromFile(books);		//serial number of book - teda poradove cislo knihy
    int SNR = readReadersFromFile(reader);		//serial number of reader - teda poradove cislo citatela
    
     for(i=0; i<SNL;i++)						//vypis na konzolu a zaroven zapis do suboru
	 {
		for(k=0 ; k<SNR; k++)
		{
     		if(loans[i].idc == reader[k].id)
			{
     			printf("%s %s \n", reader[k].priezvisko, reader[k].meno);
     			fprintf(fw,"%s %s\n",reader[k].priezvisko, reader[k].meno);
				break;
			} 	
		}
		for(j=0 ; j<SNB; j++)
		{
     		if(loans[i].idk == books[j].id)		//v pripade, ak citatel ma vypozicane knihy, vypisu a do suboru sa zapisu informacie v nasledovnom tvare
			{
     			printf(" -> %s %d.%d.%d.", books[j].nazov, loans[i].datumPozicania.den,
				loans[i].datumPozicania.mesiac, loans[i].datumPozicania.rok);
			  
				fprintf(fw," -> %s %d.%d.%d",books[j].nazov, loans[i].datumPozicania.den,
				loans[i].datumPozicania.mesiac, loans[i].datumPozicania.rok);

				if (checkDate(loans[i].datumPozicania, today) == false)
				{
					printf(" -> Kniha je po termine vratenia!\n");
					fprintf(fw, " -> Kniha je po termine vratenia!\n");
				}
				else
				{
					printf("\n");
					fprintf(fw, "\n");
				}
			}
		}
	}
	
	for(k=0 ; k<SNR; k++)
	{
		if (controlLoans(k, loans, reader, SNL) == false)	//v pripade, ak citatel nema vypozicane knihy, vypisu a do suboru sa zapisu informacie v nasledovnom tvare
		{
			printf("%s %s\n -> bez vypozicky\n", reader[k].priezvisko, reader[k].meno);
			fprintf(fw, "%s %s\n -> bez vypozicky\n", reader[k].priezvisko, reader[k].meno);
		}
	}	 
	fclose(fw);
    system("PAUSE");
    return EXIT_SUCCESS;
}

bool controlLoans(int i,Vypozicky *vypozicky, Citatel *citatel,int max)		//subor na kontrolu, ci ma citatel vypozicane knihy
{
	int j;
	for(j=0; j<max;j++)
	{
		if(citatel[i].id==vypozicky[j].idc)
		{
			return true;
		}	
	}
	return false;
}

bool checkDate(Datum rent, Datum today)
{
	int month = today.mesiac - rent.mesiac;
	int year = today.rok - rent.rok;
	if (today.mesiac < rent.mesiac)
	{
		month = 12 - rent.mesiac + today.mesiac;
	}
	if (month > 2)
	{
		return false;
	}
	else if (month == 2)
	{
		if (today.den >= rent.den)
		{
			return false;
		}
	}
	else
	{
		return true;
	}
}
