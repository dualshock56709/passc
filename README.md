# passc
## a simple password generator written in C

---

### how to use:

```passc [character count] [min ascii value] [max ascii value] '[character blacklist]'```

please consider that this program doesn't use an argument parsing library (for now), so you have to replace the arguments with '' if you don't use it

character count: the number of characters the password will have
min ascii value: the minimum char or ascii value that the program will choose (32 by default)
max ascii value: the maximum char or value that the program will choose (126 by default)
character blacklist: a list of characters between quotes that can't be in your password

