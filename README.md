# CMU-17648
Repository for coding standard configuration and documentation for CMU 17648 Sensor Based Systems.

Revision 0

### LLVM Configuration ###
This config is currently the default config dump from clang.

> clang-format -style=llvm -dump-config > llvm-style.config

### LLVM and Clang Documentation ###
Format options for clang:
https://clang.llvm.org/docs/ClangFormatStyleOptions.html

LLVM Coding standard:
https://llvm.org/docs/CodingStandards.html
This page has good explanations for the rules and variations of them.  Unfortunately there isn't a concrete mapping between the written descriptions of the rules and the corresponding configuration items (see llvm-style.config).  No actual checking for topic matches was done simply because there has been no customization of the configuration for this course.  When that process begins, mapping would begin if there were none.

GNU Coding Standards:
https://www.gnu.org/prep/standards/standards.html
