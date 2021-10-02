# Compiler
A program that implements a model language compiler.  
Objectives:  
* To develop a software tool that implements lexical analysis of the program text in the input language;
* To implement syntactic analyzer of program text in model language by recursive descent method;  
Formal Problem Model:  
The rules, operations, and expressions of the model language are as follows:
1. language operations:
    * Syntax of the "relation" group of operations (in order: unequal, equal, less than, or equal to, greater than, greater than, or equal to)  
    <relationship_group_operations>::: = != | = | < |= | > | >=  
    * Syntax of a group of "addition" operations (in order: addition, subtraction, disjunction)  
    <synthesis_group_operations>:: = + | - ||  
    * Syntax of group of operations "multiplication" (in order: multiplication, division, conjunction)  
    <operations_group_multiplication>::= * | / | &&
    * Unary operation syntax  
    <unary_operation>::= !  
2. The language expression is given by the rules:
    * <expression>::=<operand>{<operations_group_relationship> <operand>}
    * <operand>::=<summary> {<operations_group_relation> <summary>}
    * <sumptive>::= <multiplier> {<operations_group_integer> <multiplier>}
    * <multiplier>::= <identifier> | <number> | <logical_constant> |<unary_operation> <multiplier> | (<expression>)
    * <number>::= {/ <number> /}
    * <logical_constant>::= true | false
    * <identifier>::= <letter> {<letter> | <number>}
    * <letter>::= a | b | c | d | e | f | g | h | i | j | k | l | m | n | o | p | q | q | r | s | t | u | v | w | x | y | z
    * <number>::= 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9
3. A rule defining the structure of a program 
    <program>::= "{" {/ (<description> | <operator>) ; /} "}"
4. The rule defining the variable description section is
    <description>::= {<identifier> {, <identifier> } : <type> ;} 
5. Rule defining data types (in order: integer, valid, logical) 
    <type>::= % | ! 
6. A rule defining a program operator 
    <operator>::= <compound> | <assignment> | <conditional> | <fixed_cycle> | <conditional_cycle> | <input> | <output>  
   * Compound operator syntax  
    <compound>::= begin <operator> { ; <operator> } end
   * Assignment operator syntax  
    <assignment>::= <identifier> := <expression> 
   * Conditional assignment operator syntax  
    <assignment>::= <identifier> := <expression> 
   * Syntax of a fixed number of repetitions loop operator  
    <fixed_cycle>::= for <assignment> to <expression> [step <expression>] <operator> next
   * Syntax of conditional loop operator  
    <conditional_cycle>::= while (<expression>) <operator> 
   * Syntax of operator input  
    <input>::= readln identifier {, <identifier> } 
   * Output statement syntax  
    <output>::= writeln <expression> {, <expression> } 
7. Syntax of multiline comments
    * Comment start sign - /*
    * The sign of the end of the comment - */  
Algorithm:  
Lexical analyzer - a string with code is given as an input 
    * Read from file the keywords and separators, and write them into vectors
    * Read from the file the source program code, split the line on tokens using regular expression, check tokens belonging
    to lists of keywords and delimiters, forming of an individual code for each token and writing it into a vector
2. Syntactic analyzer - a vector with lexeme codes as the input
    * Description of the syntax of programming language constructions with the help of context free grammars and Backus-Naur form of notation:
        For my version, the grammar looks as follows:
        1. P → {D2}
        2. D2 → D1
        3. D1 → D | D1;D | S | S1;S
        4. D → I1:% | I1:! | I1:$ 
        5. I1 → I | I1, I.
        6. S1 → S | S1,S
        7. S → begin S;S end | I1:= E | if (E) S [else S] | for I1 to E [step E] S next | while (E) S | readln I1 | writeln E
        8. E → E1 | E1 != E1 | E1 == E1 | E1<E1 | E1 <= E1 | E1E1 | E1>=E1
        9. E1 → T | T+E1 | T-E1 | T&E1 
        10. T → F | F*T | F/T | F&&T
        11. F → N | L | I | ! 
        12. l → true | false 
        13. I → C | IC | 
        14. N → R | NR
        15. C → 𝑎 | 𝑏 | 𝑐 | 𝑑 | 𝑒 | 𝑓 | 𝑔 | ℎ |𝑖 | 𝑗 | 𝑘 | 𝑙 | 𝑚 | 𝑛 | 𝑜 | 𝑝 | 𝑞 | 𝑟 | 𝑠 | 𝑡 | 𝑢 | 𝑣 | 𝑤| 𝑥 | 𝑦 | z 
        16. R → 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9
        Grammar in the form of Bacus - Naurus 
        1. <letter>:: = 𝑎 | 𝑏 | 𝑐 | 𝑑 𝑒 | 𝑓 | 𝑔 | ℎ | 𝑖 | 𝑗 | 𝑘 | 𝑙 | 𝑚 | 𝑛 | | 𝑜 | 𝑛1 | 𝑞 | 𝑟 | 𝑠 | 𝑡 | 𝑢 | 𝑣 | 𝑤 | 𝑥 𝑦 | z
        2. <digit>::= 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9
        3. <identifier>::= <letter> {<letter> | <number>}
        4. <number>::= {/<digit>/}
        5. <keyword>::= begin | end | if | else | for | to | step |next | while | readln | writeln | true | false
        6. <separator>::= ( | ) | := | , | ; | : | { | | } | + | - | * | / | || | && | != | == | < | > |<= | => | [ | ]
        7. <program>::= { { /(<description> | <body> ); / }
        8. <description>::= { <identifier> {, <identifier> }: <type>: }
        9. <body>::= <operator>
        10. <operator>::= <component> | <assignment> | <conditional> | <fixed_cycle> | <conditional_cycle> | <input> | <output>
        11. <component>::= begin <operator> {;<operator>} end
        12. <assignment>::= <identifier> := <expression>
        13. <conditional>::= if (<expression>) <operator> [else <operator>]
        14. <fixed_cycle>::= for <assignment> to <expression> [step <expression>] <operator> next
        15. <conditional_cycle>::= while (<expression>) <operator>
        16. <input>::= readln <identifier> {, <identifier> }
        17. <output>::= writeln <expression> {, <expression> }
        18. <expression>::= <sum> | <sum> (!= | = |= | | <= | > | =>) <sum>
        19. <sum>::=<product> | <product> (+ | - ||) <product>
        20. <product>::=<multiplier> | <multiplier> (* |/ |&&) <multiplier>
        21. <multiplier>::= <identifier> | <number> | <logical_constant> | !<multiplier>
        22. <logical_constant>::= true | false
    * Formation of the set FIRST (nonterminal character and all first characters from the rules with the corresponding nonterminal character)
    * Forming the FOLLOW set (the nonterminal character and all characters that come after the corresponding nonterminal character from the right part of the rule)
    * Using FIRST and FOLLOW sets, the code string is checked for correctness from the grammatical point of view
