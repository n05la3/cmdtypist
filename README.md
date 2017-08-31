# CMDTYPIST -- _Command Line Typing Tutor_

#### By _Chiatiah Calson_

### About

_Cmdtypist_ is a programmer oriented typing tutor written in _C_, 
designed to work on the gnome-terminal, xterm and uxterm and other consoles.  It 
consists true programming lessons, so the user can type and learn at the same time.

![cmdtypist](https://raw.githubusercontent.com/Noslac/cmd_typist/master/cmtypist.gif)

### DOWNLOAD

You can get cmdtypist by cloning the repo from github
		
		git clone https://github.com/Noslac/cmd_typist

### INSTALLATION

Open a terminal and navigate to the directory containing cmdtypist and all 
it's files. Navigate to cmdtypist directory called installation and run

					./install.sh 

to install cmdtypist

### RUNNING


If _install.sh_ exited with a success message, then you have installed cmdtypist,
you can then run the command 

			cmdtypist arg1 arg2 arg3 ...

from any directory. _arg1, arg2,..._ are valid cmdtypist arguments, 
to know all valid arguments, run the cmdtypist help command or consult the help 
file which comes with the program. If you are a first time user, after installing cmdtypist, you must run the command **_cmdtypist mkuser "username"_** to create a user called username.

### CMDTYPIST ARGUMENTS

_cmdtypist_ commands are entered at the terminal with the exception of **_select "lesson-number"_** (_lesson-number is an int corresponding to a valid lesson number_) which is entered at the cmdtypist prompt prior to some other cmdtypist command entered at the terminal. 

CMDTYPIST Commands | Description
------------ | -------------
**cmtypist --help** | Displays help menu
**cmtypist**| Displays lessons and opens the cmdtypist prompt 
**cmdtypist mkuser "username"** | Creates a new user called username
**cmtypist ls** | Lists available lessons, use <select "lesson-number"> to select a lesson
**cmtypist man** | Displays cmdtypist readme file
**cmdtypist select** "lesson number" | Used to select a lesson directly from terminal 
**cmtypist atv**| Use this command if backspace is not working properly
**cmdtypist sound --on** | Activates error beep sound
**cmdtypist sound --off** | Deacativates beep sound
**cmdtypist /myown** | Changes the lessons to user's lesson copied into myown.txt
**cmtypist cchl** | Exits from user's lesson mode 
**cmdtypist mkstd** | Lessons appear as they are in lesson file 
**cmdtypist mkrand** | Lessons appear randomly
**cmdtypist chblock "lesson number"** | changes number of lines per sesson to an int 'lesson number'
**cmdtypist reset** | Does a soft reset 
**cmdtypist reset raw** | Does a hard reset, resetting to default 

Consult help file for more details of these commands


### UNINSTALL

If you are having problems with cmdtypist configurations, you can run the 
command
	
		cmdtypist reset raw

to reset settings to default. But if you want to permanently uninstall cmdtypist, 
proceed below.

To uninstall cmdtypist, open a terminal and cd into directory containing the 
unintall script by running

		cd $HOME/cmdtypist/uninstall/

finally, run

		./uninstall

to completely remove cmdtypist and associated files.


### License

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.

