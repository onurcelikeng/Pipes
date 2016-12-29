# Pipes
 
 
It must be a console application that can be compiled with standard GNU C compilers.
Program named myCat which prints the content of the file given in argv[1] to screen.
Another program named myMore that reads from the pipe until it sees 24 new lines and prints it to screen. When any key is pressed, it reads another 24 lines and prints again. Program continues with this routine until the end of the content in pipe or q is pressed. myCat can work alone with a valid argument, while myMore is to be used with myCat and should be called from the command line as:

#./myCat inputFile = myMore

When called with pipe that is the “=” symbol in our case, myCat will read the content of inputFile, write it to pipe and fork. Child process is going to call myMore program and the content will be displayed with paging.
