#ifndef GPS_DRIVER_H
#define GPS_DRIVER_H

#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>


// Estrutura para mensagem GGA
typedef struct {
    char time[11];          // Hora UTC (hhmmss.sss)
    double latitude;        // Latitude em graus decimais
    char lat_dir;           // Direção da latitude ('N' ou 'S')
    double longitude;       // Longitude em graus decimais
    char lon_dir;           // Direção da longitude ('E' ou 'W')
    int fix_quality;        // Qualidade do fix (0 = inválido, 1 = GPS fix, etc.)
    int num_satellites;     // Número de satélites usados
    double hdop;            // Diluição da precisão horizontal
    double altitude;        // Altitude em metros
    char alt_unit;          // Unidade da altitude ('M')
    double geoid_separation;// Separação geoidal
    char geoid_unit;        // Unidade da separação ('M')
    int dgps_age;           // Idade do diferencial (em segundos)
    int dgps_id;            // ID da estação DGPS
} GGA;

// // Estrutura para mensagem RMC
// typedef struct {
//     char time[11];          // Hora UTC (hhmmss.sss)
//     char status;            // Status ('A' = ativo, 'V' = inválido)
//     double latitude;        // Latitude em graus decimais
//     char lat_dir;           // Direção da latitude ('N' ou 'S')
//     double longitude;       // Longitude em graus decimais
//     char lon_dir;           // Direção da longitude ('E' ou 'W')
//     double speed;           // Velocidade em nós
//     double track_angle;     // Rumo em graus verdadeiros
//     char date[7];           // Data (ddmmyy)
//     double magnetic_var;    // Variação magnética
//     char var_dir;           // Direção da variação ('E' ou 'W')
// } RMC;
//
// // Estrutura para mensagem GSA
// typedef struct {
//     char mode;              // Modo ('M' = manual, 'A' = automático)
//     int fix_type;           // Tipo de fixação (1 = nenhuma, 2 = 2D, 3 = 3D)
//     int satellites[12];     // IDs dos satélites usados no fix
//     double pdop;            // Diluição da precisão total
//     double hdop;            // Diluição da precisão horizontal
//     double vdop;            // Diluição da precisão vertical
// } GSA;
//
// // Estrutura para mensagem GSV
// typedef struct {
//     int num_messages;       // Número total de mensagens GSV
//     int message_number;     // Número desta mensagem
//     int satellites_in_view; // Número total de satélites em visão
//     struct {
//         int prn;            // Número do satélite PRN
//         int elevation;      // Elevação em graus
//         int azimuth;        // Azimute em graus
//         int snr;            // Relação sinal-ruído (dB)
//     } satellites[4];        // Dados de até 4 satélites por mensagem
// } GSV;
//
// // Estrutura para mensagem GLL
// typedef struct {
//     double latitude;        // Latitude em graus decimais
//     char lat_dir;           // Direção da latitude ('N' ou 'S')
//     double longitude;       // Longitude em graus decimais
//     char lon_dir;           // Direção da longitude ('E' ou 'W')
//     char time[11];          // Hora UTC (hhmmss.sss)
//     char status;            // Status ('A' = ativo, 'V' = inválido)
//     char mode;              // Modo (opcional: 'A', 'D', 'E', ou 'N')
// } GLL;
//
// // Estrutura para mensagem VTG
// typedef struct {
//     double track_true;      // Rumo verdadeiro (graus)
//     char true_indicator;    // Indicador de verdadeiro ('T')
//     double track_magnetic;  // Rumo magnético (graus)
//     char magnetic_indicator;// Indicador de magnético ('M')
//     double speed_knots;     // Velocidade em nós
//     char knots_indicator;   // Indicador de nós ('N')
//     double speed_kmh;       // Velocidade em km/h
//     char kmh_indicator;     // Indicador de km/h ('K')
//     char mode;              // Modo ('A', 'D', 'E', ou 'N')
// } VTG;

// // Estrutura para mensagem TXT
// typedef struct {
//     int total_messages;     // Número total de mensagens TXT
//     int message_number;     // Número desta mensagem
//     int severity;           // Severidade (0 = aviso, 1 = erro, etc.)
//     char text[64];          // Texto da mensagem
// } TXT;

// Função que verifica se o checksum é válido
bool checksum_is_valid(const char* nmea_sentence);
// Função para calcular o checksum
char calculate_checksum(const char *nmea_sentence);

bool gps_valid(const char *nmea_sentence);

int gps_parse_to_gga(const char *nmea_sentence, GGA *gga);

// GSV gps_parse_to_gsv(const char *nmea_sentence);
// RMC gps_parse_to_rmc(const char *nmea_sentence);
// GSA gps_parse_to_gsa(const char *nmea_sentence);
// GLL gps_parse_to_gll(const char *nmea_sentence);
// VTG gps_parse_to_vtg(const char *nmea_sentence);
// TXT gps_parse_to_txt(const char *nmea_sentence);
#endif //GPS_DRIVER_H