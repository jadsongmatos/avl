#ifndef MINHA_ARVORE_AVL_HPP
#define MINHA_ARVORE_AVL_HPP

#include "MinhaArvoreDeBuscaBinaria.h"

/**
 * @brief Representa uma árvore AVL.
 *
 * @tparam T O tipo de dado guardado na árvore.
 */
template <typename T>
class MinhaArvoreAVL final : public MinhaArvoreDeBuscaBinaria<T>
{
public:
    void inserir(T chave)
    {
        inserir(value);
        Nodo<T> *pai = this->_raiz;
        Nodo<T> *filho = get_pai_rec(this->_raiz, chave,pai).value_or(nullptr);
    }
    void remover(T chave)
    {
        
    }
};

#endif