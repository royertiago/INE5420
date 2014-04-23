#Configurações do compilador
COMPILER = g++
FLAGS = -std=c++0x -Wall -pedantic -Wextra
LIBS := $(shell sdl2-config --cflags) -I./
#Esta variável foi definida com := para que não seja uma variável recursiva.\
	Variáveis recursivas têm seu valor computado toda vez que a variável \
	é usada; esta aqui, não. \
	A chamada $(shell command) incorpora à variável flag o que o comando \
	imprime. Definir esta variável como não-recursiva evita a perda \
	de performance por chamar o shell repetidas vezes.

#Lista de object files e dependências

SOURCES = $(wildcard *.cpp */*.cpp */*/*.cpp)
#A função wildcard força a expansão dos * até dois níveis de subdiretório. \
	TODO: achar algum jeito de fazer isso sem usar esta gambiarra.

OBJ = $(SOURCES:.cpp=.o)
#Substitui .cpp para .o no fim das palavras

OBJDEPS = $(SOURCES:.cpp=.d)

#Agora, temos: \
	SOURCES contém a lista de todos os .cpp do diretório. \
	OBJ contém a mesma lista, mas com .o no final. \
	OBJDEPS contém a mesma lista, mas com .d no final. \
\
A ideia é usar os .d como alvos do g++ -MM, que dá a lista de \
dependências do .cpp em questão. Então incluímos todos os .d \
no final.

a.out: $(OBJ)
	$(COMPILER) $(FLAGS) $^ $(shell sdl2-config --static-libs)
# $^ retorna todas as dependências, sem repetição.

#"Metarregra": para cada palavra em OBJDEPS que case com %.o, defina \
	a regra %.d : %.cpp \
			g++ -MM -MF $@ $<

$(OBJDEPS): %.d : %.cpp
	g++ -std=c++0x -MM $< -MF $@ -MT "$*.o $*.d" $(LIBS)
#Explicação: \
$@ retorna o target \
$< retorna a primeira dependência \
$* retorna o que quer que tenha casado com o % \
Digamos que o arquivo alce.d esteja em OBJDEPS. alce.d casará com \
%.d, ficando % == alce. A regra criada é: \
	alce.d : alce.cpp \
Cado tenha ocorrido alguma modificação em alce.cpp, reconstruímos \
alce.d. A linha executada pega todas as dependências de alce.cpp \
(-MM $<) e salva-as no arquivo alce.d (-MF $@). Entretanto, usaremos \
um target diferente: queremos que o alvo seja "alce.d alce.cpp", \
para que, ao incluírmos alce.d, todas as dependências de alce.cpp \
também provoquem a recriação de alce.d. \
No final, as regras assumem esta forma: \
alce.d alce.cpp : dependencias

$(OBJ): %.o : %.cpp
	$(COMPILER) $(FLAGS) $(LIBS) -c $< -o $@

include $(OBJDEPS)

.PHONY: clean

clean:
	-rm $(OBJ) $(OBJDEPS)
