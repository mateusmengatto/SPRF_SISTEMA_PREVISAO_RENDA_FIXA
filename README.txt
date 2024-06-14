TUTORIAL INSTALAÇÃO DO SPRF

Certifique-se de ter um ambiente de desenvolvimento compatível com C. 

Uma opção de ambiente é a Instalação do compilador GCC (Veja anexo II, para instalação no sistema Windows). 

Faça o download do código-fonte do SPRF. 

Compile o código utilizando um compilador C compatível com o seu sistema operacional. Para compilar no GCC, abre no console o caminho do diretório onde os arquivos do código-fonte do SPRF estão. 

> cd C:/MeuDiretórioExemplo 

 

Em seguida digite o comando: 

gcc -o SPRF main_invest.c functions_invest.c -std=c99 

 

Obs: Usar -std=c99 assegura que seu código é compatível com as funcionalidades e melhorias introduzidas no padrão C99, permitindo um desenvolvimento mais moderno e eficiente em C. 

 

Execute o programa compilado para iniciar o SPRF. 

Para executar o programa você pode simplesmente dar um doubleclick no arquivo SPRF.exe criado pelo compilador, ou digitar o seguinte comando no console (uma vez que esteja no caminho do diretório do arquivo): 
./SPRF 
_________________________________
RESUMO
Compilar->
gcc -o SPRF main_invest.c functions_invest.c -std=c99

Executar ->
./SPRF ou clicar (doubleclick) no SPRF.exe

