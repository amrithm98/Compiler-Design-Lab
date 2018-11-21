Details & Instructions
========================
<ul>
<li> Refer to Bash Script for the set of commands executed to compile and RUN </li>
<li> YACC contains code for symbol table creation and generation
<li> YACC contains a char array machine_code which stores the entire machine code</li>
<li> pos is a variable used to index where to next insert machine code instruction</li>
<li> stack is used to insert position where jump and goto address must be replaced. </li>
<li> interpreter.c simply does what each instruction demands. Creates an array of variables called data_segment. Pops elements from stack and does operations. Implements goto by decreasing line number </li>
</ul>