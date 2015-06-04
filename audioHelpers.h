
typedef enum { false, true } bool;
double sine = 0.0;
double cosine = 1.0;
const double B = 4/(float)M_PI;
const double C = -4/((float)M_PI*(float)M_PI);
const double P = 0.225;
const double D = 5.0*(float)M_PI*(float)M_PI;

int getStepLength (int sampleRate, int stepSize, int bitLength, int numberOfChannels) {
 int kbps = getBps (sampleRate,bitLength,numberOfChannels); 
 int stepSizeinS = stepSizetoSec(stepSize); 
 return kbps/stepSizeinS;
  }
int getFileSizePerSecond (int sampleRate, int bitLength, int numberOfChannels) { return sampleRate*(bitLength/8)*numberOfChannels; }
int getBps (int sampleRate, int bitLength, int numberOfChannels) { return sampleRate*bitLength*numberOfChannels; }
int stepSizetoSec (int stepSize) { return 1000/stepSize; }
int sigTodB (int sig) { return 20*log10(sig); }
int dBtoSig () { return 0; } // TODO
int getRMS (int *sampleBuffer,int bufferLen,int numberOfChannels) {
	int kout=0; 
	for (int i=0;i<bufferLen/numberOfChannels;i++)
		{
			kout += sampleBuffer[i] * sampleBuffer[i];
		}
		kout /=  bufferLen / numberOfChannels;  
        kout = sqrt((float)kout);
        return kout;  
          }
double calcSine (double f) { sine += f * cosine; cosine -= f*sine; return sine; }
double sineCoefficient (int frequency, int sampleRate) { return 2.0 * M_PI * frequency / sampleRate; }
double getSine (int frequency,int sampleRate) { double coef=sineCoefficient(frequency,sampleRate); return calcSine(coef); }     
double parabolicSine (double x, bool bHighPrecision) { double y=B*x+C*x*fabs(x);if (bHighPrecision) { y=P*(y*fabs(y)-y)+y; } return y; }
double BhaskaraISine (double x) { double d = fabs(x); double sgn = d == 0 ? 1.0 : x/fabs(x); return 16.0*x*(M_PI-sgn*x)/(D-sgn*4.0*x*(M_PI-sgn*x)); }

