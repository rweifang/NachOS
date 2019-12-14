/**************************************************************
 *
 * userprog/ksyscall.h
 *
 * Kernel interface for systemcalls 
 *
 * by Marcus Voelp  (c) Universitaet Karlsruhe
 *
 **************************************************************/

#ifndef __USERPROG_KSYSCALL_H__
#define __USERPROG_KSYSCALL_H__

#include "synchconsole.h"

void SysHalt()
{
  kernel->interrupt->Halt();
}

void SysGetThreadIDHandler()
{
  int result = kernel->currentThread->ThreadID;
  DEBUG(dbgSys, "ThreadID : " << result << "\n");
  kernel->machine->WriteRegister(2, (int)result);

  kernel->machine->WriteRegister(PrevPCReg, kernel->machine->ReadRegister(PCReg));
  kernel->machine->WriteRegister(PCReg, kernel->machine->ReadRegister(PCReg) + 4);
  kernel->machine->WriteRegister(NextPCReg, kernel->machine->ReadRegister(PCReg) + 4);
}

void SysGetParentTIDHandler()
{
  int result = kernel->currentThread->parentThreadID;
  DEBUG(dbgSys, "Parent ThreadID : " << result << "\n");
  kernel->machine->WriteRegister(2, (int)result);

  kernel->machine->WriteRegister(PrevPCReg, kernel->machine->ReadRegister(PCReg));
  kernel->machine->WriteRegister(PCReg, kernel->machine->ReadRegister(PCReg) + 4);
  kernel->machine->WriteRegister(NextPCReg, kernel->machine->ReadRegister(PCReg) + 4);
}

void SysExitHandler()
{
  int result = kernel->machine->ReadRegister(4);
  cout << "Exit with value : " << result << endl;
  kernel->currentThread->Finish();
}

void SysAddHandler()
{
  /* Process SysAdd Systemcall*/
  int result;
  result = (int)kernel->machine->ReadRegister(4) +
           (int)kernel->machine->ReadRegister(5);

  DEBUG(dbgSys, "Add returning with " << result << "\n");
  /* Prepare Result */
  kernel->machine->WriteRegister(2, (int)result);

  /* Modify return point */
  {
    /* set previous programm counter (debugging only)*/
    kernel->machine->WriteRegister(PrevPCReg, kernel->machine->ReadRegister(PCReg));

    /* set programm counter to next instruction (all Instructions are 4 byte wide)*/
    kernel->machine->WriteRegister(PCReg, kernel->machine->ReadRegister(PCReg) + 4);

    /* set next programm counter for brach execution */
    kernel->machine->WriteRegister(NextPCReg, kernel->machine->ReadRegister(PCReg) + 4);
  }
}

void SysPrintIntHandler()
{
  char ch[15] = {'\0'}; // the length of int isn't more than 11 digits
  int val = kernel->machine->ReadRegister(4);
  if (!val)
    kernel->synchConsoleOut->PutChar('0');
  int sign = val < 0 ? -1 : 1;
  val = val < 0 ? val * -1 : val;
  int len = 0;
  while (val)
  {
    ch[len] = val % 10 + '0';
    val /= 10;
    len++;
  }
  if (sign == -1)
  {
    ch[len] = '-';
    len++;
  }

  while (len)
  {
    kernel->synchConsoleOut->PutChar(ch[len - 1]);
    len--;
  }

  kernel->machine->WriteRegister(PrevPCReg, kernel->machine->ReadRegister(PCReg));
  kernel->machine->WriteRegister(PCReg, kernel->machine->ReadRegister(PCReg) + 4);
  kernel->machine->WriteRegister(NextPCReg, kernel->machine->ReadRegister(PCReg) + 4);
}

void SysPrintCharHandler()
{
  char ch = kernel->machine->ReadRegister(4);
  kernel->synchConsoleOut->PutChar(ch);

  kernel->machine->WriteRegister(PrevPCReg, kernel->machine->ReadRegister(PCReg));
  kernel->machine->WriteRegister(PCReg, kernel->machine->ReadRegister(PCReg) + 4);
  kernel->machine->WriteRegister(NextPCReg, kernel->machine->ReadRegister(PCReg) + 4);
}

void SysPrintStringHandler()
{
  int addr = kernel->machine->ReadRegister(4);
  int i = 0;
  int ch;
  do
  {
    kernel->machine->ReadMem(int(addr + i), 1, &ch);
    kernel->synchConsoleOut->PutChar(char(ch));
    i++;
  } while (ch != '\0');

  kernel->machine->WriteRegister(PrevPCReg, kernel->machine->ReadRegister(PCReg));
  kernel->machine->WriteRegister(PCReg, kernel->machine->ReadRegister(PCReg) + 4);
  kernel->machine->WriteRegister(NextPCReg, kernel->machine->ReadRegister(PCReg) + 4);
}

#endif /* ! __USERPROG_KSYSCALL_H__ */
