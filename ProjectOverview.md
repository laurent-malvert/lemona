_This is a very brief description of the **lemona** project._

_For more information and a complete description of the
project's proposal and project's plan refer to the
[Project Outline](ProjectOutline.md)_


**Table of Contents**

  * **Overview**
  * **General Objectives**
  * **Architectural Concepts**


---



# Overview #

**Lemona** is a research project originally started at the
Macquarie University of Sydney, driving towards a proposal
for an open decentralized monitoring architecture for
real-time and post-mortem forensics examination of
compromised systems.



---



# General Objectives #

## An Open Architecture ##

This project aims to provide a proposal for an open and
flexible architecture, reusing and relying on open and secure
standards of communication and storage.

A system compliant with the **Lemona** architecture should be:

  * decentralized
  * open

It should be able to perform:

  * real-time monitoring and tracing
  * real-time reporting
  * real-time and post-mortem analysis, based on dynamic and static rules
  * post-mortem recovery of compromised and/or damaged systems

## A Technical Proof-of-Concept & A Reference Implementation ##

A basic implementation is being developed to serve both as
a technical proof of concept for the relevance of post-mortem
forensics analysss and decentralized monitoring, and as a
reference for future parties interested developing similar systems
based on our architecture.



---



# Architectural Concepts #

## Tracing Components ##

The tracing components are defined as a suite of kernel
patches and kernel modules, intended to monitor and record
user and system activity on a specific host.

## Reporting Components ##

The reporting components relay the raw information monitored
on the host and report it securely to local or remote data
storage units as well as alert repoting systems.

## Forensics Components ##

The forensics components are either fully featured and fully
geared toolkits or standalone tools coupled with 3rd party
systems.

Their role is to process, store and analyze the reported data
information, and to automatically identify (or allow the manual
identification of) threats and attack attemps performed on the
monitored systems.

Their secondary role is the recovery of the compromised systems.


---


[Project Overview](ProjectOverview.md)