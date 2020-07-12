#######################################################

Author - Omkar Deshpande ( k10 - 33213 )

Problem Statement - Design and develop a distributed application to find the coolest/hottest year from the available weather data. Use weather data from the Internet and process it using MapReduce. 

Dataset Description - The data is stored using a line-oriented ASCII format, in which each line is a record.

0057
332130 	# USAF weather station identl?er
99999 	# weather station identifier
19500101	# observation date
0300 		# observation time
4
+51317 	# latitude (degrees x 1000)
+028783 	# longitude (degrees x 1000)
FM-12
+0171 	# elevation (meters)
99999
V020
320 		# wind direction (degrees)
1 		# quality code
N 
0072
1
00450 	# sky ceiling height (meters)
1 		# quality code
C
N
010000 	# visibility distance (meters)
1 		# quality code
N
9
—0128 	# air temperature (degrees Celsius x 10)
1 		# quality code
-o139 	# dew point temperature (degrees Celsius x 10)
1 		# quality code
10268 	# atmospheric pressure (hectopascals x 10)
1 		# quality code


#######################################################
package weatherData;



import java.io.IOException;
//import java.util.StringTokenizer;

import org.apache.hadoop.conf.Configuration;
import org.apache.hadoop.fs.Path;
import org.apache.hadoop.io.IntWritable;
import org.apache.hadoop.io.Text;
import org.apache.hadoop.mapreduce.Job;
import org.apache.hadoop.mapreduce.Mapper;
import org.apache.hadoop.mapreduce.Reducer;
import org.apache.hadoop.mapreduce.lib.input.FileInputFormat;
import org.apache.hadoop.mapreduce.lib.output.FileOutputFormat;

public class weatherData {

  public static class TokenizerMapper
       extends Mapper<Object, Text, Text, IntWritable>{

	   private static final int MISSING = 9999;
	    
	    public void map(Object key, Text value, Context context
	                    ) throws IOException, InterruptedException {

	    	String line = value.toString();
	    	String year = line.substring(15, 19);
	    	int airTemperature;
	    	if (line.charAt(87) == '+') { // parseInt doesn't like leading plus signs
	    		airTemperature = Integer.parseInt(line.substring(88, 92));
	    	} else {
	    		airTemperature = Integer.parseInt(line.substring(87, 92));
	    	}
	    	String quality = line.substring(92, 93);
	    	if (airTemperature != MISSING && quality.matches("[01459]")) {
	    		context.write(new Text(year), new IntWritable(airTemperature));
	    	}
    }
  }

  public static class IntSumReducer
       extends Reducer<Text,IntWritable,Text,IntWritable> {
    private IntWritable result = new IntWritable();
    public void reduce(Text key, Iterable<IntWritable> values,
            Context context
            ) throws IOException, InterruptedException {
int max = -9999;
int x;
for (IntWritable val : values) {
if(max<(x=val.get()))
	  max = x;
}
result.set(max);
context.write(key, result);
}
  }

  public static void main(String[] args) throws Exception {
    Configuration conf = new Configuration();
    Job job = Job.getInstance(conf, "word count");
    job.setJarByClass(weatherData.class);
    job.setMapperClass(TokenizerMapper.class);
    job.setCombinerClass(IntSumReducer.class);
    job.setReducerClass(IntSumReducer.class);
    job.setOutputKeyClass(Text.class);
    job.setOutputValueClass(IntWritable.class);
    FileInputFormat.addInputPath(job, new Path(args[0]));
    FileOutputFormat.setOutputPath(job, new Path(args[1]));
    System.exit(job.waitForCompletion(true) ? 0 : 1);
  }
}