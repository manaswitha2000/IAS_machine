#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
const int M = 1000;//for memory set
const int N = 10;//for memory set
//Functions to convert from hexadecimal to decimal
int hex_to_deci(char hex[],int len)
{
  int i,dec=0,dig,cnt=0;
  for(i=len-1;i>0;i--)
    {
        switch(hex[i])
        {
            case 'A':
                dig=10; break;
            case 'B':
                dig=11; break;
            case 'C':
                dig=12; break;
            case 'D':
                dig=13; break;
            case 'E':
                dig=14; break;
            case 'F':
                dig=15; break;
            default:
                dig=hex[i]-'0';
       }
       dec= dec+ (dig)*pow((double)16,(double)cnt);
       //printf("%d-dec %d-dig %c-hex[i]\n",dec,dig,hex[i]);
       cnt++;
   }
   if(hex[0]=='1')
     dec = -dec;
   return dec;
}
int hex_to_deci2(char memory[M][N],int x)
{
  int i,dec=0,dig,cnt=0;
  for(i=9;i>0;i--)
    {
        switch(memory[x][i])
        {
            case 'A':
                dig=10; break;
            case 'B':
                dig=11; break;
            case 'C':
                dig=12; break;
            case 'D':
                dig=13; break;
            case 'E':
                dig=14; break;
            case 'F':
                dig=15; break;
            default:
                dig=memory[x][i]-'0';
       }
       dec= dec+ (dig)*pow((double)16,(double)cnt);
       //printf("%d-dec %d-dig %c-mem[i]\n",dec,dig,memory[x][i]);
       cnt++;
   }
   if(memory[x][0]=='1')
   dec = -dec;
   return dec;
}
void fetchcycle(char memory[M][N],char PC[],char IR[],char IBR[],char MAR[],char MBR[],char AC[],char MQ[]);
void executecycle(char memory[M][N],char PC[],char IR[],char IBR[],char MAR[],char MBR[],char AC[],char MQ[]);
void Startcycle(char memory[M][N])//intializing all the registers
{
  //Initializing all the registers needed.
  char PC[3];
  char IR[2];
  char IBR[5];
  char MAR[3];
  char MBR[10];
  char AC[10];
  char MQ[10];
  int i;
  for(i=0;i<3;i++)
  PC[i] = '0';
  for(i=0;i<2;i++)
  IR[i] = '*';
  for(i=0;i<5;i++)
  IBR[i] = '*';
  for(i=0;i<10;i++)
  {
  MBR[i] = '*';
  AC[i] = '*';
  MQ[i] = '*';
  }
  for(i=0;i<3;i++)
  MAR[i] = '*';

  //Keeps executing till halt function or till all instructions are over.
  while(!((IR[0]=='F'&&IR[1]=='F')||(IR[0]=='0'&&IR[1]=='0')))
  {
  fetchcycle(memory,PC,IR,IBR,MAR,MBR,AC,MQ);
  executecycle(memory,PC,IR,IBR,MAR,MBR,AC,MQ);
  }
}
void executecycle(char memory[M][N],char PC[],char IR[],char IBR[],char MAR[],char MBR[],char AC[],char MQ[])
{
  int i;
  int mar = hex_to_deci(MAR,3);

  //Unconditional branch
  if(IR[0]=='0'&&IR[1]=='D'){
    for(i=0;i<5;i++){
      if(i<2)
      IR[i] = memory[mar][i];
      else
      MAR[i-2] = memory[mar][i];  }}
  else if(IR[0]=='0'&&IR[1]=='E'){
    for(i=0;i<5;i++){
      if(i<2)
      IR[i] = memory[mar][5+i];
      else
      MAR[i-2] = memory[mar][5+i];  }}
  //Conditional branch
  else if(IR[0]=='0'&&IR[1]=='F'){
    if(AC[0]=='0'){
      //printf("in cond1\n");
      for(i=0;i<5;i++){
        if(i<2)
          IR[i] = memory[mar][i];
        else
          MAR[i-2] = memory[mar][i];
        mar = hex_to_deci(MAR,3); }}}
  else if(IR[0]=='1'&&IR[1]=='0'){
    if(AC[0]=='0'){
      //printf("in cond2\n");
      for(i=0;i<5;i++){
        if(i<2)
          IR[i] = memory[mar][5+i];
        else
          MAR[i-2] = memory[mar][5+i];
        mar = hex_to_deci(MAR,3);}}}

  //Data transfer
  if(IR[0]=='0'&&IR[1]=='A'){
    for(i=0;i<10;i++)
    MQ[i] = AC[i];  }
  else if(IR[0]=='0'&&IR[1]=='9'){
    for(i=0;i<10;i++)
    MQ[i] = memory[mar][i];  }
  else if(IR[0]=='2'&&IR[1]=='1'){
    for(i=0;i<10;i++)
    memory[mar][i] = AC[i];  }
  else if(IR[0]=='0'&&IR[1]=='1'){
    //printf("0 1 executed\n");
    for(i=0;i<10;i++)
    AC[i] = memory[mar][i];  }
  else if(IR[0]=='0'&&IR[1]=='2'){
    for(i=0;i<10;i++)
    AC[i] = memory[mar][i];
    if(AC[0]=='0')
      AC[0] = '1';
    else
      AC[0] = '0';  }
  else if(IR[0]=='0'&&IR[1]=='3'){
    for(i=0;i<10;i++)
    AC[i] = memory[mar][i];
    AC[0] = '0';  }
  else if(IR[0]=='0'&&IR[1]=='4'){
    for(i=0;i<10;i++)
    AC[i] = memory[mar][i];
    AC[0] = '1';  }

  //Arithmetic
  //addition m(x) and |m(x)|
  else if(IR[0]=='0'&&(IR[1]=='5'||IR[1]=='7'))
  {
    int ac = hex_to_deci(AC,10);
    int m = hex_to_deci2(memory,mar);
    if(IR[1]=='5')
    ac = ac + m;
    if(IR[1]=='7')
    ac = ac + abs(m);
    i = 9;
    if(ac>0)
     AC[0] = '0';
    else
     AC[1] = '1';
    while(ac != 0)
     {
         int rem = ac % 16;  // get the right most digit
         if (rem < 10)
          AC[i--] = 48 + rem;
         else
          AC[i--] = 55 + rem;
          ac /= 16;  // get the quotient
     }

  }
  //subtraction m(x) and |m(x)|
  else if(IR[0]=='0'&&(IR[1]=='6'||IR[1]=='8'))
  {
    //printf("0 6 exectuted\n");
    int ac = hex_to_deci(AC,10);
    int m = hex_to_deci2(memory,mar);
    if(IR[1]=='6')
    ac = ac - m;
    if(IR[1]=='8')
    ac = ac - abs(m);
    i = 9;
    if(ac>0)
     AC[0] = '0';
    else
     AC[1] = '1';
    while(ac != 0)
     {
         int rem = ac % 16;  // get the right most digit
         if (rem < 10)
          AC[i--] = 48 + rem;
         else
          AC[i--] = 55 + rem;
          ac /= 16;  // get the quotient
     }

  }

  //multiplication
  else if(IR[0]=='0'&&IR[1]=='B')
  {
    int mq = hex_to_deci(MQ,10);
    int m = hex_to_deci2(memory,mar);
    mq = mq*m;
    i = 19;
    while(mq != 0)
     {
         int rem = mq % 16;  // get the right most digit
         if(i>=10){
          if (rem < 10)
           AC[i--] = 48 + rem;
          else
           AC[i--] = 55 + rem;
          }
         else{
          if (rem < 10)
           MQ[i--] = 48 + rem;
          else
           MQ[i--] = 55 + rem;
          }
          mq /= 16;  // get the quotient
     }
     /*for(i=0;i<10;i++)
     printf("%c ",AC[i]);
     printf("-AC\n");
     printf("checked perfect4\n");*/

  }

  //Address modify
  else if(IR[0]=='1'&&IR[1]=='2')
  {
    for(i=0;i<5;i++)
    memory[mar][2+i] = AC[7+i];
  }
  else if(IR[0]=='1'&&IR[1]=='3')
  {
    for(i=0;i<5;i++)
    memory[mar][7+i] = AC[7+i];
  }


}
void fetchcycle(char memory[M][N],char PC[],char IR[],char IBR[],char MAR[],char MBR[],char AC[],char MQ[])
{
  int i;
  //If IBR is 0 or executed
  if(IBR[0]=='*'||(IR[0]==IBR[0]&&IR[1]==IBR[1]&&MAR[0]==IBR[2]&&MAR[1]==IBR[3]&&MAR[2]==IBR[4]))
  {
    //MAR = PC
    for(i=0;i<3;i++)
    MAR[i] = PC[i];
    //MBR = memory[MAR]
    int mar;
    if(IBR[0]=='*')
    mar = 0;
    else
    mar = hex_to_deci(MAR,3);
    for(i=0;i<10;i++)
    MBR[i] = memory[mar][i];

    for(i=0;i<10;i++){
    if(i>=5)
      IBR[i-5] = MBR[i];
    else{
      if(i<2){
        IR[i] = MBR[i];}
      else
        MAR[i-2] = MBR[i];}}
  }
  //If IBR is not executed
  else
  {
   for(i=0;i<2;i++)
   IR[i] = IBR[i];
   for(i=0;i<3;i++)
   MAR[i] = IBR[2+i];
  }
  //PC = PC + 1
  int pc = (PC[0] - '0')+(PC[1] - '0')+(PC[2] - '0');
  if(IBR[0]=='*'||(IR[0]==IBR[0]&&IR[1]==IBR[1]&&MAR[0]==IBR[2]&&MAR[1]==IBR[3]&&MAR[2]==IBR[4]))
  pc = pc+1;
  i = 2;
  while(pc != 0)
   {
       int rem = pc % 16;  // get the right most digit
       if (rem < 10)
           PC[i--] = 48 + rem;
       else
           PC[i--] = 55 + rem;
    pc /= 16;  // get the quotient
   }
   //Printing the registers out.
   for(i=0;i<3;i++)
   printf("%c ",PC[i]);
   printf("-PC\n");
   for(i=0;i<2;i++)
   printf("%c ",IR[i]);
   printf("-IR\n");
   for(i=0;i<3;i++)
   printf("%c ",MAR[i]);
   printf("-MAR\n");
   for(i=0;i<5;i++)
   printf("%c ",IBR[i]);
   printf("-IBR\n");
}


int main()
{
  // All these are used to take input into the char array and terminate it when two '*' are given
  char var1;
  char buffer;//for new line
  int i = 0,j = 0;
  int loop_on = 1;// for the scan and print while loops to terminate.
  char memory[1000][10];
  for(i=0;i<1000;i++)
  {
    for(j=0;j<10;j++)
    memory[i][j]='0';
  }
  j = 0;
  while(loop_on)
  {
  for(i=0;i<10;i++)
  {
  scanf("%c", &var1);
  memory[j][i] = var1;
  if((memory[j][0]=='*'&&memory[j][1]=='*')||(memory[j][5]=='*'&&memory[j][6]=='*'))
  i = 10;
  }
  scanf("%c",&buffer);
  if((memory[j][0]=='*'&&memory[j][1]=='*')||(memory[j][5]=='*'&&memory[j][6]=='*'))
  loop_on = 0;
  j++;
  }
  loop_on = 1;
  j = 0;
  while(loop_on)
  {
  if((memory[j][0]=='*'&&memory[j][1]=='*'))
    loop_on = 0;
  for(i=0;i<10;i++)
  {
  printf("%c-memory ",memory[j][i]);
  }
  j++;
  printf("\n");
  }
  Startcycle(memory);
  loop_on = 1;
  j = 0;
  int count;
  while(loop_on)
  {
  if(memory[j][0]=='0'&&memory[j][1]=='0'&&memory[j][2]=='0'&&memory[j][3]=='0'
  &&memory[j][4]=='0'&&memory[j][5]=='0'&&memory[j][6]=='0'&&memory[j][7]=='0'
  &&memory[j][8]=='0'&&memory[j][9]=='0')
    loop_on = 0;
  for(i=0;i<10;i++)
  {
  printf("%c-memory ",memory[j][i]);
  }
  j++;
  printf("\n");
  }
  return 0;

}
