/* variadic.h
 * Contém classes que auxiliam a criação de funções e métodos
 * baseados em templates variádicos.
 *
 * O uso comum de templates que retornam um valor é uma estrutura
 * que possui um membro estático nomeado value, que corresponde ao
 * valor que se deseja extrair do template. */
#ifndef VARIADIC_H
#define VARIADIC_H

namespace Variadic {

/* Estrutura que toma por parâmetro uma quantidade arbitrária
 * de booleanos e retorna a conjunção generalizada entre eles.
 *
 * Único membro: const static bool value - valor da conjunção generalizada.
 *
 * Por definição, a conjunção de uma quantidade nula de booleanos
 * é verdadeira. */
template< bool ... b >
struct logical_and;


/* Estrutura que toma por parâmetro uma quantidade arbitrária
 * de booleanos e retorna a disjunção generalizada entre eles.
 *
 * Único membro: const static bool value - valor da disjunção generalizada.
 *
 * Por definição, a disjunção de uma quantidade nula de booleanos
 * é falsa. */
template< bool ... b >
struct logical_or;

/* Estrutura de índices.
 * Não contém membros. */
template< int ... index >
struct Index {
};

// Classe auxiliar
template< int, int ... > struct MakeOrderedIndexHelper;

/* Retorna uma estrutura Index<0, 1, ..., N-1> */
template< int N >
auto makeOrderedIndex() -> typename MakeOrderedIndexHelper<N>::type;



// Implementações

// logical_and
template<>
struct logical_and<> {
    const static bool value = true;
};

template< bool b, bool ... bs >
struct logical_and< b, bs... > {
    const static bool value = b && logical_and< bs... >::value;
};

// logical_or
template<>
struct logical_or<> {
    const static bool value = false;
};

template< bool b, bool ... bs >
struct logical_or< b, bs... > {
    const static bool value = b || logical_or< bs... >::value;
};

/* MakeOrderedIndexHelper
 * Funcionamento: por exemplo, com N = 3.
 * MakeOrderedIndexHelper<3>::type é definido como
 * MakeOrderedIndexHelper<2, 2>::type, que é definido como
 * MakeOrderedIndexHelper<1, 1, 2>::type, que é definido como
 * MakeOrderedIndexHelper<0, 0, 1, 2>::type, que é definido como
 * Index<0, 1, 2>. */
template< int ... Indexes >
struct MakeOrderedIndexHelper<0, Indexes...> {
    typedef Index<  Indexes... > type;
};

template< int N, int ... Indexes >
struct MakeOrderedIndexHelper {
    typedef typename MakeOrderedIndexHelper<N-1, N-1, Indexes...>::type type;
};

// makeOrderedIndex
template< int N >
typename MakeOrderedIndexHelper<N>::type makeOrderedIndex() {
    return typename MakeOrderedIndexHelper<N>::type();
    // Com C++14, podemos usar std::integer_sequence para fazer isto por nós.
}

} // namespace Variadic
#endif // VARIADIC_H
