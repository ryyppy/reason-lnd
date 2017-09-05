# Originally by mads-hartman (https://github.com/mads-hartmann/random/blob/master/gh/Makefile)

sources := \
	$(wildcard src/*.ml)

executable := \
	_build/install/default/bin/server

build: $(executable)

distclean clean:
	jbuilder clean

run: build
	$(executable)

install: build

$(executable): $(sources) src/jbuild
	jbuilder build @install
