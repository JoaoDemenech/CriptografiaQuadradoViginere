#include <iostream>

using namespace std;

int main()
{
    string resultado;
    string texto;
    string chave;

    int contadorChave = 0, contadorTexto = 0, tamTexto;
    int quadradoViginere[26][26];
    int i, y, op;

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

    //ESPACAMENTO

    cout<<endl;
    cout<<endl;
    cout<<endl;

    // PARTE QUE RODA / INTERATIVA
    do{
        cout<<"----------------------------------------------------------------------------"<<endl;
        cout<<"1 - digitar a chave e a string para criptografar"<<endl;
        cout<<"2 - enviar o caminho de um arquivo txt e uma chave"<<endl;
        cout<<"3 - encerrar o programa"<<endl;
        cout<<"digite a opcao desejada: "<<endl;
        cin>>op;
        getchar();

        switch(op){
            case(3):{
                break;
            }

            case(1):{

                cout<<"digite a chave: "<<endl;
                getline(cin, chave);

                cout<<"digite o texto: "<<endl;
                getline(cin, texto);

                resultado = texto;
                tamTexto = texto.length();

                do{
                    y = (chave[contadorChave] - 97);
                    i = (texto[contadorTexto] - 97);

                    resultado[contadorTexto] = quadradoViginere[y][i] + 97;

                    contadorChave++;
                    contadorTexto++;

                    if (contadorChave == 5){
                        contadorChave = 0;
                    }

                }while(contadorTexto<tamTexto);

                cout<<"\no resultado final foi: "<<resultado<<"\n"<<endl;
                contadorTexto = 0;
                contadorChave = 0;
                break;

            }

            case(2):{

                break;
            }

            default:{
                cout<<"opcao invalida"<<endl;
                break;
            }

        }
    }while(op!=3);

    return 0;
}
