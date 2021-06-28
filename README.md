# Thread Scheduler

The program activates N threads (N is given via the command line, N<10). It implements an internal scheduling system for its N threads.
The scheduler picks a thread to run from the queue, according to its priority.

To schedule a thread, it uses taskWake().
A thread relinquishes the processor at a preemption point.
The scheduler is invoked each T seconds (T defaults to 1, but may be changed via the command line, when given as an argument).

To simulate an external interrupt, the scheduler may also be invoked via a user signal. This is done by sending a SIGUSR1 signal to the process, through the use of the Linux CLI kill utility (man kill).
The scheduler changes the run queue to execute first the threads by the time of scheduling and not by their priority.
