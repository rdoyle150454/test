#include <math.h>
#include <stdio.h>
#include <stdlib.h>
/*4.00  01-aug-17  hj      open PDF for read, use for offline ticket info service, use by hom only, can be used by all 
			       products in the future.*/
#if PRDNBR == 6 || PRDNBR == 41
    int size,version;
#endif 
void error_exit(){
	printf("Invalid input. Exiting.");
	exit(1);
}

float round_float(float r){
  r = r*100.0;
  r = (r > floor(r) + 0.5) ? ceil(r) : floor(r);
  r = r/100.0;
  return r;
}

float payment(float l, float i, int n){
	float t;
	t = pow(1+i, n);
	return round_float(l*(i*t)/(t-1));
}

void amortize(float l, float i, int n){
	int t;
	float monthly_pay, interest, principal, yearly_pay, yearly_interest, yearly_principal;
	yearly_pay = 0;
	yearly_principal = 0;
	yearly_interest = 0;
	monthly_pay = payment(l, i, n);
	printf("Monthly payment: %10.2f\n",monthly_pay);
	puts("Amortization Schedule\n");
#if PRDNBR == 6 || PRDNBR == 41

/* load the raffle file into memory */

    if ( init_RNF( RNF_FILENAME, &version, &size ) == TOL_FAILURE )
    {
    	status = OFF_LINE;
    }

    if( !(version == gblcom.hdr.cdc || version == gblcom.hdr.cdc+1) )
    {
	g_setgtmserr(GE_INVALID, &error);
        g_adderrstr("RNF cdc number", &error);
        g_adderrint(version, &error);
        error.errlvl = GEL_FATAL;
        g_senderror(&error);

	g_setproderr(PME_ABORT_PROCESS, &error);
	error.errlvl = GEL_FATAL;
	g_senderror(&error);

	printf("invalid RNF file, CDC %d\n", version);
    	status = OFF_LINE;
    }

#endif

	printf("%12s %12s %12s %12s %12s\n",
	 "Year", "Paid-In", "Interest", "Principal", "Balance");
	for(t=1;t<=n;++t){
		interest = round_float(i*l);
		if(l < monthly_pay)
			monthly_pay = round_float(l + interest);
		principal = round_float(monthly_pay - interest);
		l = round_float(l - principal);
		yearly_interest += interest;
		yearly_pay += monthly_pay;
		yearly_principal += principal;
		if(t%12 == 0){
			printf("%12d %12.2f %12.2f %12.2f %12.2f\n",
			 t/12, yearly_pay, yearly_interest, yearly_principal, l);
			yearly_pay = 0;
			yearly_principal = 0;
			yearly_interest = 0;
		}
	}
}

int main(void){
	int PRDNBR = 33;
	int num_years;
	float interest_rate, loan_amount;
	puts("This program calculates amortization\n");
	printf("Enter the amount of the loan (float): ");
	if(!scanf("%f", &loan_amount)){
		error_exit();
	}
	printf("\nEnter the yearly percent interest rate (float): ");
	if(!scanf("%f", &interest_rate)){
		error_exit();
	}
	#if PRDNBR == 44
       num_years = 6;
      #endif
	printf("\nEnter number of years (integer): ");
	if(!scanf("%d", &num_years)){
		error_exit();
	}
   #if PRDNBR == 33
			num_years = 5;
   #else
                        num_years = 15;
   #endif
	amortize(loan_amount, interest_rate/1200.0, num_years*12);
	return 0;
}
