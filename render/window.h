/* window.h
 * Representação da janela de visualização nas mais variadas
 * dimensões.
 *
 * Uma janela de visualização delimina o pedaço visível do mundo.
 * Estes objetos são entidades que possuem suas dimensões 
 *
 * As coordenadas de window são uma versão normalizada das coordenadas
 * de mundo, visando facilitar projeção e clipping. São obtidas a partir
 * das coordenadas de mundo através de transformações lineares.
 *
 * Para windows bidimensionais, as coordenadas de window satisfazem:
 *  - O centro da window é a origem;
 *  - O view-up vector (VUP) é o vetor (0, 1), o vetor unitário que
 *  aponta para cima;
 *  - O "plano" de projeção é o quadrado [-1, 1] x [-1, 1].
 * 
 * Para windows tridimensionais, as coordenadas de window satisfazem:
 *  - O centro de projeção (COP) está sempre na origem;
 *  - O view-up vector (VUP) é o vetor (0, 1, 0), o vetor unitário que
 *  aponta "para cima" (na direção do eixo y);
 *  - O view plane normal (VPN) é o vetor (0, 0, 1), o vetor unitário
 *  que aponta "para frente" (na direção do eixo z);
 *  - O "plano" de projeção é o quadrado [-1, 1] x [-1, 1] x {1}; isto
 *  é, o quadrado [-1, 1] x [-1, 1] "deslocado" uma unidade à frente.
 *
 * O quadrado de projeção é o objeto contra o qual os vetores devem
 * ser projetados; no caso da window bidimensional, não há necessidade
 * de projeção. Os pontos projetados nestes quadrados são mapeados
 * diretamente para coordenadas de window projetadas simplesmente ignorando
 * as dimensões extras; o que ficar fora do quadrado [-1, 1] x [-1, 1] não
 * é exibido na tela.
 *
 * Todas as instanciações da window possuem os métodos
 *  Math::Point<N> map( Math::Point<N> ) const;
 *  double area() const;
 * O primeiro método toma como parâmetro um ponto em coordenadas do
 * mundo e retornam este ponto, agora em coordenadas de window.
 * O segundo devolve a área do retângulo de projeção.
 */
#ifndef WINDOW_H
#define WINDOW_H

template< int N >
class Window;

#include "window2d.h"
#include "window3d.h"

#endif // WINDOW_H
