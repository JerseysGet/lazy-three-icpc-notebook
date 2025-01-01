import os, sys
import pathlib
dir_name = os.path.dirname(__file__)
content_directory = os.path.join(dir_name, "content")

section_list = os.listdir(content_directory)
section_path_list = [ os.path.join(content_directory, section) for section in section_list ]

TYPST_EXTENSION = ".typ"
TYPST_HEADER = "```cpp\n"
TYPST_TAILER = "\n```"
TYPST_HEADING_PREFIX = "== "

def write_to_typst(file, dir_path):
    source_file = os.path.join(dir_path, file)
    file_name = pathlib.Path(file).stem
    dest_file = os.path.join(dir_path, file_name + TYPST_EXTENSION)
    data = ""
    with open(source_file, "r") as _file:
        data = _file.read()
    data =  f"{TYPST_HEADING_PREFIX}{file}\n{TYPST_HEADER}{data}{TYPST_TAILER}"
    with open(dest_file, "w") as _file:
        _file.write(data)
    

for section_name, section_path in zip(section_list, section_path_list):
    for file in os.listdir(section_path):
        if pathlib.Path(file).suffix != ".h":
            continue
        write_to_typst(file, section_path)

    chapter_file_path = os.path.join(section_path, "chapter.typ")
    chapter_content = ""
    for file in os.listdir(section_path):
        if pathlib.Path(file).suffix != ".typ" or file == "chapter.typ":
            continue
        chapter_content += f"#include \"{file}\"\n"
    # with open(chapter_file_path, "w") as chapter_file:
    #     chapter_file.write(chapter_content)