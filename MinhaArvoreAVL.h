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
protected:
    int calcula_altura(Nodo<T> *tmp)
    {
        if (tmp == nullptr)
        {
            return 0;
        }
        int altura_esquerda = this->calcula_altura(tmp->filhoEsquerda);
        int altura_direita = this->calcula_altura(tmp->filhoDireita);
        return altura_esquerda > altura_direita ? altura_esquerda + 1 : altura_direita + 1;
    }

    void rotacao_direita(Nodo<T> *tmp)
    {
        Nodo<T> *tmp_esquerda = tmp->filhoEsquerda;
        Nodo<T> *tmp_esquerda_direita = tmp_esquerda->filhoDireita;

        tmp_esquerda->filhoDireita = tmp;
        tmp->filhoEsquerda = tmp_esquerda_direita;
    }

    void rotacao_esquerda(Nodo<T> *tmp)
    {
        Nodo<T> *tmp_dir = tmp->filhoDireita;
        tmp->filhoDireita = tmp_dir->filhoEsquerda;
        tmp_dir->filhoEsquerda = tmp;
        tmp->altura = this->calcula_altura(tmp);
        tmp_dir->altura = this->calcula_altura(tmp_dir);
        tmp = tmp_dir;
    }

    void rotacao_esquerda_direita(Nodo<T> *tmp)
    {
        this->rotacao_esquerda(tmp->filhoEsquerda);
        this->rotacao_direita(tmp);
    }

    void rotacao_direita_esquerda(Nodo<T> *tmp)
    {
        this->rotacao_direita(tmp->filhoDireita);
        this->rotacao_esquerda(tmp);
    }

    void balanceia_arvore(Nodo<T> *tmp)
    {
        if (tmp == nullptr)
        {
            return;
        }
        int fator = this->fator_balanceamento(tmp);
        if (fator > 1)
        {
            if (this->fator_balanceamento(tmp->filhoEsquerda) > 0)
            {
                this->rotacao_direita(tmp);
            }
            else
            {
                this->rotacao_esquerda_direita(tmp);
            }
        }
        else if (fator < -1)
        {
            if (this->fator_balanceamento(tmp->filhoDireita) < 0)
            {
                this->rotacao_esquerda(tmp);
            }
            else
            {
                this->rotacao_direita_esquerda(tmp);
            }
        }
        this->balanceia_arvore(tmp->filhoEsquerda);
        this->balanceia_arvore(tmp->filhoDireita);
    }

    int fator_balanceamento(Nodo<T> *tmp)
    {
        int altura_esquerda = tmp->filhoEsquerda != nullptr ? tmp->filhoEsquerda->altura : 0;
        int altura_direita = tmp->filhoDireita != nullptr ? tmp->filhoDireita->altura : 0;
        return altura_esquerda - altura_direita;
    }

    void inserir_rec(T chave, Nodo<T> *tmp)
    {
        int altura = 0;
        if (chave < tmp->chave)
        {
            if (tmp->filhoEsquerda != nullptr)
            {
                inserir_rec(chave, tmp->filhoEsquerda);
                altura = tmp->filhoEsquerda->altura;
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
                inserir_rec(chave, tmp->filhoDireita);
                altura = tmp->filhoDireita->altura > altura ? tmp->filhoDireita->altura : altura;
            }
            else
            {
                tmp->filhoDireita = new Nodo<T>;
                tmp->filhoDireita->chave = chave;
            }
        }
        
        altura++;
        tmp->altura = altura;

        int balance = fator_balanceamento(node);

        // If this node becomes unbalanced, then
        // there are 4 cases

        // Left Left Case
        if (balance > 1 && chave < tmp->filhoEsquerda->chave)
            return rightRotate(tmp);

        // Right Right Case
        if (balance < -1 && chave > tmp->filhoDireita->chave)
            return leftRotate(tmp);

        // Left Right Case
        if (balance > 1 && chave > tmp->filhoEsquerda->chave)
        {
            tmp->left = leftRotate(tmp->filhoEsquerda);
            return rightRotate(tmp);
        }

        // Right Left Case
        if (balance < -1 && key < tmp->filhoDireita->chave)
        {
            tmp->filhoDireita = rightRotate(tmp->filhoDireita);
            return leftRotate(tmp);
        }
    }

public:
    void inserir(T chave)
    {
        if (this->_raiz != nullptr)
        {
            inserir_rec(chave, this->_raiz);

            if (this->_raiz->filhoEsquerda != nullptr)
            {
                this->_raiz->altura = this->_raiz->filhoEsquerda->altura + 1;
            }
            if (this->_raiz->filhoDireita != nullptr)
            {
                this->_raiz->altura = this->_raiz->altura - 1 + this->_raiz->filhoDireita->altura;
            }
        }
        else
        {
            this->_raiz = new Nodo<T>;
            this->_raiz->chave = chave;
        }
    }
    virtual void remover(T chave)
    {
        Nodo<T> *pai = this->_raiz;
        Nodo<T> *filho = MinhaArvoreDeBuscaBinaria<T>::get_pai_rec(this->_raiz, pai, chave).value_or(nullptr);
        MinhaArvoreDeBuscaBinaria<T>::remover_rec(this->_raiz, chave);

        this->balanceia_arvore(pai);

        if (this->_raiz)
        {
            if (this->_raiz->altura == -1)
            {
                delete this->_raiz;
                this->_raiz = nullptr;
            }
            else
            {
                if (this->_raiz->filhoEsquerda != nullptr)
                {
                    this->_raiz->altura = this->_raiz->filhoEsquerda->altura + 1;
                }
                if (this->_raiz->filhoDireita != nullptr)
                {
                    this->_raiz->altura = this->_raiz->altura - 1 + this->_raiz->filhoDireita->altura;
                }
            }
        }
    }
};

#endif