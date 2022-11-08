#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main ()
{
	FILE* fp;
	float percentage = 0.0;
	float X;
	long int period = 20000L;
	char *str;
	char tval1,tval2,tval3,tval4;
	char sval1,sval2,sval3,sval4;
	size_t num_of_bytes = 6;
	
	

	while(1)
	{
		
		//Citanje vrednosti tastera
		fp = fopen ("/dev/button", "r");
		if(fp==NULL)
		{
			puts("Problem pri otvaranju /dev/button");
			return -1;
		}
		
		str = (char *)malloc(num_of_bytes+1); 
		getline(&str, &num_of_bytes, fp); 

		if(fclose(fp))
		{
			puts("Problem pri zatvaranju /dev/button");
			return -1;
		}
		
		tval1 = str[2] - 48;
		tval2 = str[3] - 48;
		tval3 = str[4] - 48;
		tval4 = str[5] - 48;

		free(str);
		
		sleep(1);
		
		//Citanje vrednosti sviceva
		fp = fopen ("/dev/switch", "r");
		if(fp==NULL)
		{
			puts("Problem pri otvaranju /dev/switch");
			return -1;
		}


		str = (char *)malloc(num_of_bytes+1); 
		getline(&str, &num_of_bytes, fp); 

		if(fclose(fp))
		{
			puts("Problem pri zatvaranju /dev/switch");
			return -1;
		}

		sval1 = str[2] - 48;
		sval2 = str[3] - 48;
		sval3 = str[4] - 48;
		sval4 = str[5] - 48;
		
		free(str);
		
		sleep(1);
		
		if(sval2 == 0 && sval1 == 0)
		{
			X = 0.05;
		}
		
		if(sval2 == 0 && sval1 == 1)
		{
			X = 0.1;
		}
		
		if(sval2 == 1 && sval1 == 0)
		{
			X = 0.15;
		}
		
		if(sval2 == 1 && sval1 == 1)
		{
			X = 0.2;
		}
				
		if(tval1 != 0)
		{
				percentage += 0.1;
		}
		if(tval4 != 0)
		{
				percentage -= 0.1;
		}
		if(tval2 != 0)
		{
				percentage += X;
		}
		if(tval3 != 0)
		{
				percentage -= X;
		}
		
		// Upali diode
		fp = fopen("/dev/led", "w");
		if(fp == NULL)
		{
			printf("Problem pri otvaranju /dev/led\n");
			return -1;
		}
		fputs("0x0Fs\n", fp);
		
		if(fclose(fp))
		{
			printf("Problem pri zatvaranju /dev/led\n");
			return -1;
		}
		usleep(percentage*period);
		
		
		// Ugasi diode
		fp = fopen("/dev/led", "w");
		if(fp == NULL)
		{
			printf("Problem pri otvaranju /dev/led\n");
			return -1;
		}
		fputs("0x00\n", fp);
		if(fclose(fp))
		{
			printf("Problem pri zatvaranju /dev/led\n");
			return -1;
		}
		usleep((1-percentage)*period);
	}
	
	return 0;
}
