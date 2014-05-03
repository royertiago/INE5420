/* variadic.h
 * Contém classes que auxiliam a criação de funções e métodos
 * baseados em templates variádicos.
 *
 * O uso comum de templates que retornam um valor é uma estrutura
 * que possui um membro estático nomeado value, que corresponde ao
 * valor que se deseja extrair do template. */
#ifndef VARIADIC_H
#define VARIADIC_H

/* Estrutura que toma por parâmetro uma quantidade arbitrária
 * de booleanos e retorna a conjunção generalizada entre eles.
 *
 * Por definição, a conjunção de uma quantidade nula de booleanos
 * é verdadeira. */
template< bool ... b >
struct logical_and;


/* Estrutura que toma por parâmetro uma quantidade arbitrária
 * de booleanos e retorna a disjunção generalizada entre eles.
 *
 * Por definição, a disjunção de uma quantidade nula de booleanos
 * é falsa. */
template< bool ... b >
struct logical_or;



//Implementações

template<>
struct logical_and<> {
    const static bool value = true;
};

template< bool b, bool ... bs >
struct logical_and< b, bs... > {
    const static bool value = b && logical_and< bs... >::value;
};

template<>
struct logical_or<> {
    const static bool value = false;
};

template< bool b, bool ... bs >
struct logical_or< b, bs... > {
    const static bool value = b || logical_or< bs... >::value;
};
#endif // VARIADIC_H
