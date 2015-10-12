# # Use 'make V=1' to see the full commands
#使用安静模式可以不看gcc,g++的参数
CC := gcc 
CXX := g++

INCLUDE := -I/usr/local/include  -I../message/include
LIBS := -L/usr/local/lib -L../message/lib -lpthread -lboost_system -lprotobuf -lmessage
CFLAGS := 
CPPFLAGS := -std=c++0x -O2 -g
LDFLAGS := 
CFILES := $(wildcard *.c)
CPPFILES := $(wildcard *.cc *.cpp)
OBJECTS := $(addsuffix .o, $(basename $(CFILES)) $(basename $(CPPFILES)))
TARGETS := $(basename $(OBJECTS))

ifeq ("$(origin V)", "command line")
   BUILD_VERBOSE = $(V)
endif
ifndef BUILD_VERBOSE
   BUILD_VERBOSE = 0
endif

ifeq ($(BUILD_VERBOSE),0)
	QUIET_CC        = @echo '   ' CC $@;
	QUIET_CXX       = @echo '   ' CXX $@;
	QUIET_LINK      = @echo '   ' LINK $@;
endif

all:$(TARGETS)
	@echo "--------------------------make successful-----------------------"

$(TARGETS):$(OBJECTS)
	$(QUIET_LINK)$(CXX) $(LDFLAGS) -o $@ $(addsuffix .o, $@) $(LIBS)

%.o:%.c
	$(QUIET_CC)$(CC) $(INCLUDE) $(CFLAGS) -c $<

%.o:%.cc
	$(QUIET_CXX)$(CXX) $(INCLUDE) $(CPPFLAGS) -c $<

%.o:%.cpp
	$(QUIET_CXX)$(CXX) $(INCLUDE) $(CPPFLAGS) -c $<

.PHONY:clean

clean:
	-rm -f $(TARGETS) $(OBJECTS)
	@echo "----------------------------make clean-----------------------"
