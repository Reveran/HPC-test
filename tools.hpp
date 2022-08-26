#include <sys/time.h>
const char usageString[344] = "Usage:\n%s <Size of Matrix> <Parallel Count> <Execution Mode>\n\n\tSize of Matrix:\t(Integer), dimmensions of the square matrix.\n\tParallel Count:\t(Integer), the workload will be splited equally into this anmount of parallels.\n\tExecution Mode: (--sequential, --threading, --process), Defines the mode of parallelism.\nExample:\n\t%s 480 4 --threading\n\n";
double calcTime(timeval start, timeval end)
{
    double time_taken;

    time_taken = (end.tv_sec - start.tv_sec) * 1e6;
    time_taken = (time_taken + (end.tv_usec -
                                start.tv_usec)) *
                 1e-6;
    return time_taken;
}