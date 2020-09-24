To use the shell scripts in this directory, the source code must be
installed in the following directory:
    ~/ModArmAsm
See Appendix A for more information.

To run the shell scripts, you must change the file permissions as follows:

1. Open a terminal window in your home directory.

2. Type the following commands:
    cd ModArmAsm/Sh
    chmod u+x *.sh

----------------------------------------------------------

The script clean32.sh runs "make clean" for all 32-bit
source code examples.

The script make32.sh runs "make" for all 32-bit
source code examples.

The script run32.sh executes all 32-bit source code examples.

The scripts clean64.sh, make64.sh, and run64.sh are the counterpart
scripts for the 64-bit source code examples.

The files dirs32.txt and dirs64.txt contain the source code example
subdirectory names. These files are used by the scripts.
