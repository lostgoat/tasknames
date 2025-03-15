#define _GNU_SOURCE

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include <sys/eventfd.h>

// -----------------------------------------------------
struct ThreadContext_t
{
	pthread_t nThreadId;
	int nExitFd;
	int nReadyFd;
};


// -----------------------------------------------------
void Signal(int nFd)
{
	uint64_t nValue = 1;
	write(nFd, &nValue, sizeof(nValue));
}


// -----------------------------------------------------
void Wait(int nFd)
{
	uint64_t nValue = 1;
	read(nFd, &nValue, sizeof(nValue));
}


// -----------------------------------------------------
// Threads just wait for exit
// -----------------------------------------------------
void *ThreadMain( void *pArg )
{
	struct ThreadContext_t *pContext = (struct ThreadContext_t *)pArg;

	// Set the extended thread name via some new pthread helper
	char rgName[32];
	snprintf(rgName, sizeof(rgName), "NameThatIsTooLongForComm[%d]", gettid());
	// pthread_setname_extended_np(pthread_self(), rgName);

	char rgNameTruncated[16];
	strncpy(rgNameTruncated, rgName, sizeof(rgNameTruncated));
	rgNameTruncated[15] = '\0';
	pthread_setname_np(pthread_self(), rgNameTruncated);

	printf( "%s: waiting\n", rgName);
	Signal(pContext->nReadyFd);
	Wait(pContext->nExitFd);
	printf( "%s: exiting\n", rgName);

	return NULL;
}


// -----------------------------------------------------
// Simple app that generates threads with long names
//
// Repro steps:
//  > make
//  > gdb threadnames
//  > break after thread creation
//  > info thread
// -----------------------------------------------------
int main( int argc, char **argv )
{
	static const size_t kThreadCount = 8;

	struct ThreadContext_t contexts[kThreadCount];
	for ( size_t i = 0; i < kThreadCount; ++i )
	{
		struct ThreadContext_t *pContext = &contexts[i];
		pContext->nExitFd = eventfd(0, EFD_SEMAPHORE);
		pContext->nReadyFd = eventfd(0, EFD_SEMAPHORE);

		pthread_create(&pContext->nThreadId, NULL, ThreadMain, pContext);
		Wait(pContext->nReadyFd);
	}

	printf("Process[%d] created %zu threads. Press any key to exit\n", getpid(), kThreadCount);
	getc(stdin);

	for ( size_t i = 0; i < kThreadCount; ++i )
	{
		struct ThreadContext_t *pContext = &contexts[i];

		Signal(pContext->nExitFd);
		void *pIgnored;
		pthread_join(pContext->nThreadId, &pIgnored);
	}

	return 0;
}