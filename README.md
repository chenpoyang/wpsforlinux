wpsforlinux  --  just a demo...^^
===========

Enviroment variables:
	QTSDK_HOME           : your QtSDK HOME, eg: /usr/local/QtSDK4.8.0
	CPLUS_INCLUDE_PATH   : the cplusplus header path, eg: /usr/local/QtSDK4.8.0/include
	LD_LIBRARH_PATH      : the QtSDK Library, eg: /usr/local/QTSDK4.8.0/lib
	PATH                 : QtSDB's bin path, eg: /usr/local/QTSDK4.8.0/bin

	for example:
		QTSDK_HOME=/usr/local/QtSDK4.8.0
		CPLUS_INCLUDE_PATH=$QTSDK_HOME/include:$CPLUS_INCLUDE_PATH
		LD_LIBRARY_PATH=$QTSDK_HOME/lib:$LD_LIBRARY_PATH
		PATH=$QTSDK_HOME/bin:$PATH
		
		export QTSDK_HOME CPLUS_INCLUDE_PATH LD_LIBRARY_PATH PATH

Build:
	1):
	qmake -project
	qmake
	make

	2):
	build with qt-creator, just open wpsforlinux.pro
