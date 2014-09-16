/*Practical Neural Network Recipes in C++
 * Chap4 Time-Series Prediction
 * detrend : raw data sequence - linear reggression line
 * Timothy Masters
 * Thomas Tsai , thomas@biotrump.com
 */

//sum of the least square error to calculate linear reggression Y = intercept + slope * X
static void detrend_lsq(
	double *source,		//input signal for detrending
	int n,				//its length
	double *dest,		//Detrended output, may replace input
	double *slope,		//output of slope per pt
	double *intercept	//input of the intercept at the first point
)
{
	int i;
	double x=0.0,y=0.0,xmean=0.0,ymean=0.0,xvar=0.0,xy=0.0;

	xmean = (double) (n -1) / 2.0;
	
	for(i=0;i<n;i++) ymean += source[i];
	ymean /= (double)n;

	for(i = 0; i < n ; i ++){
		x = (double) i - xmean;
		y = source[i] - ymean;
		xvar += x * x;
		xy += x * y;
	}
	*slope = xy / xvar;
	*intercept = ymean - *slope * xmean;

	//Do the detrending here
	for(i=0;i<n;i++){
		y = *slope *(double)i + *intercept;
		dest[i]=source[i] - y;
	}
}

static void detrend_endpt(
	double *source,		//input signal for detrending
	int n,				//its length
	double *dest,		//Detrended output, may replace input
	double *slope,		//output of slope per pt
	double *intercept	//input of the intercept at the first point
)
{
	int i;
	double y;
	*slope = (source[n-1]-source[0])/(double)(n-1);
	*intercept = source[0];

	//Do the detrending here
	for(i=0;i<n;i++){
		y = *slope *(double)i + *intercept;
		dest[i]=source[i] - y;
	}
}

//Main detrending routine
void detrend(
	double *source,		//input signal for detrending
	int n,				//its length
	double *dest,		//Detrended output, may replace input
	int type,			//1=lsq, 2=endpt
	double *slope,		//output of slope per pt
	double *intercept	//input of the intercept at the first point
)
{
	if(n < 2) {		//degenerate case
		*slope = 0.0f;
		*intercept = source[0];
		return;
	}
	switch(type){
		case 2: detrend_endpt(source, n, dest,slope, intercept);break;
		case 1: detrend_lsq(source, n, dest,slope, intercept);
		default:
			break;
	}
}

//Retrend routine
void retrend(
	double *source,		//input signal for detrending
	int n,				//its length
	double *dest,		//Detrended output, may replace input
	double *slope,		//output of slope per pt
	double *intercept	//input of the intercept at the first point
)
{
	int i;
	double y;
	for(i=0;i<n;i++){
		y=*slope *(double) i + *intercept;
		dest[i] = source[i] + y;
	}
}

