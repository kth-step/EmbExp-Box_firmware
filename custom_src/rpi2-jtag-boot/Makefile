#CROSS	= aarch64-linux-gnu-
ifndef CROSS
  ifdef HOLBA_GCC_ARM_CROSS
    CROSS = ${HOLBA_GCC_ARM_CROSS}
  endif
endif
ifndef CROSS
  $(error need variable CROSS to be defined as gcc path prefix)
endif


OUTDIR  = output
NAME	= ${OUTDIR}/program.elf
KERNEL	= ${OUTDIR}/kernel.img

rwildcard=$(foreach d,$(wildcard $1*),$(call rwildcard,$d/,$2) $(filter $(subst *,%,$2),$d))


SOURCES_C     = $(call rwildcard, src/, *.c)
SOURCES_S     = $(call rwildcard, src/, *.asm)
INCLUDE_FILES = $(call rwildcard, inc/, *.h)

OBJECTS       = $(SOURCES_C:.c=.o) $(SOURCES_S:.asm=.o)


CFLAGS	= -ggdb3 -std=gnu99 -Wall -Iinc -mcpu=cortex-a7 -mfloat-abi=soft -mfpu=neon-vfpv4 -mlittle-endian -ffreestanding -fno-builtin
LDFLAGS = -Bstatic --gc-sections -nostartfiles -nostdlib


all: $(KERNEL)

%.o: %.asm
	${CROSS}as -o $@ $<

%.o: %.c
	${CROSS}gcc ${CFLAGS} -c -o $@ $<

$(NAME): ${OBJECTS} ${SOURCES_C} ${SOURCES_S} ${INCLUDE_FILES}
	mkdir -p ${OUTDIR}
	${CROSS}ld $(LDFLAGS) -o $@ -T linkerscript.ld ${OBJECTS}
	${CROSS}objdump -t -h -D $@ > "$@_da"

$(KERNEL): $(NAME)
	mkdir -p ${OUTDIR}
	${CROSS}objcopy --gap-fill=0xff -j .text -j .rodata -j .data -O binary $< $@

clean:
	rm -rf ${OUTDIR}
	rm -f $(KERNEL) $(NAME) ${OBJECTS}


.PHONY: all clean

