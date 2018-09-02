
MAKEFLAGS += --no-builtin-rules
MAKEFLAGS += --no-builtin-variables

CC = gcc
HAL := host

CFLAGS ?= -std=c99 -Wall -Werror
CFLAGS += -MMD -MT $@ -MF $@.d

DEBUG=1
ifneq ($(DEBUG),)
CFLAGS += -g
LDFLAGS += -g
endif

PCFLAGS = -ffreestanding --sysroot=./sysroot
UCFLAGS = $(PCFLAGS) -I=/include

HALDIR = ./$(HAL)hal

HCLFAGS = -iquote $(HALDIR)/include

BUILD = ./build
IMAGE = $(BUILD)/image

KER = $(BUILD)/kernel.o
LIBC = $(BUILD)/libc.a

KSRC = $(wildcard kernel/*.c)
KOBJ = $(KSRC:%.c=$(BUILD)/%.o)
$(KOBJ) : CFLAGS += $(PCFLAGS) $(HCLFAGS) -iquote =/include

HCSRC = $(wildcard $(HALDIR)/*.c)
HSSRC = $(wildcard $(HALDIR)/*.S)
HOBJ = $(HCSRC:%.c=$(BUILD)/%.o) $(HSSRC:%.S=$(BUILD)/%.o)
$(HOBJ) : CFLAGS += $(HCLFAGS) -iquote ./kernel

CSRC = $(wildcard libc/*.c)
COBJ = $(CSRC:%.c=$(BUILD)/%.o)
$(COBJ) : CFLAGS += $(UCFLAGS)

ASRC = $(wildcard apps/*.c)
AOBJ = $(ASRC:%.c=$(BUILD)/%.o)
$(AOBJ) : CFLAGS += $(UCFLAGS)

.PHONY : all clean force

all : $(IMAGE)

$(IMAGE) : $(AOBJ) $(KOBJ) $(HOBJ) $(LIBC)
	$(CC) $(LDFLAGS) -o $@ $^

$(BUILD)/%.o : %.c
	@mkdir -p $(@D)
	$(CC) -c $(CFLAGS) -o $@ $<

$(BUILD)/%.o : %.S
	@mkdir -p $(@D)
	$(CC) -c $(ASFLAGS) -o $@ $<

$(LIBC) : $(COBJ)
	ar rcs $@ $^

clean :
	rm -rf ./build


-include $(patsubst %,%.d,$(KOBJ) $(KOBJ) $(HOBJ) $(COBJ) $(AOBJ))
