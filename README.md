# gene-transfer-model
Quick simulation demonstration of nuclear transfer stabilised by mutational robustness

`gene-transfer.c` simulates a population of N organisms evolving through non-overlapping, asexual generations. A single gene determines fitness. It can be encoded in the mitochondrion or in the nucleus. If in the mitochondrion, it experiences a loss of function mutation with probability μ per genome per generation, which leads to a reduction in fitness. If in the nucleus, it never mutates. The simulation begins with a single individual with nuclear encoding and N-1 with organelle encoding. As μ increases, the proportion of simulations that retain nuclear-encoding individuals increases above the neutral case towards unity. There is no contribution of mutation rate to the fitness function: it suffices that a lineage prone to mutation is more likely to die out.

`plot-sim.R` plots the results:
![image](https://github.com/StochasticBiology/gene-transfer-model/assets/50171196/bec1d410-3b8b-4d46-9e6f-b6f5efea0ce0)
