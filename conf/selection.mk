# ---------------------------------------------------------------------------- #
# Makefile template v 2.1										2026-01-08
# ---------------------------------------------------------------------------- #
#
#								BUILD SELECTION
#
# ---------------------------------------------------------------------------- #

# MODE affects flags + output directories; regular, sanitizer, valgrind
MODE	?= reg
# PART affects which sources are compiled; mandatory or bonus
PART	?= man

# Output layout to isolate objects and binaries per mode & part.
# NOTE: must be recursive (=), because MODE/PART are target-specific and change.
OBJ_DIR	= build/$(MODE)/$(PART)/
BIN_DIR	= bin/$(MODE)/$(PART)/
BIN		= $(BIN_DIR)$(PROG_NAME)

# Choose sources based on PART.
# NOTE: cannot use make directives (ifeq)
#		because they are set while reading not when builing
#		=> PART is target specific and can change
SRC	= $(if $(filter bon,$(PART)),$(SRC_BON),$(SRC_MAN))

OBJ	= $(addprefix $(OBJ_DIR),$(SRC:.c=.o))