### Shell Grammar

```
    <command line>      ::=      <job> ';' <command line>
                            |    <job> '&' <command line>
                            |    <job> ';'
                            |    <job> '&'
                            |    <job>

    <job>               ::=      <job> '|' <command>
                            |    <command>

    <command>           ::=      <simple command> '<' <str>
                            |    <simple command> '>' <str>
                            |    <simple command> '>>' <str>
                            |    <simple command>

    <simple command>    ::=      <cd command>
                            |    <path command>

    <cd command>        ::=      'cd' <str>
                            |    'cd'

    <path command>      ::=      <str> <path command>
                            |    <str>
```

### Shell Grammar for recursive descent parser
### Removed left recursion and left factoring

```
    <command line>      ::=     <job> <command line 1>

    <command line 1>    ::=     <command line 1.1>
                            |   <command line 1.2>
                            |   epsilon

    <command line 1.1>  ::=     ';' <command line 1.3>

    <command line 1.2>  ::=     '&' <command line 1.3>

    <command line 1.3>  ::=     <command line>
                            |   epsilon

    <job>               ::=     <command> <job 1>

    <job 1>             ::=     '|' <job 1>
                            |   epsilon

    <command>           ::=     <simple command> <command 1>

    <command 1>         ::=     '<' <str>
                            |   '>' <str>
                            |   '>>' <str>
                            |   epsilon

    <simple command>    ::=     <cd command>
                            |   <path command>

    <cd command>        ::=     'cd' <str>
                            |   'cd'

    <path command>      ::=     <str> <path command 1>
    
    <path command 1>    ::=     <str> <path command 1>
                            |   epsilon
```

