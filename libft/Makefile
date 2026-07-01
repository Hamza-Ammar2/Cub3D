# Colours
RED     = \033[0;31m
GREEN   = \033[0;32m
YELLOW  = \033[0;33m
BLUE    = \033[0;34m
RESET   = \033[0m

# Library name
NAME     = libft.a

# Source files
PART_1   = ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c \
           ft_strlen.c ft_memset.c ft_bzero.c ft_memcpy.c ft_memmove.c \
           ft_strlcpy.c ft_strlcat.c ft_toupper.c ft_tolower.c ft_strchr.c \
           ft_strrchr.c ft_strncmp.c ft_memchr.c ft_memcmp.c ft_strnstr.c \
           ft_atoi.c ft_calloc.c ft_strdup.c ft_strcmp.c ft_isspace.c

PART_2   = ft_substr.c ft_strjoin.c ft_strtrim.c ft_split.c ft_itoa.c \
           ft_strmapi.c ft_striteri.c ft_putchar_fd.c ft_putstr_fd.c \
           ft_putendl_fd.c ft_putnbr_fd.c

BONUS    = ft_lstadd_back_bonus.c ft_lstadd_front_bonus.c ft_lstclear_bonus.c \
           ft_lstdelone_bonus.c ft_lstiter_bonus.c ft_lstlast_bonus.c \
           ft_lstmap_bonus.c ft_lstnew_bonus.c ft_lstsize_bonus.c

SRCS       = $(PART_1) $(PART_2)
OBJECTS    = $(SRCS:.c=.o)
OBJDIR     = obj
OBJFILES   = $(addprefix $(OBJDIR)/, $(OBJECTS))
BONUS_OBJS = $(BONUS:.c=.o)
BONUS_FILES= $(addprefix $(OBJDIR)/, $(BONUS_OBJS))

# Tools & flags
CC       = cc
CFLAGS   = -Wall -Wextra -Werror
AR       = ar rcs

.PHONY: all bonus clean fclean re

# Default build
all: $(NAME)

$(NAME): $(OBJFILES)
	@echo "$(YELLOW)Archiving $(BLUE)$@$(YELLOW)…$(RESET)"
	@$(AR) $@ $^
	@echo "$(GREEN)Built library: $(BLUE)$@$(RESET)"

# Compile each .c → obj/.o
$(OBJDIR)/%.o: %.c
	@mkdir -p $(OBJDIR)
	@echo "$(BLUE)Compiling:$(RESET) $<"
	@$(CC) $(CFLAGS) -c $< -o $@

# Bonus target
bonus: $(BONUS_FILES)
	@if [ -f .bonus_done ]; then \
    	echo "$(YELLOW)Bonus already added.$(RESET)"; \
	else \
    	echo "$(YELLOW)Adding bonus objects…$(RESET)"; \
    	$(AR) $(NAME) $(BONUS_FILES); \
    	touch .bonus_done; \
	fi
# Cleanup
clean:
	@echo "$(RED)Cleaning objects…$(RESET)"
	@rm -rf $(OBJDIR) .bonus_done

fclean: clean
	@echo "$(RED)Removing library…$(RESET)"
	@rm -f $(NAME)

re: fclean all
	@echo "$(YELLOW)Rebuilt everything!$(RESET)"



