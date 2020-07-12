####################################################################################
# Author - Omkar Deshpande (33213 - K10)
#
# Problem statement - Perform the following operations using R/Python on the Air quality and Heart Diseases data sets 
#               a. Data cleaning 
#               b. Data integration 
#               c. Data transformation 
#               d. Error correcting 
#               e. Data model building  
#####################################################################################

#load library reshape2
library(reshape2)

#get working directory
getwd()

#set working directory
setwd("P:\\TE_SEM_6\\SL-VI-33213\\Assignment 5\\Facebook")
getwd()

#mport dataset
df<-read.csv("dataset_Facebook.csv",sep = ';')#import csv file


dim(df)         # View Dataframe dimensions
print(names(df))
head(df)

#create subset
subset<-df[c("Page.total.likes","Type","Category","comment","like","share")]      
head(subset)

#create subset
subset1<-df[c("Page.total.likes","Type","Post.Month","Post.Weekday","Post.Hour","like","comment","share")]
head(subset1)

#create subset
subset2<-subset(subset1,subset1$Type=="Photo" ,select=c(Page.total.likes,Post.Weekday,like,comment,share)) 
head(subset2)

#merging of subsets
merged<-merge(subset,subset2,by="Page.total.likes")      
head(head(merged))

#sorting of data
sortdf<-df[order(df$Page.total.likes),]        
head(sortdf)

#transpose
transposedf = t(df)       
View(transposedf)

#Melt
meltData<-melt(data=df,id.vars="Lifetime.Engaged.Users",measure.vars=c("Total.Interactions"))
head(meltData)

#cast
castData<-acast(data=meltData,Lifetime.Engaged.Users~variable,mean) 
head(castData)

