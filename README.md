wpsforlinux  --  Demo
===========

Introduction:
===========
The structure of the directory:
    wpsforlinux
        ----doc          : the different between std::list and QList
        ----link         : the reference links
        ----src          : the source code
        ----test         : store two input files and theirs' backup
            Make.Linux   : A Makefile written without qmake
            README.md(ReadMe.txt) : introduction
            wpsforlinux.pro	: project file for qt-creator
            usemake.sh   : clean the project and use Makefile only

Development Environment
===========
Enviroment variables:
	To bulid the source, your need to install QtSDK, and set the following variables:
		QTSDK_HOME, CPLUS_INCLUDE_PATH, LD_LIBRARY_PATH, PATH

	Download the latest QtSDK and Compile:
		Download: http://qt.nokia.com/downloads/linux-x11-cpp
		Compile and Configuration:http://qt-project.org/doc/qt-4.8/install-x11.html

	for example, just put the following six lines to ~/.bash_profile:
		----------------------------------------------------------
		QTSDK_HOME=/usr/local/QtSDK4.8.0
		CPLUS_INCLUDE_PATH=$QTSDK_HOME/include:$CPLUS_INCLUDE_PATH
		LD_LIBRARY_PATH=$QTSDK_HOME/lib:$LD_LIBRARY_PATH
		PATH=$QTSDK_HOME/bin:$PATH
		
		export QTSDK_HOME CPLUS_INCLUDE_PATH LD_LIBRARY_PATH PATH
		----------------------------------------------------------

Build
===========
There is several methods to build the source, choose the one you prefer:

	1):
	    qmake
	    make
	tips: make sure to execute: make distclean, if your want to build with other
	methods!

	2):
	build with qt-creator, just open wpsforlinux.pro

	3):
	    a):rename Make.Linux to Makefile(both wpsforlinux/Make.Linux and wpsforlinux/src/Make.Linux)
		b):type 'make' to build to source

		or just run usemake.sh
