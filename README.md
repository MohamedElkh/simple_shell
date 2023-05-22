0x16. C - Simple Shell Project
Group Members:  Mohamed Elkharashy and Foday Malike Kabah

0x16. C-Simple Shell Project
🐚 This project is a C-based implementation of a simple shell, developed by Foday Malike Kabah and Mohammed Elkharashy. The shell provides a command-line interface where users can execute various commands and interact with the underlying operating system.

Features
🚀 Command Execution: The shell allows users to execute commands just like a traditional command-line interface. It supports both built-in commands and external commands.

⚙️ Built-in Commands: The shell supports a set of built-in commands such as cd (change directory), help (display information about built-in commands), and exit (terminate the shell).

↔️ Input/Output Redirection: Users can redirect input and output streams of commands. It supports input redirection using < and output redirection using >.

🔁 Piping: The shell supports command piping, allowing users to connect multiple commands together by sending the output of one command as the input of another.

⏯️ Background Processes: Users can execute commands in the background by appending & at the end of the command. The shell continues to accept new commands while the background process runs.

Usage
Clone the repository:

shell
Copy code
git clone https://github.com/MohamedElkh/simple_shell.git
Change to the project directory:

shell
Copy code
cd {repository}
Compile the source code:

shell
Copy code
gcc -o shell shell.c
Run the shell:

shell
Copy code
./shell
Start entering commands and explore the features of the shell! ✨

Examples
Execute an external command:

shell
Copy code
> ls -l
Change directory:

shell
Copy code
> cd /path/to/directory
Redirect input/output:

shell
Copy code
> cat < input.txt > output.txt
Pipe commands:

shell
Copy code
> ls -l | grep ".txt"
Run a command in the background:

shell
Copy code
> sleep 10 &
Contributions
We welcome contributions to enhance the functionality and usability of the C-Simple Shell Project. If you find any issues or have suggestions for improvements, please feel free to open an issue or submit a pull request on the GitHub repository. 🙌

Authors
Foday Malike Kabah
Mohammed Elkharashy
License
This project is licensed under the MIT License. Feel free to use, modify, and distribute the code as per the terms of the license. 📝
