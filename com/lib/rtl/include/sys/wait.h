

#include <sys/types.h>   //for pid_t
//#include <unistd.h>      //for pid_t


/*
#ifndef __pid_t_defined
#define __pid_t_defined
typedef __pid_t pid_t;
#endif
*/



/*
 * Macros to test the exit status returned by wait
 * and extract the relevant values.
 */
//#ifdef _POSIX_SOURCE
#define	_W_INT(i)	(i)
//#else
//#define	_W_INT(w)	(*(int *)&(w))	/* convert union wait to int */
//#define	WCOREFLAG	0200
//#endif /* _POSIX_SOURCE */

#define	_WSTATUS(x)	(_W_INT(x) & 0177)
#define	_WSTOPPED	0177		/* _WSTATUS if process is stopped */
#define WIFSTOPPED(x)	(_WSTATUS(x) == _WSTOPPED)
#define WSTOPSIG(x)	(_W_INT(x) >> 8)
#define WIFSIGNALED(x)	(_WSTATUS(x) != _WSTOPPED && _WSTATUS(x) != 0)
#define WTERMSIG(x)	(_WSTATUS(x))
#define WIFEXITED(x)	(_WSTATUS(x) == 0)
#define WEXITSTATUS(x)	(_W_INT(x) >> 8)

#if !defined(_POSIX_SOURCE)
#define WCOREDUMP(x)	(_W_INT(x) & WCOREFLAG)

#define	W_EXITCODE(ret, sig)	((ret) << 8 | (sig))
#define	W_STOPCODE(sig)		((sig) << 8 | _WSTOPPED)
#endif /* !defined(_POSIX_SOURCE) */



/*
 * Option bits for the third argument of wait4.  WNOHANG causes the
 * wait to not hang if there are no stopped or terminated processes, rather
 * returning an error indication in this case (pid==0).  WUNTRACED
 * indicates that the caller should receive status about untraced children
 * which stop due to signals.  If children are stopped and a wait without
 * this option is done, it is as though they were still running... nothing
 * about them is returned.
 */
#define WNOHANG		1	/* don't hang in wait */
#define WUNTRACED	2	/* tell about stopped, untraced children */


/*
 * Tokens for special values of the "pid" parameter to wait4.
 */
#define	WAIT_ANY	(-1)	/* any process */
#define	WAIT_MYPGRP	0	/* any process in my process group */


pid_t wait ( int *status );
pid_t waitpid (pid_t pid, int *status, int options); 


/*
 //BSD System Calls Manual        
 // wait, wait3, wait4, waitpid -- wait for process termination 
#include <sys/wait.h>

     pid_t wait(int *stat_loc);
     pid_t wait3(int *stat_loc, int options, struct rusage *rusage);
     pid_t wait4(pid_t pid, int *stat_loc, int options, struct rusage *rusage);
     pid_t waitpid(pid_t pid, int *stat_loc, int options);
*/


/*

https://www.dca.ufrn.br/~adelardo/cursos/DCA409/node36.html
    
	  int *status               // status descrevendo a morte do filho 

       pid_t wait(int *status)    // espera a morte de um filho 
       pid_t waitpid(pid_t pid, int *status, int options)	 

Valor de retorno: identificador do processo morto ou -1 em caso de erro. 
A fun????o wait suspende a execu????o do processo at?? a morte de seu filho. 
Se o filho j?? estiver morto no instante da chamada da primitiva 
(caso de um processo zumbi, abordado mais a frente), a fun????o retorna imediatamente.

??? refletindo
ent??o wait faz uma chamada ao kernel e se encontrar o filho morto, ja retorna.
caso n??o encontre o filho morto ent??o o kernel muda o status da thread e retorna da interrup????o
isso far?? com que a thread n??o rode mais apos uma interruo????o do timer;
??

A fun????o waitpid suspende a execu????o do processo at?? que o filho especificado pelo argumento 
pid tenha morrido. Se ele j?? estiver morto no momento da chamada, o comportamento ?? id??ntico ao descrito anteriormente.

O valor do argumento pid pode ser:

< -1 : significando que o pai espera a morte de qualquer filho cujo o ID do grupo ?? igual so valor de pid;
-1 : significando que o pai espera a morte de qualquer filho;
0 : significando que o pai espera a morte de qualquer processo filho cujo ID do grupo ?? igual ao do processo chamado;
> 0 : significando que o pai espera a morte de um processo filho com um valor de ID exatamente igual a pid.


Se status ?? n??o nulo (NULL), wait e waitpid armazena a informa????o relativa a raz??o da morte do processo filho, sendo apontada pelo ponteiro status. Este valor pode ser avaliado com diversas macros que s??o listadas com o comando shell man 2 wait.

O c??digo de retorno via status indica a morte do processo que pode ser devido uma:

uma chamada exit(), e neste caso, o byte ?? direita de status vale 0, e o byte ?? esquerda ?? o par??metro passado a exit pelo filho;
uma recep????o de um sinal fatal, e neste caso, o byte ?? direita de status ?? n??o nulo. Os sete primeiros bits deste byte cont??m o n??mero do sinal que matou o filho.
*/




