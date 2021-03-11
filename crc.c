#include<stdio.h>
#include<string.h>
#include<stdint.h>
#include<stdint.h>
FILE * pIn;
FILE * pOut;
uint64_t fSize;
uint8_t out[100];
uint32_t cal_crc()
{

    uint8_t buffer[2];
    size_t result;

    int32_t i, j;
    uint32_t byte, crc, mask;

    crc = 0xFFFFFFFF;

    fseek (pIn , 0 , SEEK_END);
    fSize = ftell (pIn);
    rewind (pIn);
    printf("size = %d\n", fSize);

    for(int i = 0; i < fSize; i++){
        
        result = fread (buffer,1, 1,pIn);
        
         byte = buffer[0];//get next byte.
         crc = crc ^ byte;

         for (j = 7; j >= 0; j--) {
             mask = -(crc & 1);
             crc = (crc >> 1) ^ (0xEDB88320 & mask);
         }
    }
    printf("crc = 0x%x\n", ~crc);
    return ~crc;

}

void open_outfile(char *name)
{
    char tmp[100] = {0};
    char *dot;
    int len = 0;
    dot = strstr(name, ".");
    len = (int)(dot - name);
    
    if(len){
        strncpy(tmp, name, len);
        tmp[len] = '\0';
        strcat(tmp, "_header.hex");
        pOut = fopen ( tmp , "wb" );
    }


}

int main (int argc, char *argv[]) {

    uint32_t crc = 0;
    char *str = "OTASTART";
    uint8_t buffer[2];
    
    if(argc > 1){
        pIn = fopen ( argv[1] , "rb" );
        if (pIn == NULL) {fputs ("File error",stderr); exit (1);}
    }
    else{
        
        fputs ("Missing filename\n",stderr); exit (1);
    }

    open_outfile(argv[1]);
    crc = cal_crc();

    memcpy(out, str, strlen(str));
    memcpy(out + 8, &fSize, sizeof(fSize));
    memcpy(out + 16, &crc, sizeof(crc));
    fwrite (out,1, 24 * sizeof(uint8_t), pOut);

    rewind (pIn);
    for(int i = 0; i < fSize; i++){
        
        fread (buffer,1, 1,pIn);
        fwrite (buffer,1, 1,pOut);
    }

    fclose (pIn);
    fclose (pOut);
    return 0;
}