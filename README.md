# lazy three's icpc team notebook compiled with typst

To compile the notebook, run
```
make notebook
```

To add sections, make a folder for that section in `content/` and add `.h` files, include the section in `notebook.typ`. 

To rearrange the contents of a section, first run `make notebook` so that the `chapter.typ` files are present in all the sections, then re-arrange the `#include ..`'s in the corresponding `chapter.typ` file and run `make renotebook`.

The page layout, fonts, margins, number of columns etc. can be changed in `notebook.typ`

