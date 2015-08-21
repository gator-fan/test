package com.mvad.hadoop.tutorial.mr;

import com.mediav.data.log.CookieEvent;
import com.twitter.elephantbird.mapreduce.input.combine.DelegateCombineFileInputFormat;
import org.apache.hadoop.conf.Configuration;
import org.apache.hadoop.conf.Configured;
import org.apache.hadoop.fs.Path;
import org.apache.hadoop.io.IntWritable;
import org.apache.hadoop.io.Text;
import org.apache.hadoop.mapreduce.Job;
import org.apache.hadoop.mapreduce.Mapper;
import org.apache.hadoop.mapreduce.Reducer;
import org.apache.hadoop.mapreduce.lib.output.FileOutputFormat;
import org.apache.hadoop.util.GenericOptionsParser;
import org.apache.hadoop.util.Tool;
import org.apache.hadoop.util.ToolRunner;
import parquet.hadoop.thrift.ParquetThriftInputFormat;

import java.io.IOException;

/**
 * Created by guangbin on 15-07-07.
 * <p/>
 * This is an example of Using ParquetThriftInputFormat,
 * which explains reading CookieEvent Parquet File and count events number group by evenType ()
 */
public class CookieEventCountByEventType extends Configured implements Tool {


  public enum EVENTTYPE {
    S, C, T, V, OTHER
  }

  public static class CookieEventMapper extends Mapper<Object, CookieEvent, Text, IntWritable> {

    private final static IntWritable one = new IntWritable(1);
    private Text eventType = new Text();

    @Override
    protected void map(Object key, CookieEvent value, Context context) throws IOException, InterruptedException {

      // Fill in Your code here
    }
  }

  public static class IntSumReducer extends Reducer<IntWritable, IntWritable, IntWritable, IntWritable> {

    private IntWritable result = new IntWritable();

    @Override
    protected void reduce(IntWritable key, Iterable<IntWritable> values, Context context) throws IOException, InterruptedException {

      // Fill in Your code here
    }
  }


  public int run(String[] args) throws Exception {

    Configuration conf = new Configuration();
    String[] otherArgs = new GenericOptionsParser(conf, args).getRemainingArgs();
    if (otherArgs.length != 2) {
      System.err.println("Usage: CookieEventCountByEventType <in> <out>");
      System.exit(2);
    }
    Path in = new Path(otherArgs[0]);
    Path out = new Path(otherArgs[1]);

    // setup job
    Job job = Job.getInstance(conf);
    job.setJobName("CookieEventCountByEventType");
    job.setJarByClass(CookieEventCountByEventType.class);
    job.setMapperClass(CookieEventMapper.class);
    job.setCombinerClass(IntSumReducer.class);
    job.setReducerClass(IntSumReducer.class);
    job.setOutputKeyClass(Text.class);
    job.setOutputValueClass(IntWritable.class);

    // set InputFormatClass to be DelegateCombineFileInputFormat to Combine Small Splits
    job.setInputFormatClass(DelegateCombineFileInputFormat.class);
    DelegateCombineFileInputFormat.setCombinedInputFormatDelegate(job.getConfiguration(), ParquetThriftInputFormat.class);
    ParquetThriftInputFormat.addInputPath(job, in);

    // be sure to set ParquetThriftInputFormat ReadSupportClass and ThriftClass
    ParquetThriftInputFormat.setReadSupportClass(job, CookieEvent.class);
    ParquetThriftInputFormat.setThriftClass(job.getConfiguration(), CookieEvent.class);

    FileOutputFormat.setOutputPath(job, out);
    return job.waitForCompletion(true) ? 0 : 1;

  }

  public static void main(String[] args) throws Exception {
    ToolRunner.run(new Configuration(), new CookieEventCountByEventType(), args);
  }


}
