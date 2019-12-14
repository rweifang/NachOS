// exception.cc
//	Entry point into the Nachos kernel from user programs.
//	There are two kinds of things that can cause control to
//	transfer back to here from user code:
//
//	syscall -- The user code explicitly requests to call a procedure
//	in the Nachos kernel.  Right now, the only function we support is
//	"Halt".
//
//	exceptions -- The user code does something that the CPU can't handle.
//	For instance, accessing memory that doesn't exist, arithmetic errors,
//	etc.
//
//	Interrupts (which can also cause control to transfer from user
//	code into the Nachos kernel) are handled elsewhere.
//
// For now, this only handles the Halt() system call.
// Everything else core dumps.
//
// Copyright (c) 1992-1996 The Regents of the University of California.
// All rights reserved.  See copyright.h for copyright notice and limitation
// of liability and disclaimer of warranty provisions.

#include "copyright.h"
#include "main.h"
#include "syscall.h"
#include "ksyscall.h"
//----------------------------------------------------------------------
// ExceptionHandler
// 	Entry point into the Nachos kernel.  Called when a user program
//	is executing, and either does a syscall, or generates an addressing
//	or arithmetic exception.
//
// 	For system calls, the following is the calling convention:
//
// 	system call code -- r2
//		arg1 -- r4
//		arg2 -- r5
//		arg3 -- r6
//		arg4 -- r7
//
//	The result of the system call, if any, must be put back into r2.
//
// If you are handling a system call, don't forget to increment the pc
// before returning. (Or else you'll loop making the same system call forever!)
//
//	"which" is the kind of exception.  The list of possible exceptions
//	is in machine.h.
//----------------------------------------------------------------------

void ExceptionHandler(ExceptionType which)
{
	int type = kernel->machine->ReadRegister(2);

	DEBUG(dbgSys, "Received Exception " << which << " type: " << type << "\n");

	switch (which)
	{
	case SyscallException:
		switch (type)
		{

		case SC_ThreadFork:
			DEBUG(dbgSys, "System Call: ThreadFork().\n");

			SysThreadForkHandler();

			return;
			ASSERTNOTREACHED();
			break;

		case SC_Time:
			DEBUG(dbgSys, "System Call: Time().\n");

			SysTimeHandler();

			return;
			ASSERTNOTREACHED();
			break;

		case SC_NumInstr:
			DEBUG(dbgSys, "System Call: GetNumInstr().\n");

			SysGetNumInstrHandler();

			return;
			ASSERTNOTREACHED();
			break;

		case SC_GetThreadID:
			DEBUG(dbgSys, "System Call: GetThreadID().\n");

			SysGetThreadIDHandler();

			return;
			ASSERTNOTREACHED();
			break;

		case SC_GetParentTID:
			DEBUG(dbgSys, "System Call: GetParentTID().\n");

			SysGetParentTIDHandler();

			return;
			ASSERTNOTREACHED();
			break;

		case SC_Exit:
			DEBUG(dbgSys, "System Call: Exit().\n");

			SysExitHandler();

			return;
			ASSERTNOTREACHED();
			break;

		case SC_PrintInt:
			DEBUG(dbgSys, "System Call: PrintInt().\n");

			SysPrintIntHandler();

			return;
			ASSERTNOTREACHED();
			break;

		case SC_PrintChar:
			DEBUG(dbgSys, "System Call: PrintChar().\n");

			SysPrintCharHandler();

			return;
			ASSERTNOTREACHED();
			break;

		case SC_PrintString:
			DEBUG(dbgSys, "System Call: PrintString().\n");

			SysPrintStringHandler();

			return;
			ASSERTNOTREACHED();
			break;

		case SC_Halt:
			DEBUG(dbgSys, "Shutdown, initiated by user program.\n");

			SysHalt();

			ASSERTNOTREACHED();
			break;

		case SC_Add:
			DEBUG(dbgSys, "Add " << kernel->machine->ReadRegister(4) << " + " << kernel->machine->ReadRegister(5) << "\n");
			SysAddHandler();

			return;
			ASSERTNOTREACHED();
			break;

		default:
			cerr << "Unexpected system call " << type << "\n";
			break;
		}
		break;
	default:
		cerr << "Unexpected user mode exception" << (int)which << "\n";
		break;
	}
	ASSERTNOTREACHED();
}
