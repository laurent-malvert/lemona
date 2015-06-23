| **DOWNLOADS** | [PDF](http://lemona.googlecode.com/svn/docs/presentations/2008.09.19/%5BITEC810%5D%20-%20Presentation%201.pdf) | [PPTX](http://lemona.googlecode.com/svn/docs/presentations/2008.09.19/%5BITEC810%5D%20-%20Presentation%201.pptx) | [PPT](http://lemona.googlecode.com/svn/docs/presentations/2008.09.19/%5BITEC810%5D%20-%20Presentation%201.ppt) |
|:--------------|:---------------------------------------------------------------------------------------------------------------|:-----------------------------------------------------------------------------------------------------------------|:---------------------------------------------------------------------------------------------------------------|

# Table of Contents #

  * **Introduction**
  * **Presentation**
  * **Slides**


---



# Introduction #

A Presentation held at Macquarie University for ITEC810, giving a broad overview of computer forensics and the scope of Lemona.

This is the first presentation ever written on Lemona.



---



# Presentation #

## Title Slide ##

  * **LEMONA**
  * _Linux Enhanced Monitoring Architecture_
  * (Linux zest for security)

  * **Authors**
    * Kenfe-Mickael Laventure
    * Laurent Malvert

  * **Venue**
    * Macquarie University
    * 2008.09.19

## Outline ##

  * **Security and Forensics**
    * Forensics
    * Computer Security
    * Computer Forensics
  * **Related Work**
  * **Lemona**
    * Project
    * Overview
    * Architecture
  * **References**

## Slide 3: Forensics ##

  * Short for “Forensic Science”
  * Aims at:
    * Collecting Evidence
    * Providing Legal Proof (used in court)
  * Concerned with Computers / Networks

## Slide 4: Computer Security ##

  * **CIA**
    * Confidentiality
    * Integrity
    * Availability

## Slide 5: Computer Security ##

  * Denial of Service
  * Eavesdropping
  * Illegal Access
  * Impersonation
  * Repudiation
  * Tampering

## Slide 6: Computer Forensics ##

  * Memory Analysis...
    * Volatile Memory	(i.e. RAM)
    * Optical Drives	(i.e. CD-ROM)
    * Magnetic Drives	(i.e. HDD, Floppies)
  * ... but also Logs Analysis
    * Network
    * System

## Slide 7: Computer Forensics ##

  * **Incomplete**
    * Logs are not activated by default
    * Not everything is logged
    * Not all applications generate logs
  * **Unreliable**
    * Generated in User Land
    * Editable by an Attacker

## Slide 9: Related Work ##

  * **Forensix**
    * +System Calls Interposition
    * +Attack Reconstruction
  * **Sarmoria**
    * +Memory Mapped Files Monitoring
    * -Not "State Aware"
  * **Kprove / DjProbe**
    * +Dynamic Kernel Probing
    * +Built in Kernel (but inactive by default)
  * **ReVirt**
    * +Sandboxing

## Slide 11: Lemona - Project ##

  * **Open Architecture**
    * Open Protocols
    * Open Source Implementation
  * **Decentralized**
    * Local Tracing Components
    * Remote Monitoring Components
  * Prevention, Detection, Forensics, Recovery
    * Possible ... ?

## Slide 12: Lemona - Overview ##

  * **Exhaustiveness**
    * Kernel Land Tracer -> 100% User Land Coverage
  * **Integrity**
    * Harder to bypass -> Would require Kernel Level code
    * Integrity Checks
  * **Flexibility**
    * Variable Granularity Levels
    * Selectable Hooks

## Slide 13: Lemona - Architecture ##

  * **Workflow / Hooks**
    * User Application
      * System Call
        * Entry
        * Execution
        * Return
      * Memory Mapped File
        * Open
        * Read/Write PageFault
        * Close
  * **Architecture** (graphic)

## Slide 15: References - Lemona ##

  * [home](http://lemona.googlecode)
  * [blog](http://lemona-project.blogspot.com/)
  * [wiki](http://lemona.googlecode.com/wiki/)
  * [SCM](http://lemona.googlecode.com/svn/)
  * [newsgroup](http://groups.google.com/group/lemona/)

## Slide 16: References - Related ##

  * **SARMORIA, C. G. & CHAPIN, S. J. (2005)**
    * _Monitoring access to shared memory-mapped files._
    * Proc. of the 2005 Digital Forensics Research Workshop (DFRWS). New Orleans.
  * **GOEL, A., FENG, W. C., MAIER, D. & WALPOLE, J. (2005)**
    * _Forensix: a robust, high-performance reconstruction system._
    * Distributed Computing Systems Workshops, 2005. 25th IEEE International Conference on, 155-162.
  * **KRISHNAKUMAR, R. (2005)**
    * _Kernel korner: kprobes-a kernel debugger._
    * Linux Journal, 2005.



---


[Presentations](Presentations.md) > [Presentation MQ 2008.09.17](Presentation20080917.md)
