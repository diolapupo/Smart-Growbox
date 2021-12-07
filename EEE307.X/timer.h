int tmr_select(int tmr,int prescaler,int counter,int value){
    if(tmr==0){
        if(counter==0){
            OPTION_REGbits.T0CS=0;
            OPTION_REGbits.PSA=0;
            if(prescaler==2){OPTION_REGbits.PS2=0;OPTION_REGbits.PS1=0;OPTION_REGbits.PS0=0;}
            if(prescaler==4){OPTION_REGbits.PS2=0;OPTION_REGbits.PS1=0;OPTION_REGbits.PS0=1;}
            if(prescaler==8){OPTION_REGbits.PS2=0;OPTION_REGbits.PS1=1;OPTION_REGbits.PS0=0;}
            if(prescaler==16){OPTION_REGbits.PS2=0;OPTION_REGbits.PS1=1;OPTION_REGbits.PS0=1;}
            if(prescaler==32){OPTION_REGbits.PS2=1;OPTION_REGbits.PS1=0;OPTION_REGbits.PS0=0;}
            if(prescaler==64){OPTION_REGbits.PS2=1;OPTION_REGbits.PS1=0;OPTION_REGbits.PS0=1;}
            if(prescaler==128){OPTION_REGbits.PS2=1;OPTION_REGbits.PS1=1;OPTION_REGbits.PS0=0;}
            if(prescaler==256){OPTION_REGbits.PS2=1;OPTION_REGbits.PS1=1;OPTION_REGbits.PS0=1;}
        }else if(counter==1){
            OPTION_REGbits.T0CS=1;
            OPTION_REGbits.T0SE=0;
            OPTION_REGbits.PSA=1;
        }
        TMR0=value;
        return TMR0;
    }else if(tmr==1){
        T1CONbits.TMR1ON=0;
        T1CONbits.T1OSCEN=0;
        if(counter==0){
            T1CONbits.TMR1CS=0;
            if(prescaler==1){T1CONbits.T1CKPS1=0;T1CONbits.T1CKPS0=0;}
            if(prescaler==2){T1CONbits.T1CKPS1=0;T1CONbits.T1CKPS0=1;}
            if(prescaler==4){T1CONbits.T1CKPS1=1;T1CONbits.T1CKPS0=0;}
            if(prescaler==8){T1CONbits.T1CKPS1=1;T1CONbits.T1CKPS0=1;}
        }else if(counter==1){
            T1CONbits.TMR1CS=1;
            T1CONbits.T1SYNC=1;
        }
        TMR1=value;
        return TMR1;
    }else return 0;
}