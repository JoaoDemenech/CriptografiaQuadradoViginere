#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>

namespace fs = std::filesystem;
using namespace std;

string nomeArquivoSaida(int contadorSaidas){
    string nomeArquivo = "arquivosSaida/saida.txt";

    if(fs::exists(nomeArquivo)){
        do{
            contadorSaidas++;
            nomeArquivo = "arquivosSaida/saida("+to_string(contadorSaidas)+").txt";
        }while(fs::exists(nomeArquivo));

        return (nomeArquivo);
    }
    else{
        nomeArquivo = "arquivosSaida/saida.txt";
        return (nomeArquivo);
    }
}

int textoDireto(int quadradoViginere[26][26]){

    string resultado;
    string texto;
    string chave;

    int contadorChave = 0, contadorTexto = 0, tamTexto;
    int i, y;

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
        return 1;
}

int textoArquivo(int quadradoViginere[26][26], int contadorSaidas){

    string resultado;
    string texto;
    string chave;
    string caminhoArquivo;
    string linha;

    ifstream arquivo;
    ofstream arquivoSaida(nomeArquivoSaida(contadorSaidas));

    int contadorChave = 0, contadorTexto = 0, tamTexto;
    int i, y;

    cout<<"digite a chave que vai ser utilizada: "<<endl;
    getline(cin, chave);

    cout<<"digite o caminho completo do arquivo de entrada: "<<endl;
    getline(cin, caminhoArquivo);

    //------------------------------------------------------------------
    //ARQUIVO DE ENTRADA
    arquivo.open(caminhoArquivo);

    if (!arquivo.is_open()){
        cout<<"ERRO AO ABRIR O ARQUIVO"<<endl;
        return 1;
    }
    else{
        cout<<"ARQUIVO ENTRADA ABERTO COM SUCESSO"<<endl;
    }

    //ARQUIVO DE SAIDA

    if (!arquivoSaida.is_open()){
        cout<<"ERRO AO CRIAR O ARQUIVO DE SAIDA"<<endl;
        return 1;
    }
    else{
        cout<<"ARQUIVO SAIDA ABERTO COM SUCESSO\n"<<endl;
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
        return 1;

}

int main()
{
    int quadradoViginere[26][26];
    int i, y, op, contadorSaidas = 0;

    // nem eu sei que maracutaia eu fiz aqui que deu certo a implementacao do quadrado de viginere, tava usando 3 variaveis
    // fiquei pensando nisso e fazia sentido, agora nem eu sei como q cheguei nessa bomba
    // INICIA OS VALORES DO QUADRADO DE VIGINERE

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
    /*
    for(i=0;i<26;i++){
        for(y=0;y<26;y++){
            cout<<quadradoViginere[i][y]<<" ";
        }
        cout<<endl;
    }
    */

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
                textoDireto(quadradoViginere);
                break;
            }

            case(2):{
                textoArquivo(quadradoViginere, contadorSaidas);
                contadorSaidas++;
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
