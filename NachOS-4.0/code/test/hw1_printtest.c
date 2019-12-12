#include "syscall.h"

int main()
{
   PrintString("Hello,");
   PrintChar(' ');
   PrintChar('W');
   PrintChar('o');
   PrintChar('r');
   PrintChar('l');
   PrintChar('d');
   PrintChar('!');
   PrintChar('\n');

   PrintInt(123456789);
   PrintChar('\n');
   PrintInt(0);
   PrintChar('\n');
   PrintInt(-123456789);
   PrintChar('\n');

   Halt();
}