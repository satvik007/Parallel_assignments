read() and STDIN_FILENO come from <unistd.h>. We are asking read() to read 1 byte from the standard input 
into the variable c, and to keep doing it until there are no more bytes to read. read() returns the number
of bytes that it read, and will return 0 when it reaches the end of a file.

However, by default your terminal starts in canonical mode, also called cooked mode. In this mode, keyboard
input is only sent to your program when the user presses Enter.

We can set a terminal’s attributes by (1) using tcgetattr() to read the current attributes into a struct, 
(2) modifying the struct by hand, and (3) passing the modified struct to tcsetattr() to write the new terminal
attributes back out. Let’s try turning off the ECHO feature this way.

struct termios, tcgetattr(), tcsetattr(), ECHO, and TCSAFLUSH all come from <termios.h>.

The ECHO feature causes each key you type to be printed to the terminal, so you can see what you’re typing. 
This is useful in canonical mode, but really gets in the way when we are trying to carefully render a user
interface in raw mode. So we turn it off. 

Terminal attributes can be read into a termios struct by tcgetattr(). After modifying them, you can then apply
them to the terminal using tcsetattr(). The TCSAFLUSH argument specifies when to apply the change: in this case,
it waits for all pending output to be written to the terminal, and also discards any input that hasn’t been read.

The c_lflag field is for “local flags”. A comment in macOS’s <termios.h> describes it as a “dumping ground for
other state”. So perhaps it should be thought of as “miscellaneous flags”. The other flag fields are c_iflag 
(input flags), c_oflag (output flags), and c_cflag (control flags), all of which we will have to modify to 
enable raw mode.

ECHO is a bitflag, defined as 00000000000000000000000000001000 in binary.

Let’s be nice to the user and restore their terminal’s original attributes when our program exits. We’ll save 
a copy of the termios struct in its original state, and use tcsetattr() to apply it to the terminal when the
program exits.

atexit() comes from <stdlib.h>. We use it to register our disableRawMode() function to be called automatically
 when the program exits, whether it exits by returning from main(), or by calling the exit() function.

You may notice that leftover input is no longer fed into your shell after the program quits. This is because 
of the TCSAFLUSH option being passed to tcsetattr() when the program exits. 

There is an ICANON flag that allows us to turn off canonical mode. This means we will finally be reading 
input byte-by-byte, instead of line-by-line.

ICANON comes from <termios.h>. Input flags (the ones in the c_iflag field) generally start with I like ICANON does.
However, ICANON is not an input flag, it’s a “local” flag in the c_lflag field. So that’s confusing.

iscntrl() comes from <ctype.h>, and printf() comes from <stdio.h>.

iscntrl() tests whether a character is a control character. Control characters are nonprintable characters 
that we don’t want to print to the screen. ASCII codes 0–31 are all control characters, and 127 is also a 
control character. ASCII codes 32–126 are all printable. (Check out the ASCII table to see all of the characters.)


By default, Ctrl-C sends a SIGINT signal to the current process which causes it to terminate, and Ctrl-Z 
sends a SIGTSTP signal to the current process which causes it to suspend. Let’s turn off the sending of both 
of these signals.

ISIG comes from <termios.h>. Like ICANON, it starts with I but isn’t an input flag.

Now Ctrl-C can be read as a 3 byte and Ctrl-Z can be read as a 26 byte.


By default, Ctrl-S and Ctrl-Q are used for software flow control. Ctrl-S stops data from being transmitted 
to the terminal until you press Ctrl-Q. This originates in the days when you might want to pause the transmission
of data to let a device like a printer catch up.

IXON comes from <termios.h>. The I stands for “input flag” (which it is, unlike the other I flags we’ve seen 
so far) and XON comes from the names of the two control characters that Ctrl-S and Ctrl-Q produce: XOFF to
pause transmission and XON to resume transmission.

Now Ctrl-S can be read as a 19 byte and Ctrl-Q can be read as a 17 byte.

On some systems, when you type Ctrl-V, the terminal waits for you to type another character and then sends 
that character literally. For example, before we disabled Ctrl-C, you might’ve been able to type Ctrl-V and 
then Ctrl-C to input a 3 byte. We can turn off this feature using the IEXTEN flag.

Turning off IEXTEN also fixes Ctrl-O in macOS, whose terminal driver is otherwise set to discard that control
character.

IEXTEN comes from <termios.h>. It is another flag that starts with I but belongs in the c_lflag field.

Ctrl-V can now be read as a 22 byte, and Ctrl-O as a 15 byte.

If you run the program now and go through the whole alphabet while holding down Ctrl, you should see that we 
have every letter except M. Ctrl-M is weird: it’s being read as 10, when we expect it to be read as 13, since
 it is the 13th letter of the alphabet, and Ctrl-J already produces a 10. What else produces 10? The Enter key does.

It turns out that the terminal is helpfully translating any carriage returns (13, '\r') inputted by the user 
into newlines (10, '\n'). Let’s turn off this feature.

ICRNL comes from <termios.h>. The I stands for “input flag”, CR stands for “carriage return”, and NL stands
 for “new line”.

Now Ctrl-M is read as a 13 (carriage return), and the Enter key is also read as a 13.


