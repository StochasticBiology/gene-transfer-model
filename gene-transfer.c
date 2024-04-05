#include <stdio.h>
#include <stdlib.h>

#define RND drand48()

#define NPOP 100      // population size
#define NEXPT 10000   // number of samples
#define MAXT 100      // number of generations

int main(void)
{
  // labels denoting which compartment the gene is stored in (0 MT, 1 NU)
  int compartment[NPOP], new_compartment[NPOP];
  // fitness across population
  double fitness[NPOP], new_fitness[NPOP];
  double mean_compartment;
  FILE *fp;
  int expt, t;
  int i, r;
  double fitdiff;   // fitness cost for a mutation
  double MU;        // MT mutation rate
  double transfer;  // proportion of experiments maintaining >= 1 NU-encoded individual

  // initialise output file
  fp = fopen("output.csv", "w");
  fprintf(fp, "mu,fitdiff,transfer\n");

  // loop through mutation rates
  for(MU = 1e-3; MU <= 1; MU *= 2)
    {
      // loop over fitness loss for mutated gene
      for(fitdiff = 0; fitdiff <= 1; fitdiff+=0.5)
	{
	  // initialise counter for these parameters
	  transfer = 0;
	  // loop over samples
	  for(expt = 0; expt < NEXPT; expt++)
	    {
	      // initialise population with one NU-encoding individual
	      // all fitnesses are 1
	      for(i = 0; i < NPOP; i++)
		{
		  compartment[i] = (i==0);
		  fitness[i] = 1;
		}

	      // loop through generations
	      for(t = 0; t < MAXT; t++)
		{
		  mean_compartment = 0;
		  // apply random mutation (loss of fitness) to any MT-encoding individuals
		  for(i = 0; i < NPOP; i++)
		    {
		      if(compartment[i] == 0 && RND < MU)
			fitness[i] -= fitdiff;
		    }
		  // select individuals for next generation based on fitness
		  for(i = 0; i < NPOP; i++)
		    {
		      // choose an individual with nonzero fitness
		      do{
			r = RND*NPOP;
		      }while(fitness[r] == 0);
		      new_compartment[i] = compartment[r];
		      new_fitness[i] = fitness[r];
		    }
		  // update population and compartment statistic
		  for(i = 0; i < NPOP; i++)
		    {
		      compartment[i] = new_compartment[i];
		      fitness[i] = new_fitness[i];
		      mean_compartment += compartment[i];
		    }
		}
	      // if we have retained any NU encoding, record this
	      if(mean_compartment > 0)
		transfer++;
	    }
	  // output info
	  fprintf(fp, "%e,%e,%e\n", MU, fitdiff, transfer/NEXPT);
	  printf("%e,%e,%e\n", MU, fitdiff, transfer/NEXPT);
	}    
    }
  fclose(fp);

  return 0;
}
      
