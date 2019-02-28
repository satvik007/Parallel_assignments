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

It turns out that the terminal does a similar translation on the output side. It translates each newline
 ("\n") we print into a carriage return followed by a newline ("\r\n"). The terminal requires both of these 
 characters in order to start a new line of text. The carriage return moves the cursor back to the beginning 
 of the current line, and the newline moves the cursor down a line, scrolling the screen if necessary.

We will turn off all output processing features by turning off the OPOST flag. In practice, the "\n" to 
"\r\n" translation is likely the only output processing feature turned on by default.

OPOST comes from <termios.h>. O means it’s an output flag, and I assume POST stands for “post-processing of output”.

BRKINT, INPCK, ISTRIP, and CS8 all come from <termios.h>.

When BRKINT is turned on, a break condition will cause a SIGINT signal to be sent to the program, 
    like pressing Ctrl-C.
INPCK enables parity checking, which doesn’t seem to apply to modern terminal emulators.
ISTRIP causes the 8th bit of each input byte to be stripped, meaning it will set it to 0. This is 
    probably already turned off.
CS8 is not a flag, it is a bit mask with multiple bits, which we set using the bitwise-OR (|) operator
    unlike all the flags we are turning off. It sets the character size (CS) to 8 bits per byte. On my system,
    it’s already set that way.

Currently, read() will wait indefinitely for input from the keyboard before it returns. What if we want to do
something like animate something on the screen while waiting for user input? We can set a timeout, so that 
read() returns if it doesn’t get any input for a certain amount of time.

VMIN and VTIME come from <termios.h>. They are indexes into the c_cc field, which stands for 
"control characters", an array of bytes that control various terminal settings.

The VMIN value sets the minimum number of bytes of input needed before read() can return. We set it to 0 
so that read() returns as soon as there is any input to be read. The VTIME value sets the maximum amount of
time to wait before read() returns. It is in tenths of a second, so we set it to 1/10 of a second, or 100 
milliseconds. If read() times out, it will return 0, which makes sense because its usual return value is 
the number of bytes read.

perror() comes from <stdio.h>, and exit() comes from <stdlib.h>.

Most C library functions that fail will set the global errno variable to indicate what the error was. perror()
looks at the global errno variable and prints a descriptive error message for it. It also prints the string 
given to it before it prints the error message, which is meant to provide context about what part of your
code caused the error.

errno and EAGAIN come from <errno.h>.

tcsetattr(), tcgetattr(), and read() all return -1 on failure, and set the errno value to indicate the error.

In Cygwin, when read() times out it returns -1 with an errno of EAGAIN, instead of just returning 0 like 
it’s supposed to. To make it work in Cygwin, we won’t treat EAGAIN as an error.

An easy way to make tcgetattr() fail is to give your program a text file or a pipe as the standard input instead
of your terminal. To give it a file as standard input, run ./kilo <kilo.c. To give it a pipe, run echo test |
./kilo. Both should result in the same error from tcgetattr(), something like Inappropriate ioctl for device.

The CTRL_KEY macro bitwise-ANDs a character with the value 00011111, in binary. (In C, you generally specify 
bitmasks using hexadecimal, since C doesn’t have binary literals, and hexadecimal is more concise and readable
once you get used to it.) In other words, it sets the upper 3 bits of the character to 0. This mirrors what
the Ctrl key does in the terminal: it strips bits 5 and 6 from whatever key you press in combination with
Ctrl, and sends that. (By convention, bit numbering starts from 0.) The ASCII character set seems to be designed
this way on purpose. (It is also similarly designed so that you can set and clear bit 5 to switch between 
lowercase and uppercase.)

write() and STDOUT_FILENO come from <unistd.h>.

The 4 in our write() call means we are writing 4 bytes out to the terminal. The first byte is \x1b, which is 
the escape character, or 27 in decimal. (Try and remember \x1b, we will be using it a lot.) The other three
bytes are [2J.

We are writing an escape sequence to the terminal. Escape sequences always start with an escape character 
(27) followed by a [ character. Escape sequences instruct the terminal to do various text formatting tasks, 
such as coloring text, moving the cursor around, and clearing parts of the screen.

We are using the J command (Erase In Display) to clear the screen. Escape sequence commands take arguments,
which come before the command. In this case the argument is 2, which says to clear the entire screen. <esc>
[1J would clear the screen up to where the cursor is, and <esc>[0J would clear the screen from the cursor 
up to the end of the screen. Also, 0 is the default argument for J, so just <esc>[J by itself would also
clear the screen from the cursor to the end.

For our text editor, we will be mostly using VT100 escape sequences, which are supported very widely by 
modern terminal emulators. See the VT100 User Guide for complete documentation of each escape sequence.

If we wanted to support the maximum number of terminals out there, we could use the ncurses library, which
uses the terminfo database to figure out the capabilities of a terminal and what escape sequences to use 
for that particular terminal.

You may notice that the <esc>[2J command left the cursor at the bottom of the screen. Let’s reposition it 
at the top-left corner so that we’re ready to draw the editor interface from top to bottom.

This escape sequence is only 3 bytes long, and uses the H command (Cursor Position) to position the cursor. 
The H command actually takes two arguments: the row number and the column number at which to position the cursor.
So if you have an 80×24 size terminal and you want the cursor in the center of the screen, you could use the
command <esc>[12;40H. (Multiple arguments are separated by a ; character.) The default arguments for H both
happen to be 1, so we can leave both arguments out and it will position the cursor at the first row and first
column, as if we had sent the <esc>[1;1H command. (Rows and columns are numbered starting at 1, not 0.)

On most systems, you should be able to get the size of the terminal by simply calling ioctl() with the 
TIOCGWINSZ request. (As far as I can tell, it stands for Terminal IOCtl (which itself stands for Input/Output
Control) Get WINdow SiZe.)

ioctl(), TIOCGWINSZ, and struct winsize come from <sys/ioctl.h>.

On success, ioctl() will place the number of columns wide and the number of rows high the terminal is into
the given winsize struct. On failure, ioctl() returns -1. We also check to make sure the values it gave 
back weren’t 0, because apparently that’s a possible erroneous outcome. If ioctl() failed in either way, 
we have getWindowSize() report failure by returning -1. If it succeeded, we pass the values back by setting
the int references that were passed to the function.

Now let’s add screenrows and screencols to our global editor state, and call getWindowSize() to fill in those values.

initEditor()’s job will be to initialize all the fields in the E struct.
Now we’re ready to display the proper number of tildes on the screen:

We are sending two escape sequences one after the other. The C command (Cursor Forward) moves the cursor 
to the right, and the B command (Cursor Down) moves the cursor down. The argument says how much to move it 
right or down by. We use a very large value, 999, which should ensure that the cursor reaches the right and 
bottom edges of the screen.

The C and B commands are specifically documented to stop the cursor from going past the edge of the screen.
The reason we don’t use the <esc>[999;999H command is that the documentation doesn’t specify what happens 
when you try to move the cursor off-screen.




