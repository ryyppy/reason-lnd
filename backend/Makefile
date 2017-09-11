sources := \
	src/jbuild \
	$(wildcard src/*.ml)

executable := \
	_build/install/default/bin/server

build: $(executable)

clean:
	jbuilder clean

run: build
	$(executable)

install: build

$(executable): $(sources) src/jbuild
	jbuilder build @install

.PHONY: clean build run install
