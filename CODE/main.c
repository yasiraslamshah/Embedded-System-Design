/********************************************
***********YASIR ASLAM SHAH ***********
*********************************************/
/********************************************
***********LAB 3 REQUIRED***********
*********************************************/
/*1.allocate heap 0f 3000 bytes*/
#include <mcs51/at89c51ed2.h>
#include <stdio.h>
#include <mcs51reg.h>
#include <malloc.h>
#define HEAP_SIZE 3000   // size must be smaller than available XRAM
__xdata unsigned char heap[HEAP_SIZE];
int atoi(char *s);
/********************************************
***********SDCC EXTERNAL STARTUP***********
*********************************************/
_sdcc_external_startup()
{
    AUXR|= 0x0C;
    init_dynamic_memory(heap, HEAP_SIZE);
    return 1;
}
/********************************************
***********DEBUG function defnition***********
*********************************************/
void debug(unsigned char debugchar)
{
    __xdata unsigned char *p = (__xdata unsigned char *)(0xFFFF);
    *p = debugchar;
}
/********************************************
***********Putchar function defnition***********
*********************************************/
void putchar (char z )
{
    SBUF = z;  	// load serial port with transmit value
	while (TI == 0); // wait for TX ready, spin on TI
	TI = 0;  	// clear TI flag
}
/********************************************
***********Putstr function defnition***********
*********************************************/
int putstr (char *s)
{
	int i = 0;
	while (*s){			// output characters until NULL found
		putchar(*s++);
		i++;
	}
	putchar('\r\n');
	return i+1;
}
/********************************************
***********Getchar function defnition***********/
/*********************************************/

char getchar ()
{
	unsigned char cc;
  	while (RI == 0);
  	cc = SBUF;
	RI = 0;			// clear RI flag
	putchar(cc);
	return cc;  	// return character from SBUF
}
char str[100];

//2.use pointers to allocate buffer_0 of 32-24000 bytes(eveny divisible by 16) using malloc in XRAM*
//	if buffer fails
//	tell user and allocate buffer of small memory,


//3.use pointers to allocate buffer_1 of 32-24000 bytes(eveny divisible by 16) using malloc in XRAM
	//if buffer fails
	//tell user and allocate buffer of small memory,*/

/********************************************
***********Main function defnition***********
*********************************************/

    void main()
{        //  variable

            unsigned int x1;
        __xdata unsigned int bsize[100];
        __xdata unsigned char *bAdress[100];
        __xdata unsigned char * buffer0;  // pointers
        __xdata unsigned char * buffer1;
        __xdata unsigned char * buffern;
        __xdata unsigned int  bCount=0;
        __xdata unsigned int Nofchar=0;
        __xdata volatile unsigned char start  = 0;
        __xdata unsigned char c;
        __xdata unsigned char t;
        __xdata unsigned int b0char=0;
        __xdata unsigned int b1char=0;
         __xdata unsigned int count1=10;
        __xdata unsigned int b00char=0;
        __xdata unsigned int  b11char=0;
        __xdata signed int bnumber=0;
        __xdata unsigned int bufferNo=0;
        __xdata unsigned int bufferLen=0;
        __xdata volatile unsigned int bufferDat=0;
        __xdata unsigned int bufferAdd=0;
        __xdata unsigned int counter=0;
       __xdata unsigned int newcounter=0;
        char str[100];

//char string

//serial communication
        TMOD |= 0x20;
        SCON |= 0x50;
        TH1  = 0xFD;
        TL1  = 0xFD;
        TR1  = 1;
       printf_tiny("\r++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
       printf_tiny("\r++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
//allocating buffer to NULL
        buffer0 = 0;
        buffer1 = 0;
        buffern = 0;

//start point
  start: printf_tiny("\r++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
      printf_tiny("\r\nEnter the Buffer0 and Buffer1 size between 32 and 3000,divisible by 16:\n");
//get character from keyboard for the sze of buffers
label1: gets(str);
        x1=atoi(str);
        if((x1%16)!=0)      //not divisible by zero
            {
            printf_tiny("\r++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
            printf_tiny("\r\nPlease print a size divisible by 16 in range given above:\n");
            goto label1;
            }
        else

    do//value of size must be between 32 and 3000
        //if buffer size is proper  then buffer is allocated as per space avaialble
    {
        if ((x1>=32) && (x1<=3000))
        {   buffer0 = (__xdata unsigned char*)malloc(x1);//allocating buffer0 pointer to the starting of malloc for buffer0 of x1
            buffer1 = (__xdata unsigned char*)malloc(x1);//allocating buffer0 pointer to the starting of malloc for buffer1 of x1
                        if (((buffer0) != 0)&&((buffer0) != 0))  //allocate buffer0
                                {   printf_tiny("\r\n Congrats! BUFFER0 ALOOCATED!");//printing successfull allocation message
                                    printf_tiny("\r\n Congrats! BUFFER1 ALLOCATED!");//printing successfull allocation message
                                    printf_tiny("\n\r++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
                                bsize[0]=x1;//size of buffer 0
                                bsize[1]=x1;//size of buufer 1

                                }
                        else    {
                                    free(buffer0);//if the buufer is not allocated then free buffer 0
                                    printf_tiny("\r\nMALLOC FAILED, BUFFER0 & BUFFER1 FAILED.Enter a smaller size");
                                        //priting messgae that buffer 0 and buffer1 failed
                                    printf_tiny("\r\nBUFFER0 Freed!");//message dispalyed to show that the buffer 0 has been freed from memory
                                    gets(str);//again read data from keyboard for the proper sizes of buffer0 and 1
                                    x1=atoi(str);//use atoi function to use that string of data as int data type
                                }
        }
        else{
                printf_tiny("\r\nPleas enter a proper smaller size in range between 32 and 400 only\n");
                goto label1;
            }
      }while((buffer0 ==NULL)||(buffer1 ==NULL));
//storing buffer address and length using different pointers already initialised above
bAdress[0]=buffer0;//saving the address for buffer 0 using buffer0 pointer in bAdress[0]
bAdress[1]=buffer1;//saving the address for buffer 1 using buffer1 pointer in bAdress[0]
bsize[0]=x1;//bsize holds the value for the size of buffer0
bsize[1]=x1;//bsize holds the value for the size of buffer1
bCount=bCount+2;//bcount is the number of buffer in heap,it includes buffer0 and buffer1 and will increment as per new allocation of buffers

while(start == 0)

{ debug(0x01);
    //read character from keyboard
    printf_tiny("\r\nEnter a character: ");//printing a character or command
c=getchar();//char C type will represent the value from keyboard input
Nofchar++; //Noofchar is an counter to keep count of characters recieved
//For Uppercase, store all uppercase to buffer 0
/********************************************************************************************************************/
/*******************************************        UPPERCASE     ****************************************************************/
/********************************************************************************************************************/

    if ((c >= 'A')&&(c <= 'Z'))//for upper case from A to Z
        {if (b0char<bsize[0])
            {   *(buffer0+b0char) = c; //incase of UPPERCASE,save the character in buffer0+b0char(a counter to move across buffer0)
                b0char++;//increment the b0char and save the charcters in incremented position in buffer0
           printf_tiny("\nSTORING UPPERCASE IN BUFFER0");//display message that uppercase is saved in buffer0
           }else printf_tiny("\tBUFFER0 FULL!");
           }


/********************************************************************************************************************/
/*******************************************        numbers     ****************************************************************/
/********************************************************************************************************************/

    else if ((c >= '0')&& (c <= '9'))//if the character recieved is number then save the number in buffer1
//For numbers, store all uppercase to buffer 1
            {if (b0char<bsize[0])
            {   *(buffer1+b1char) = c;//save the character recievd in buffer1+b1char(a counter to transverse through buffer1
                    b1char++;//increment buffer address by one for next storing element incase of number
            printf_tiny("\nSTORING NUMBER IN BUFFER1");//display the message that number is storesd in buffer1
             }else printf_tiny("\tBUFFER1 FULL!");
             }
    else//if the number is not UPPERCASE or Number than do the follwing
    {

        switch(c)//using switchcases for other characters and commands other than UPPERCASE and numbers


    //case1 is plus sign, using this a new buffer is allocated of size between 40 and 200
/********************************************************************************************************************/
/*******************************************        case1'+'     ****************************************************************/
/********************************************************************************************************************/
{


        case'+'://CASE1 IS plus SIGN'+'

                    printf_tiny("\r================================================================================\n");//DECORATION
                    printf_tiny("\r|\t\t\tADDING BUFFEER!                                                              |");
                    printf_tiny("\n\r==============================================================================\n");//DECORATION
                    printf_tiny("\n\rADD A NEW BUFFER \n");//DISPLAY MESSAGE TO ADD NEW BUFFER
                    printf_tiny("\r\nENTER A NEW BUFFER OF SIZE BETWEEN 40 AND 400 BYTES:\  n");//DISPLAY MESSAGE TO INDICATE SIZE
                    x1 = 0;//CLEAR THE INT X1
                    gets(str);//RECIVE FROM INPUT(KEYBOARD)
                    x1=atoi(str);//USING ATOI FUNCTION TO TRANSFER THE DATA TYPE FROM STRING TO INT TO BE USED

                        do
                            {
                            if ((x1>=40) && (x1<=400))//IF THE RECIEVED INPUT IS IN RANGE OF 40 AND 400 THEN ITS PERFECT SIZE!
                                {   buffern = (__xdata unsigned char*)malloc(x1);//ALLOCATE A NEW BUFFER USING MALLOC
                                    if (((buffern) != 0))  //IF BUFFERN IS NOT NULL THEN ITS SUCCESSFULLY CREATED
                                            {printf_tiny("\r\n Congrats! BUFFERN ALOOCATED!");//PRINT THE CONGRATULATIONS MESSAGE
                                   bAdress[bCount]=buffern;//allocate  buffern to bAdress[bcount]
                                   bsize[bCount]=x1;//allocating the size to bsize[count]
                                   bCount++;//increment counter  }else printf_tiny("BUFFER0 FULL!");
                                            }
                                    else {printf_tiny("\r\nMALLOC FAILED, BUFFERN FAILED.");}//ELSE IF IT FAILS,GIVE THEBAD NEWS
                                }
                            else    {
                                printf_tiny("\n\nOOPS! Error\n");//PRINT THAT THE BUFFER ALLOCATION FAILED
                                    printf_tiny("\n\rSIZE OUT OF RANGE.BUFFERN FAILED!");}//IF THE INPUT SIZE IS NOT FOLLOWING THE RANGE THEN OOPS!ERROR
                            }   while((buffern ==NULL)||(buffern ==NULL));//CHECK THE CONDITION FOR DO-WHILE LOOOP
                                break;//BREAK FROM THIS CASE

//case2 is Minus and a buffer will be deleted as specified by the user.
/********************************************************************************************************************/
/*******************************************        case2'-'     ****************************************************************/
/********************************************************************************************************************/

        case'-':        printf_tiny("\r================================================================================\n");//DECORATION
                        printf_tiny("\r\t\t\tDELETE BUFFER!                                                            \n");//DECORATION
                        printf_tiny("\n\r===============================================================================\n");//DECORATION
                    printf_tiny("\r++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
                    printf_tiny("\r\nSPECIFY BUFFER NUMBER TO BE DELETED FROM MEMORY:");//PRINT MESSAGE TO DELETE
                    bnumber= 0;//USING A NEW VARIABLE TO INPUT BUFFER NUMBER
                    gets(str);//RECEIVING BUFFER NUMBER USING GETS FUNCTION
                    bnumber=atoi(str);////USING ATOI FUNCTION TO TRANSFER THE DATA TYPE FROM CHAR TO INT
                        if((bnumber<= 0) || (bnumber>=9))//IF THE INPUT IS NOT A DECIMAL
                                {printf_tiny("\r\nEnter  a valid number decimal number greater than 1");}//PRINTING A MESSAGE TO INPUT DECIMAL NUMBER
                        else if((bnumber>= 0)&& (bnumber <= 9))//ELSE IF THE INPUT IS BETWEEN 0-9,THEN PROCEED FURTHER
                                {       if(bnumber<2)//IF INPUT IS 0 OR 1 GIVE AN ERROR AS BUFFER 0 AND BUFFER1 ARE INDISPENSIBLE
                                        {printf_tiny("CANNOT DELETE BUFFER0 and BUFFER1");}//I TOLD YOU! YOU DONT MESS WITH BUFFER 0 AND BUFFER 1
                                        else if (bnumber >=2 )//ELSE IF THE INPUT IS BETWEEN 2-9 THEN PROCEED TO DELELTION
                                        {   free (bAdress[bnumber]);//FREE THAT POOR BUFFER USING BUFFERNAME[BUFFERNUMBER]
                                            bAdress[bnumber] = 0;
                                            bsize[bnumber] = 0;
                                            bCount=bCount-1;
                                            printf_tiny("\r\n BUFFER%d DELETED SUCCESSFULLY",bnumber);
                                        }
                                }
        break;

/********************************************************************************************************************/
/*******************************************        case3'@'     ****************************************************************/
/********************************************************************************************************************/
      //case3 is @ and this command will delete all buffers and free heap and return to start

        case '@':
                        printf_tiny("\r================================================================================\n");//DECORATION
                       printf_tiny("\r\t\t\tFREE HEAP!CONSERVE SPACE!                                                 \n");
                        printf_tiny("\n\r==============================================================================\n");//DECORATION
                       printf_tiny("\r\nSELECTED COMMAND WILL FREE ALL BUFFERS.Continue(Y/N)?");//PRINTING MESSAGE,ASKING USER WHETHER TO FREE THE HEAP OR NOT
                    t=getchar();//RECIEVE A POSITIVE OR NEGATIVE ANSWER AS YES OR NO
                        if((t =='N')||(t =='n'))//IF USER ANSWERS NO,TERMINATE THE FREEING PROCESS
                            {printf_tiny("\r\n\tPROCESS TERMINATED.\n");//DISPLAY THE RESULT AS NOT FREEING BUFFERS
                             break;}//BREAK FROM THE SWITCH CASE
                        else if((t =='y')||(t =='Y'))//IF YES, FREE ALL THE BUFFERS
                            {
                            printf_tiny("\r\n\tFREEING ALL BUFFERS\n");//DISPLAY THE MESSAGE
                            bufferNo=0;//COUNTER TO INITAILISE FROM BUFFER ZERO TILL BUFFER N
                                for(bufferNo=0;bufferNo<101;bufferNo++)//THIS LOOP WILL TRAVEL FROM BUFFER ZERO TILL BUFFER N
                                    {
                                        free(bAdress[bufferNo]);//FREE BUFFER
                                        bAdress[bufferNo]=0;//FREE THE ADDRESS
                                        bsize[bufferNo]=0;//FREE THE SIZE PARAMETERS
                                    }
                             }
                        bCount= 0;//IF FREED ALL BUFFERS, BUFFER COUNT IS ZERO NOW
                        printf_tiny("\nSTARTING AGAIN\n");//STARTING AGAIN
                        printf_tiny("\nWELCOME AGAIN!\n");//WELCOME USER WARMLY

                         //start == 1;
                         goto start;//GO TO START
        break;//BREAK FROM THIS CASE SWITCH

        /********************************************************************************************************************/
/*******************************************        case4'='     ****************************************************************/
/********************************************************************************************************************/
         case '='://case 4 is "=" and this command will show the contents of buffer 0 and buffer 1
                        printf_tiny("\r================================================================================\n");//DECORATION
                       printf_tiny("\r\t\t\tADDRESS OF BUFFERS IN HEX                                                  \n");
                        printf_tiny("\n\r================================================================================\n");//DECORATION

                        printf_tiny("\r\nSELECTED OPTION WILL SHOW THE CONTENTS OF BUFFER0 AND BUFFER1");//BUFFER CONTENTS ALONG WITH ADDRESSES IS SHOWN FOR EXISTING BUFFERS
                       printf_tiny("\r\n");//NOTHING BUT A NEW LINE SO THAT THE INTERFACE IS NOT THAT CRUMBLED INTO SMALL SPACE
                        bufferLen=0;
                        bufferAdd=0;//NEW VARIABLE AS COUNTER INITIALISED TO ZERO
                        bufferLen = bsize[0];//BUFFER LENGTH HOLDS THE VALUE OF BUFFER SIZE FOR BUFFER0

                        if (b0char<bufferLen)
                        {
                        while(bufferAdd <bufferLen )//WHILE THE COUNTER IS LESS THAN THE SIZE OF BUFFER0
                                {   printf("\r\nADDRESS FOR BUFFER 0: \n%p:",(buffer0+bufferAdd));//PRINTING MESSAGE THAT THE CONTENTS OF BUFFER ARE AS FOLLOWS
                                    bufferDat=0;//NEW DATA COUNTER TO ACCESS DATA AT LOCATION IN BUUFFER0 AND TRANSVERSING THE BUFFER0 USING THIS COUNTER
                                   while(bufferDat<(b0char+1))//WHILE THE DATA COUNTER IS LESS THAN OR EQUAL TO THE NUMBER OF CHARACTERS PRESENT IN BUFFER0
                                        {
                                             printf("% x ",*((buffer0 + bufferAdd) + bufferDat));//THIS STATEMENT WILL PRINT THAT OUT BY TRAVELLING FROM ZERO LOCATION TILL THE LOCATION OF LAST STORED CHARACTER IN BUFFER0
                                bufferDat++;//INCREMENT DATA COUNTER
                                        }
                                    printf("\n\r");//PRINT THE NEXT STUFF IN NEW LINE TO OVER CROWD THE ALREADY COMPLEX PROGRAM
                                    bufferAdd = bufferAdd + bufferDat;//UPDATE THE VALUE OF BUFFER ADRESS POINTER BY ADING THE ALREADY PRINTED CHARACTER LOCATION
                                }
                        }
                        else
                          {printf_tiny("\n\rBUFFER FULL");}//PRINT THE MESSAGE
                            printf_tiny("\r\n");//NOTHING BUT A NEW LINE SO THAT THE INTERFACE IS NOT THAT CRUMBLED INTO SMALL SPACE
                            bufferLen=0;
                            bufferAdd=0;//LOCAL ADRESS COUNTER USED FOR TRANSVERSING THE ENTIRE BUFFER1
                            bufferLen= bsize[1];//BUFFERLENGTH IS NOW EQUAL TO BUFFER1 SIZE

                           if (b1char<bufferLen)//CHECK IF THE NO OF CHARACTERS IN BUFFER1 ARE CONTAINED IN LESS THAN THE SIZE OF BUFFER1
                            {
                                while (bufferAdd<bufferLen)//WHILE THE ADDRESS COUNTER IS LESS THAN THE LENGTH,IT WILL GO THROUGH OTS ENTIRELENGTH
                            {   printf_tiny("\r\nADDRESS FOR BUFFER 1: \n%p:",(buffer1+bufferAdd));//ADDRESS MESSAGE
                                bufferDat=0;//DATA VARAIBLE USING FOR ACCESSING THE DATA AT THESE PLACES
                                    while (bufferDat < (b1char+1))//TRANSVERSING THE BUFFER TILL THE NO OF CHARACTERS
                                    {
                                    printf("% x ",*((buffer1 + bufferAdd) + bufferDat));//PRINTING THE VALUES
                                    bufferDat++ ;//INCREMENTING THE DATA COUNTER TILL THE NO OF CHARACTERS IN BUFFER1
                                    }
                                printf("\n\r");//SPACING IS IMPORTANT!
                                bufferAdd = bufferAdd + bufferDat;//UPDATE THE ADDRESS AT THE LOCATION TILL WHICH THE VALUES ARE PRINTED
                                }

                            printf_tiny("\r\n");//SPACING SPACING AND SPACING

                            }
                             else
                         {printf_tiny("\n\rBUFFER1 IS FULL");
                       printf_tiny("\r\nPRESS '@' IF YOU NEED DETAILED CONTENT OF BUFFERS");}
                       break;


        /********************************************************************************************************************/
/*******************************************        case5'?'     ****************************************************************/
/********************************************************************************************************************/

                    case '?'://case5 is "?" and this will show the deatisla bout buffer as below
                        printf_tiny("\r================================================================================\n");//DECORATION
                        printf_tiny("\r\n\t\t\tREPORT ABOUT BUFFERS                                                    \n");//HEADING ABOUT WHAT THIS COMMAND IS SUPPOSED TO DO
                        printf_tiny("\n\r==============================================================================\n");//DECORATION

                            bufferAdd=0;//NEW LOCAL COUNTER SET TO ZERO
                            while (bufferAdd < (bCount))//WHILE THE COUNTER IS LESS THAN THE NO OF BUFFERS PRESESNT
                                {
                                if ((bAdress[bufferAdd]) != 0)//IF THE BUFFER IS NOT NULL
                                        {
                                printf_tiny("\r\n\t\t\tBUFFER%d DETAILS AS FOLLOWS\t\t\t\n ",bufferAdd);//PRINT THE BUFFERNAME
                                printf_tiny("\r\n\tBUFFER %d STARTS FROM                    :    %p",bufferAdd,bAdress[bufferAdd]);//STARTING ADDRESS
                                printf_tiny("\r\n\tBUFFER %d ENDING ADDRESS                 :    %p",bufferAdd,(bAdress[bufferAdd]+bsize[bufferAdd]));//ENDING ADRESS
                                printf_tiny("\r\n\tSIZE OF BUFFER %d                        :    %d",bufferAdd,bsize[bufferAdd]);//SIZE OF BUFFER


                                if(bufferAdd == 0)//IF BUFFER IS BUFFER0
                                counter = b0char;//INITIALISE THE NOUMBER OF CHARACTERS IN BUFFER0 IN COUNTER
                                else if(bufferAdd == 1)//IF BUFFER IS BUFFER1
                                counter = b1char;//INITIALISE THE NOUMBER OF CHARACTERS IN BUFFER1 IN COUNTER
                                else//ELSE IF BUFFER IS ANY OTHER BUFFER OTHER THAN BUFFER0 AND BUFFER1
                                counter = 0;//COUNTER IS ZERO
                                printf_tiny("\t\r\n");//SPACING
                                printf_tiny("\t\r\nNUMBER OF CONTENTS OF BUFFER %d                   :    %d", bufferAdd,counter);//NUMBER OF CONTENTS
                                printf_tiny("\t\r\nFREE SPACE IN BUFFER %d                           :    %d",bufferAdd,(bsize[bufferAdd] - counter));printf_tiny("\r\n");//FREE SPACE IN BUFFER
                                printf_tiny("\r\n");
                            }   bufferAdd++;
                                }
                        printf_tiny("\r\n");//SPACING
                        newcounter=((b0char+b1char)-newcounter);//NEW COUNTER IS EQUAL TO THE NUMBER OF CHARACTERS RECIEVED TILL NOW SINCE LAST '?'
                            printf_tiny("\r\n\tNumber of characters received till last'?'   : %d\n", newcounter);//PRINT THE NUMBER OF  CHARACTERS RECIEVED TILL NOW SINCE LAST '?'
                        printf_tiny("\r--------------------------------------------------------------------------------\n");//DECORATION

                        printf_tiny("\r\n\tCONTENTS OF BUFFER0:\n   ");//VIEW THE CONTENTS OF BUFFER0
                        bufferAdd=0;//NEW COUNTER SET TO ZERO
                        while( bufferAdd < (b0char+1))//WHILE THE LOOP GOES TILL THE NO OF CHARCTERS IN BUFFER0
                        {
                            putchar((buffer0[bufferAdd]));//DISPALY THE CONTENTS OF BUFFER0
                            buffer0[bufferAdd] = 0;//CLEAR THE BUFFER0 OF ANY DATA
                            printf_tiny("   \t");//SPACING IS GOOD!
                            bufferAdd++;//INCREMENT TO NEXT POSITION
                        }
                            b0char = 0;//CLEAR THE COUNTER FOR NUMBER OF CHARACTERS IN BUFFER0

                   printf_tiny("\r\n\tCONTENTS OF BUFFER1:\n    ");//DISPLAY CONTENTS OF BUFFER1

                        bufferAdd = 0;//INITIALISE COUNTER
                        while( bufferAdd< (b1char+1))//WHILE THE LOOP TRAVELS TLL ITS LAST DATA POSITION
                        {
                            putchar((buffer1[bufferAdd]));//DISPLAY DATA
                                buffer1[bufferAdd] = 0;//CLEAR THE DATA FROM BUFFER0
                                printf_tiny("   \t");//SPACING
                                bufferAdd++;//INCREMENT ADDRESS TO NEXT POSITION IN BUFFER1
                        }
                            b1char= 0;//CLEAR THE COUNTER THAT CONTAINS THE NUMBER OF CHARACTERS IN BUFFEER1
                    printf_tiny("\r\n");//SPACING
                     break;//BREAK



                    default://INCASE OF lowercase AND OTHER INPUT
                    printf_tiny("\r\n NOT STORING.JUST DISPLAYING!\n");//DISPLAY A MESSAGE
                    printf_tiny("\r++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");//DECPRATION IS GOOD
                    break;//BREAK




                     }}}}




/********************************************
*********** ATOI function definition***********
*********************************************/
/*int atoi(char * s)
{
     register int rv=0;
     register char sign = 0;

     skip till we find either a digit or '+' or '-'
     while (*s) {
	if (*s <= '9' && *s >= '0')
		break;
	if (*s == '-' || *s == '+')
		break;
	s++;
     }

     sign = (*s == '-');
     if (*s == '-' || *s == '+') s++;

     while (*s && *s >= '0' && *s <= '9') {
	rv = (rv * 10) + (*s - '0');
        s++;
     }

     return (sign ? -rv : rv);
}*/
/********************************************
***********Gets function defnition***********
*********************************************/
//*
/*char * gets(const char *str) {
  char *s=str;
  char c;
  unsigned int count=0;

  while (1) {
    c=getchar();
    switch(c) {
    case '\b': // backspace
      if (count) {
	putchar ('\b');
	putchar (' ');
	putchar ('\b');
	s--;
	count--;
      }
      break;
    case '\n':
    case '\r': // CR or LF
      putchar('\r');
      putchar('\n');
      *s=0;
      return str;
    default:
      *s++=c;
      count++;
      putchar(c);
      break;
    }
  }
}*/
/********************************************
***********Puts function defnition***********
*********************************************/
/*extern void putchar(char);

int puts (char *s)
{
	int i = 0;
	while (*s){
		putchar(*s++);
		i++;
	}
	putchar('\n');
	return i+1;
}*/
