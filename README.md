# Compiler for E-expressions (EPP Compiler)

This project extends the capabilities of the E++ expression evaluator to include compilation and code generation for input E++ expressions.
## Author : Abdullah
## Setup & Requirements

### Download Tester
To begin, download the tester from this [link](https://github.com/aditm7/Starter_Code-COL106_A5/archive/refs/heads/main.zip). The tester includes:

- **bin**: Stores compiled binaries.
- **include**: Contains header files; replace empty headers with provided headers.
- **samples**: Offers sample targ and e++ files for reference.
- **src**: Holds .cpp files; replace empty .cpp files with provided ones.
- **tests**: Solely for testing; refrain from making changes here.

### Building the Compiler
From the main directory, run the following command to build the compiler:
```bash
make
```
If the build process is successfull then a binary file named e++ would have been generated in the bin folder. <br>

`Note:` For windows systems, it won’t work, you need to install GNU make command first.
Running the compiler:<br>

You can test your compiler by running it on a set of E++ expressions. Write the set of valid E++ expressions
in a file (suppose it’s `a.txt`), in the tokenized form i.e between each token there should be an at least one
space character separating the two tokens. Also note that the empty lines are ignored. See the samples
folder for examples.<br>

To compile the set of E++ expressions in the file, place your built compiler in the same directory as the `a.txt`
and run the command (eg is for MacOS/Linux):<br>
```bash
./e++ a.txt
```
If there are no errors in the process, then a file named ``targ.txt``, would be generated containing the targ
commands for `a.txt` .

### Testing the Targ Syntax
In the directory tests/targ there are binaries for each OS. Copy the respective binary file to the same
folder in which your filename.txt is there, containing the Targ commands. Run the following command (eg
is for MacOS/Linux):
```bash
./targ++ filename.txt
```
- If you get the permission denied error, then run `sudo chmod +x targ++` only once to make system
trust the executable.
- For MacOS, if the issue persists still or you get unidentified developer error then open the binary by
right-clicking on it and now you will be able to run the binary normally by `./targ++`.
- `Note:` The binaries only checks that the commands are syntactically correct or not. Neither their
semantics nor their logical output is being checked.

### Tester
`Note:` The tester is designed for Unix based systems only (i.e Linux and MacOS), it is strongly advised for
Windows users to either install WSL.
- **Building and Running the Tester**:
  - Run the following command from the parent directory:
```bash
make tester
```
  - If there are no errors then a binary file named tester would have been generated in the bin folder. Change
your directory to the bin folder and run the command :
```bash
./tester
```
  - Follow rest of the instructions on your screen in order to run the tests.

`Note :` These instructions are also given in assignment pdf
