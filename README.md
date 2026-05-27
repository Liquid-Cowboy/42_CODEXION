<i>This project has been created as part of the 42 curriculum by mnogueir</i>

# Codexion


## Description
<b>Codexion</b> is a coding project whose purpose is to show mastery over <b>multi-thread management</b> by dealing with race conditions, deadlocks, thread starvation prevention and scheduling.  
By simulating a roundtable with coders that are **compiling**, **debugging** and **refactoring**, the project establishes the perfect analogy for multiple threads attempting execution. Each coder needs a pair of dongles to compile with and there are as many dongles as there are coders. Coder 1 will grab the dongle to his left - dongle 1 - and the dongle to his right - dongle 2; Coder 2 will grab the dongle to his left - dongle 2 - and the dongle to his right - dongle 3, an so on and so forth. Coder ```<number_of_coders>``` will grab dongle ```<number_of_coders>``` and dongle 1.  

<i>Visual representation</i>


```
C = coder
D = dongle
n = number of coders

╔══════╗  ╔══════╗  ╔══════╗  ╔══════╗
║  Dn  ║  ║  D1  ║  ║  D2  ║  ║  Dn  ║
╚══════╝  ╚══════╝  ╚══════╝  ╚══════╝
     \       / \       / \       /
      \     /   \     /   \     /
       \   /     \   /     \   /
     ╔══════╗  ╔══════╗  ╔══════╗  
     ║  Cn  ║  ║  C1  ║  ║  C2  ║  
     ╚══════╝  ╚══════╝  ╚══════╝ 		
```
At all times, two coders are competing for the same dongle. If one of them waits for too long, they might burn out, which begs the need for some kind of priority queue. Coders' starvation will be handled by one of the following two schedulers :
 - **FIFO** (***F**irst **I**n **F**irst **O**ut*) - The first coder to compile is then put last on the priority queue;
 - **EDF** (***E**arliest **D**eadline **F**irst*) - The coder which is closer to burning out is put first;  

Since we're dealing with only pairs of coders, I handle the sorting the following way:
```
coder 1 - has a pointer to dongle 1 and another one to dongle 2;

dongle 1 - has a pointer back to coder 1 and another one to coder <number of coders>;

dongle 2 - has a pointer back to coder 1 and another one to coder 2;


Following the given scheduler, coder 1 checks if he's prioritized against coder <number of coders> and coder 2. If this is true, coder 1 will try to grab both dongles and compile, or else he will wait for his turn.
```
While all these threads (coders) compete for the same resources (dongles), a separated monitor thread will keep track of each of the coders' lifespan and stop the program if one of them burns out (printing a descritptive message just before).
  
---

In order to complete this assignment, it is critical to understand the three following concepts:

- **Pthreads (POSIX threads)** - separate streams of action executing concurrently - the system manages resources, interleaving between them and making them appear to act simultaneously. We can use them in C by calling the ```<pthread.h>``` library.

- **Mutexes** - a kind of lock that protects a section of code and prevents it from being altered by other threads while being accessed.

- **Conditional variable** - a resource efficient way to make threads wait until a certain condition is met. Once this condition is finally truthful, it's state must be either signaled to a single thread or broadcasted to every thread at once.



## Instructions

To run codexion, the program must be launched with the following arguments:
<table>
<tr>
	<td><b>number_of_coders (digit)</b></td>
	<td>How many coders are connected to the Quantum Compiler.</td>
</tr>
<tr>
	<td><b>time_to_burnout (digit)</b></td>
	<td>How many milliseconds until a coder burns out (since last compilation start).</td>
</tr>
<tr>
	<td><b>time_to_compile (digit)</b></td>
	<td>How many milliseconds until a coder compiles.</td>
</tr>
<tr>
	<td><b>time_to_debbug (digit)</b></td>
	<td>How many milliseconds until a coder debbugs.</td>
</tr>
<tr>
	<td><b>time_to_refactor (digit)</b></td>
	<td>How many milliseconds until a coder refactors.</td>
</tr>
<tr>
	<td><b>number_of_compiles_required (digit)</b></td>
	<td>How many times a coder has to compile to exit simulation.</td>
</tr>
<tr>
	<td><b>dongle_cooldown (digit)</b></td>
	<td>How many milliseconds until a dongle is available again after being used.</td>
</tr>
<tr>
	<td><b>scheduler ("fifo" / "edf")</b></td>
	<td>Set priority to "First In First Out" or "Earliest Deadline First".</td>
</tr>
</table>

Alternatively, running **codexion** with ```--help``` will display a table similar to the one above, showing the user how to execute the program.

### Makefile Instructions
<table>
<tr>
<td><code>make / make all</code></td>
<td> Compiles the program into an executable file.</td>
</tr>
<tr>
<td><code>make clean</code></td>
<td> Cleans binaries.</td>
</tr>
<tr>
<td><code>make fclean</code></td>
<td> Cleans binaries and executable.</td>
</tr>
<tr>
<td><code>make re</code></td>
<td> Cleans binaries and executable and compiles everything all over again.</td>
</tr>
<tr>
<td><code>make def</code></td>
<td> Compiles the program into an executable file and runs it with default arguments.</td>
</tr>
</table>

## Blocking cases handled

Let's imagine the following scenario in which two coders are trying to compile. Coder 1 takes dongle 1 and, simultaneously, coder 2 takes dongle 2. Because coder 2 has taken dongle 2, coder 1 will have no other choice than to wait for dongle 2, but coder 2 can't compile either, since it's waiting for dongle 1, which has already been taken by coder 1. This is what's called a deadlock - coders will be waiting for each other until one of them eventually burns out.  
Here are met the four <b>Coffman's conditions</b>:
<table>
<tr>
<td><b>Mutual Exclusion</b></td>
<td>When multiple threads compete for the same resources (our dongles in this case), whichever threads get access to the shared resources, exclude all the other ones from getting them at that moment. If threads keep on excluding each other endlessly, a deadlock is has taken place.</td>
</tr>
<tr>
<td><b>Hold and Wait</b></td>
<td> Threads already holding resources can request additional resources and wait while holding the ones they were granted access to. This can also lead to a blockage of resources and eventual deadlock.</td>
</tr>
<tr>
<td><b>No Preemption</b></td>
<td>Resources cannot be forcibly taken from another thread's process. Threads must voluntarily release these resources so they can be used by other threads. If a thread holds a resource and can't proceed, a potential deadlock can arise.</td>
</tr>
<tr>
<td><b>Circular Wait</b></td>
<td>When a circular chain is implemented and threads wait on resources held by the next ones.</td>
</tr>
</table>

To avoid this kind of scenario a rule is put in place.
In my specific resolution of the problem I made it so coders always try to grab the dongle with the lower index first. This makes it so coder 2 will not try to grab dongle 2 first but instead dongle 1. If coder 1 grabs dongle 1 first, then coder 2 will wait while coder 1 compiles, having free access to both dongles. Other valid resolutions to this problem could be opting for dongles with an even index first or making the last coder wait.  
<br>
<b>Dongle cooldown</b> is calculated by keeping track of the precise moment the given dongle was last left and measuring whether the cooldown amount has already passed. A signal on the dongle state is broadcasted and ```<pthread_cond_timedwait>``` releases the dongle mutex until that moment or until the deadline arrives.

<b>Burnout</b> on the other hand is handled by the monitor, who keeps iterating between coders, checking their deadlines and setting the simulation state has <b>stopped</b> in case any of them actualy burns out. The monitor also holds a mutex for log serialization that can be accessed by all other threads to log their actions or by the monitor itself to announce burn out.


## Thread synchronization mechanisms

```<pthread_mutex_t>``` is used in three distint moments throughout codexion:
 - inside the coder struct to protect coder data from being accessed and dereferenced at the same time (ex. updating the last compilation start, checking the coder's ID,...)  ;
 - in the dongle struct to protect the current dongle state and the record of the last time it was used;
 - in the monitor struct so the log printing can be safely accessed one at a time, avoiding superimposed print statements.

 In the specific case of dongle mutexes, ```<pthread_cond_timedwait>``` is used so that coders can temporarily release this mutex and wait for a change in the dongle's state. This is an efficient way of managing system resources since the threads aren't needlessly running the loop and are ready to resume the process once the condition gets satisfied.


## Resources
- CodeVault's series on pthreads: <a href="https://www.youtube.com/watch?v=d9s_d28yJq0&t=4s">
Short introduction to threads (pthreads) </a><i>by CodeVault;</i>

- Pthreads tutorial: <a href="https://www.youtube.com/watch?v=uA8X5zNOGw8">
How to create and join threads in C (pthreads).</a><i> by Jacob Sorber;</i>

- Coffman's conditions explained: <a href="https://faq.computersciencewiki.org/index.php/home/article/coffman-conditions">
Coffman conditions</a><i> by ComputerScience KB;</i>


### AI use
 AI was used throught this project mainly to brainstorm on how to keep the project structured and figuring how ```<pthread_cond_timedwait>``` works. AI was also used to figure how to segment code and adhere to norminette's rules.
