# Universal makefile for single C++ program
#
# Use gcc flag -MMD (user) or -MD (user/system) to generate dependences among source files.
# Use make default rules for commonly used file-name suffixes and make variables names.
#
# % make [ a.out ]

########## Variables ##########

CXX = u++					# compiler
CXXFLAGS = -g -multi -Wall -Wno-unused-label -MMD			# compiler flags
MAKEFILE_NAME = ${firstword ${MAKEFILE_LIST}}	# makefile name

OBJECTS = Bank.o BottlingPlant.o Groupoff.o NameServer.o Parent.o Printer.o Student.o Truck.o VendingMachine.o WATCard.o WATCardOffice.o config.o main.o				# object files forming executable
DEPENDS = ${OBJECTS:.o=.d}			# substitute ".o" with ".d"
EXEC = soda					# executable name

########## Targets ##########

.PHONY : clean					# not file names

${EXEC} : ${OBJECTS}				# link step
	${CXX} ${CXXFLAGS} $^ -o $@		# additional object files before $^

${OBJECTS} : ${MAKEFILE_NAME}			# OPTIONAL : changes to this file => recompile

# make implicitly generates rules to compile C++ files that generate .o files

-include ${DEPENDS}				# include *.d files containing program dependences

clean :						# remove files that can be regenerated
	rm -f ${DEPENDS} ${OBJECTS} ${EXEC}
