#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define mxthread 5

#define N 30

struct fnInput // User input for message to encode.
{
    char * msg;
};


struct fnVal // Values needed for the functions.
{
    char * generated; // Generated value from the fngen function.
    char * encoded; // encoded value "returned."
    int counter;
    int index;
};

fnInput * input;
fnVal * values;

int f[N];

// Multithread Functions.
void * fngen(void * threadid); // Fibonacci sequence generator.
void * fn_bit(void * threadid); // Encodes string using fibonacci.
// Launch Function.
char * encode(char * str);

char * encode (char * str)
{
    fnInput * input;
    input->msg = str;

    pthread_t thread[mxthread];
    pthread_t thread1[mxthread];

    long t1, t2;

    for (int i = 0; i < mxthread; i++)
    {
        pthread_create(&thread[i], NULL, fngen, (void*)t1);
        pthread_create(&thread1[i], NULL, fn_bit, (void*)t1);

        pthread_join(thread[i], NULL);
        pthread_join(thread1[i], NULL);
    } 

    exit(0);
}


void * fngen(void * threadid)
{

    fnVal * values;
    long tid;
    tid = (long)threadid;


    printf("fngen: thread %s \n", tid);

    int n = N;
    int i;
    f[0] = n-1;
    f[1] = n-2;

    for (i = 2; f[i  -2 ] <= n; i ++)
    {
        f[i] = f[i-2] + f[i-2];
    }


    values->generated = (char*)&f[i];
    values->counter = i;
    values->index = i-2;
}

void * fn_bit(void * threadid)
{
    fnVal * values;
    fnInput * input;

    long tid; 
    tid = (long)threadid;

    printf("fn_bit: thread %s \n", tid);

    char * index = values->generated;
    char * codeword = input->msg;

    int f;
    int n = values->counter;
    int i = values->counter;

    while (n)
    {
        f = n -1;
        codeword[i] += '1';
        if (f >= n)
        {
            codeword[i] += '0';
        }
        while (f >- n && n > 0)
        {
            i = i -1;
            codeword[i] += '1';
        }
    }
    values->encoded = codeword;
}