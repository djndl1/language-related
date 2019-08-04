In the simplest case, a script is nothing more than a lsit of system commands stored in a file.

she-bang is actually a two-byte magic number, see `man magic`.

# Basics

- `;;`: terminator in a case option

- `,`: comma operator links together a series of arithmetic operations. All are evaluted, but only the last one is returned.

```shell
let "t2 = ((a = 9, 15 / 3))"
```
The comma can also concatenate strings.

- `"'`: lowercase conversion in parameter substitution

- ```: command substitution, also known as backquotes, or backticks.

- `:`: null command, NOP. Its exit status is true, thus can be considered a synonym for the shell builtin true.

```bash
while : // while true
do 
    op-1
    op-2
    ...
    op-n
done
```

```bash
if condition
then : # do nothing
else
    take-some-action
fi
```

Also a placeholder where a binary operation is expected.

```bash
: ${username=`whoami`}
: ${1?"Usage: $0 ARUGMENT"}

: ${HOSTNAME?} ${USER?} ${MAIL?}
: > data.xxx // truncate a file same as `cat /dev/null > data.xxx` without forking a process
: >> target.xxx // create if not present, otherwise nothing
```

Also a field separator, as in `$PATH` or in  `/etc/passwd`.

- `!`: reverse or negate the sense of a test or exit status [bang]. Or indirect variablre references.

- `*`: wildcard in globbing; `?`: single character in globbing.

- `$`: variable substitution.

- `${}`: parameter substitution.

- `$'...'`: quoted string expansion.

- `$*`, `$@`: positional parameter.

- `$?`: exit status

- `$$`: process ID variable.

- `()`: command group; a listing of commands within parentheses starts a subshell.

```bash
(a=hello; echo $a)
```

- `{xxx,yyy,zzz}`: brace expansion

``` bash
> echo ab{1,2,3,4}cd
ab1cd ab2cd ab3cd ab4cd
```

- `{a...z}`: extended brace expansion

```bash
> echo a{1..3}b
a1b a2b a3b
```

- `{}`: block of code; inline group, which creates an anonymous function. The variable inside a code block remain visible to the remainder of the script.

- `[]`: test

- `[[]]`: test

- `(())`: integer expansion, expand and evaluate integer expression within.

- `> &> >& >> < <>`: redirection;

```bash
scriptname > filename # redirects the output of `scriptname` to `filename`
command &> filename # redirects both stdout and stderr of command to filename
command >&2 # redirects stdout of command to stderr
scriptnam >> filename # appends the output of scripname to filename
[i]<> filename # opens filename for reading and writing and assigns file descriptor i to it. If filename does not exist, it is created.
```

- `<` `>` ascii comparison

```bash
if [[ "$veg1" < "$veg2" ]]
then
    ...
else
    ...
fi
```

- `<<`: redirectionin a here document

- `<<<`: redirection in a here string

- `|`: A pipe runs as a child process, and therefore cannot alter script variables. If one of the commands in the pipe aborts, this prematurely terminates execution of the pipe, called a _broken pipe_, sending a `SIGPIPE` signal.

- `>|`: force redirection.

- `-`: redirection from/to stdin or stdout, not a bash builtin. Where a filename is expected, `-` redirects output to stdout or accepts input from stdin.

```bash
 $ file -
#!/usr/bin/env python
/dev/stdin: Python script, ASCII text executable
```

- `~+`: current working directory, `$PWD`

- `~-`: previous working directory, `$OLDPWD`, ???

## Control characters

`Ctl-G`: bell.

`Ctl-H`: rubout, destructive backspace

`Ctl-J`: line feed

`Ctl-K`: vertical tab. Within a script, vertical tab goes straight down.

`Ctl-I`: horizontal tab

`Ctl-U`: kill backwards to the beginning or the whole line

`Ctl-M`: carriage return

`Ctl-L`: formfeed

`Ctl-O`: issue a newline

`Ctl-R`: backwards search for text in history buffer

`Ctl-S`: suspend

`Ctl-Q`: resume

`Ctl-V`: inserts control characters

`Ctl-T`: swap the current char with the previous one

`Ctl-W`: kill a word backwards

## Variables and Parameters



`$VAR` is a simplified form of `${VAR}`. Undeclared/uninitialized variable has a null value. Quoted strings exists as a whole.

```bash
a=15+5     # a 15+5
let b=20+1 # b 21
read a     # implicitly set a

var= # null value
unset var  # unset it
```

A null-valued variable is not the same as unsetting it.

Bash variables are untyped. Bash does not segregate its variables by type. Essentially, Bash variables are character strings. Depending on context, Bash permits arithmetic operations and comparsions on variables. The determining factor is whether the value of a variable contains only digits.

```bash
a=2345
let "a += 5" # a is now 2350
b=${a/23/BB} # However, it's still a string and can be substituted.
declare -i b # declaring it an integer doesn't help
let "b += 1" # b is now 1, the integer value of a string is 0

e='' # null value is integer 0
```

- `local var`: variable visible only within a code block or function

- `Environmental var`: variables that affect the behavior or the shell or user interface

- `$0`, `$1`, `$2`, ..., `${10}`, `$*`/`$@`: positional parameters with the final two denoting all the positional parameters and the first denoting the script's name; `$#`: the number of positional parameters, with `$0` not included.

The last argument is obtained using indirect reference:

```bash
args=$#
lastarg=${!args}
```

The `shift` command reassigns the positional parameters, in effect shifting them to the left one notch. A numerical parameter indicates how many positions to shift.

```bash
$1 <-- $2, $2 <-- $3, $3 <-- $4, ...
```

## Quoting

Quoting has the effect of protecting special character in teh tring from reinterpretation or expansion by the shell or shell script.

When referencing a variable, it is generally advisable to enclose its name in double quotes, which prevents reinterpretation of all special charactes within the quoted string, except `$`, ```(backquote) and `\`(escape). Use double quotes to prevent word splitting.

`\b` is not the backspace on the keyboard, more like the left arrow.

`$'abc'` is string expansion.

```bash
$ echo $'afd\nbcd'
afd
bcd
```

```bash
    case "$key" in
        $'x\1b\x5b\x32\x7e')
            echo Insert Key
            ;;

        d)
            date
            ;;
        q)
            echo Time to quit...
            echo
            exit 0
    esac
```

```bash
echo "foo\
bar"
#foobar
```

## Exit

An `exit` with no parameter, the exit status of the script is the exit status of the last command executed in the script.

`$?` reads the exit status of the last command executed. A `$?` following the executation of a pip gives the exit status of the last command executed.

## Tests

An `if/then` construct tests whether the exit status of a list of commands of is 0.

`[` (a command)  is a synonym for `test`. `[[...]]` is the _extended test command_ where `[[` is a keyword.

`((...))` and `let...` constructs return an exit status according to whether the arithmetic expressions they evaluate expand to a nonzero value. If the last ARG evaluates to 0, let returns 1;  returns 0 otherwise.

The exit status of an arithmetic expression is not an error value.

An `if ` can test any command, not just conditions enclosed within brackets.

```bash
if cmp a b &> /dev/null
then 
if cmp a b &> /dev/null
then
    echo "Files a and b are identical"
else
    echo "Files a and b differ"
fi
```

```bash
if echo "$word" | grep -q "$letter_sequence"
then
    echo "$letter_sequence found in $word"
else
    echo "$letter_sequence not found in $word"
fi
```

Note the differnce between `0` `1` `-1`  and `[ 0 ]`, `[ 1 ]`, `[ -1 ]`. The latter three all evaluate to true. 

When `if` and `then` are on the same line in a conditional test, a semicolon must terminate the `if` statement. Both `if` and `then` are keywords, which themselves begin statements. `[` doesn't necessarily requires `]`, however, newer versions of Bash requires it. There are builtin `[`, `/usr/bin/test` and `/usr/bin/[`. They are all the same.

`[[]]` construct is the more versatile Bash version of `[]`. Using the `[[ ... ]]` test construct, rather than `[ ... ]` can prevent many logic errors in scripts. For example, the `&&`, `||`, `<`, and `>` operators work within a `[[ ]]` test, despite giving an error within a `[ ]` construct. Arithmetic evaluation of octal / hexadecimal constants takes place automatically within a `[[ ... ]]` construct.

```bash
if [[ 15 -eq 0x0f ]] // [] error
then
    echo "Equal"
else
    echo "NotEqual"
fi
# Equal
```

A condition within test brackets may stand alone without an `if`, when used in combination with a list construct.

```bash 
[[ 15 -eq 0xfd ]] && echo "Equal" # Equal
```


Arithmatic expansion has the property of returning an exit status 0 when evaluating to nonzero, which is exactly what `if` needs.

```bash
if (( "5 > 2" ))
then
    echo "5>2"
else
    echo "5<=2"
    
fi
```

### Important file test operators

- `-e`/`-a`: file exists

- `-f`: regular files

- `-s`: not zero size

- `-d`: directory file

- `-b`: block file

- `-c`: character file

- `-p`: pipe file

```bash
echo "Input" | [[ -p /dev/fd/0 ]] && echo PIPE || echo STDIN
PIPE
```

- `-h`, `-L`: symbolic link

- `-S`: socket

- `-t`: file (descriptor) is associated with a terminal device

- `-r`;`-w`;`-x`: read/write/execute permission

- `-g`: set-group-id, a file within such a directory belongs to the group that owns the directory, not necessarily th the group of the user who created the file. This may be useful for a directory shared by a workgroup.

- `-u`: set-user-id, a binary owned by root with this flag runs with root priviledges, even when an ordinary user invokes it.

- `-k`: sticky bit, if set on a file, it's kept in cache memory; if set on a directory, it restricts write permission. This restricts altering or deleting specific files in such a directory to the owner of those files.

- `-O`: are you the owner?

- `-G`: your group?

### integer comparison

- `-eq`; `-ne`; `-gt`; `-ge`; `-lt`; `-le`;

- `<`; `<=`; `>`; `>=` only within `[[ ]]`

### String comparison

- `=`; `==`; `==` behaves diffferently within a double-bracket test than within single brackets

```bash
[[ $a == z* ]] # True if $a starts with an "z" (pattern matching).
[[ $a == "z*" ]] # True if $a is equal to z* (literal matching).
[ $a == z* ]  # File globbing and word splitting take place.
[ "$a" == "z*" ] # True if $a is equal to z* (literal matching).
```

- `!=`; `<`; `>`; the latter two needs an escape in `[ ]`

- `-z`: null string

- `-n`: not null string, always quote a tested string; the `[...]` test alone detects whether the string is null

### compound comparison

- `exp1 -a exp2`: logical and, or `[[ condition1 && condition2 ]]` (short-circuit)

- `exp1 -o exp2`: logical or, or `[[ conditional1 || condition2 ]]` (short-circuit)

Condition tests using the `if/then` may be nested.

## Operators

- `=`: all purpose assignment operator, which works for both arithmetic and string assignment

- `+`; `-`; `*`; `/`; `**` (exponentiation); `+=`; `-=`; `*=`; `/=`; `%=`;