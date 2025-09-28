#include <iostream>

using namespace std;

int main()
{
    char resultado[5];
    string teste = "teste";
    string chave = "admin";
    char temp;

    int contadorChave = 0, contadorTeste = 0, tamTeste = teste.length();
    int quadradoViginere[26][26];
    int i, y;

    // nem eu sei que maracutaia eu fiz aqui que deu certo a implementacao do quadrado de viginere, tava usando 3 variaveis
    // fiquei pensando nisso e fazia sentido, agora nem eu sei como q cheguei nessa bomba

    for(i=0;i<26;i++){
        for(y=0;y<26;y++){
            if (y+i > 25){
                quadradoViginere[i][y] = y-(26-i);
            }
            else{
                quadradoViginere[i][y] = y + i;
            }
        }
    }

    //TESTE PRA SABER SE A COLOCACO DOS VALORES ESTA CORRETA

    for(i=0;i<26;i++){
        for(y=0;y<26;y++){
            cout<<quadradoViginere[i][y]<<" ";
        }
        cout<<endl;
    }

    cout<<endl;
    cout<<endl;
    cout<<endl;

    do{
        y = (chave[contadorChave] - 97);
        i = (teste[contadorTeste] - 97);

        resultado[contadorTeste] = quadradoViginere[y][i] + 97;

        contadorChave++;
        contadorTeste++;

        if (contadorChave == 5){
            contadorChave = 0;
        }

    }while(contadorTeste<tamTeste);

    cout<<resultado<<endl;

    return 0;
}
