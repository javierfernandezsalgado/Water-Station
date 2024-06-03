#include "lora.h"


// Definición de pines
#define RFM95_CS 5
#define RFM95_RST 14
#define RFM95_DIO0 26

// Configuración del módulo LoRa
SX1278 lora = new Module(RFM95_CS, RFM95_DIO0, RFM95_RST, -1);


extern int8_t init_communication()
{
 // Inicialización de la comunicación LoRa
    int8_t result=0;
    int8_t state = lora.begin();


    return state;
}
extern int8_t send_value(const uint8_t parameter,const void value,const size_t lenght)
{
    

}
extern int8_t receive_value(const int8_t timeout,uint8_t * parameter, void * value, size_t * lenght)
{


}