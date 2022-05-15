TARGET = brainfrick

SRCDIR = src
INCDIR = inc
OBJDIR = obj
OUTDIR = out

SOURCES = ${wildcard ${SRCDIR}/**.cpp}
OBJECTS = ${patsubst ${SRCDIR}/%.cpp, ${OBJDIR}/%.o, ${SOURCES}}

CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -Wshadow -I${INCDIR} -lm -g -O0

LD = g++
LDFLAGS = -O0 -g

all: ${TARGET}
	mv ${TARGET} ${OUTDIR}/

${TARGET}: ${OBJECTS}
	${LD} ${LDFLAGS} ${OBJECTS} -o ${TARGET}

${OBJDIR}/%.o: ${SRCDIR}/%.cpp
	${CXX} ${CXXFLAGS} -c -o $@ $<

cleanall: clean execlean

clean:
	rm -rf ${OBJDIR}/*

execlean:
	rm -f ${OUTDIR}/${TARGET}

run: all
	./${OUTDIR}/${TARGET}
