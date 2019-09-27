### Shell Grammar

```
    <command line>      ::=      <job> ';' <command line>
                            |    <job> '&' <command line>
                            |    <job> ';'
                            |    <job> '&'
                            |    <job>

    <job>               ::=      <job> '|' <command>
                            |    <command>

    <command>           ::=      <simple command> '<' <filename>
                            |    <simple command> '>' <filename>
                            |    <simple command> '>>' <filename>
                            |    <simple command>

    <simple command>    ::=      'cd' <str list>
                            |    <path command>

    <path command>      ::=      <str> <str list>

    <str list>          ::=      <str> <str list>
                            |    epsilon
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

    <command1>          ::=     '<' <filename>
                            |   '>' <filename>
                            |   '>>' <filename>
                            |   epsilon

    <simple command>    ::=     'cd' <str list>
                            |    <path command>

    <path command>      ::=      <str> <str list>

    <str list>          ::=      <str> <str list>
                            |    epsilon
```

