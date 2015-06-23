# KML's Notes #

Computer Forensic Research Paper
  * Three Type of Intruders (according, According William Stallings book Cryptography and Network Security[2003](Stallings.md))
    * Masquerader
    * Misfeasor
    * Clandestine user
  * IDS Goals
> > The ultimate goal of Intrusion Detection is to identify, preferably in real\*time, unauthorized use, misuse, and abuse of computer systems by both systems insiders and external penetrators.

Know Your Ennemy
  * Example of forensics using the snort (N)IDS and an honeypot

Forensic Readiness
  * 4 potential source of incident data
    * The victim system(s) RAM, registers and raw disk
    * The attacking system(s) RAM, registers and raw disk
    * Logs (from the victim and attacking systems as well as intermediary systems)
    * Physical security at the attacking system (eg., camera monitoring, etc)
  * Cost
    * 2 hours intruder time -> x40 for forensic
  * Secured logs
  * Timestamp in GMT
  * Every thing should be kept

ReVirt
  * Place target in Virtualized Environment by using the UMLinux Virtual Machine
  * Log every non\*deterministic event (and some deterministic if they affect vm execution)
  * Lost time in replaying attack to determine what happens, can't not just query logs

Traps and Pitfalls - Pratical Problems in System Call Interposition Based Security Tools

> Common Mistakes:
    * OS Related
      * Incorrectly Mirroring OS state (by forgeting to monitor a given syscall for instance)
      * Incorrectly Mirroring OS code (like path resolution)
      * Overlooking Indirect Paths to Resources (it's possible to read/write from mmap for instance)
    * Race Conditions
      * Symbolic Link Race (symlink get changed before actually being used but after checking)
      * Relative Path Access (directory get moved before being used but after checking)
      * Argument Race (User memory containing arg get updated after checking but before use)
      * FS Race in MultiThreaded app (One thread open a file, get accepted, but a chroot is executed by another one and get done before the end of the opening process)
      * Shared Descriptor Race (close, dup2. This rejoined the Overlooking Indirect Path)
> Some Solutions:
    * Argument Race
      * Copying them into kernel first
      * Making them or copying them in a then write protected area
      * Checking for shared memory location
    * FS Race
      * Overloading of c library for verifiable access pattern (LD\_PRELOAD)
    * OS Related
      * Let the Kernel do the work when possible (call its inner function)

Efficient, Unified, and Scalable Performance Monitoring for Multiprocessor Operating Systems (K42)
  * Lockless Logging (K42 method based)
  * Non size\*fixed event recording
  * semi\*random access logs
  * per process buffer

relayfs - An Efficient Unified Approach for Transmitting Data from Kernel to User Space (page 519)
  * Mean to transfer data from kernel to user land
  * based on channel (they render buffering transparent)
  * Lockless event logging (borrowed from k42)
  * Timestamp: TSC or gettimeofday delta (both are optional)
  * overflow handling
    * overwrite old data
    * suspend writing (thus loosing new events)
    * grow channel size
  * used by LTT

Tracefs - A File System to Trace Them All
  * stackable FS (under user VFS)
  * can be used to monitor FS activity

Forensix - A Robust, High-Performance Reconstruction System (Full)
  * Instrument Target at Kernel Level (only logs syscall)
    * code based on SNARE
    * hooks syscall table and some specific code around syscall to capture argument
  * Logs are ketp on a secured host linked with a secured link to the target
    * MySQL based
  * Tools given to analyzed logs more easily by querying them
    * PID & Process time form the primary key
  * Attribute activity to someone by the mean of session started via the network or a daemon
  * Impact (compiling a kernel)
    * Network off (thus no sending to backend, but stored in local) 6%
    * Network on 8%
  * Impact (throughput of an apache webserver)
    * Network off -7%
    * Network on -37%

Monitoring Access to Shared Memory-Mapped Files
  * Monitor mapped memory area, 3 Level
    * object level (syscall)
    * VMA level
    * Page level	(the more complete)
  * set PTE flag to provocke a page fault at every access
    * Flag reset if process rescheduled (an restore once the process is back on CPU)
    * x86 limitation: cannot detect the switch from write to read
      * can be resolved by adding a trap instruction after read/write op. but should be really slow unless loop are taken in account

Forensic Discovery
  * NOTHING USEFUL JUST CULTURE GE

The LTTng tracer - A low impact performance and behavior monitor for Linux
  * Based on LTT
  * The policy are moved to Userland
  * Tracing generated from XML file
  * Use RelayFS for sending data to userland
  * Use K42 lockless mechanism

Probing the Gust of Kprobes
  * classic Probe
    * allow dynamic insertion (and thus instrumentation) of probe (break) in the kernel
    * use the int3 (breakpoint) for being invoked
      * then code is deviated to kprobe, which invoke handler, then switch back to the original code
  * JProbe
    * allow to inspect function arguments
    * built on above classical probe
  * function returned probe
    * let one analyzed the return value of a given func

Towards Runtime Monitoring In Real-Time Systems
  * L4 environment
  * Transmit monitored data using only shared memory

Djprobe - Kernel probing with the smallest overhead
  * Enhanced Kprobe performance by using jmp instead of int3 (breakpoint)
