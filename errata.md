# Errata for *Modern Arm Assembly Language Programming*

On **page 267** after the label CalcArraySumA_ cmp uses the wrong argument:

The code reads cmp w1,**w0** when it should read cmp w1,**0** as it is trying to compare the second function parameter and value n to 0 and not to the first function parameter x which is an address.

***

On **page 267** after the label LoopB a comment refers to an register name which doesn't exist on arm64.
 
The comment reads **r5** = x[i] when it should read **x4** = x[i].

***

On **page xx** [Summary of error]:
 
Details of error here. Highlight key pieces in **bold**.

***