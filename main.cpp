#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>
#include <cstdlib>

namespace fs = std::filesystem;
using namespace std;

int textoDireto(int quadradoViginere[26][26]){

    string resultado;
    string texto;
    string chave;

    int contadorChave = 0, contadorTexto = 0, tamTexto;
    int i, y;

    system("cls");

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

int textoArquivo(int quadradoViginere[26][26]){

    string resultado;
    string texto;
    string chave;
    string caminhoArquivo;
    string linha;
    string nomeArquivoSaida;

    ifstream arquivo;


    int contadorChave = 0, contadorTexto = 0, tamTexto;
    int i, y;

    system("cls");

    cout<<"digite a chave que vai ser utilizada: "<<endl;
    getline(cin, chave);

    cout<<"digite o caminho completo do arquivo de entrada: "<<endl;
    getline(cin, caminhoArquivo);

    cout << "digite o nome do caminho de saida: " << endl;
    getline(cin, nomeArquivoSaida);

    ofstream arquivoSaida(nomeArquivoSaida);

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
        }
        return 1;

}

string escolherArquivo(){

    int contador = 1;
    int op;
    string nomeArquivo;

    system("cls");

    for (const auto& entrada : fs::directory_iterator("arquivosCriptografados")){
        cout << contador << "- " << entrada.path().filename() << endl;
        contador++;
    }

    cout << "digite o numero referente ao arquivo que voce quer descriptografar: " << endl;
    cin >> op;
    getchar();

    contador = 1;
    for (const auto& entrada : fs::directory_iterator("arquivosCriptografados")){
        if (contador == op){
            nomeArquivo = entrada.path().filename().string();
        }
        contador++;
    }
    return (nomeArquivo);
}

int descriptografarArquivo(int quadradoViginere[26][26]){

    string nomeArquivo = "arquivosCriptografados/"+escolherArquivo();
    string linha;
    string resultado;
    string texto;
    string chave;

    int tamTexto, contadorTexto = 0, contadorChave = 0;
    int x, y = 0, z;


    ifstream arquivoCriptografado;
    ofstream arquivoDescriptografado("Descriptografado.txt");

    arquivoCriptografado.open(nomeArquivo);

    //================================================================
    // ABRIR ARQUIVOS

    if (!arquivoCriptografado.is_open()){
        cout<<"ERRO AO ABRIR O ARQUIVO CRIPTOGRAFADO"<<endl;
        return 1;
    }
    else{
        cout<<"ARQUIVO CRIPTOGRAFADO ABERTO COM SUCESSO"<<endl;
    }


    if (!arquivoDescriptografado.is_open()){
        cout<<"ERRO AO CRIAR O ARQUIVO DESCRIPTOGRAFADO"<<endl;
        return 1;
    }
    else{
        cout<<"ARQUIVO DESCRIPTOGRAFADO ABERTO COM SUCESSO\n"<<endl;
    }
    // ====================================================================
    // PEGAR CHAVE

    system("cls");

    cout<<"digite a chave do arquivo: "<<endl;
    getline(cin, chave);

    while (getline(arquivoCriptografado, linha)){

        texto = linha;
        tamTexto = texto.length();
        resultado = texto;

        do{
            x = chave[contadorChave] - 97;
            z = quadradoViginere[y][x];

            if (texto[contadorTexto] == 32){
                resultado[contadorTexto] = 32;
            }
            else{
                while(z != texto[contadorTexto] - 97){
                    y++;
                    z = quadradoViginere[y][x];
                }

            resultado[contadorTexto] = y + 97;
            contadorChave++;
            }

            if (contadorChave == chave.length()){
                contadorChave = 0;
            }
            contadorTexto++;
            y = 0;

        }while(contadorTexto < tamTexto);

        arquivoDescriptografado << resultado << endl;
        contadorTexto = 0;
    }

    return 1;
}

int main()
{
    int quadradoViginere[26][26];
    int x, y, op;

    // X - CHAVE
    // Y - TEXTO

    // nem eu sei que maracutaia eu fiz aqui que deu certo a implementacao do quadrado de viginere, tava usando 3 variaveis
    // fiquei pensando nisso e fazia sentido, agora nem eu sei como q cheguei nessa bomba
    // INICIA OS VALORES DO QUADRADO DE VIGINERE

    for(y=0;y<26;y++){
        for(x=0;x<26;x++){
            if (x+y > 25){
                quadradoViginere[y][x] = x-(26-y);
            }
            else{
                quadradoViginere[y][x] = x + y;
            }
        }
    }

    //TESTE PRA SABER SE A COLOCACO DOS VALORES ESTA CORRETA

    /*
    for(y=0;y<26;y++){
        for(x=0;x<26;x++){
            cout<<quadradoViginere[y][x]<<" ";
        }
        cout<<endl;
    }
    */

    // iniciar a pasta de saidas caso nao exista

    if (!(fs::is_directory("arquivosCriptografados"))){
        fs::create_directory("arquivosCriptografados");
    }

    // PARTE QUE RODA / INTERATIVA
    do{
        system("cls");

        cout<<"----------------------------------------------------------------------------"<<endl;
        cout<<"1 - digitar a chave e a string para criptografar"<<endl;
        cout<<"2 - enviar o caminho de um arquivo txt e uma chave"<<endl;
        cout<<"3 - encerrar o programa"<<endl;
        cout<<"4 - descriptografar um arquivo"<<endl;
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
                textoArquivo(quadradoViginere);
                break;
            }
            case (4):{
                descriptografarArquivo(quadradoViginere);
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
