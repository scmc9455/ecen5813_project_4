#**************************************************************************#
#@file - Makefile
#
#@breif - This is the Makefile that will compiler the project1 executable
#
#@author - Scott McElroy
#
#@data - April 3rd, 2018
#
#**************************************************************************#

include sources.mk

#***********Variables******
GENFLAGS:= -Wall -Werror -g -std=c99
LDFLAGS:= -Wl,-Map=main.map

ifeq ($(OPTI),LOW-OP)
GENFLAGS += -O0
else ifeq ($(OPTI),HI-OP)
GENFLAGS += -O3
else
GENFLAGS += -O0
endif

#**************Switch statements for the platform determination**********
ifeq ($(PLATFORM),KL25Z)
CPU = cortex-m0plus
CC = arm-none-eabi-gcc
ARCH= armv6-m	
CFLAGS = $(GENFLAGS) -march=$(ARCH) -mcpu=$(CPU) -mthumb \
-mfloat-abi=soft -mfpu=fpv4-sp-d16 --specs=nosys.specs -DKL25Z
INCLUDES = -I./../include/common \
-I./../include/kl25z \
-I./../include/CMSIS \
-I./../platform
LDFLAGS += -T ./../platform/MKL25Z128xxx4_flash.ld

else ifeq ($(PLATFORM),KL25Z_PRO)
CPU = cortex-m0plus
CC = arm-none-eabi-gcc
ARCH= armv6-m	
CFLAGS = $(GENFLAGS) -march=$(ARCH) -mcpu=$(CPU) -mthumb \
-mfloat-abi=soft -mfpu=fpv4-sp-d16 --specs=nosys.specs -DKL25Z_PRO
INCLUDES = -I./../include/common \
-I./../include/kl25z \
-I./../include/CMSIS \
-I./../platform
LDFLAGS += -T ./../platform/MKL25Z128xxx4_flash.ld

else ifeq ($(PLATFORM),BBB)
CC = arm-linux-gnueabi-gcc
CFLAGS = $(GENFLAGS) -DVERBOSE -DBBB
INCLUDES = -I./../include/common \

else ifeq ($(PLATFORM),BBB_PRO)
CC = arm-linux-gnueabi-gcc
CFLAGS = $(GENFLAGS) -DVERBOSE -DBBB_PRO -D_POSIX_C_SOURCE=199309L
INCLUDES = -I./../include/common \

else ifeq ($(PLATFORM),HOST)
CC = gcc
CFLAGS = $(GENFLAGS) -DVERBOSE -DHOST -D_POSIX_C_SOURCE=199309L
INCLUDES:= -I./../include/common

#added a make line to do unit testing
else ifeq ($(PLATFORM),CMOCKA)
CC = gcc
CFLAGS = $(GENFLAGS) -DVERBOSE
INCLUDES:= -I./../include/common \
-I./../include/CMSIS \
-I./../include/kl25z

#this will default to the native compiler
else 
CC= gcc
CFLAG = $(GENFLAGS) -DVERBOSE
CPPFLAGS = #-DHOST
INCLUDES:= -I./../include/common

endif	

#variables that are needed for the build
ifeq ($(PROJECT),PROJECT1)
CFLAGS += -DPROJECT1
TARGET := project1.elf
else ifeq ($(PROJECT),PROJECT2)
TARGET := project2.elf
CFLAGS += -DPROJECT2
else ifeq ($(PROJECT),PROJECT3)
CFLAGS += -DPROJECT3
TARGET := project3.elf
else ifeq ($(PROJECT),CMOCKA)
TARGET :=  unit_tests.elf
else
TARGET:= default.elf
endif

#Logger function enabling
ifeq ($(LOG),ENABLE)
CFLAGS += -DLOG_ENABLE
SRCS += ./logger.c
else
CFLAGS += -DLOG_OFF
endif

OBJS:= $(SRCS:.c=.o)
PREPRO:= $(SRCS:.c=.i)
ASM:= $(SRCS:.c=.s)
#DEPFLAGS = #-MT -$@ -MMD -MP -MF $*.dep


#******************************************************************************
#**********Command "make build"*******************************************
.PHONY: build
build: clean $(TARGET)
$(TARGET):$(OBJS)
	$(CC) $(CFLAGS) $(INCLUDES) $(LDFLAGS) $(OBJS) -o $(TARGET)

#**********Command "make compile-all"*************************************
.PHONY: compile-all
compile-all: $(OBJS)

#**********Command "make clean"*******************************************
.PHONY: clean
clean: 
	rm -f *.o *.i *.s *.elf *.dep *.map

#**********Command "make size"*********************************************
.PHONY: size
size: 
	size $(OBJS) $(TARGET)

#**********Command "make upload_BBB"*********************************************
.PHONY: upload_BBB_project1
upload_BBB_project1: clean $(TARGET) LOAD

.PHONY: LOAD
LOAD: 
	sudo scp project1.elf root@192.168.7.2:/root/ecen5813_project_1

#***************************
.PHONY: upload_BBB_project3
upload_BBB_project3: clean $(TARGET) LOAD3

.PHONY: LOAD3
LOAD3:
	sudo scp project3.elf root@192.168.7.2:/root/ecen5813_project_3

#**********Command allows direct connect to BBB************************************
.PHONY: BBB_connect
BBB_connect: 
	ssh root@192.168.7.2

#******This section will generate the assembly files*********************
%.s:%.c
	$(CC) $(CFLAGS) $(INCLUDES) $@ -S -o $<

#******This section will generate the preprocessed files*****************
%.i:%.c
	$(CC) $(CFLAGS) $(INCLUDES)  $< -E -o $@

#*******Create only all object files*************************************
%.o:%.c
	$(CC) $(CFLAGS) $(INCLUDES) $< -c -o $@
#**************************End of File************************************
#************************************************************************

