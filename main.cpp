#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main()
{
    string resultado;
    string texto;
    string chave;
    string caminhoArquivo;
    string linha;

    ifstream arquivo;
    ofstream arquivoSaida("saida.txt");

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

                tamTexto = texto.length();

                // EXISTE PARA QUE O TAMANHO DO RESULTADO SEJA O MESMO QUE O DO TEXTO
                resultado = texto;


                do{

                    y = (chave[contadorChave] - 97);
                    i = (texto[contadorTexto] - 97);

                    if (texto[contadorTexto] == 32){
                        resultado[contadorTexto] = 32;
                    }
                    else{
                        resultado[contadorTexto] = quadradoViginere[y][i] + 97;
                        contadorChave++;
                    }

                    contadorTexto++;

                    if (contadorChave == chave.length()){
                        contadorChave = 0;
                    }

                }while(contadorTexto<tamTexto);

                cout<<"\no resultado final foi: "<<resultado<<"\n"<<endl;
                contadorTexto = 0;
                contadorChave = 0;
                break;

            }

            case(2):{

                cout<<"digite a chave que vai ser utilizada: "<<endl;
                getline(cin, chave);

                cout<<"digite o caminho completo do arquivo: "<<endl;
                getline(cin, caminhoArquivo);

                //--------------------------------------------------------------------
                //ARQUIVO DE ENTRADA
                arquivo.open(caminhoArquivo);

                if (!arquivo.is_open()){
                    cout<<"ERRO AO ABRIR O ARQUIVO"<<endl;
                    break;
                }
                else{
                    cout<<"ARQUIVO ENTRADA ABERTO COM SUCESSO"<<endl;
                }

                //ENTRADA DE SAIDA

                if (!arquivoSaida.is_open()){
                    cout<<"ERRO AO CRIAR O ARQUIVO DE SAIDA"<<endl;
                    break;
                }
                else{
                    cout<<"ARQUIVO SAIDA ABERTO COM SUCESSO"<<endl;
                }

                //--------------------------------------------------------------------

                while(getline(arquivo, linha)){

                    // vai trabalhar linha a linha, ou seja, vai imprimir na tela o resultado criptografado a cada linha

                    texto = linha;
                    tamTexto = texto.length();

                    // EXISTE PARA QUE O TAMANHO DO RESULTADO SEJA O MESMO QUE O DO TEXTO
                    resultado = texto;

                    do{

                        y = (chave[contadorChave] - 97);
                        i = (texto[contadorTexto] - 97);

                        if (texto[contadorTexto] == 32){
                            resultado[contadorTexto] = 32;
                        }
                        else{
                            resultado[contadorTexto] = quadradoViginere[y][i] + 97;
                            contadorChave++;
                        }

                        contadorTexto++;

                        if (contadorChave == chave.length()){
                            contadorChave = 0;
                        }

                }while(contadorTexto<tamTexto);
                    cout<<resultado<<endl;
                    arquivoSaida << resultado << endl;
                    contadorTexto = 0;
                    contadorChave = 0;
                }
                break;
            }

            default:{
                cout<<"opcao invalida"<<endl;
                break;
            }

        }
    }while(op!=3);

    arquivo.close();
    arquivoSaida.close();

    return 0;
}
