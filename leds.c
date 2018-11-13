#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
	FILE * fp;
  FILE * fp1;
  FILE * fp2;
	float procenat = 0;
	long int period = 20000L;
  int vr1, vr2, flag1 = 0, flag2 = 0;
	char *str;
  size_t bajt = 1;


  while(1)
	{
    //rad sa tasterima
    //Citanje vrednosti prvog tastera
    fp1 = fopen ("/sys/class/gpio/gpio956/value", "r");
    if(fp1==NULL)
    {
      puts("Problem pri otvaranju fajla Taster1\n");
    }
    str = (char *)malloc(bajt+1);
    getline(&str, &bajt, fp1);

    if(fclose(fp1))
    {
      puts("Problem pri zatvaranju fajla Taster1.\n");
    }
    sscanf(str, "%d", &vr1); //konverzija
    free(str);

    //Citanje vrednosti drugog tastera
    fp2 = fopen ("/sys/class/gpio/gpio957/value", "r");
    if(fp2==NULL)
    {
      puts("Problem pri otvaranju fajla Taster2\n");
    }
    str = (char *)malloc(bajt+1);
    getline(&str, &bajt, fp2);

    if(fclose(fp2))
    {
      puts("Problem pri zatvaranju fajla Taster2.\n");
    }
    sscanf(str, "%d", &vr2);
    free(str);

    if ((vr1 == 1) && (flag1 == 0) && (procenat < 1))
    {
      procenat += 0.2;
      flag1 = 1;
    }else if(vr1 == 0)
    {
      flag1 = 0;
    }else if ((vr2 == 1) && (flag2 == 0) && (procenat > 0))
    {
      procenat -= 0.2;
      flag2 = 1;
    }else if(vr2 == 0)
    {
      flag2 = 0;
    }

    // rad sa diodama
		fp = fopen("/proc/myled", "w");
		if(fp == NULL)
		{
			printf("Neuspesno otvaranje fajla /proc/myled za upis.\n");
			return -1;
		}
		fputs("0xFF\n", fp);
		fclose(fp);
		usleep(procenat*period);

		fp = fopen("/proc/myled", "w");
		if(fp == NULL)
		{
      printf("Neuspesno otvaranje fajla /proc/myled za upis.\n");
			return -1;
		}
		fputs("0x00\n", fp);
		fclose(fp);
		usleep((1-procenat)*period);
	}
	return 0;
}
