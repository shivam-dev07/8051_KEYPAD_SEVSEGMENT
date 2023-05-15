#include<reg51.h>
 
#define LEDPORT	P2		//Connect 8 lins of Sevenegment Display here

#define		ZERO	0xC0
#define 	ONE	  0xF9
#define 	TWO		0xA4
#define 	THREE	0xB0 
#define 	FOUR	0x99
#define 	FIVE	0x92 
#define 	SIX		0x82 
#define 	SEVEN	0xF8
#define 	EIGHT	0x80 
#define 	NINE	0x90 

    //Function declarations
    void cct_init(void);
    void delay(int);
    char READ_SWITCHES(void);
    char get_key(void);
		void writedata(key); 

    //*******************
    //Pin description
    /*
    P2 is 7 seg data
    P1.0 to P1.3 are keypad row outputs
    P1.4 to P1.7 are keypad column inputs
    */
    //********************
    // Define Pins
    //********************
    sbit RowA = P1^0;     //RowA
    sbit RowB = P1^1;     //RowB
    sbit RowC = P1^2;     //RowC
    sbit RowD = P1^3;     //RowD

    sbit C1   = P1^4;     //Column1
    sbit C2   = P1^5;     //Column2
    sbit C3   = P1^6;     //Column3
    sbit C4   = P1^7;     //Column4


    // ***********************************************************
    // Main program
    //
    int main(void)
    {
       char key;                // key char for keeping record of pressed key

       cct_init();              // Make input and output pins as required
      
       while(1)
       { 
         key = get_key();       // Get pressed key
         writedata(key);        // Echo the key pressed to seven seg led
       }
    }

    void cct_init(void)
    {
        P0 = 0x00;   //not used
        P1 = 0xf0;   //used for generating outputs and taking inputs from Keypad
        P2 = 0x00;   //used as data port for seven seg led
         
    }

  

    char READ_SWITCHES(void)    
    {   
        RowA = 0; RowB = 1; RowC = 1; RowD = 1;     //Test Row A

        if (C1 == 0) { delay(10000); while (C1==0); return '7'; }
        if (C2 == 0) { delay(10000); while (C2==0); return '8'; }
        if (C3 == 0) { delay(10000); while (C3==0); return '9'; }
        if (C4 == 0) { delay(10000); while (C4==0); return '/'; }

        RowA = 1; RowB = 0; RowC = 1; RowD = 1;     //Test Row B

        if (C1 == 0) { delay(10000); while (C1==0); return '4'; }
        if (C2 == 0) { delay(10000); while (C2==0); return '5'; }
        if (C3 == 0) { delay(10000); while (C3==0); return '6'; }
        if (C4 == 0) { delay(10000); while (C4==0); return 'x'; }

        RowA = 1; RowB = 1; RowC = 0; RowD = 1;     //Test Row C

        if (C1 == 0) { delay(10000); while (C1==0); return '1'; }
        if (C2 == 0) { delay(10000); while (C2==0); return '2'; }
        if (C3 == 0) { delay(10000); while (C3==0); return '3'; }
        if (C4 == 0) { delay(10000); while (C4==0); return '-'; }

        RowA = 1; RowB = 1; RowC = 1; RowD = 0;     //Test Row D

        if (C1 == 0) { delay(10000); while (C1==0); return 'C'; }
        if (C2 == 0) { delay(10000); while (C2==0); return '0'; }
        if (C3 == 0) { delay(10000); while (C3==0); return '='; }
        if (C4 == 0) { delay(10000); while (C4==0); return '+'; }

        return 'n';             // Means no key has been pressed
    }

    char get_key(void)           //get key from user
    {
        char key = 'n';              //assume no key pressed

        while(key=='n')              //wait untill a key is pressed
            key = READ_SWITCHES();   //scan the keys again and again

        return key;                  //when key pressed then return its value
    }
		
		void writedata(key)
		{
			key = key - 48 ;
			switch (key)
			{
				case 0 : LEDPORT = ZERO ; break ;
				case 1 : LEDPORT = ONE ;  break;
				case 2 : LEDPORT = TWO ; break;
			  case 3 : LEDPORT = THREE ; break;
				case 4 : LEDPORT = FOUR ; break;
				case 5 : LEDPORT = FIVE ; break;
				case 6 : LEDPORT = SIX ; break;
				case 7 : LEDPORT = SEVEN ; break;
				case 8 : LEDPORT = EIGHT ; break;
				case 9 : LEDPORT = NINE ;
			}
		}
		
		 void delay(int a)
    {
       int i;
       for(i=0;i<a;i++);   //null statement
    }