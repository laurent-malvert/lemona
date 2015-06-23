**Table of Contents**

  * **Information Gathering, Monitoring**
    * Logging
    * Hooks & Checkpoints
    * System Call Interception
    * Probes
  * **Information Reporting Specifics**
    * Reporting Architecture
      * Local
      * Remote and Centralized
      * Remote, Decentralized and Redundant
    * Reporting Modes
      * Uni-Directional
      * Bi-Directional
    * Response Times
      * Delayed / Post-Mortem
      * Near Real-Time
      * Real-Time
  * **Forensics Analysis Specifics**
  * **Reconstruction and Recovery Specifics**
    * Imaging: Snapshots, Clones and Ghosts
    * Revisions and Rollbacks
    * Virtualization / Sandboxing
    * Reconstruction


---


There is an urging need for always more dynamic and autonomous
intrusion detection systems and forensics analysis tools, capable of
reacting in real-time to attempted break-ins by securing the system or
recording suspicious activity.

Therefore, there is a flourishing mass of research projects published
on the net, describing various approaches to the resolution of
problems we exposed earlier, and which aim to fill in the gaps left
open by the current security architectures already available on
standard operating systems.

We will attempt to review these approaches from a conceptual
standpoint and provide an extensive review of their capabilities and
efficiency, to determine how they qualify (or not) for Lemona.

Though forensics analysis and system surveillance encompasses numerous
fields like we outlined above, we are here only going to focus on the
elements for which we intend to conduct, at least in the first place,
thorough research to design and implement the lemona framework.

Therefore, we will describe below research projects and their
approaches following four axis of study. Namely:

  * Monitoring Specifics
  * Reporting Specifics
  * Forensics Analysis Specifics
  * Recovery / Reconstruction Specifics



## Monitoring Specifics ##

Monitoring is the act of gathering information about a target system
and its current active state(s). There are various ways which one can
use to monitor a system, which we're going to review below.

### Logging ###

We refer as logging to the basic activity or recording a piece of
software's activity via the duplication and storage of its obvious
Input/Output channels and actions.

Such a monitoring system is a common and well-known feature, available
on almost every mainstream system nowadays.

Its full range of capabilities can be quite large, as it embodies the
simple act of an application logging its own IO and actions to buffer
files, either voluntarily (via the use of standard log files), or
indirectly (via the use of standard capture frameworks, such as the
classic syslog protocol and its syslogd daemon on UNIX systems [3 ](.md)).
The gathering and centralization of different logging information can
lead to the realization of an IDS [18 ](.md).

Logging features do not present much of an interest for us in the
context of our research, as they are by all aspects an existing and
well defined solution to higher-level concerns, but which cannot be
used to record a system's life long activity in a consistent, usable
and exhaustive manner.

They are, however, a standard and usable complement to other
solutions, and can be used as complimentary evidence. They sometimes
are enough to find the beginning of an intrusion scheme as shown by
Spitzner for his honeypot project [20 ](.md).

### System Call Interception ###

A very popular monitoring technique, which is still being heavily
researched is the one refered to as "System Call Interposition", or
"System Call Interception".

This technique relies on the fact that during the lifetime of any
given process or system activity of any kind, the kernel's core system
functions (the "system calls"), will be called upon to execute
specific actions.

It is possible to "intercept" at runtime calls to these core
functions. This is a very common method, used for instance by debugger
and tracers. It can be achieved in various ways, however the level of
granularity and reliability varies.

One could for instance use standard tools implementing the POSIX
tracing interfaces, such as the strace binary and its underlying
ptrace() function [11 ](.md). Ptrace() allows a program to spawn a new
process and follow its execution from start to finish, allowing the
observer to monitor each call of the child process to the system's
function, and to retrieve memory states. Similarly, one can attach to
an existing ptrace to undergo the same examination.

However, ptrace is not a reliable and viable solution in the case of
highly-critical systems, and for strict forensics examinations.

First of all ptrace() executes in userland and may be tampered with
relatively easily, allowing one to circumvent its action. Following a
similar approach, an attacker could also use ptrace() to its own
avantage to de-route a tracing system using ptrace() by using ptrace
himself, thus tracing the tracer and redefining its behavior at
runtime.

Finally, ptrace()'s performance might not be satisfactory. This not
only comes from the fact that a program executing ptrace() would
reside in userland, thus being undermined by resource-consuming
context switches, but also that it would not have a granularity
accurate enough to record timestamped valid system traces.

The other solution, which is employed by several projects [ 9, 12, 23
], is to patch the kernel source or to design it with the tracing in
mind from the beginning. The difference being mostly on the
architecture and goals chosen as well on the post-processing tools.
However, one need to be careful about the different problems inherent
to this style of instrumentation as referenced in the "Traps and
Pifalls" publication by Garfinkel [8 ](.md).

### Hooks and Checkpoints ###

We call a "hook" or a "checkpoint" a deliberate modification to a
system's kernel meant to inject a static piece of software recording
activity occuring at this specific point of the kernel's execution
flow.

This approach can be used for various purposes, for instance to
examine the performance of a system (by defining checkpoints one could
reuse to benchmark it) or to realize system call interposition (which
we have treated as a special case earlier).

This method provide the advantage of being quite flexible when it
comes to its penetration capabilities: it is virtually possible to
define static hooks for any part of a software, as long as one can
edit this software and recompile it for future - traced -
execution. The LTTng project chose this approach while managing to
incur a low performance impact when the checkpoints are not enabled[ 5
].

This technique is also used by project which aims are to only monitor
a subset of the kernel operations. Sarmoria [19 ](.md) used it to update
the Linux Kernel Memory Management code in order to instrument
accesses realized on Memory-Mapped files.


The obvious trade-off, however is the complexity of such a
manipulation, as it implies the tampering of software components of
the kernel. Such a system has to be validated against any new update
of the kernel source tree to ensure that new code changes don't impact
its behavior and/or stability. On the other hand, Sun with its Solaris
OS doesn't incur this penalty since the DTrace patches are maintained
and integrated by the kernel developers themselves [4 ](.md).

Also, static hooks are paradoxically unflexible, as you cannot
redefine at a user's request and at any given time the behavior of a
given checkpoint.

### Software Probes ###

Software probes are in the logic continuity of static system
hooks. We call a software probe any piece of software that allows
the injection at a given point of a software (the hook) another
independent piece of software (the probe), which will commonly be
used for monitoring purposes.

We call kernel probes instances of such a system that are
implemented in kernel land and allow an observer to monitor the
kernel's activity.

Their underlying logic is the same as the one of a system hook,
except they allow one to more or less dynamically reconfigure new
probes with different behaviors, and to hook itself up at any point
of the execution flow, granted one knows to which address to jump.

A probe will simply stop the execution of a process to execute as a
> "side behavior" when a checkpoint or hook is reached, and call its
defined handler(s). Upon completion of the probe's task(s), the
probe redirects the execution flow to the exact point where it left
off.

Various systems have been experimented with, benchmarking different
scenarios to reach decent level of granularity and verbosity for
low-level tracing, with very little overhead.

On Linux, the most common ones are Kprobe [14 ](.md) and Djprobe [ 12
]. The difference between the two being their implementations. The
approach which has been chosen by djprobe allow for less performance
impact although in some case kprobe mechanism will need to be used as
a fallback.

These probes facilities has lead to some interesting projects like the
systemtap architecture [7 ](.md) which based on these probes allow a more
generic approach for generating probe points or like Uprobes [11 ](.md)
which duplicate the behavior of kprobes for userland application.


## Information Reporting Specifics ##

Reporting is the act of transfering information from the source
system (also refered to as the audited system), where we gather
information from, to the storage system (also refered to as the
watch system), where we store the relevant collected data and
process it to extract information.

Reporting can be done in various ways, and even though it isn't in
itself a specific research point we are focusing on, it poses some
interesting security issues and design constraints, which impact its
use and the functionalities of the complete surveillance system.


### Reporting Architecture ###

We distinguish 3 different approaches to the design of the reporting
architecture.

#### Local ####

Some systems use a simple local reporting and storage system. This
system is the simplest by design, and requires no additional
hardware and diminishes the overhead of having to manage separate
systems.

However, it can also be rendered completely pointless if an attacker
gets full control of the compromised system and tampers with the
recorded data after they have been collected.

Similarly, if the system is brought to a complete failure, it might
not be possible to recover the collected data, thus rendering the
whole surveillance system ineffective.

Linux Kernel module for instance, can use the relayfs [24 ](.md) facility
to do so, making their log more easily accessible by userland software
thus avoiding to bloat the log captured by syslogd.

#### Remote and Centralized ####

This problem can be addressed by the use of a remote storage system.
The reporting agents located on the source host transmit all the
required data over a (preferably secure) communication channel. Which
is the architecture chosen by the Forensix project [9 ](.md).

As the collected data is being sent over the network to a separate
host, we can assign another team to the surveillance task, thus
separating concerns and restricing accesses.

In the case of a complete failure of the monitored system, the data
can still be accessed and the forensics analysis undergone
post-mortem.

However, a remote architecture, as opposed to a local one, also
poses several security issues. An attacker might be able to
interfere with such a system by:

  * Intercepting the collected data to get some knowledge on the
surveillance system
  * Penetrating and compromising the remote storage point itself
  * Severing the connection between the remote storage point and the
monitored host before attempting to break into the later.

#### Remote, Decentralized and Redundant ####

A possible alternative to the previous solution is to use a
decentralized and/or redundant architecture.

By decentralized, we mean an architecture where only partial
information about the monitored host is being stored on a single
storage point. Reconstructing the data could only be done by
retrieving it from various storage points, thus adding another layer
of anonymity (and possibly reducing load and separating concerns
again, by allocating one storage point to network data, and another
one to local IO, for instance).

By redudant, we mean an architecture where the data is being
duplicated on various hosts, ensuring that it can be cross-checked
for future use. Thus, the risk of loss of information by accidental
loss or malevolent tampering is reduced, as the complexity increases
for the attacker to conver his tracks.

However, we have not found any reference to any project using such a
design to this day.


### Reporting Modes ###

We expose here 2 different concepts in the use of reporting
techniques.


#### Uni-Directional ####

We call "uni-directional" reporting the act of only reporting
information from one host to another. In such a situation, we are
only in presence of a monitored source host, and a storage target
host.

Though the information can be processed either in near real-time or
after a given delay, in this concept the surveillance system won't
provide feedback to the monitored source to report on recommended
preventive or mitigating actions and counter-measures, should an
attack attempt be detected.

#### Bi-Directional ####

We call "bi-directional" a setting where both the monitored source
and the storage target communicate and interact with one another.

In this setting, the surveillance system makes it possible for the
host to react to an attack attempt or a system failure by receiving
information from the storage point, which takes care of the
defensive decision-taking process.

Such a design allows for dynamic defenses, and opens a very broad
range of perspective for surveillance systems, and aims to defer the
use of forensics analysis to a last resort.

Also, a monitored system might be instructed to disconnect of the
network or shut down if an aggression is being detected and cannot
be stopped, to prevent theft of sensitive information.

However, because of their complexity, it is difficult to implement
this kind of surveillance system in a practical setting, considering
the actual state of the hardware components, in terms of processing
power and bandwidth.


### Response Times ###

The response time of a surveillance system, may it be an IPS, IDS, an
hybrid system or a honeypot, can be sorted in one of the following
categories.

#### Delayed / Post-Mortem ####

A "delayed" or "post-mortem" analysis is performed after the event
occurred. Either the delay is so important that any relevant action
cannot be undertaken to have any noticeable effet, or the system is
already considered compromised, and eventually damaged beyond repair.

We consider it a "delayed" response time if we are in presence of a
slow, but still reactive surveillance system (either automated or
controlled by a human).

We consider it a "post-mortem" response time if no attempt is being
made to process the information at runtime, and the data is only
being inspected to undertake a forensics examination after an
incident.

#### Near Real-Time ####

A "near real-time" response time is considered when a monitoring
system is capable of reacting to an attempted attack in a very short
delay, possibly while the attack is being performed.

There is however still a delay, as the surveillance system only
collects and records data after an activity occurs, thus making it
impossible to guarantee (though it remains possible) the termination
an attack before it reaches a critical state.

#### Real-Time ####

A "real-time" surveillance system is one which can actually process
and react to the collected information before any further action can
be undertaken by either the attacker or the monitored system.

Typically, this would be possible by using a bi-directional reporting
system if we were in a setting allowing a monitored system to trace
and intercept all user activity, report it to the watch system, which
would then validate the pending action based on its knowledge of the
actual state of the monitored system.

It would then provide it with informative feed-back to block the
required action (and possibly contain or expell the attacker) or allow
it to executed.

This approach, as idealist as it may appear, is theoretically
possible. It is the logical evolution and combination of our hybrid
defense systems and honeypots, combining reactive monitoring and
control for dynamic intrusion prevention, detection, containment and
mitigation. Unfortunately, considering the current state of hardware
components at the day of this writing, the impact on the monitored
system's performance would probably render it unusable for most
enterprise use cases, and we assume this is the only reason why such a
system has not been designed and implemented yet.


## Forensics Analysis Specifics ##

We call here forensics analysis the act of processing collected data
to examine a digital crime-scene, for instance by reproducing an
attempted attack (or any other critical or casual activity).

This is made possible through extensive tracing of all low-level user
activity as described in the previous sections, which allows the
development of forensics tools to go through a legitimate or
illegitimate user ste-by-step.

Eventually, such an approach allows one to not only reproduce an
attack, to be able to:

  * understand how the system has been penetrated and compromised,
  * but also to recover a damaged or destroyed system.

There are various appropriate techniques we list as reference on how
to reproduce an attack. Some approaches rely on the very fine
granularity of the monitored data and its timestamping to build a
textual and possibly visual representation of the penetration.

An example of textual representation would consist in the querying of
the collected database to extract only information relative to a given
time frame, for a given user's execution of a very specific command.

An example of a visual representation could be derived from such
queries to form a graphical workflow of every atomic actions leading
ultimately to the compromised state, from the evidence of the attacker
exploiting a vulnerability to his covering of his tracks.


## Reconstruction and Recovery Specifics ##

We provide in this section a brief overview of the existing data
recovery methods, as well as the existing system and scenario
reconstruction techniques used by commercial and open source software
solutions.

We outline their specific strengths and weaknesses, to lead to the
conclusion that they could be combined for improved performance
depending on the favored angle of the size/speed/integrity trade-off.


### Imaging: Snapshots, Clones and Ghosts ###

In the world of software backup, an image refers to a bit-to-bit copy
which can be saved on storage media. In the occurrence of a system
crash, the whole image of the damaged system can be copied back onto
the live hardware (or on another machine with similar hardware
specifications).  This technique can be found in various commercial
and open source software solutions.

The term snapshot is often used in virtualized environments, like in
the xVM VirtualBox [29](.md) or VMWare [30](.md) products. In this case, a
"snapshot" of the virtual machine is captured to be reverted to at a
later stage.  Various file systems, like ZFS [27](.md), also use the same
systems to revert to previous states.

The term "clone" or disk cloning is more general, and usually used in
the context of "disk cloning", when a bit-to-bit copy of single hard
drive is being done. It is also sometimes refered to as "ghosting", as
a drive is being completely cloned, hence being frozen as a shadow
copy. This term is use for instace by Symantec's Norton Ghost [31](.md)
product line.

Imaging solutions provide a relatively convenient method for
safeguarding the loss of sensitive data. However they also come with
some major drawbacks, as they might require quite a huge amount of
storage space, and a reliable infrastructure to automate the
snapshots. The principle of "incremental backup" comes in very handy
here, as the successive storage of regular snapshots allows one to
remove previous images.

Also, if a snapshot is taken after the state of a machine has been
(even partially) compromised, and the previous backups have not been
preserved, then we are left with a potentially harmful snapshot.


### Revisions and Rollbacks ###

"Revision Control Systems" provide incremental backup features to
document management systems or file systems, while allowing them to
spare some storage space. Such solutions allow the user to "roll back"
to a previous state, as one would do with an image, but by using
incremental differential revisions of a file. In this case, a given
file is not being backed up following at regular time intervals, but
every time a modification occurs.

This of course that on very active systems, this setting will also
have potential impacts on the required storage space.

Such systems exist for various purposes, and are very common as
Software Configuration Management suites. Classics of the likes are of
course CVS [32](.md), SubVersioN [33](.md), Bazaar [34](.md), Mercurial [35](.md), git
[36](.md)...  each and every one of them coming with similar capabilities
extended by sets of more specific features, depending on the desired
software development approach (distributed or centralized, for
instance).

Some experimental file systems also resort to revision control, like
Wayback [28](.md), RepoFS [25](.md) or the Carbon Copy FileSystem [26](.md).

### Virtualization / Sandboxing ###

Virtualization is a technique allowing a complete system to run on top
of another system without been aware of it which has become quite
common in the past couple of years.

The ReVirt project [6 ](.md) had proven that it is possible, by capturing
and logging all non deterministic event generated by a target system
inside a vitual machine to be able to reproduce actively the execution
of a system from a given point. However, this technique has the
disadvantage to take as much time to reconstruct and discover what
happened as the time it took to the intrusion to be realised.


### Reconstruction ###

We have found to different but interesting method for reconstructing a
path of event.

The first one is the approach taken by the Forensix project [9 ](.md)
which based on their logs can generate SQL-based querie to retrieve a
succession of events based on different key input (PID, Time, File
accessed, ...).

The second approach, which Bactracker [12 ](.md) use, is starting from the
intrusion detection point to go backward, building a graph containing
all possible chain of events which could have lead to it. This allow
to obtain the process use the intruder to achieve his mischief.



---


[Literature Review](LiteratureReview.md) >
[Related Work](LiteratureReviewRelatedWork.md)