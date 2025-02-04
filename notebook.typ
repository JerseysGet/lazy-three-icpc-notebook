/* Set the font of regular text, code, math */
#set text(size: 12pt, font: "Times New Roman") // Font for text
#show raw: set text(font: "Times New Roman", size: 12pt) // Font for code
#show math.equation: set text(font: "Times New Roman", size: 12pt) // Font for math

#set page(
  paper:"a4",
  flipped: true,
  columns: 2,
  /* Margins */
  margin: (x: 1in, y: 1in),
  // numbering: "1",
  // header: left("hi"),
  // header: "IIIT Hyderabad Lazy Three",
  header: grid(
    columns: (1fr, 1fr),
    align(left, "IIIT Hyderabad - Lazy Three"),
    align(right, counter(page).display()),
  ),
)

/* Set heading properties*/
#set heading(numbering: "1.1.")
#show heading.where(level:1): set text(size: 14pt)
#show heading.where(level:2): set text(size: 13pt)
#set heading(outlined: false)

/* Page numbers of sections */
#outline()

#heading(outlined: true, level: 1)[Contest]
#include "content/contest/chapter.typ"

#heading(outlined: true, level: 1)[Data Structures]
#include "content/data-structures/chapter.typ"

#heading(outlined: true, level: 1)[Graph]
#include "content/graph/chapter.typ"


#heading(outlined: true, level: 1)[Number Theory]
#include "content/number-theory/chapter.typ"

#heading(outlined: true, level: 1)[Strings]
#include "content/string/chapter.typ"

// Add bitwise stuff here

#heading(outlined: true, level: 1)[Numerical]
#include "content/numerical/chapter.typ"

#heading(outlined: true, level: 1)[Geometry]
#include "content/geometry/chapter.typ"