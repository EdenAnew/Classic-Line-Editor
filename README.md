# Classic-Line-Editor
A line-based text editor for the command line, made in C++

<b>Using the Program:</b>

Assuming the program has been installed and added to your path, there are two ways to initialize the program:
```
ClassicLineEditor.exe output.txt
```
Adding in only an argument for the file name, a new folder will automatically be created within the branch that the executable was called from to hold output.txt.
```
ClassicLineEditor.exe output.txt C:\SomeFolder\TextHolder
```
Adding in both an argument for the file name and the path, the output.txt file will be placed within the given path upon quitting the program.

Usage of the program will then continue until the user inputs 'quit' or 'close' (which also will save any changes made to the file). The full command list can be seen below:

<img width="445" height="465" alt="LineEditorHelpMenu" src="https://github.com/user-attachments/assets/1e3a7994-420c-4150-96be-fb72a87aee03"/>

<b>Installation (Windows):</b>

1. Run Command Prompt as Administrator
2. Clone the github repo using the URL given from the green "Code" button at the top of the repo within your desired directory:
```
git clone URL
```
3. Upon navigating to the created directory, make a build folder and navigate into it.
4. Set up your generator with the command:
```
cmake .. -G "Visual Studio 18 2026"
```
Note that the generator is different from user to user. See the CMake docs for the list of all available generators.

5. Run the following command:
```
cmake --build . --config Release
```
6. Run the following Command:
```
cmake --install .
```
7. From here, the terminal should print the location of the "install" folder, follow this path and find the folder containing the ClassicLineBuilder.exe. Copy this path.
8. Navigate to the "Edit system environment variables" program
9. Advanced > Environment Variables > Under 'System Variables', click 'Path' > Edit > New > Paste the copied file path into the new textbox and hit "OK"

Now, you should be able to run this program from the command line, on any user from any directory, by first denoting a command with "ClassicLineEditor.exe".
