# Table of Contents #

  * **Background / Problem**
  * **Description**
  * **Scope**
  * **Deliverables**



# Background / Problem #

Enterprise Information Technology Systems are more often than not the
target of malevolent threats and behaviors intended to compromise
their integrity or the confidentiality of the data they retain.

Today's IT systems have recourse to intrusion prevention and detection
systems as well as anti-virus and malware protection softwares to
preserve their users' sensitive information.

However, once an attacker manages to break in, knowing that the system
has been compromised might not be enough, and forensics team are
requested to provide evidence of the intrusion and solutions to
circumvent future attempts to penetrate the system or its likes.

Such forensics examination requires the following pre-requisites, or a
combination of those:

  * technically highly proficient specialists;
  * the compromised system to still be available at hand and in a usable state.

Unfortunately, the second point is a crucial one, as an experienced
and skilled attacker will take great care in covering his tracks, and
eventually damaging the system beyond repair. He might not mind
setting off the alarms and prefer to damage data to hide his failed
and successful penetration attempts. In such a scenario, the forensics
team is left with little information to recreate the attacks and
understand what happened.

The goal of this project is to address this issue by providing an open
and decentralized redundant monitoring architecture for forensics
examination, allowing compromised systems to be evaluated post-mortem,
and ultimately to reconstruct attack scenarios step by step and
possibly recover the defunct system.



# Description #

The **lemona** project aims to produce a set of software
components implementing an open architecture addressing the issue
detailed above.

These software components include:

  * **tracers**

> These components interact in close collaboration with the
> operating system's kernel, via a set of patches and modules, to
> monitor the system's and user's activity to the lowest level
> possible, providing forensics team down the line with the most
> accurate data.

  * **reporting agents**

> These components might be integrated into the kernel but would
> probably better be suited to reside in user land, where they would
> collect the data traced in kernel land and re-route them to the
> next components' category.

> The reporting agents will use their own communication protocol to
> convey the raw collected data over secured datasets and in an
> exportable way, but might alternatively also reuse existent
> standard reporting protocols, such as SNMP.

> They might also be passive and implement features allowing
> standard high-level monitoring facilities, such as Nagios, to
> query their status.

  * **forensics tools**

> These components would constitute the visual front-end to the
> whole architecture and provide usable and meaningful information
> extracted from the raw datasets reported by the agents.

> Located on local or most probably remote repositories for the sake
> of security, those forensics tool would process the raw
> information received over secured communication channels to report
> to system administration and forensics team members willing to
> examine a system's status and reconstruct the last past events of
> its life for a given timespan.

> Restoration of disabled systems and data-recovery or
> reconstruction might also be possible in specific cases.



# Scope #

The scope of the **lemona** project within the Macquarie University's
ITEC unit is focused on the research and implementation of the
kernel land patches and modules, as well as on the drafting of the
whole architecture for the decentralized system, to allow future
improvements to build on it without backward compatibility issues.

Any other implemented feature at the project due date is to be
regarded as an extension.



# Deliverables #

The deliverables for the specified elements are:

  * **a small set of basic tracers**

> these kernel patches and modules implement basic memory and processes tracing routines.

  * **a small set of basic reporting agents** and **a reporting agents' controller**

> these convey the data collected by the tracers to the forensics storage and analysis tools.

  * **a small set of basic forensics tools**

> these help forensics teams to dissect attacks or failures endured by a monitored system.



---


[Project Outline](ProjectOutline.md) > [Project Proposal](ProjectProposal.md)