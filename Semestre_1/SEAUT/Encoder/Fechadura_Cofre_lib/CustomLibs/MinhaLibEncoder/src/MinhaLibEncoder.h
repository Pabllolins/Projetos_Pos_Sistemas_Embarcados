#ifndef __MINHALIBENCODER_H__
#define __MINHALIBENCODER_H__

#ifdef __cplusplus
    extern "C" {
#endif


#define depuracao


// class MeuEncoder
// {
//     public:
//         U_Init(void);
//         void U_Transmit(unsigned char data);
//         unsigned char U_Receive( void );
//         void U_StrTx(const char*);
//         void U_rxIE(void);        
//     private:

// };

void v_IniciaEncoder(int PinClk, int PinData, int PinSw);
void LeEncoder(int PinClk, int PinData, int *VarParaA, int *UltimoValorA);

#ifdef __cplusplus
    }
#endif

#endif //__MINHALIBENCODER_H__