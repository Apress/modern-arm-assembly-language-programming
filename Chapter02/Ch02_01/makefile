# Target, include, and object directories 
TARGET = Ch02_01
INCDIR1 = .
INCDIR2 = ../../Include
OBJDIR = obj

# include files
CPPINCFILES1 = $(wildcard $(INCDIR1)/*.h)
CPPINCFILES2 = $(wildcard $(INCDIR2)/*.h)
ASMINCFILES1 = $(wildcard $(INCDIR1)/*.inc)
ASMINCFILES2 = $(wildcard $(INCDIR2)/*.inc)

# .cpp files in current directory   
CPPFILES = $(wildcard *.cpp)
CPPOBJFILES_ = $(CPPFILES:.cpp=.o)
CPPOBJFILES = $(patsubst %, $(OBJDIR)/%, $(CPPOBJFILES_))

# .s files in current directory   
ASMFILES = $(wildcard *.s)
ASMOBJFILES_ = $(ASMFILES:.s=.o)
ASMOBJFILES = $(patsubst %, $(OBJDIR)/%, $(ASMOBJFILES_))

# Target object files
OBJFILES = $(CPPOBJFILES) $(ASMOBJFILES)

# g++ and assembler options - required
GPPOPT = -march=armv8-a+simd -O3 -std=c++14 -Wall
ASMOPT = -march=armv8-a+simd

# g++ and assembler options - optional (uncomment to enable)
DEBUG = -g
LISTFILE_CPP = -Wa,-aghl=$(OBJDIR)/$(basename $<).lst -save-temps=$(OBJDIR)
LISTFILE_ASM = -aghlms=$(OBJDIR)/$(basename $<).lst

# Create directory for object and temp files
MKOBJDIR := $(shell mkdir -p $(OBJDIR))

# Build rules
$(TARGET): $(OBJFILES)
	g++ $(OBJFILES) -o $(TARGET)

# Note: full recompiles/assembles on any include file changes
$(OBJDIR)/%.o: %.cpp $(CPPINCFILES1) $(CPPINCFILES2)
	g++ $(DEBUG) $(LISTFILE_CPP) $(GPPOPT) -I$(INCDIR1) -I$(INCDIR2) -c $< -o $@

$(OBJDIR)/%.o: %.s $(ASMINCFILES1) $(ASMINCFILES2)
	as  $(DEBUG) $(LISTFILE_ASM) $(ASMOPT) -I$(INCDIR1) -I$(INCDIR2) $< -o $@

.PHONY:	clean

clean:
	rm -f $(TARGET)
	rm -rf $(OBJDIR)
