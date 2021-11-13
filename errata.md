# Errata for *Modern Arm Assembly Language Programming*

On **page 287** the function ConvertB_ has a superfluous return type.
 
The forward declare for the function ConvertB_ is listed as follows:

extern "C" int ConvertB_(int* x, const char** msg_strings, double a);

The return value of int is not used by the calling code in ConvertB nor is it meaningfully set by the implementation of the function ConvertB_. The value in x0 upon return happens to still be the pointer to x. As such it should be listed as follows:

extern "C" void ConvertB_(int* x, const char** msg_strings, double a);

***

On **page xx** [Summary of error]:
 
Details of error here. Highlight key pieces in **bold**.

***