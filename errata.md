# Errata for *Modern Arm Assembly Language Programming*

On **page 304** struct alignas(16) Vec128 is missing a final semicolon:
 
Due to a partial inclusion of this type from the header Vec128.h the code as written does not compile and is potentially unclear to the reader as a result.

***

On **page xx** [Summary of error]:
 
Details of error here. Highlight key pieces in **bold**.

***