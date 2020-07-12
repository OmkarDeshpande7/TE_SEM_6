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

library(reshape2)      #load library reshape2

#get working directory
getwd()

#set working directory
setwd("P:\\TE_SEM_6\\SL-VI-33213\\Assignment 5\\breastcancer")
getwd()

#import dataset without first line as header
df<-read.csv("BreastCancerWc.csv", header=FALSE)
#assign names to columns
names(df)<-c("CN", "CT", "CSiU", "CShU", "MA", "SECS", "BN", "BC", "NN", "Mitoses", "Class")


print(dim(df))     # print Dataframe dimensions
print(names(df))    #print column names

df$Class[df$Class==4] <- 1 # replace 4 with 1
df$Class[df$Class==2] <- 0 # replace 2 with 0

df$BN[df$BN=="?"]<-NA   #replacing ? by NA
head(table(df$BN))

df$BN[is.na(df$BN)]<-1  #replacing NA with 1
head(table(df$BN))

#converting string to numeric
df$BN <- as.numeric(df$BN)
head(df)



# Subset of Dataframe
subset <- df[c("CN", "CT", "CSiU","Mitoses", "Class")]
head(subset)

# Conditional Subset of Dataframe
subset1<-df[c("CN", "CT", "CSiU", "SECS", "BN","Mitoses", "Class")]
subset2<-subset(subset1,subset1$CT>=7 ,select=c("CN","CT", "Mitoses", "CSiU", "SECS", "Class")) 
head(subset2)

# Merging Dataframe
merged1<-merge(subset1,subset2,by="CN")
head(merged1)
dim(subset1)
dim(subset2)
dim(merged1)
merged2<-merge(subset1,subset2,by="CT")
head(merged2)
dim(subset1)
dim(subset2)
dim(merged2)

sortdf<-df[order(df$CT, df$Mitoses),]       # Sorting Dataframe
head(sortdf)

transposedf = t(df)        #transpose
head(transposedf)

Data1<-melt(data=df,id=c("CN", "Class"))     # Melting
View(Data1)

Data2<-melt(data=df,id=c("CN", "Class"),measure=c("Mitoses"))
View(Data2)

Data<-dcast(data=Data1,CN+Class~variable,mean)     # Casting
View(Data)
