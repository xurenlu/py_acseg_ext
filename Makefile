all:
	 python ./setup.py build
	cp build//lib.macosx-10.8-x86_64-2.7/acseg.so ./
	python ./test.py
