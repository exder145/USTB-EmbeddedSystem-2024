

int main (void) {
	
	int a,a1;
	unsigned char b,b1;
	long c,c1;
	long d,d1;
	int i;
	
	a=20;	
	b=1;
	
	a1=sizeof(int);
  b1=sizeof(long);
  c1=sizeof(float);
	d1=sizeof(double);
  
	d=a1+b1+c1+d1;

	while(1){
		
		c=a*b;
		b=b+d;
    a=c;		
		for(i=0;i<=10000;i++){};
	}
	
}


// 72M，HSI = 8M；
void SystemInit(void)
{
	// 函数体为空，目的是为了骗过编译器不报错
}

