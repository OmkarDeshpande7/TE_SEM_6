library(readxl)     #load library readxl

#importing preprocessed dataset
dataset <- read.csv("P:\\TE_SEM_6\\SL-VI-33213\\Assignment 8\\new_air_1.csv")
View(dataset) 

#stripchart for CO.GT. values
stripchart(dataset$CO.GT.[1:100],xlab="value",ylab="CO.GT.")

#stripchart for NOx.GT. values
stripchart(dataset$NOx.GT.[1:100],xlab="value",ylab="NOx.GT.")

#plot temperature vs CO.GT.
plot(x = dataset$T[1:50],y= dataset$CO.GT.[1:50], col="blue",xlab = "temperature", ylab = "CO.GT.")
#give title to plot
title(main="Autos", font.main=4)

#barplot of first 100 records
barplot(dataset$CO.GT.[1:100],xlab = "TIME",ylab = "Value of CO.GT.")
hist(dataset$CO.GT.)     #Histogram


#division of records per temperature scale
pie(table(floor(dataset$T[1:50])),main = "No. of records per temp")

#dotchart
dotchart((dataset$CO.GT.[1:100]))   #Dotcharts

#boxplot of temperature range
boxplot(dataset$T[1:500]) #Boxplot

#plot CO.GT. vs C6H6.GT.
plot(dataset$CO.GT.[1:500],dataset$C6H6.GT.[1:500])

#plot CO.GT. vs C6H6.GT.
plot(dataset$CO.GT.[1:500],dataset$C6H6.GT.[1:500], main="CO vs C6H6", xlab="CO(GT)", ylab="C6H6(GT)")


