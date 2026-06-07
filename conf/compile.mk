# ---------------------------------------------------------------------------- #
# Makefile template v 2.1										2026-01-08
# ---------------------------------------------------------------------------- #
#
#							PROJECT COPMILE DATA
#
# ---------------------------------------------------------------------------- #

CWWW	?= -Wall -Werror -Wextra
CINCL	= $(addprefix -I,$(INC_PATHS))

# Mode-specific flags
C_FLAGS_reg		:=
C_FLAGS_asan	:= -g -fsanitize=address -fno-omit-frame-pointer -O0 -DDEBUG=1
C_FLAGS_val		:= -g -O0 -DDEBUG=1

# Final flags used for compilation/linking (recursive; MODE is target-specific)
CFLAGS	= $(CWWW) $(CFLAGS_OTHER) $(C_FLAGS_$(MODE))