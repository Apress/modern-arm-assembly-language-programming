# Errata for *Modern Arm Assembly Language Programming*

On **page 307** in PackedAdd/SubI16 saturated results read results from the wrong register:
 
sqadd v3.8h,v0.8h,v1.8h and sqsub v3.8h,v0.8h,v1.8h write results v3/q3. however, when storing the value to [x0,16] we read the previous results from q2 instead of q3.

***

On **page xx** [Summary of error]:
 
Details of error here. Highlight key pieces in **bold**.

***