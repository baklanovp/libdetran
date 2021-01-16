# Run example


all:
	/usr/bin/swig -python example.i
	python setup.py build_ext --inplace

clean:
	rm -f example_wrap.c example.py _example.so example.pyc
	rm -f -R build/	