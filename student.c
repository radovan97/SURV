#include<stdio.h>
#include<string.h>
#include<stdlib.h>
//#include<math.h>
//#include <termios.h>
//#include <unistd.h>

typedef struct { int id; char ime[15]; char prezime[15]; int ocene[15]; char br_ind[15]; } Student ;
void dodaj_s(FILE * fp);
FILE * obrisi(FILE * fp);
void izmeni(FILE * fp);
void lista_s(FILE * fp);
void pretrazi(FILE * fp);
void printChar(char ch, int n);
void printNaslov();
void isprazni_bafer();

int ID ;

int main()
{
  FILE * fp;
  Student s;
  size_t bajt = 1;
  int opcija, siz = sizeof(s), t, d, kon;
  char c, ch;

  if((fp=fopen("studentInfo.txt","rb+"))==NULL)
  {
    if((fp=fopen("studentInfo.txt","wb+"))==NULL)
    {
      printf("can't open file");
      return 0;
    }else
    {
      ID = 0;
    }
  }else
  {
    fseek(fp, -siz , SEEK_END);
    if((fread(&s,siz,1,fp)) == 1)
    {
      ID = s.id;
    }else
    {
      return 1;
    }
  }
  printNaslov();
  printChar('-', 49);
  while (1)
  {
    printNaslov();
    printf("\n\n\t1. DODAJ studenta\n\n");
    printf("\t2. LISTA studenta\n\n");
    printf("\t3. IZMENI studenta\n\n");
    printf("\t4. PRETRAZI studenta\n\n");
    printf("\t0. IZLAZ \n\n");
    printf("    >>> Unesite opciju koju zelite: --> ");
    scanf("%s", &ch);
    d = strlen(&ch);
    //getline(&s, bajt, stdin)

    kon = sscanf(&ch,"%d",&opcija);
    if((kon != 1) || (d > 1))
    {
      opcija = 5;
    }

    switch(opcija)
    {
        case 0: return 0;
                break;
        case 1: dodaj_s(fp);
                break;
        case 2: lista_s(fp);
                break;
        case 3: izmeni(fp);
                break;
        case 4: pretrazi(fp);
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

// void isprazni_bafer()
// {
//   while((getchar() != '\n') && (getchar() != '\0'))
//   {}
// }

void dodaj_s(FILE * fp)
{
  Student s;
  int i;
  printNaslov();
  fseek(fp,0,SEEK_END);
  ID += 1;
  s.id = ID;
	printf("\tUpisite IME studenta:  ");
  scanf("%s", s.ime);
  printf("\tUpisite PREZIME studenta:  ");
  scanf("%s", s.prezime);
  printf("\tUpisite BROJ INDEKSA u formatu ET1/2000:  ");
  scanf("%s", s.br_ind);
  printf("\tUpisite OCENE studenta: ");

  for(i=0; i < 3; i++)
  {
    printf("--> ");
    scanf("%d", &s.ocene[i]);
    printf("\t\t\t\t");
  }

  fwrite(&s, sizeof(s), 1, fp);
  printf("\n");
}

void lista_s(FILE * fp)
{
  Student s;
  printNaslov();
  int i, siz=sizeof(s), podaci;
  rewind(fp); //pocicioniraj se na pocetak fajla

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
       printf("\n\n\tRedni broj : %d",s.id);
       printf("\n\n\tIME : %s",s.ime);
       printf("\n\n\tPREZIME : %s\t",s.prezime);
       printf("\n\n\tBROJ INDEKSA : %s\n\t",s.br_ind);
       printf("\n\tOCENE : ");
       for(i = 0; i < 3; i++)
       {
         printf("| %d |",s.ocene[i]);
       }
       printf("\n\n\t");
       printChar('-',64);
    }
  }

  printf("\n\n\t");
  printChar('*',30);
  printf("kraj");
  printChar('*',30);
  printf("\n");

}

void izmeni(FILE *fp)
{
  printNaslov();
  Student s;
  int i,d,kon, opcija;
  char ch;
  int flag=0,uslov=0, siz=sizeof(s), greska, rb;
  printf("\n\n\tUnesite REDNI BROJ studenta koga zelite menjati.");
  printf("\n\n\t\t\tRedni broj: --> ");
  scanf("%d", &rb);
  //dodati kod...
  rewind(fp);

  while(((fread(&s,siz,1,fp)) == 1))
  {
    if (rb == s.id)
    {
      flag=1;
      break;
    }
  }

  if(flag == 1)
  {
      fseek(fp,-siz,SEEK_CUR);
      printf("\n\n\t1. izmeni IME\n\n");
      printf("\t2. izmeni PREZIME\n\n");
      printf("\t3. izmeni BROJ INDEKSA\n\n");
      printf("\t4. izmeni OCENE\n\n");
      printf("\t0. IZLAZ \n\n");


      printf("    >>> Unesite opciju koju zelite: --> ");
      scanf("%s", &ch);
      d = strlen(&ch);
      kon = sscanf(&ch,"%d",&opcija);
      if((kon != 1) || (d > 1))
      {
        opcija = 5;
      }

      switch(opcija)
      {
          case 0: uslov=1;
                  break;
          case 1:
                  printf("\n\n\tUpisite novo IME studenta:  ");
                  scanf("%s", s.ime);
                  break;
          case 2:
                  printf("\n\tUpisite novo PREZIME studenta:  ");
                  scanf("%s", s.prezime);
                  break;
          case 3:
                  printf("\n\tUpisite novi BROJ INDEKSA u formatu ET1/2000:  ");
                  scanf("%s", s.br_ind);
                  break;
          case 4:
                  printf("\n\tUpisite nove OCENE studenta: ");
                  for(i=0; i < 3; i++)
                  {
                    printf("--> ");
                    scanf("%d", &s.ocene[i]);
                    printf("\t\t\t\t     ");
                  }
                  break;
          default: printf("\n\t\tPritisnuli ste pogresan taster.");
                  printf("\n\t\tZa IZLAZ iz programa pritisnite 0");
                  izmeni(fp);
      }

    fwrite(&s,siz,1,fp);
    printf("\n\n\t* USPESNO STE IZVRSILI IZMENE\n\n");
  }else
  {
    printf("\n\n\t\t  >>> STUDENT NIJE PRONADJEN <<<");
    printf("\n\n\t\t    - Proverite da li ste ispravno uneli podatke." );
    printf("\n\n\t\t    - Zatim proverite listu studenata i uverite se da nije prazna!\n\t");
  }

}


void pretrazi(FILE *fp)
{
  Student s;
  char str[20];
  int i, flag=0, siz=sizeof(s);
  printf("\n\n\tUpisite tekst za pretragu po prezimenu: --> ");
  scanf("%s", str);
  rewind(fp);

  while( (fread(&s,siz,1,fp)) == 1)
  {
      //s.prezime
    //strcmp(str, nekistr)
    for(i = 0; i <= strlen(str)-1; i++)
    {
      if(str[i] == s.prezime[i])
      {
          if(i == strlen(str)-1)
          {
            printf("\n\tREZULTAT PRETRAGE:\n" );
            printf("\n\n\tRedni broj: %d", s.id);
            printf("\n\n\tIME : %s",s.ime);
            printf("\n\n\tPREZIME : %s\t",s.prezime);
            printf("\n\n\tBROJ INDEKSA : %s\n\t",s.br_ind);
            printf("\n\tOCENE : ");
            for(i = 0; i < 3; i++)
            {
              printf("| %d |",s.ocene[i]);
            }
            printf("\n\n\t");
            printChar('-',64);
            flag = 1;
          }
       }else
       {
         i = strlen(str);
       }
    }
  }

  if(flag !=1)
  {
    printf("\n\t>>> Nema prezime koje procinje sa `%s` <<<\n", str);
  }
}

//==============================================
