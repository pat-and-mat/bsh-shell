### Shell Grammar
```
    <command line>      ::=     <job> <command line 1>
                            |   epsilon

    <command line 1>    ::=     ';' <command line>
                            |   '&' <command line>
                            |   epsilon

    <job>               ::=     <command> <job 1>

    <job 1>             ::=     '|' <job 1>
                            |   epsilon

    <command>           ::=     <redirect list> <str> <arg list>

    <redirect>          ::=     '<' <str>
                            |   '>' <str>
                            |   '>>' <str>

    <redirect list>     ::=     <redirect> <redirect list>
                            |   epsilon

    <str list>          ::=     <str> <str list>
                            |   epsilon

    <arg list>          ::=     <str> <arg list>
                            |   <redirect> <arg list>
                            |   epsilon
```