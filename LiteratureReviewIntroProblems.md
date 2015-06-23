When a team of computer forensics experts conducts the analysis of a
digital crime scene, it faces several challenges, which constitute a
critical path to the acceptance of any potential evidence produced as
an outcome [17 ](.md):

  * **Admissible**
    * Must be able to be used in court or elsewhere
  * **Authentic**
    * Evidence relates to incident in relevant way
  * **Complete** (no tunnel vision)
    * Exculpatory evidence for alternative suspects
  * **Reliable**
    * No question about authenticity & veracity
  * **Believable**
    * Clear, easy to understand, and believable by a jury

While computer forensics is not an entirely new field per se, there
are still gray areas in its legal definition and
application. Therefore it is important to pay crucial attention to the
details of the forensics analysis setting and its execution.

Also, a company who wants to protect its digital assets might want to
reuse various components of an Information Security Management System
or a similar framework, destined to prevent the destruction and/or
stealth of its corporate information, and to facilitate its recovery,
should the worst happen.

Such concerns, though not addressed in this document, are in close
relationship with its content, as some of the elements described in
existing specifications of such frameworks are part of the general
concepts of computer forensics we describe, or applied by the
solutions we review.

In the context of a company in the position of building a legally
receivable case, the questions we aim to ask and answer in this paper
are the following:

  * What information are available on a common system (default installation)?
  * What information should be collected ?
  * How can this information be collected ?
  * How can this information be stored ?
  * How can this information be transferred ?
  * What impact will be induced on system performance by the gathering of information ?

This brings us to consider the various elements of a forensics
analysis system:

  * The data source/host system,
  * The data samples themselves,
  * The data storage system.

These questions have several aspects pertaining to the collected
information (the "data"), regarding its courtwise validity and value:

  * Exhaustiveness,
  * Integrity,
  * Confidentiality,
  * Reliability.

# More on Computer Security #

Before going further, let us quickly explain what type of intrusion
and attacks a computer system can be exposed to and what can we do,
from a forensics point-of-view, to detect these attacks.

## Computer Intrusion ##

William Stallings defined three distinct types of Computer Intrusion [21 ](.md):
  * Masquerader
    * An individual who is not authorized to use the computer and who penetrates a system’s access controls to exploit a legitimate user account.
  * Misfeasor
    * A legitimate user who accesses data, programs, or resources for which such access is not authorized, or who is authorized for such access but misuses his or her privileges.
  * Clandestine User
    * An individual who seizes supervisory control of the system and uses this control to evade auditing and access controls or to suppress audit collection.

## Computer Vulnerabilities ##

In 2000, Eric Knight gave an exhausting list of Computer
Vulnerabilities [13 ](.md), although time has passed they are still the
same nowadays:

  * Logic Errors
    * Mistakes in the design of the software that allows a security breach.
  * Social Engineering
    * "Art of personal manipulation"
  * Computer Weakness
    * Very similar to vulnerabilities, the difference being that weaknesses might never have a resolution (e.g. encryption key size)
  * Policy Oversights
    * Doesn't necessarily involve people, can be simple "Act of God" such as fire or hardware failures
  * Faults
    * Commonly known as Bugs

## Computer Forensics ##

When one of the above vulnerabilities is successfully applied to
perform an intrusion computer forensics is used to [22, 2, 16 ](.md):

  * assess that an intrusion as happened
  * what have been affected
  * how the intrusion did happen

In order to do so, evidences can be collected from various sources [22, 2 ](.md):

  * Hard Drives
  * Memory
  * System Logs
  * Network Traffic
  * IDS (both NIDS, HIDS)
  * Physical Security

However, on a default system only System Logs level would be
available. Unfortunately, they can be easily modified by the attacker
and are not configured to log as many data as possible by default and
these are often not kept long enough or in a secure location. On the
other hand, IDS and Physical Security when installed and correctly
configured can cut down forensics investigation time in half [22 ](.md).


---


[Literature Review](LiteratureReview.md) >
[Introduction](LiteratureReviewIntro.md) >
[Research Problems](LiteratureReviewIntroProblems.md)