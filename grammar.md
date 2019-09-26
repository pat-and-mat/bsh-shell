### Shell Grammar

```
	<command line>	::=  	<job>
						|	<job> '&'
						|	<job> '&' <command line>
						|	<job> ';'
						|	<job> ';' <command line>

	<job>			::=		<command>
						|	<job> '|' <command>

	<command>		::=		<simple command>
						|	<simple command> '<' <filename>
						|	<simple command> '>' <filename>
						|	<simple command> '>>' <filename>

	<simple command>::=		<pathname>
						|	<simple command>  <token>
```

### Shell Grammar for recursive descent parser
### Removed left recursion and left factoring

```
	<command line>	::= 	<job> <command line1>
						|	<job> <command line2>

	<command line1>	::= 	';' <command line>
						| 	';'
						|	(EMPTY)
	
	<command line2>	::= 	'&' <command line>
						| 	'&'
						|	(EMPTY)

	<job>			::=		<command> <job1>

	<job1>			::=		'|' <job1>
						|	(EMPTY)

	<command>		::=		<simple command> <command1>

	<command1>		::=		'<' <filename>
						|	'>' <filename>
						|	'>>' <filename>
						|	(EMPTY)

	<simple command>::=		'cd' <token list>
						|	<pathname> <token list>

	<token list> ::=	<token> <token list>
						| (EMPTY)
```

