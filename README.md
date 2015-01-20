# LibCringe -- Never cringe when using strings in C again.
LibCringe is unlike many other dynamic string libraries. Instead of going the usual way - holding buffers and size in structs which are the actual strings, LibCringe, as inspired by the Simple Dynamic Strings library, goes a different path.

Instead of the Cringe string being a struct, the "crstring" type is nothing more than a typedef for char\*. Yes, that's right. Cringe strings are char pointers. How does it work then? How can it be dynamic and store additional data?

LibCringe is inspired by SDS, the Simple Dynamic Strings library. SDS uses an ingenious way of storing additional data like size alongside the dynamic strings. It uses tricks and quirks in the C language to implement strings fully compatible with read-only functions. LibCringe improves upon SDS by implementing besides other features better error handling and cleaner code.

# How is LibCringe better than other dynamic string libraries?
Let's check this on a simple printf function call.
In your usual string library, to output the content of a string, you'd probably do this:

    string str = newString("Hello world!");
    printf("str = %s\n", getString(str));

In LibCringe you do this:

    crstring str = cr_new("Hello world!");
    printf("str = %s\n", str);

Yup! That's right. We just passed a crstring as a string to the printf call. What's the result of the program? Guess yourself.

# SDS behaves the same. How is LibCringe better than SDS?
SDS's code is full of useless and sometimes wrong things. For example, SDS stores the size of a string in a 32-bit signed integer. The maximum of a 32-bit signed integer on my computer is 2147483647. How much is that? ~268MB. What does that mean? Your program is very vulnerable to overflow attacks. LibCringe stores the size of a string in a size\_t. On my computer it's a long unsigned int, which holds about 2306 PETABYTES. Yup, you read it right. PETABYTES. Your program using LibCringe is vulnerable to overflow attacks as well. Be ready for aliens 10000 years later cracking your programs.

# Boooring... I can do the same just changing "int" to "size\_t" in SDS. Is there anything truly special about LibCringe?
Yes. Remember how I said you can use LibCringe/SDS strings just like normal in read-only functions? Well... what if I told you you can use LibCringe strings in functions that... write to strings? It can. What's even better? They are dynamic in this case as well. Unless you have a function that manually sets strings (in which case you should stop using it...), the functions you use that set strings use functions from string.h. This header contains many routines like memcpy, strcat etc. that help with managing memory. LibCringe includes a header file called "cringe-string.h". It includes wrappers for those functions and defines macros to replace them. These wrappers check if the string is a crstring and use the dynamic functions to change them. That ensures that almost ANY of the functions you used before with C-style strings can be used with LibCringe strings as well. How cool is that?

# That's interesting. How do I install LibCringe?
Clone the repo, 'make', 'make install' and you're done. Easy, huh?

# Licensing
LibCringe is dual-licensed under GPLv2 and GPLv3. You're free to use LibCringe in projects licensed under at least one of these licenses. See the files "LICENSE", "LICENSE.GPL2" and "LICENSE.GPL3".
