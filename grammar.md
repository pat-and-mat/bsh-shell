### Shell Grammar

```
	<command line>	::=  	<job>
						|	<job> '&'
						| 	<job> '&' <command line>
						|	<job> ';'
						|	<job> ';' <command line>

	<job>			::=		<command>
						|	< job > '|' < command >

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
	<command line>	::= 	<job> ';' <command line>
						|	<job> ';'
						| 	<job> '&' <command line>
						|	<job> '&'
							<job>

	<job>			::=		<command> '|' <job>
						|	<command>

	<command>		::=		<simple command> '<' <filename>
						|	<simple command> '>' <filename>
						|	<simple command>

	<simple command>::=		<pathname> <token list>

	<token list>	::=		<token> <token list>
						|	(EMPTY)
```
