INSTALL_PREFIX?=../install
BUILD_DIR?=../build

all:
	cd $(BUILD_DIR) && \
	cmake -DCMAKE_INSTALL_PREFIX=$(INSTALL_PREFIX) ../fringe-tree && \
	make -k

test:
	cd $(BUILD_DIR) && \
	make test

install:
	cd $(BUILD_DIR) && \
	make install

clean:
	cd $(BUILD_DIR) && \
	make clean
