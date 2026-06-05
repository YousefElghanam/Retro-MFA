# ---------------------------------------------------------------------------- #
# Makefile template v 2.1										2026-01-08
# ---------------------------------------------------------------------------- #
#
#									LIBFT
#
# ---------------------------------------------------------------------------- #

# libft
LFT_DIR		= $(LFT_ROOT)lib/$(MODE)/
LFT_NAME	:= libft.a

# Construct or remove libft dependency references.
ifeq ($(USE_LIBFT),1)
	LFT_DEP		= $(LFT_DIR)$(LFT_NAME)
	CLIBS		= $(LFT_DEP) $(LIBS)
	INC_PATHS	+= $(LFT_ROOT)include/
	HEADER		+= $(LFT_ROOT)include/libft.h
	LFT_CLEAN	= @$(MAKE) -C $(LFT_ROOT) clean --no-print-directory
	LFT_FCLEAN	= @$(MAKE) -C $(LFT_ROOT) fclean --no-print-directory
	LFT_PRINT	= @$(MAKE) -C $(LFT_ROOT) print --no-print-directory
	LFT_NORM	= @$(MAKE) -C $(LFT_ROOT) norm --no-print-directory
else
	CLIBS	= $(LIBS)
endif
