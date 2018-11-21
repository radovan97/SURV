#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>
#include <termios.h>
#include <unistd.h>

typedef struct { char ime[10]; char prezime[15]; int ocene[10]; char br_ind[15]; } Student ;
void dodaj_s(FILE * fp);
FILE * obrisi(FILE * fp);
void izmeni(FILE * fp);
void lista_s(FILE * fp);
void pretrazi(FILE * fp);
void izmena_naloga(FILE * fp);
void printChar(char ch, int n);
void printNaslov();
void promena(FILE *fp);
// void isprazniBafer() {
//   char c ;
//   c = getchar();
//   while((c != '\n') && (c != '\0'))
//   {
//     c = getchar();
//   }
// }


// testirati sve mogucnosti promene lozinke i izmena
//srediti ispis
//obavestiti kada ne pronadje trazeni text pretragom..itd

int main()
{
  FILE * fp;
  Student s;
  int opcija, kon, d;
  char adm[16], usr[16] = "admin", psw[16] = "1234", loz[16];
  char c, *str, *pas;
  size_t bajt = 1;
  char op[]="";
  size_t ob_count = 1, vel = 16;

  size_t greska_w1, greska_w2, greska_r1, greska_r2;
  if((fp=fopen("studentInfo.txt","rb+")) == NULL)
  {
    if((fp=fopen("studentInfo.txt","wb+"))==NULL)
    {
      printf("Ne mogu da otvorim fajl.");
      return 0;
    }else
    {
      //ako se fajl kreira prvi put, upisi usr i psw
      rewind(fp);
      greska_w1 = fwrite (&usr, vel, ob_count, fp);
      fseek(fp, vel, SEEK_SET);
      greska_w2 = fwrite (&psw, vel, ob_count, fp);

      if ((greska_w1 != ob_count) || (greska_w2 != ob_count))
      {
        printf ("Greska prilikom upisa u fajl1.\n");
        return 1;
      }
    }
  }else
  {
    // ako fajl postoji, procitaj usri psw
    rewind(fp);
    greska_r1 = fread (&usr, vel, ob_count, fp);
    fseek(fp, vel, SEEK_SET);
    greska_r2 = fread (&psw, vel, ob_count, fp);
    if ((greska_r1 != ob_count) || (greska_r2 != ob_count))
    {
      printf ("Greska prilikom upisa u fajl2.\n");
      return 1;
    }
    else
    {
      printf ("Uspesan upis u fajl2.\n");
    }
  }

  do
  {
    printNaslov();
    printf("\n\tUpisite administratorsko ime: --> " );
    scanf("%s", adm);
    if((strcmp(adm, "0") == 0))
    {
      return 0;
    }
    pas = getpass("\n\t             Upisite lozinku: --> ");
    //printf("\tADMIN: %s  a LOZINKA: %s\n\n", usr, psw);
    if((strcmp(adm, usr) == 0) && (strcmp(pas, psw) == 0))
    {
      break;
    }else
    {
      printf("\tADMIN: %s  a LOZINKA: %s\n\n", usr, psw);
      printf("\n\n\t>>> Nepravilan unos podataka <<<\n\t    Pokusajte ponovo. ( Za izlaz iz programa unesite 0 ili koristite ctr+c )\n\n" );
    }
  }while(1);


  printNaslov();
  printChar('-', 49);
  //isprazniBafer();
  while (1)
  {
    printNaslov();
    printf("\n\n\t1. DODAJ studenta\n\n");
    printf("\t2. LISTA studenta\n\n");
    printf("\t3. IZMENI studenta\n\n");
    printf("\t4. OBRISI studenta\n\n");
    printf("\t5. PRETRAZI\n\n");
    printf("\t6. PODESAVANJE NALOGA\n\n");
    printf("\t0. IZLAZ \n\n");
    printf("    >>> Unesite opciju koju zelite: --> ");
    kon = 0;
    scanf("%s", op);
    //problem sa praznjenjem bafera prilikom istovremenog korsrenja getline i funkcije getpass!!! Pitati prof
    //getline (&str, &nbajt, stdin);
    d = strlen(op);
    kon =  sscanf(op,"%d",&opcija);
    if((kon != 1) || (d > 1))
    {
      opcija = 7;
      //kon = 1;
    }
    switch(opcija)
    {
        case 0: return 1;

        case 1: dodaj_s(fp);
                break;
        case 2: lista_s(fp);
                break;
        case 3: izmeni(fp);
                break;
        case 4: fp = obrisi(fp);
                break;
        case 5: pretrazi(fp);
                break;
        case 6: izmena_naloga(fp);
                break;
        default: printf("\n\t\tPritisnuli ste pogresan taster.");
                  printf("\n\t\tZa IZLAZ iz programa pritisnite 0");
    }
  }
  return 0;
}

void printChar(char ch,int n)
{
    while(n--)
    {
        putchar(ch);
    }
}

void printNaslov()
{
  printf("\n\n\t");
  printChar('=',15);
  printf("[STUDENTSKI] [SERVIS] ");
  printChar('=',15);
  printf("\n\n");
}

void dodaj_s(FILE * fp)
{
  Student s;
  printNaslov();
  //char sledeci [] = "y" ;
  fseek(fp,0,SEEK_END);
	printf("\tUpisite IME studenta:  ");
  scanf("%s", s.ime);
  printf("\tUpisite PREZIME studenta:  ");
  scanf("%s", s.prezime);
  printf("\tUpisite BROJ INDEKSA u formatu ET1/2000:  ");
  scanf("%s", s.br_ind);
  fwrite(&s,sizeof(s),1,fp);
  printf("\n");
}

void izmena_naloga(FILE *fp)
{
  int flag=0, kon, opcija, d;
  char op[]="";
  while(flag != 1)
  {
    printNaslov();
    printf("\n\n\t1. IZMENI KORISNICKO IME I LOZINKU\n\n");
    printf("\t0. IZLAZ\n\n");
    printf("    >>> Unesite opciju koju zelite: --> ");
    kon = 0;
    scanf("%s", op);
    d = strlen(op);
    kon =  sscanf(op,"%d",&opcija);
    if((kon != 1) || (d > 1))
    {
      opcija = 3;
    }
    switch(opcija)
    {
        case 0: flag = 1;
                break;
        case 1: promena(fp);
                break;
        default: printf("\n\t\tPritisnuli ste pogresan taster.");
                  printf("\n\t\tZa IZLAZ iz programa pritisnite 0");
    }

  }
}

void promena(FILE *fp)
{
  int flag = 0;
  char *pas, *pas1, *pas2, adm[16], usr[16], psw[16], loz[16];
  size_t greska_w1,greska_w2 ,greska_r1, greska_r2, ob_count = 1, vel = 16;

//procitaj trenutno ime i loz
  rewind(fp);
  greska_r1 = fread (&usr, vel, ob_count, fp);
  greska_r2 = fread (&psw, vel, ob_count, fp);
  if ((greska_r1 != ob_count) || (greska_r2 != ob_count))
  {
    printf ("Greska prilikom prilikom izmene podataka. Pokusajte ponovo\n");

  }else
  {
    do
    {
      printNaslov();
      printf("\n\tUpisite administratorsko ime: --> " );
      scanf("%s", adm);
      if((strcmp(adm, "0") == 0))
      {
        break;
      }
      pas = getpass("\n\t             Upisite lozinku: --> ");
      if((strcmp(adm, usr) == 0) && (strcmp(pas, psw) == 0))
      {
        do{
            printf("\n\tUpisite novo administratorsko ime: --> " );
            scanf("%s", adm);
            pas1 = getpass("\n\t      Upisite novu lozinku: --> ");
            pas2 = getpass("\n\t         Potvrdite lozinku: --> ");
            if(strlen(adm) < 5)
            {
             printf("\nIme mora da sadrzi minimum 5 slova a maksimum 15.\n");
            }else if(strlen(pas1) < 4)
            {
              printf("\nLozinka mora da sadrzi minimum 4 karaktera a maksimum 15.\n");
            }else if(strcmp(pas1, pas2) != 0)
            {
              printf("Lozinke nisu iste. Molimo pokusajte ponovo.\n");
            }
            else
            {
              //upisi u fajl
              rewind(fp);
              greska_w1 = fwrite (&adm, vel, ob_count, fp);
              fseek(fp, vel, SEEK_SET);
              //PROBLEM
              strcpy(loz, pas);
              printf("LOZ: %s , PAS: %s\n",loz,pas);
              greska_w2 = fwrite (&loz, vel, ob_count, fp);
              printf("Ime admina1 je: -> %s a lozinka1 je: -> %s\n\n",usr, psw);
              if ((greska_w1 != ob_count) || (greska_w2 != ob_count))
              {
                printf ("Greska prilikom izmene podataka.\n");
              }else
              {
                flag = 1;
                break;
              }

            }
        }while(1);
        //noovo ime
      }else
      {
        printf("\n\n\t>>> Nepravilan unos podataka <<<\n\t    Pokusajte ponovo. ( Za izlaz iz programa unesite 0 ili koristite ctr+c )\n\n" );
      }
    }while(flag != 1);
  }
}
void lista_s(FILE * fp)
{
  Student s;
  size_t vel = 32;
  printNaslov();
  int i, siz=sizeof(s), podaci;
  fseek(fp,vel,SEEK_SET);
  //sassssssssssssssss
  if(fread(&s,siz,1,fp) == 0)
  {
    printf("\n\n\t");
    //printChar('',44);
    printf("\n\tTrenutno nema upisanih studenta u sistemu.\n\t");
    printChar('^',44);
  }else
  {
    fseek(fp,vel,SEEK_SET);
    while((fread(&s,siz,1,fp)) == 1)
    {
       printf("\n\n\tIME : %s",s.ime);
       printf("\n\n\tPREZIME : %s\t",s.prezime);
       printf("\n\n\tBROJ INDEKSA : %s\n\t",s.br_ind);
       printChar('-',30);
    }
  }

  printf("\n\n\t");
  printChar('*',30);
  printf("kraj");
  printChar('*',30);
  printf("\n");
  //system("pause");

}
void izmeni(FILE *fp)
{
  printNaslov();
  Student s;
  char str[15];
  int flag=0, siz=sizeof(s), greska;
  printf("\n\n\tUnesite broj indeksa za studenta koga zelite menjati.");
  printf("\n\n\t\t\tBROJ INDEKSA: --> ");
  scanf("%s", str);

  rewind(fp);

  while(((fread(&s,siz,1,fp)) == 1))
  {
    if ((strcmp(str, s.br_ind) == 0))
    {
      flag=1;
      break;
    }
  }

  if(flag==1)
    {
      fseek(fp,-siz,SEEK_CUR);
      printf("\n\n\t\t>Upisite nove podatke za studenta<");
      printf("\n\n\tUpisite IME studenta:  ");
      scanf("%s", s.ime);
      printf("\n\tUpisite PREZIME studenta:  ");
      scanf("%s", s.prezime);
      printf("\n\tUpisite BROJ INDEKSA u formatu ET1/2000:  ");
      scanf("%s", s.br_ind);

      fwrite(&s,siz,1,fp);

      printf("\n\n\t* USPESNO STE IZVRSLI IZMENE.");
      printf("\n\n\t  Podaci o studentu nakom izmene:\n\t %s\n\t %s\n\t %s\n",s.ime, s.prezime, s.br_ind);
      printf("\n\n\t");
    }else
    {
      printf("\n\n\t\t  >>> STUDENT NIJE PRONADJEN <<<");
      printf("\n\n\t\t    - Proverite da li ste ispravno uneli podatke." );
      printf("\n\n\t\t    - Zatim proverite listu studenata i uverite se da nije prazna!\n\t");
    }
}

FILE * obrisi(FILE *fp)
{
  FILE *ft;
  Student s;
  char str[15];
  int greska, flag=0, siz=sizeof(s);

  printNaslov();

  if((ft=fopen("temp.txt","wb+"))==NULL)
  {
     printf("\n\n\t\t\t\t>>>GRESKA: prilikom otvaranja fajla !!!\n\t\t");
     return fp;
  }

  printf("\n\n\tUnesite broj indeksa za studenta koga zelite obrisati.");
  printf("\n\n\t\t\tBROJ INDEKSA: --> ");
  scanf("%s",str);
  rewind(fp);
  while( (fread(&s,siz,1,fp)) == 1)
  {
    if ((flag == 0) && (strcmp(str, s.br_ind) == 0))
    {
      flag=1;
    }
    else
    {
      fwrite(&s,siz,1,ft);
    }
  }

  greska = fclose (fp);
  if(greska != 0){
    printf(">>> GRESKA prilikom zatvaranja fajla !!!\n");
  }
  greska = fclose (ft);
  if(greska != 0){
    printf(">>> GRESKA prilikom zatvaranja fajla !!!\n");
  }

  remove("studentInfo.txt");
  rename("temp.txt","studentInfo.txt");

  if((fp=fopen("studentInfo.txt","rb+"))==NULL)
  {
     printf(">>> GRESKA prilikom otvaranja fajla !!!");
     return  NULL;
  }

  if(flag == 1)
  {
    printf("\n\n\t* STUDENT JE USPESNO OBRISAN.\n");
  }else
  {
    printf("\n\n\t\t  >>> STUDENT NIJE PRONADJEN <<<");
    printf("\n\n\t\t    - Proverite da li ste ispravno uneli podatke." );
    printf("\n\n\t\t    - Zatim proverite listu studenata i uverite se da nije prazna!\n\t");
  }

  printChar('-',75);
  printf("\n\t");
  return fp;

}
void pretrazi(FILE *fp)
{
  Student s;
  char str[20];
  int i=0, flag1=0, flag2=0, siz=sizeof(s);
  printf("\n\n\tUpisite tekst za pretragu: --> ");
  scanf("%s", str);
  rewind(fp);
  while( (fread(&s,siz,1,fp)) == 1)
  {
    while(i <= strlen(str)-1)
    {
      if ((flag1 == 0) && (str[i] == s.ime[i]))
      {
        if(str[i+1] == '\0')
        {
          printf("\n\tREZULTAT PRETRAGE:\n" );
          printf("\n\n\tIME : %s",s.ime);
          printf("\n\n\tPREZIME : %s\t",s.prezime);
          printf("\n\n\tBROJ INDEKSA : %s\n\t",s.br_ind);
          printChar('-',30);
          flag2=1;
        }
      }else
      {
        flag1 = 1;
      }

      if((flag2 == 0) && (str[i] == s.prezime[i]))
      {
        if(str[i+1] == '\0')
        {
          printf("\n\tREZULTAT PRETRAGE:\n" );
          printf("\n\n\tIME : %s",s.ime);
          printf("\n\n\tPREZIME : %s\t",s.prezime);
          printf("\n\n\tBROJ INDEKSA : %s\n\t",s.br_ind);
          printChar('-',30);
        }
      }else
      {
        flag2 = 1;
      }
      i += 1;
    }

    flag1 = 0;
    flag2 = 0;
    i = 0;
  }

}





//==============================================
