# Variáveis
NAME        :=   ircserv
HDR_DIR  	:=   ./header
SRC_DIR     :=   ./source
INCLD_DIR 	:=   $(shell find $(HDR_DIR) -type d)      # Encontra todos os diretórios em headers
SRC_FILES   :=   $(shell find $(SRC_DIR) -name '*.cpp')   # Encontra todos os arquivos .cpp em source e subpastas

all:
	@c++ -Wall -Wextra -Werror -std=c++98 $(SRC_FILES) $(addprefix -I, $(INCLD_DIR)) -o $(NAME)

clean:
	@echo "Nothing to be done."

fclean:
	@rm -f $(NAME)

re: fclean all
