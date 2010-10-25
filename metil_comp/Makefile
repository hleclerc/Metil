SOURCES     = metil_comp.cpp System.cpp String.cpp File.cpp Stream.cpp CompilationEnvironment.cpp CompilationGraph.cpp CompilationCppParser.cpp Memory.cpp
OBJECTS     = metil_comp.o   System.o   String.o   File.o   Stream.o   CompilationEnvironment.o   CompilationGraph.o   CompilationCppParser.o   Memory.o
CXXFLAGS    = -I/usr/include/qt4 -g3 -O3
INSTALL_DIR = `pwd`/../src

all: metil_comp

tests:
	make -C tests

metil_comp: ${OBJECTS}
	${CXX} -L/usr/share/qt4/lib/ -lQtCore -o metil_comp ${OBJECTS}
	
clean:
	rm -f *.o metil_comp InstallDir.h
	
depend:
	makedepend -Y ${SOURCES}

InstallDir.h:
	echo \#define INSTALL_DIR \"${INSTALL_DIR}\" > InstallDir.h


# DO NOT DELETE

metil_comp.o: CompilationGraph.h CompilationEnvironment.h CompilationError.h
metil_comp.o: String.h CommonFunctions.h StdOp.h TypePromote.h TypeConfig.h
metil_comp.o: File.h StreamWithEndlBeforeDestroy.h Stream.h StringStream.h
metil_comp.o: System.h AutoPtr.h
System.o: System.h String.h CommonFunctions.h StdOp.h TypePromote.h
System.o: TypeConfig.h File.h StreamWithEndlBeforeDestroy.h Stream.h
System.o: StringStream.h
String.o: String.h CommonFunctions.h StdOp.h TypePromote.h TypeConfig.h
String.o: File.h StreamWithEndlBeforeDestroy.h Stream.h StringStream.h
File.o: File.h StreamWithEndlBeforeDestroy.h Stream.h TypeConfig.h String.h
File.o: CommonFunctions.h StdOp.h TypePromote.h StringStream.h
Stream.o: Stream.h TypeConfig.h String.h CommonFunctions.h StdOp.h
Stream.o: TypePromote.h File.h StreamWithEndlBeforeDestroy.h StringStream.h
Stream.o: Number.h
CompilationEnvironment.o: CompilationEnvironment.h CompilationError.h
CompilationEnvironment.o: String.h CommonFunctions.h StdOp.h TypePromote.h
CompilationEnvironment.o: TypeConfig.h File.h StreamWithEndlBeforeDestroy.h
CompilationEnvironment.o: Stream.h StringStream.h System.h InstallDir.h
CompilationGraph.o: CompilationGraph.h CompilationEnvironment.h
CompilationGraph.o: CompilationError.h String.h CommonFunctions.h StdOp.h
CompilationGraph.o: TypePromote.h TypeConfig.h File.h
CompilationGraph.o: StreamWithEndlBeforeDestroy.h Stream.h StringStream.h
CompilationGraph.o: CompilationCppParser.h System.h
CompilationCppParser.o: CompilationCppParser.h CompilationEnvironment.h
CompilationCppParser.o: CompilationError.h String.h CommonFunctions.h StdOp.h
CompilationCppParser.o: TypePromote.h TypeConfig.h File.h
CompilationCppParser.o: StreamWithEndlBeforeDestroy.h Stream.h StringStream.h
CompilationCppParser.o: CompilationGraph.h System.h
