sources := \
	src/jbuild \
	$(wildcard src/*.ml)

executable := \
	_build/install/default/bin/server

testexec := \
  _build/default/src/test.exe

build: $(executable)

clean:
	jbuilder clean

run: build
	$(executable)

install: build

test: build
	$(testexec)

$(executable): $(sources) src/jbuild
	jbuilder build @install

.PHONY: clean build run install
