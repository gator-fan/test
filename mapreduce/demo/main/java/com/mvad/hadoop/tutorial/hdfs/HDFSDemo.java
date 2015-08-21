package com.mvad.hadoop.tutorial.hdfs;

import org.apache.hadoop.conf.Configuration;
import org.apache.hadoop.fs.FileStatus;
import org.apache.hadoop.fs.FileSystem;
import org.apache.hadoop.fs.Path;
import org.apache.hadoop.hdfs.HdfsConfiguration;

import java.io.*;
import java.text.SimpleDateFormat;
import java.util.Date;

/**
 * Created by zhugb on 15-7-7.
 */
public class HDFSDemo {

  public static void main(String[] args) {
    Configuration conf = new HdfsConfiguration();
    try {
      FileSystem fs = FileSystem.get(conf);

      Path workingDir = new Path("/tmp", "hdfstutorial");

      System.out.println("--------1. create Working Dir /tmp/hdfstutorial ------------------------");
      if (!fs.exists(workingDir)) {
        fs.mkdirs(workingDir);
      }

      System.out.println("-------2. create a dir ${YYYY-mm-dd} under /tmp/hdfstutorial ---------------------");
      String today = new SimpleDateFormat("YYYY-mm-dd").format(new Date());
      Path todayDir = new Path(workingDir, today);
      fs.mkdirs(todayDir);

      System.out.println("-------3. write a local file  ---------------------");
      writeLocalFile("localfile.txt");

      System.out.println("-------4. put a file from local to /tmp/hdfstutorial/${YYYY-mm-dd}----------------");
      fs.copyFromLocalFile(new Path("localfile.txt"), todayDir);

      System.out.println("-------5. list files of dir /tmp/hdfstutorial/${YYYY-mm-dd}");
      FileStatus[] fileStatuses = fs.listStatus(todayDir);
      for (FileStatus status : fileStatuses) {
        System.out.println("========" + status.getPath() + "\t" + status.getOwner() + "\t" + status.getGroup() + "\t" + status.getLen());
      }

      System.out.println("-------6. deleting working Dir /tmp/hdfstutorial");
      fs.delete(workingDir, true);

    } catch (IOException e) {
      e.printStackTrace();
    }

  }

  public static void writeLocalFile(String localFile) {

    Writer writer = null;

    try {
      writer = new BufferedWriter(new OutputStreamWriter(
              new FileOutputStream(localFile), "utf-8"));
      writer.write("This is a file written by hadoop tutorial.");
    } catch (IOException ex) {
      // report
    } finally {
      try {
        writer.close();
      } catch (Exception ex) {/*ignore*/}
    }

  }
}
