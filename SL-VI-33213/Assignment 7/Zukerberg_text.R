##Install Packages
#install.packages("tm")  # for text mining
#install.packages("SnowballC") # for text stemming
#install.packages("wordcloud") # word-cloud generator 
#install.packages("RColorBrewer") # color palettes
##Load Require Library
library(tm)
library(SnowballC)
library(RColorBrewer)
library(wordcloud)

##Read the Data
mark_txt<-readLines("P:\\TE_SEM_6\\SL-VI-33213\\Assignment 7\\MarkZukerberg.txt")

mark_data<-Corpus(VectorSource(mark_txt)) #getting corpus
mark_data<-tm_map(mark_data,tolower)  #make lower case
mark_data<-tm_map(mark_data,removeNumbers)  #removing the numbers
mark_data<-tm_map(mark_data,removeWords,stopwords("english"))   #removing stopwords
mark_data<-tm_map(mark_data,removePunctuation)    #remove punctuation marks
mark_data<-tm_map(mark_data,stripWhitespace)      #strip white spaces
mark_data<-tm_map(mark_data,stemDocument)         #stem document
                     
wordcloud(mark_data,max.words = 200,min.freq = 0,random.color = TRUE,random.order=TRUE)  #plotting wordcloud

