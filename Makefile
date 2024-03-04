re_notebook:
	typst compile notebook.typ

notebook:
	# make clean
	python3 notebook_gen.py
	typst compile notebook.typ

clean:
	rm -f content/*/*.typ