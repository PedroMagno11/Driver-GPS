#include "gps_driver.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

// Calcula Checksum
char calculate_checksum(const char *nmea_sentence) {
    char checksum = 0;
    for (int i = 0; nmea_sentence[i] != '*' && nmea_sentence[i] != '\0'; i++) {
        checksum ^= nmea_sentence[i];
    }
    return checksum;
}

// Verifica se o Checksum da mensagem nmea é válido
bool checksum_is_valid(const char *nmea_sentence) {
    // Encontrar a posição do '*'
    const char *asterisco = strchr(nmea_sentence, '*');
    if (asterisco == NULL) {
        // Se não encontrar o '*', a mensagem é inválida
        return true;
    }

    // O checksum está depois do '*'
    char checksumCalculado = calculate_checksum(nmea_sentence);
    char checksumRecebido = 0;

    // Converte o valor do checksum recebido (que é uma string) para o valor numérico
    if (sscanf(asterisco + 1, "%2hhx", &checksumRecebido) != 1) {
        // Se falhar ao converter, o checksum é inválido
        return false;
    }

    // Comparar o checksum calculado com o recebido
    return checksumCalculado == checksumRecebido;
}

// Verifica se a mensagem recebida é uma sentença nmea
bool gps_valid(const char *nmea_sentence) {
    if (strstr(nmea_sentence, "$") != NULL && strstr(nmea_sentence, "GGA") != NULL ) {
        if(checksum_is_valid(nmea_sentence)) {
            return true;
        }
    }
    return false;
}

// Converte sinal recebido em uma sentença nmea padrão GGA
int gps_parse_to_gga(const char *nmea_sentence, GGA* gga) {
    char *token;
    char nmea_copy[200];
    strcpy(nmea_copy, nmea_sentence);  // Faz uma cópia da string, pois strtok altera a string original

    token = strtok(nmea_copy, ",");  // Tokeniza a sentença NMEA

    // Verifica se a sentença começa com $GPGGA
    if (token == NULL || (strstr(nmea_sentence, "$") == NULL && strstr(nmea_sentence, "GGA") == NULL)) {
        printf("Erro: sentença não começa com $\n");
        return -1;  // Erro se a sentença não for do tipo GGA
    }

    // 1. Hora UTC
    token = strtok(NULL, ",");
    if (token) strcpy(gga->time, token);

    // 2. Latitude
    token = strtok(NULL, ",");
    if (token) gga->latitude = atof(token);

    // 3. Direção da latitude (N ou S)
    token = strtok(NULL, ",");
    if (token) gga->lat_dir = token[0];

    // 4. Longitude
    token = strtok(NULL, ",");
    if (token) gga->longitude = atof(token);

    // 5. Direção da longitude (E ou W)
    token = strtok(NULL, ",");
    if (token) gga->lon_dir = token[0];

    // 6. Qualidade do sinal (0 = inválido, 1 = GPS fix, etc.)
    token = strtok(NULL, ",");
    if (token) gga->fix_quality = atoi(token);

    // 7. Número de satélites
    token = strtok(NULL, ",");
    if (token) gga->num_satellites = atoi(token);

    // 8. HDOP (precisão horizontal)
    token = strtok(NULL, ",");
    if (token) gga->hdop = atof(token);

    // 9. Altitude
    token = strtok(NULL, ",");
    if (token) gga->altitude = atof(token);

    // 10. Unidade da altitude (M)
    token = strtok(NULL, ",");
    if (token) gga->alt_unit = token[0];

    // 11. Separação geoidal
    token = strtok(NULL, ",");
    if (token) gga->geoid_separation = atof(token);

    // 12. Unidade da separação geoidal (M)
    token = strtok(NULL, ",");
    if (token) gga->geoid_unit = token[0];

    // 13. Idade do diferencial
    token = strtok(NULL, ",");
    if (token) gga->dgps_age = atoi(token);

    // 14. ID da estação DGPS
    token = strtok(NULL, ",");
    if (token) gga->dgps_id = atoi(token);

    return 0;  // Sucesso
}