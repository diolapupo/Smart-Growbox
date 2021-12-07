#define dhtpindir TRISBbits.TRISB4
#define dhtpin PORTBbits.RB4
unsigned char dht_init();
unsigned char dht_check();
unsigned char dht_read();
unsigned short data,t1,t2,r1,r2,chk;
int RH,temp;

unsigned char dht_init(){
    data=0;
    dhtpindir=0;
    dhtpin=0;
    __delay_ms(18);
    dhtpin=1;
    dhtpindir=1;
    while(dhtpin==1);
    return 1;
}

unsigned char dht_check(){
   while(dhtpin==0);
    if(TMR0>80)return 0;
    else{
        tmr_select(0,4,0,0);
        while(dhtpin==1);
        if(TMR0>80)return 0;
        else{
            tmr_select(0,4,0,0);
            return 1;
        }
    }
}

unsigned char dht_read(){
    data=0;
    for(int i=0;i<8;i++){
        while(dhtpin==0);
        __delay_us(40);
        
        if(dhtpin==1)data=(data<<1)|1;
        else data=data<<1;
        while(dhtpin==1);
    }
    return data;
}

unsigned char dht_run(){
    __delay_ms(500);
    if(dht_init()){
            tmr_select(0,4,0,0);
            if(dht_check()){
               r1=dht_read();
                r2=dht_read();
                t1=dht_read();
                t2=dht_read();
                chk=dht_read();
                RH=(r1<<8)|r2;
                temp=(t1<<8)|t2;
            }
        }
}
