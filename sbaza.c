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
void printChar(char ch, int n);
void printNaslov();

void isprazniBafer() {
    while(getchar() != '\n')
    { };
}

int main()
{
  FILE * fp;
  Student s;
  int opcija, kon;
  char adm[15];
  char loz[15];
  char c, *str;
  char k;
  size_t nbajt = 100;
  int d;
  if((fp=fopen("studentInfo.txt","rb+"))==NULL)
  {
    if((fp=fopen("studentInfo.txt","wb+"))==NULL)
    {
      printf("can't open file");
      return 0;
    }
  }

  do
  {
    printNaslov();
    printf("\n\tUpisite administratorsko ime: --> " );
    scanf("%s", adm);
    printf("\n\t             Upisite lozinku: --> ");
    scanf("%s", loz);
    if((strcmp(adm, "admin") == 0) && (strcmp(loz, "1234") == 0))
    {
      break;
    }else
    {
      printf("\n\n\t>>> Nepravilan unos podataka <<<\n\t    Pokusajte ponovo.\n\n" );
    }
  }while(1);

  printNaslov();
  //printf("\n\tadmin: admin\n\tlozinka: none\n\n\t");
  printChar('-', 49);

  isprazniBafer();
  while (1)
  {
    printNaslov();
    printf("\n\n\t1. DODAJ studenta\n\n");
    printf("\t2. LISTA studenta\n\n");
    printf("\t3. IZMENI studenta\n\n");
    printf("\t4. OBRISI studenta\n\n");
    printf("\t5. PRETRAZI\n\n");
    printf("\t0. IZLAZ \n\n");
    printf("    >>> Unesite opciju koju zelite: --> ");
    kon = 0;
    getline (&str, &nbajt, stdin);
    d = strlen(str);
    kon =  sscanf(str,"%d",&opcija);
    if((kon != 1) || (d > 2))
    {
      opcija = 6;
      kon = 1;
    }

    printf("Duzina: %d\n", d);
    printf("Opcija je: %d\n", opcija);
    switch(opcija)
    {
        case 0: return 1;
                break;
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
        default: printf("\n\t\tPritisnuli ste pogresan taster.");
                  printf("\n\t\tZa IZLAZ iz programa pritisnite 0");
    }
    //opcija=6;
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

void lista_s(FILE * fp)
{
  Student s;
  printNaslov();
  int i, siz=sizeof(s), podaci;
  rewind(fp);
  if(fread(&s,siz,1,fp) == 0)
  {
    printf("\n\n\t");
    //printChar('',44);
    printf("\n\tTrenutno nema upisanih studenta u sistemu.\n\t");
    printChar('^',44);
  }else
  {
    rewind(fp);
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
