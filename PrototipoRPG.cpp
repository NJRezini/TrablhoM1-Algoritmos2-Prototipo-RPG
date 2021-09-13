#include <iostream>
#include <stdlib.h>
#include <time.h>
//#include "header.h"
using namespace std;

enum Genero {
    F,
    M
};

struct Arma {
    string nome;
    int danoMinimo;
    int danoMaximo;
    Genero genero;
    int precisao;
};

struct Inimigo {
    string nome;
    int vida;
    Arma arma;
    int defesa = 10;
};

struct Fase {
    string nome;
    Inimigo inimigos[5];
};

struct Jogador {
    int nivel;
    int vida;
    string nome;
    Arma arma;
    int defesa = 10;
};

struct Acerto {
    bool sucesso;
    int resultado;
};

template<typename T>
bool morreu(T personagem) {
    if (personagem.vida <= 0) {
        return true;
    }
    else {
        return false;
    }
}


template<typename T, typename T2>
Acerto acerto(T atacante, T2 defensor) {
    Acerto acerto = { false };
    acerto.resultado = rand() % (20) + 1;
    cout << endl << atacante.nome << " jogou " << acerto.resultado + atacante.arma.precisao << " para acertar e ";
    if (acerto.resultado + atacante.arma.precisao >= defensor.defesa) {
        cout << "acertou";
        acerto.sucesso = true;
        if (acerto.resultado == 20) {
            cout << " um golpe CRÍTICO";
        }
        cout << "!";
    }
    else {
        cout << "errou... \n";
    }
    return acerto;
}

template<typename T>
int dano(T personagem) {
    int resultado = (rand() % ((personagem.arma.danoMaximo + 1) - personagem.arma.danoMinimo)) + personagem.arma.danoMinimo;
    return resultado;
}

template<typename T, typename T2>
T2 ataque(T atacante, T2 defensor) {
    Acerto acerto1 = acerto(atacante, defensor);
    int danoTotal;
    if (acerto1.sucesso) {
        danoTotal = dano(atacante);
        if (acerto1.resultado == 20) {
            danoTotal += dano(atacante);
        }
        defensor.vida -= danoTotal;
        cout << endl << atacante.nome << " deu " << danoTotal << " de dano com ";
        if (atacante.arma.genero == F) {
            cout << "sua ";
        }
        else {
            cout << "seu ";
        }
        cout << atacante.arma.nome << ". ";
        if (morreu(defensor)) {
            cout << "\nO " << defensor.nome << " ficou com " << defensor.vida << " pontos de vida e MORREU!\n";
        }
        else {
            cout << "\nO " << defensor.nome << " ficou com " << defensor.vida << " pontos de vida continua vivo.\n";
        }
    }
    return defensor;
}

template<typename T>
T escolherNome(T personagem) {
    cout << "Digite o nome do personagem: ";
    cin >> personagem.nome;
    return personagem;
}

void jogarFase(Jogador protagonista, Fase fase) {
    cout << "\nEntrando em " << fase.nome << " com " << protagonista.arma.nome << "...\n";
    int quantidadeInimigos = sizeof(fase.inimigos) / sizeof(fase.inimigos[0]), inimigosVivos = quantidadeInimigos;
    for (int i = 0; i < quantidadeInimigos; i++) {
        Inimigo inimigo = fase.inimigos[i];
        cout << "\nUm inimigo se aproxima, e seu nome é " << inimigo.nome << ".\n";
        while (inimigo.vida > 0) {
            inimigo = ataque<Jogador, Inimigo>(protagonista, inimigo);
            if (!morreu(inimigo)) {
                protagonista = ataque<Inimigo, Jogador>(inimigo, protagonista);
            }
            else {
                inimigosVivos--;
            }
            if (morreu(protagonista)) {
                cout << "\nVOCÊ PERDEU. FIM DE JOGO!";
                break;
            }
            if (inimigosVivos == 0) {
                cout << "\nPARABÉNS, VOCÊ ZEROU O JOGO!";
            }
        }
    }
    cout << "\nAperte ENTER para retornar ao menu.";
    getchar(); getchar();
}

template<typename T>
T selecionarArma(T entidade, Arma armasDisponiveis[]) {
    int selecionar;
    cout << "\nEscolha a sua arma: \n \t\t\tDano\t\tPrecisao \n[1] Machado\t\t12\t\t-2 \n[2] Adaga\t\t4\t\t+4 \n[3] Espada\t\t9\t\t+0 \n[4] Lança\t\t10\t\t-1 \n[5] Arco\t\t8\t\t+2\n";
    cin >> selecionar;
    selecionar--;
    if (selecionar >= 1 && selecionar <= 5) {
        entidade.arma = armasDisponiveis[selecionar];
        cout << entidade.arma.nome << endl;
    }
    else {
        cout << "Opção inválida, escolha uma das armas disponíveis.";
    }
    return entidade;
}


int main() {

    int menu;

    Arma machado = { "Machado", 1, 12, M, -2 },
        adaga = { "Adaga", 1, 4, F, 4 },
        espada = { "Espada", 1, 9, F, 0 },
        lanca = { "Lança", 1, 10, F, -1 },
        arco = { "Arco", 1, 8, M, 2 };

    Arma armasDisponiveis[] = { machado, adaga, espada, lanca, arco };

    Jogador protagonista = { 1, 50, "Jogador", machado };
    Inimigo inimigo1 = { "Texugo", 10, adaga, 7 },
        inimigo2 = { "Gosmanuel", 10, espada, 8 },
        inimigo3 = { "Gosmarcos", 10, arco, 9 },
        inimigo4 = { "Gosmarcelo", 10, lanca,10 },
        inimigo5 = { "Ente Ancião", 20, machado, 11 };

    Fase fase1 = { "Floresta do Desafio" };
    fase1.inimigos[0] = inimigo1;
    fase1.inimigos[1] = inimigo2;
    fase1.inimigos[2] = inimigo3;
    fase1.inimigos[3] = inimigo4;
    fase1.inimigos[4] = inimigo5;

    srand(time(NULL));

    do {
        system("CLS");
        cout << "Olá! Bem-vindo ao RPGenérico. Digite o número correspondente ao item do menu que você deseja acessar.\n\n[1] Jogar\n[2] Sobre o Jogo\n[3] Sair do Jogo\n";
        cin >> menu;
        system("CLS");
        switch (menu) {
        case 1:
            protagonista = escolherNome(protagonista);
            protagonista = selecionarArma(protagonista, armasDisponiveis);
            jogarFase(protagonista, fase1);
            break;
        case 2:
            cout << "Sobre o jogo.\n\nDesenvolvido por Nathan Rezini e Thomas Hammes.\nFeito em Setembro de 2021 como trabalho da disciplina de Algoritmos e Programação II do professor Rodrigo Lyra.\n\nAperte ENTER para retornar ao menu.";
            getchar(); getchar();
            break;
        }
    } while (menu != 3);

    return 0;
}
