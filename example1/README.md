# Flex/Bison

## Unix

Look at the makefile.  The -ll (mac) might be -lfl on linux.

## Windows (Visual Studio)

Follow instructions at

https://sourceforge.net/p/winflexbison/wiki/Visual%20Studio%20custom%20build%20rules/

Note you should start with an empty console roject or delete the boilerplate main.

EXCEPT: Copy the entire directory of the bison flex distribution (usually under Program Files) into your project folder, so win_bison.exe and win_flex.exe are in the root of your project folder.
