<i>This project has been created as part of the 42 curriculum by mnogueir</i>

# Codexion


## Description
<b>Codexion</b> is a coding project whose purpose is to show mastery over <b>multi-thread management</b> by dealing with race conditions, deadlocks, thread starvation prevention and scheduling.  
By simulating a roundtable with coders that are **compiling**, **debugging** and **refactoring**, the project establishes the perfect analogy for multiple threads attempting execution. Each coder needs a pair of dongles to compile with and there are as many dongles as there are coders. Coder 1 will grab the dongle to his left - dongle ```<number of coders>``` - and the dongle to his right - dongle 2; Coder 2 will grab the dongle to his left - dongle 1 - and the dongle to his right - dongle 3, an so on and so forth.  

<i>Visual representation</i>


```
C = coder
D = dongle
n = number of coders

╔══════╗  ╔══════╗  ╔══════╗  ╔══════╗
║  Dn  ║  ║  D1  ║  ║  D2  ║  ║  D3  ║
╚══════╝  ╚══════╝  ╚══════╝  ╚══════╝
       \         \  /         /
        \         \/         /
         \        /\        /
  	      \      /  \      /  
╔══════╗  ╔══════╗  ╔══════╗  ╔══════╗ 
║  Cn  ║  ║  C1  ║  ║  C2  ║  ║  C3  ║ 
╚══════╝  ╚══════╝  ╚══════╝  ╚══════╝		
```
At all times, two coders are competing for the same dongle. If one of them waits for too long, they might burn out, which begs the need for some kind of priority queue. Coders' starvation will be handled by one of the following two schedulers :
 - **FIFO** (***F**irst **I**n **F**irst **O**ut*) - The first coder to compile is then put last on the priority queue;
 - **EDF** (***E**arliest **D**eadline **F**irst*) - The coder which is closer to burning out is put first;  

Since we're dealing with only two coders, I handle the sorting the following way:
```
coder 1 - has a pointer to dongle <number of coders> and another one to dongle 2;

dongle <number of coders> - has a pointer back to coder 1 and another one to coder <number of coders - 1>;

dongle 2 - has a pointer back to coder 1 and another one to coder 3;


Following the given scheduler, coder 1 checks if he's prioritized against coder <number of coders - 1> and coder 3. If this is true, coder 1 will try to grab both dongles and compile, or else he will wait for his turn.
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
section describing all the concurrency issues addressed
in your solution (e.g., deadlock prevention and Coffman’s conditions, starvation
prevention, cooldown handling, precise burnout detection, and log serialization).


## Thread synchronization mechanisms
section explaining the specific threading
primitives used in your implementation (pthread_mutex_t, pthread_cond_t,
custom event implementation) and how they coordinate access to shared resources
(dongles, logging, monitor state). Include examples of how race conditions are
prevented and how thread-safe communication is achieved between coders and the
monitor.

## Resources

### AI use