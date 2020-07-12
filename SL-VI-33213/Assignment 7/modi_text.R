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
modi_txt<-readLines("C:\\Users\\omkar\\Downloads\\NarendraModi.txt")

modi<-Corpus(VectorSource(modi_txt)) #getting corpus
modi_data<-tm_map(modi_data,tolower)  #make lower case
modi_data<-tm_map(modi_data,removeNumbers)  #removing the numbers
modi_data<-tm_map(modi_data,removeWords,stopwords("english"))   #removing stopwords
modi_data
modi_data<-tm_map(modi_data,removePunctuation)    #remove punctuation marks
modi_data<-tm_map(modi_data,stripWhitespace)      #strip white spaces
modi_data<-tm_map(modi_data,stemDocument)         #stem document
                     
wordcloud(modi_data,max.words = 200,min.freq = 1,random.color = TRUE,random.order=FALSE)  #plotting wordcloud

