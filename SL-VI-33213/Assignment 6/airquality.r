# Load Libraries
library("ggplot2")
library("dplyr")
library("Metrics")
library("caret")
library("randomForest")
library("e1071")
library("caTools")
set.seed(1)

getwd()
setwd("P:\\TE_SEM_6\\SL-VI-33213\\Assignment 6")
getwd()
df <- read.csv("AirQualityUCI.csv", header=TRUE, sep=",")


# Removing -200 

for(i in names(df)[c(3:15)]){
  df[i][df[i]==-200] <- NA
}
print(summary(df))

# Filling NA with Mean
for(i in names(df)[c(3:15)]){
  df[i][is.na(df[i])] = mean(df[[i]], na.rm=TRUE)
}
print(summary(df))

# Filling NA with Median


# Box Plots to Check for Outliers
for(i in names(df)[c(3:15)]){
  boxplot(x=df[i], main=i, col="red")
}

# Finding Correlations
cat("Correlations on df filled with Mean: ")
print(cor(df[names(df)[c(3:15)]], use="complete.obs", method="kendall"))

# C6H6.GT. and PT08.S2.NHMC. have a high correlation of ~ 1 and also have almost similar correlations with the target variables and hence PT08.S2.NHMC. can be dropped
df$PT08.S2.NMHC. <- NULL

# 1. Taking Temperature as Variable to be predicted

# Normalizing Data
df[names(df)[c(3:11,13,14)]]<-scale(df[names(df)[c(3:11,13,14)]])

# Train Test Split
sample = sample.split(df$T, SplitRatio = .80)
train = subset(df, sample == TRUE)
test  = subset(df, sample == FALSE)
cat("Train Dimensions: ", dim(train), "\n")
cat("Test Dimensions: ", dim(test), "\n")

# Multiple Linear Regression
T_linearRegressor <- lm(T ~ CO.GT.+PT08.S1.CO.+NMHC.GT.+C6H6.GT.+NOx.GT.+PT08.S3.NOx.+NO2.GT.+PT08.S4.NO2.+PT08.S5.O3.+RH+AH, data=train)
# show results
print(summary(T_linearRegressor))

# Test Prediction and Accuracy
pred <- predict(T_linearRegressor, test)
cat("\nTest Dataset Scores - \n")
print(data.frame(R2 = R2(pred, test$T),RMSE = RMSE(pred, test$T),MAE = MAE(pred, test$T),MSE = mse(pred, test$T)))

# Train Prediction and Accuracy
pred <- predict(T_linearRegressor, train)
cat("\nTrain Dataset Scores - \n")
print(data.frame(R2 = R2(pred, train$T),RMSE = RMSE(pred, train$T),MAE = MAE(pred, train$T),MSE = mse(pred, train$T)))

plot(T_linearRegressor)
#
#
#
# Random Forest Regression
cat("Random Forest Regressor - \n")
T_RFregressor <- randomForest(T ~ CO.GT.+PT08.S1.CO.+NMHC.GT.+C6H6.GT.+NOx.GT.+PT08.S3.NOx.+NO2.GT.+PT08.S4.NO2.+PT08.S5.O3.+RH+AH, data=train, ntree = 100)
print(T_RFregressor) # show results
plot(T_RFregressor)

# Test Prediction and Accuracy
pred <- predict(T_RFregressor, test)
cat("\nTest Dataset Scores - \n")
print(data.frame(R2 = R2(pred, test$T),RMSE = RMSE(pred, test$T),MAE = MAE(pred, test$T),MSE = mse(pred, test$T)))

# Train Prediction and Accuracy
pred <- predict(T_RFregressor, train)
cat("\nTrain Dataset Scores - \n")
print(data.frame(R2 = R2(pred, train$T),RMSE = RMSE(pred, train$T),MAE = MAE(pred, train$T),MSE = mse(pred, train$T)))