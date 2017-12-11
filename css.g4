grammar css;
 
expressions			: expression+;


 assignment			: WORD (WORD | Variable | HEX)* ';'		#command
					| OFFSET WORD SIGN HEX ';'					#offset
					;

 expression			: GROUP WORD ID+ '{' assignment+ '}'	#groupassign
					| VAR Variable '=' (WORD | HEX)			#varassign
					| ID '{' assignment+ '}'				#idassign
					;

 
 fragment DIGIT		: [0-9];
 fragment LETTER	: [a-zA-Z];

 SIGN				: ('-'|'+');
 OFFSET				: 'Offset';
 GROUP				: 'Group';
 VAR				: 'Var';
 Variable			: '$' LETTER+;
 HEX				: '0x' (DIGIT | [aAbBcCdDeEfF])+;

 WORD				: (LETTER | '-' | '%' | NUMBER)+;
 ID					: ('.' | '#') LETTER (LETTER | DIGIT | '-')*;
 NUMBER				: DIGIT+ ;
 
WHITESPACE          : (' '|'\t'|'\r'|'\n')+ -> skip ;