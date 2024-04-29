A intelitrader foi contratada para traduzir uma mensagem capturada na rede de um navio e ela está criptografada. Não sabemos que tipo de criptografia eles usaram, a única coisa que sabemos até agora, é que, a cada 8 bits, os dois últimos estão invertidos e a cada 4 bits, os 4 bits foram trocados com os próximos 4.

Mensagem criptografada:
10010110 11110111 01010110 00000001 00010111 00100110 01010111 00000001 00010111 01110110 01010111 00110110 11110111 11010111 01010111 00000011

Instruções:
De preferência, coloque o código em um arquivo único, para que seja possível executar online e coloque o link do site que executa. Ex: playcode.io/javascript
Existe mais de uma maneira de resolver este problema, mas aqui está alguns conceitos que podem te ajudar:
Tabela ASCII
Operadores lógicos
Números binários e hexadecimais
Você saberá se conseguiu descriptografar a mensagem se ela for legível e em inglês. Pois, qualquer bit errado, você terá uma mensagem cheia de símbolos.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// Função para inverter os dois últimos bits a cada 8 bits
char* inverter(char* mensagemCriptografada)
{
    int i;
    int tamanho = strlen(mensagemCriptografada);
    int acumulador = 0;
    for(i=0;i<tamanho;i++)
    {
        if(i == 7 && i>0)
        {
                // Colher o último bit e o penúltimo bit e trocar
                char ultimoBit = mensagemCriptografada[i];
                char penultimoBit = mensagemCriptografada[i-1];
                mensagemCriptografada[i-1] = ultimoBit;
                mensagemCriptografada[i] = penultimoBit;
                acumulador = i+9;
        }else if(i == acumulador && i != 0)
        {
                // Colher o último bit e o penúltimo bit e trocar
                acumulador = i+9;
                char ultimoBit = mensagemCriptografada[i];
                char penultimoBit = mensagemCriptografada[i-1];
                mensagemCriptografada[i-1] = ultimoBit;
                mensagemCriptografada[i] = penultimoBit;
        }
    }

    
    return mensagemCriptografada;
}

// Função para trocar os 4 bits com os próximos 4 a cada 4 bits
char* positionInverter(char* mensagemCriptografada)
{
    int tamanho = strlen(mensagemCriptografada);
    int count = 0;
    for (int i = 0; i < tamanho; i++)
    {
        if (mensagemCriptografada[i] != ' ')
        {
            count++;
            if (count % 8 == 0) // Verifica se chegou ao final de um grupo de 8 bits
            {
                // Reorganiza os bits dentro de cada grupo de 8 bits
                char caractere = 0;
                for (int j = 0; j < 8; j++)
                {
                    char bit = mensagemCriptografada[i - 7 + j];
                    caractere |= (bit - '0') << (7 - j);
                }

                caractere = ((caractere & 0xF0) >> 4) | ((caractere & 0x0F) << 4);

                for (int j = 0; j < 8; j++)
                {
                    mensagemCriptografada[i - 7 + j] = ((caractere >> (7 - j)) & 1) ? '1' : '0';
                }
            }
        }
    }
    return mensagemCriptografada;
}

// Função para converter a mensagem criptografada em ASCII
char* toASCII(char* mensagemCriptografada)
{
    int tamanho = strlen(mensagemCriptografada);
    char* ascii = malloc(tamanho / 8 + 1); // Tamanho da mensagem em ASCII
    int count = 0;
    char caractere = 0;

    for (int i = 0; i < tamanho; i++)
    {
        if (mensagemCriptografada[i] != ' ')
        {
            // Constrói o caractere de 8 bits
            caractere |= (mensagemCriptografada[i] - '0') << (7 - (i % 8));

            if ((i + 1) % 8 == 0) // Verifica se completou um caractere de 8 bits
            {
                ascii[count++] = caractere; // Armazena o caractere ASCII
                caractere = 0; // Reinicia o caractere
            }
        }
    }

    ascii[count] = '\0'; // Adiciona o caractere nulo ao final da string
    return ascii;
}

int main()
{
    char mensagemCriptografada[] = "10010110 11110111 01010110 00000001 00010111 00100110 01010111 00000001 00010111 01110110 01010111 00110110 11110111 11010111 01010111 00000011";
    
    printf("Número normal: %s\n", mensagemCriptografada);
    
    char* numeroInvertido = inverter(mensagemCriptografada);
    printf("Novo número binário 2 invertidos: %s\n", numeroInvertido);

    char* numeroFinal = positionInverter(numeroInvertido);
    printf("Número 4 trocados: %s\n", numeroFinal);

    char* ascii = toASCII(numeroFinal);
    printf("Mensagem em ASCII: %s\n", ascii);

    free(ascii); // Liberar memória alocada

    return 0;
}
