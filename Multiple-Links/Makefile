
Q=@
CC = gcc
NM = nm
CSRC = main.c lib.c

CONFIG_MULTIPLE_LINK = y

CURRENT_DIR := $(shell pwd)
CFLAGS = -Wno-format -I$(CURRENT_DIR)/inc -no-pie
TARGET = app

CSRC += parse/parse.c

SRC = $(addprefix src/, $(CSRC))
OBJ = $(addprefix bin/, $(SRC:.c=.o))

# 运行指令

all: clean ld $(TARGET)
	$(Q) ./app

# 创建临时文件用于存放临时文件

bin:
	$(Q) mkdir $@
	$(Q) mkdir $@/src
	$(Q) mkdir $@/src/parse

# 自动生成链接脚本

ld: bin
	$(Q) $(CC) $(CFLAGS) -Wl,-verbose 2>&1 | \
	     sed -e '/====/,/====/!d;//d' \
	         -e '/__executable_start/s/$$/PROVIDE(_stext = .);/' \
	         -e 's/^\(\s\+\)\(\.init_array\)/\1\2 : { }\n\1.sinit/g' \
	         -e 's/^\(\s\+\)\(\.fini_array\)/\1\2 : { }\n\1.einit/g' \
	         -e 's/__init_array_start/_sinit/g' -e 's/__init_array_end/_einit/g' \
	         -e 's/__fini_array_start/_sfini/g' -e 's/__fini_array_end/_efini/g' >$</ld
	$(Q) echo "__init_array_start = .; __init_array_end = .; __fini_array_start = .; __fini_array_end = .;" >>$</ld

# 链接环节

$(TARGET): $(OBJ)
	$(Q) ./py/nmparse.py bin/nm.tmp > bin/nm.c
	$(Q) $(CC) -c bin/nm.c -o bin/nm.o $(CFLAGS)
	$(Q) $(CC) -o $@ $^ bin/nm.o -Tbin/ld $(LDFLAGS)

ifeq ($(CONFIG_MULTIPLE_LINK),y)
	$(Q) $(NM) -S $(TARGET) > bin/nm.tmp && ./py/nmparse.py bin/nm.tmp > bin/nm.c
	$(Q) $(CC) -c bin/nm.c -o bin/nm.o $(CFLAGS)
	$(Q) $(CC) -o $@ $^ bin/nm.o -Tbin/ld $(LDFLAGS)

	$(Q) $(NM) -S $(TARGET) > bin/nm.tmp && ./py/nmparse.py bin/nm.tmp > bin/nm.c
	$(Q) $(CC) -c bin/nm.c -o bin/nm.o $(CFLAGS)
	$(Q) $(CC) -o $@ $^ bin/nm.o -Tbin/ld $(LDFLAGS)
endif

# 编译环节

$(OBJ): bin/%.o: %.c
	$(Q) $(CC) -c $< -o $@ $(CFLAGS)

# 清理环境

clean:
	$(Q) rm -rf bin
	$(Q) rm -rf app
