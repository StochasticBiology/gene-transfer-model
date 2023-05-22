library(ggplot2)
df = read.csv("output.csv")
ggplot(df, aes(x=mu,y=transfer,color=factor(fitdiff))) + geom_line() + 
  theme(legend.position="none") + scale_x_continuous(trans="log10")

