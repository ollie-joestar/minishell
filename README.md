▗▖  ▗▖▗▄▄▄▖▗▖  ▗▖▗▄▄▄▖ ▗▄▄▖▗▖ ▗▖▗▄▄▄▖▗▖   ▗▖   
▐▛▚▞▜▌  █  ▐▛▚▖▐▌  █  ▐▌   ▐▌ ▐▌▐▌   ▐▌   ▐▌   
▐▌  ▐▌  █  ▐▌ ▝▜▌  █   ▝▀▚▖▐▛▀▜▌▐▛▀▀▘▐▌   ▐▌   
▐▌  ▐▌▗▄█▄▖▐▌  ▐▌▗▄█▄▖▗▄▄▞▘▐▌ ▐▌▐▙▄▄▖▐▙▄▄▖▐▙▄▄▖
                                               
Our `minishell` with **Hanju-kun** *UwU*


***PLAN***

1. **Read from the command line**:
    - Read the input from the command line.
    - The input will be a string of words separated by spaces.
    - The program will read the input and store it in a variable.
    - Handle the signals `Ctrl+C` and `Ctrl+D`etc.
    `getcmd()`
    returns *string*

2. **Syntax check**:
    - Check if the input is a valid format.
    - If the input is not a valid format, print an error message and exit the program.
    <!--- If the input is builtin, put builtin in the builtin list.-->
    `syntaxcheck()` 
    returns *boolean*

3. **Lexical analysis**:
    - Split the input into typeless tokens.
    - Associate the tokens with their respective types.
    - Expand the variables if needed.
    - Store the tokens in a list with their respective types.
    `lex()`
    returns *list* of tokens

4. **Parsing**:
    
5. **Execution**:
    - Execute the command.
    - If the command is a builtin command, execute the builtin command.
    - If the command is not a builtin command, execute the external command.
    `execute()`
    returns *None*

//WORST CASE
//minishell> < infile1 << "lim" > outfile1 echo hello world > outfile2 < infile2 | < infile3 "ca""t" > outfile3 *** BONUS PART***  && echo hello world
// ";" not implemented
//< infile > outfile NOT NEEDED !!!!!!!!!!
//< infile cat > outfile should work
//< infile cat | > outfile should NOT WORK
//

test="first"
another="anything here"
<!--[echo] [-n] ['$word'N$test"something] [else"] [$another] [|] [cat] // input line-->
<!--[echo] [-n] [$wordN$test"something] [else"] [$another] [|] [cat] // open single quote-->
<!--[echo] [-n] [$wordNfirst"something] [else"] [$another] [|] [cat] // expand variable-->
<!--[echo] [-n] [$wordNfirstsomething else] [$another] [|] [cat] // open double quote-->
<!--[echo] [-n] [$wordNfirstsomething] [else] [$another] [|] [cat] // split by space-->
<!--[echo] [-n] [$wordNfirstsomething] [else] [anything here] [|] [cat] // expand variable-->
<!--[echo] [-n] [$wordNfirstsomething] [else] [anything] [here] [|] [cat] // split by space-->

open double quote -> expand variable -> split by space
expand variable -> split by space
open single quote -> split by space
