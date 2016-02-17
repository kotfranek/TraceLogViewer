ifndef ESYS_HOME
    $(warning ESYS_HOME environment variable undefined, using default)
    ESYS_HOME=../ESys
endif

ifndef TRACELOG_HOME
    $(warning TRACELOG_HOME environment variable undefined, using default)
    TRACELOG_HOME=../TraceLog
endif


TARGET = tlview
OUTDIR = bin
LIBS = -lesys -ltracecommon
CC = g++
INCLUDES = include $(ESYS_HOME)/include $(TRACELOG_HOME)/include
LIBDIRS = lib/ $(ESYS_HOME)/lib $(TRACELOG_HOME)/lib

INCPARAMS=$(foreach d, $(INCLUDES),-I$d)
LIBDIRPARAMS=$(foreach d, $(LIBDIRS),-L$d)

#OPTFLAGS = -s -O3
CFLAGS = -g -Wall -std=c++11 $(INCPARAMS) $(OPTFLAGS)
LFLAGS = -Wall $(LIBDIRPARAMS)
RUNARGS = 

SRCS = src/main.cpp 
SRCS+= src/trace/client/UdpClientThread.cpp src/trace/client/FileReader.cpp
SRCS+= src/trace/client/LogOutput.cpp

OBJS = $(subst .cpp,.o,$(SRCS))

.PHONY: default all clean

default: all
all: $(TARGET)

.PRECIOUS: $(TARGET) $(OBJS)

DEPS := $(OBJS:.o=.d)

-include $(DEPS)

%.o: %.cpp
	@$(CC) $(CFLAGS) -MM -MT $@ -MF $(patsubst %.o,%.d,$@) $<
	$(CC) $(CFLAGS) -c $< -o $@


$(TARGET): $(OBJS)
	@mkdir -p $(OUTDIR)
	$(CC) $(OBJS) $(LFLAGS) $(LIBS) -o $(OUTDIR)/$@ -pthread $(OPTFLAGS)

clean:
	@rm -f $(OBJS)
	@rm -f $(DEPS)	
	@rm -f $(OUTDIR)/$(TARGET).a
