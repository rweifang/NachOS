#include "syscall.h"

int main()
{
   int x;

   PrintString("Parent ThreadID: ");
   PrintInt(GetThreadID());
   PrintChar('\n');
   x = ThreadFork(0);
   PrintChar('\n');

   if (x == 0)
   {
      PrintString("Child PID: ");
      PrintInt(GetThreadID());
      PrintChar('\n');
      PrintString("Child's parent PID: ");
      PrintInt(GetParentTID());
      PrintChar('\n');
      PrintString("Child calling sleep at time: ");
      PrintInt(Time());
      PrintChar('\n');
      // Sleep(100);
      PrintString("Child returned from sleep at time: ");
      PrintInt(Time());
      PrintChar('\n');
      PrintString("Child executed ");
      PrintInt(GetNumInstr());
      PrintString(" instructions.\n");
   }
   else
   {
      PrintString("ThreadID of this thread : ");
      PrintInt(GetThreadID());
      PrintChar('\n');
      PrintString("Parent after fork waiting for child: ");
      PrintInt(x);
      PrintChar('\n');
      Join(x);
      PrintString("Parent executed ");
      PrintInt(GetNumInstr());
      PrintString(" instructions.\n");
   }

   return 0;
}