The three folders here are:
1. gui - has the scaffolding code to make a window'd application under Linux or Widows that uses tacent.
2. shellcmd - creates a command line utility that uses tacent
3. sharedlib - creates a library that uses tacent, and creates a command line utility that uses the library and tacent

To start a new project that uses tacent, it's very easy to use these as a starting point.  Copy the folder that makes the type of application you are interested in, and then rename the copied folder to the name you wnat to call your application.  For each type of application, there are some further renames that need to be done globally.  I'll explain these now.

USING gui
Let's assume you are interested in a window'd application.  Copy gui to a location where you want to create your app, and rename to the name you like.  Let's pretend that's myWindowApp.  

Visual Studio Code Users:  If you open the myWindowApp folder in VS Code and it prompts you for a kit, just press ESC.  That will prevent code from configuring the project.  However, if it has configured a build folder (noramlly that would be myWindowApp/build) then delete that build folder before you start the rename below.  

Serach in the myWindowApp folder, through all files, for gui (case sensitive) and replace that with myWindowApp.  Serach for GUI (again case sensitive) and replace with MYWINDOWAPP.  Rename the src/gui.cpp file to src/mywindowapp.cpp.

You can now reconfigure with CMake and build.  If you choose the build target install, you will get, right inside myWindowApp, a program called myWindowsApp (or myWindowApp.exe on Windows) that you can execute.  All it will do right now is open a windows and show a version string, but all of tacent is at your disposal, and all include paths, etc. are set up.

You can now fill out the application, starting with src/myWindowApp.cpp.


USING shellcmd
Let's assume you are interested in a command line (console) application.  Copy shellcmd to a location where you want to create your app, and rename to the name you like.  Let's pretend that's myCommandLineTool.  

Visual Studio Code Users:  If you open the myCommandLineTool folder in VS Code and it prompts you for a kit, just press ESC.  That will prevent code from configuring the project.  However, if it has configured a build folder (noramlly that would be myCommandLineTool/build) then delete that build folder before you start the rename below.  

Serach in the myCommandLineTool folder, through all files, for shellcmd (case sensitive) and replace that with myCommandLineTool.  Serach for SHELLCMD (again case sensitive) and replace with MYCOMMANDLINETOOL.  Rename the src/shellcmd.cpp file to src/myCommandLineTool.cpp.

You can now reconfigure with CMake and build.  If you choose the build target install, you will get, right inside myCommandLineTool, a program called myCommandLineTool (or myCommandLineTool.exe on Windows) that you can execute.  All it will do right now is print a version string, but all of tacent is at your disposal, and all include paths, etc. are set up.

You can now fill out the application, starting with src/myCommandLineTool.cpp.


USING sharedlib
Let's assume you are interested in a number of applications taht all share a common library.  They all, including the shared library, will use tacent.  Copy sharedlib to a location where you want to create your library and applications, and rename the new folder to the name you like.  Let's pretend that's tools.  Let's also pretend the shared library will be called myCommonLib and the first "tool" will be called myFirstTool.

Visual Studio Code Users:  If you open the tools folder in VS Code and it prompts you for a kit, just press ESC.  That will prevent code from configuring the project.  However, if it has configured a build folder (noramlly that would be tools/build) then delete that build folder before you start the rename below.  

Serach in the tools folder, through all files, for mylib (case sensitive) and replace that with myCommonLib.  Serach for MYLIB (again case sensitive) and replace with MYCOMMONLIB.  Rename useslib to myFirstTool and also rename the myCommonLib/src/mylib.cpp file to myCommonLib/src/myCommonLib.cpp.

Now serach in the tools folder, through all files, for useslib (case sensitive) and replace that with myFirstTool.  Serach for USESLIB (again case sensitive) and replace with MYFIRSTTOOL.  Rename useslib to myFirstTool and also rename the myFirstTool/src/useslib.cpp file to myCommonLib/src/myFirstTool.cpp.

Lastly, serach for SHAREDLIB in tools/CMakeLists.txt and replace that with TOOLS (this step is not important).

You can now reconfigure with CMake and build.  If you choose the build target install, you will get, right inside tools, a program called myFirstTool (or myFirstTool.exe on Windows) that you can execute.  All it will do right now is print a version string for itself and the shared library, but all of tacent is at your disposal, and all include paths, etc. are set up.

You can now fill out the application, starting with myFirstTool/src/myFirstTool.cpp for the tool itself, or myCommonLib/src/myCommonLib.cpp and myCommonLib/inc/myCommonLib.h for the library.

If you want to have a GUI application that uses the shared library, all you need to do is edit the useslib/CMakeLists.txt file - look for the line "Foundation Math System Image" (no quotes) and add the name of the shared library below that (example myCommonLib).  Also search for Windows GUI in that same CMakeLists.txt file and uncomment the lines where you fond it (the first is the line it is on, WIN32 and the second instance is the line right below where you will fine Windows GUI, starting with target_link_options).
