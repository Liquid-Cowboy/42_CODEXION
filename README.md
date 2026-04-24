<i>This project has been created as part of the 42 curriculum by mnogueir</i>

# Codexion


## Description
<b>Codexion</b> is a coding project whose purpose is to show mastery over <b>multi-thread management</b> by dealing with race conditions, deadlocks, thread starvation prevention and scheduling.  
By simulating a roundtable with coders that are compiling, debugging and refactoring, the project establishes the perfect analogy for multiple threads attempting execution. Each coder needs a pair of dongles to compile and there are as many dongles as there are coders. 


```
C = coder
D = dongle
n = number of coders

╔══════╗  ╔══════╗  ╔══════╗  ╔══════╗ 
║  Cn  ║  ║  C1  ║  ║  C2  ║  ║  C3  ║ 
╚══════╝  ╚══════╝  ╚══════╝  ╚══════╝
          /      \  /      \ 
		 /        \/        \
		/         /\         \
	   /         /  \         \
╔══════╗  ╔══════╗  ╔══════╗  ╔══════╗
║  Dn  ║  ║  D1  ║  ║  D2  ║  ║  D3  ║
╚══════╝  ╚══════╝  ╚══════╝  ╚══════╝
		
```



## Instructions

## Blocking cases handled

## Thread synchronization mechanisms
section describing all the concurrency issues addressed
in your solution (e.g., deadlock prevention and Coffman’s conditions, starvation
prevention, cooldown handling, precise burnout detection, and log serialization).


## Resources
section explaining the specific threading
primitives used in your implementation (pthread_mutex_t, pthread_cond_t,
custom event implementation) and how they coordinate access to shared resources
(dongles, logging, monitor state). Include examples of how race conditions are
prevented and how thread-safe communication is achieved between coders and the
monitor.