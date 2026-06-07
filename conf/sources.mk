# ---------------------------------------------------------------------------- #
# Makefile template v 2.1										2026-01-08
# ---------------------------------------------------------------------------- #
#
#								PROJECT SOURCES
#
# ---------------------------------------------------------------------------- #

# Root directory that contains the source files.
SRC_ROOT		?= sources/
# Include directories (space-separated). Used to build CINCL flags.
INC_PATHS		?= include/

# ---------------------------------------------------------------------------- #
# List project headers with relative path to trigger rebuilds on header change.
# libft header is added automatically
HEADER		?= include/Retro_MFA.h
# ---------------------------------------------------------------------------- #

# Give File names relative to SRC_ROOT directory
SRC_MAN		?= main.c init.c cleanup.c read.c convert.c magic.c render.c color.c
#			   test_rawdata.c
#			   test_image.c 
SRC_BON		?= 

# Pattern for source files in subdirectories. WITH DIR SLASH
#   DIR_PARSER = parser/
#   SRC_PARSER = tokenize.c parse.c
#   SRC_MAN   += $(addprefix $(DIR_PARSER),$(SRC_PARSER))

  DIR_PARSER = mlxu/
  SRC_PARSER = ft_lstadd_back.c ft_lstdelone.c ft_lstnew.c mlxu_setup.c \
			   ft_lstclear.c ft_lstlast.c \
			   mlxu_buffer.c  mlxu_terminate.c
  SRC_MAN   += $(addprefix $(DIR_PARSER),$(SRC_PARSER))
