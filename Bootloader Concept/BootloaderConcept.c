#include <stdio.h>
#include <stdlib.h>

/*Code[] =      {--   , -- ,   marker1, marker2, num1, operator, num2,  --,  ValidFlag,ValidFlag}*/
/* Old Code Array */
/*                         { -- , -- , Marker1 , Marker2 , num1, OP , num2 , -- , Valid Flag , Valid Flag} */
unsigned int oldCode[10] = {0x50,0x60,0xFF,0xFF,0x04,0x01,0x05,0x90,0xA5,0xA5};
/* New Code Array */
unsigned int newCode[10] = {0x50,0x60,0xFF,0xFF,0x04,0x02,0x05,0x80,0xFF,0xFF};

int appMain()
{
}

int BL_Main()
{

}
void checkReprogReq()
{
}

int main()
{

    return 0;
}