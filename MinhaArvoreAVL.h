#ifndef MINHA_ARVORE_AVL_HPP
#define MINHA_ARVORE_AVL_HPP

#include "MinhaArvoreDeBuscaBinaria.h"
//#include <algorithm>
/**
 * @brief Representa uma árvore AVL.
 *
 * @tparam T O tipo de dado guardado na árvore.
 */
template <typename T>
class MinhaArvoreAVL final : public MinhaArvoreDeBuscaBinaria<T>
{
protected:
    Nodo<T> *rotacao_direita(Nodo<T> *y)
    {
        Nodo<T> *x = y->filhoEsquerda;
        Nodo<T> *T2 = x->filhoDireita;

        x->filhoDireita = y;
        y->filhoEsquerda = T2;

        y->altura = std::max(y->filhoEsquerda ? y->filhoEsquerda->altura : 0, y->filhoDireita ? (y->filhoDireita->altura + 1) : 0);
        x->altura = std::max(x->filhoEsquerda ? x->filhoEsquerda->altura : 0, x->filhoDireita ? (x->filhoDireita->altura + 1) : 0);
        return x;
    }

    Nodo<T> *rotacao_esquerda(Nodo<T> *x)
    {
        Nodo<T> *y = x->filhoDireita;
        Nodo<T> *T2 = y->filhoEsquerda;

        y->filhoEsquerda = x;
        x->filhoDireita = T2;

        x->altura = std::max(x->filhoEsquerda ? x->filhoEsquerda->altura : 0, x->filhoDireita ? (x->filhoDireita->altura + 1) : 0);
        y->altura = std::max(y->filhoEsquerda ? y->filhoEsquerda->altura : 0, y->filhoDireita ? (y->filhoDireita->altura + 1) : 0);

        return y;
    }

    int fator_balanceamento(Nodo<T> *tmp)
    {
        if (tmp != nullptr)
        {
            int altura_esquerda = tmp->filhoEsquerda != nullptr ? tmp->filhoEsquerda->altura : -1;
            int altura_direita = tmp->filhoDireita != nullptr ? tmp->filhoDireita->altura : -1;
            return altura_esquerda - altura_direita;
        }
        return 0;
    }

    Nodo<T> *inserir_rec(T chave, Nodo<T> *tmp)
    {
        if (chave < tmp->chave)
        {
            if (tmp->filhoEsquerda != nullptr)
            {
                tmp->filhoEsquerda = inserir_rec(chave, tmp->filhoEsquerda);
            }
            else
            {
                tmp->filhoEsquerda = new Nodo<T>;
                tmp->filhoEsquerda->chave = chave;
            }
        }
        else
        {
            if (tmp->filhoDireita != nullptr)
            {
                tmp->filhoDireita = inserir_rec(chave, tmp->filhoDireita);
            }
            else
            {
                tmp->filhoDireita = new Nodo<T>;
                tmp->filhoDireita->chave = chave;
            }
        }

        // altura++;
        // tmp->altura = altura;
        tmp->altura = 1 + std::max(tmp->filhoEsquerda ? tmp->filhoEsquerda->altura : 0, tmp->filhoDireita ? tmp->filhoDireita->altura : 0);

        int balance = fator_balanceamento(tmp);

        if (balance > 1 && chave < tmp->filhoEsquerda->chave)
        {
            return rotacao_direita(tmp);
        }

        if (balance < -1 && chave > tmp->filhoDireita->chave)
        {
            return rotacao_esquerda(tmp);
        }

        if (balance > 1 && chave > tmp->filhoEsquerda->chave)
        {
            tmp->filhoEsquerda = rotacao_esquerda(tmp->filhoEsquerda);
            return rotacao_direita(tmp);
        }

        if (balance < -1 && chave < tmp->filhoDireita->chave)
        {
            tmp->filhoDireita = rotacao_direita(tmp->filhoDireita);
            return rotacao_esquerda(tmp);
        }
        return tmp;
    }

    Nodo<T> *remover_rec(T chave, Nodo<T> *root)
    {
        if (root != nullptr)
        {
            if (chave > root->chave)
            {
                root->filhoDireita = remover_rec(chave, root->filhoDireita);
                if (root->filhoDireita != nullptr)
                {
                    if (root->filhoDireita->altura == -1)
                    {
                        Nodo<T> *tmp = root->filhoDireita;
                        root->filhoDireita = nullptr;
                        delete tmp;
                    }
                }
                if (root->filhoEsquerda != nullptr)
                {
                    if (root->filhoEsquerda->altura == -1)
                    {
                        Nodo<T> *tmp = root->filhoEsquerda;
                        root->filhoEsquerda = nullptr;
                        delete tmp;
                    }
                }
            }
            else if (chave < root->chave)
            {
                root-> filhoEsquerda = remover_rec(chave, root->filhoEsquerda);
                if (root->filhoDireita != nullptr)
                {
                    if (root->filhoDireita->altura == -1)
                    {
                        Nodo<T> *tmp = root->filhoDireita;
                        root->filhoDireita = nullptr;
                        delete tmp;
                    }
                }
                if (root->filhoEsquerda != nullptr)
                {
                    if (root->filhoEsquerda->altura == -1)
                    {
                        Nodo<T> *tmp = root->filhoEsquerda;
                        root->filhoEsquerda = nullptr;
                        delete tmp;
                    }
                }
            }
            else
            {
                if (root->filhoDireita == nullptr && root->filhoEsquerda == nullptr)
                {
                    root->altura = -1;
                    return root;
                }
                else if (root->filhoDireita && root->filhoEsquerda)
                {
                    Nodo<T> *predecessor = MinhaArvoreDeBuscaBinaria<T>::get_max(root->filhoDireita);

                    root->chave = predecessor->chave;
                    remover_rec(predecessor->chave, root->filhoDireita);
                }
                else
                {
                    if (root->filhoDireita)
                    {
                        Nodo<T> *child = root->filhoDireita;
                        root->chave = child->chave;
                        root->filhoDireita = nullptr;
                        root->altura = 0;
                        delete child;
                    }
                    else
                    {
                        Nodo<T> *child = root->filhoEsquerda;
                        root->chave = child->chave;
                        root->filhoEsquerda = nullptr;
                        root->altura = 0;
                        delete child;
                    }
                }
            }

            root->altura = 1 + std::max(root->filhoEsquerda ? root->filhoEsquerda->altura : 0, root->filhoDireita ? root->filhoDireita->altura : 0);

            int balance = fator_balanceamento(root);

            if (balance > 1 && fator_balanceamento(root->filhoEsquerda) >= 0)
            {
                return rotacao_direita(root);
            }

            if (balance > 1 && fator_balanceamento(root->filhoEsquerda) < 0)
            {
                root->filhoEsquerda = rotacao_esquerda(root->filhoEsquerda);
                return rotacao_direita(root);
            }

            if (balance < -1 &&
                fator_balanceamento(root->filhoDireita) <= 0)
                return rotacao_esquerda(root);

            if (balance < -1 &&
                fator_balanceamento(root->filhoDireita) > 0)
            {
                root->filhoDireita = rotacao_direita(root->filhoDireita);
                return rotacao_esquerda(root);
            }

            return root;
        }
    }

public:
    void inserir(T chave)
    {
        if (this->_raiz != nullptr)
        {
            this->_raiz = inserir_rec(chave, this->_raiz);

            this->_raiz->altura = 1 + std::max(this->_raiz->filhoEsquerda ? this->_raiz->filhoEsquerda->altura : 0, this->_raiz->filhoDireita ? this->_raiz->filhoDireita->altura : 0);
        }
        else
        {
            this->_raiz = new Nodo<T>;
            this->_raiz->chave = chave;
        }
    }
    virtual void remover(T chave)
    {
        this->_raiz = remover_rec(chave, this->_raiz);
        if (this->_raiz)
        {
            if (this->_raiz->altura == -1)
            {
                delete this->_raiz;
                this->_raiz = nullptr;
            }
            else
            {
                this->_raiz->altura = 1 + std::max(this->_raiz->filhoEsquerda ? this->_raiz->filhoEsquerda->altura : 0, this->_raiz->filhoDireita ? this->_raiz->filhoDireita->altura : 0);
            }
        }
    }
};

#endif
