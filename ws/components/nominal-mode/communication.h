




extern int8_t init_communication();
extern int8_t send_value(const uint8_t parameter,const void value,const size_t lenght);
extern int8_t receive_value(const int8_t timeout,uint8_t * parameter, void * value, size_t * lenght);